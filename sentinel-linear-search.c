#include <stdio.h>

#define LEN 20

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
	int array[LEN] = {3, 1, 4, 7, 10,
			  20, 17, 19, 15, 16,
			  18, 2, 5, 6, 8,
			  9, 11, 13, 12, 14};

	printf("Index: %d\n", sentinel_linear_search(array, LEN, 14));

	return 0;
}
