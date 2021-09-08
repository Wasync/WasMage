#include <stdio.h>
#include <stdbool.h>

void reverseWord(char *string, int size){
    char reversed[size];

    for (int i = 2 ; i <= size; i++){
        reversed[i] = string[size - i];
    }
	reversed[size] = '\0';
    printf("\n");
    printf("rev %s", reversed);
}

int main(){

	bool rt;
	char c;

	printf("Registered? (Y/N)\n");
	printf("Getchar got %c \n ", getchar());
	scanf("%c", &c);

	printf("scanf got %c \n ", c);
	while(c != 'n' && c != 'N' && c != 'y' && c != 'Y')
	{
		printf("Error! Try again! char is %c \n", c);
		getchar();
		scanf("%c", &c);
	}
	if(c == 'y' || c == 'Y'){
		rt = true;
	}
	else{
		rt = false;
	}
    return 0;
}

