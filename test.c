#include <stdio.h>

int recurse(int prev, int n)
{
	if (n == -1)
		return prev;
	prev = recurse(prev, n - 1);
	return prev * 2 - n;
}

int main()
{
	int *str;

	printf("Char %lu, sizeof *str %lu", sizeof(int), sizeof(*str));
	return 0;
}
