int solution1(int a[], int n, int num) {

	int flag = 0;/*the flag is used to determine if find the two number*/
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			if (a[i] + a[j] == num) { flag = 1/*change the value of flag to show that find the two number*/; break; }
		}
		if (flag)break/*break the loop*/;
	}/*double for loop*/
	if (flag)printf("%d %d\n", a[i], a[j]);
	else printf("not found");/*give the answer*/

	return 0;
}