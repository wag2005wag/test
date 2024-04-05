#include <stdio.h>
#include "tree.h"

#define ll long long
void build(Node *p){// adjust the real sides of sons
	if(!p) return;
	if(p->lc && p->lc->val >= p->val){// the left son should be on the right
		Node *tmp = p->lc;// swap left son pointer with right
		p->lc = p->rc;
		p->rc = tmp;
	}
	else if(p->rc && p->val > p->rc->val){// the right son should be on the left
		Node *tmp = p->lc;// swap left son pointer with right 
		p->lc = p->rc;
		p->rc = tmp;
	}
	build(p->lc);// build subtrees
	build(p->rc);
}
int CheckTree(Node *p, ll lv, ll rv){// to check if p is a BST
	if(!p)return 0;
	if(p->val < lv || p-> val > rv) return 1;// this node's value is out of bounds
	if(p->lc && p->lc->val >= p->val)// left son's value bigger
		return 1;
	else if(p->rc && p->rc->val < p->val)// right son's value smaller
		return 1;
	else
		return CheckTree(p->lc, lv, p->val - 1) | CheckTree(p->rc, p->val, rv);// check subtrees
}
Node* Findprev(Node *p){// find the node with maximum value in those smaller than value of p
	if(p->lc){// choose the rightmost descendant of left son
		Node *tmp = p->lc;
		while(tmp->rc) tmp = tmp->rc;
		return tmp;
	}
	else{// choose the first ancestor with value smaller than p
		Node *tmp = p;
		while(tmp->fa && tmp->fa->lc == tmp)// ignore those with value bigger than p
			tmp = tmp->fa;
		if(tmp->fa)
			return tmp->fa;
		else
			return 0;
	}
}
Node* Findnext(Node *p){// find the node with minimum value in those bigger than value of p
	if(p->rc){// choose the leftmost descendant of right son
		Node *tmp = p->rc;
		while(tmp->lc) tmp = tmp->lc;
		return tmp;
	}
	else{// choose the first ancestor with value bigger than p
		Node *tmp = p;
		while(tmp->fa && tmp->fa->rc == tmp)// ignore those with value smaller than p
			tmp = tmp->fa;
		if(tmp->fa)
			return tmp->fa;
		else
			return 0;
	}
}
void FindComb(Node *p1, Node *p2, ll sum, void (*record)(ll, ll)){
	while(p1->lc) p1 = p1->lc;// find the minimum of T1
	while(p2->rc) p2 = p2->rc;// find the maximum of T2
	while(p1){
		while(p2 && p1->val + p2->val > sum)
			p2 = Findprev(p2);
			// for those p2' > p2 and p1' > p1, (p1, p2) is never a valid combination
			// so we should choose smaller p2
		if(!p2)break;
		if(p1->val + p2->val == sum)// valid combinations found
			record(p1->val, p2->val);
		ll v = p1->val;
		while(p1 && p1->val == v)// skip nodes with same value of p1
			p1 = Findnext(p1);
	}
}
void Preorder(Node *p){// preorder traverse
	if(!p) return;
	printf("%lld ", p->val);
	Preorder(p->lc);
	Preorder(p->rc);
}
void Inorder(Node *p){// inorder traverse
	if(!p) return;
	Inorder(p->lc);
	printf("%lld ", p->val);
	Inorder(p->rc);
}
void Postorder(Node *p){// postorder traverse
	if(!p) return;
	Postorder(p->lc);
	Postorder(p->rc);
	printf("%lld ", p->val);
}
#undef ll