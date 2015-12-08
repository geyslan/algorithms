#include <stdio.h>

int sentinel_linear_search(int *arr, int n, int key)
{
	--n; /* considering that n is the real size of elements */

	if (n < 1)
		return -1;

	int last_member = arr[n];

	/* set array last member as the key */
	arr[n] = key;

	int i = 0;
	while (arr[i] != key) {
		++i;
	}

	/* recover the real array last member */
	arr[n] = last_member;

	if ((i < n) ||
	    (i == n && last_member == key)) /* worst case */
		return i;

	return -1;
}


int main(void)
{
	int tab[100];

	for (int i = 0; i < 100; ++i) {
		tab[i] = i;
	}

	printf("Index: %d\n", sentinel_linear_search(tab, 100, 97));

	return 0;
}
