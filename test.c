#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
	void *ptr;
	u_int8_t *p;

	ptr = malloc(12 *sizeof(void));
	p = ptr + 3;

	printf("float %p fouble %p \n",ptr, p);
}
