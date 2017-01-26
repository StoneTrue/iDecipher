#include <stdio.h>

int main()

{
	int Option = 0;

	printf("Welcome to iDecipher!\n");
	printf("Choose an option: \n");
	printf("1 - Enter a cipher text\n");
	printf("2 - Read a cipher text from a file\n");
	printf("3 - Analyze an entered cipher text\n");
	printf("4 - Enter a key manually\n");
	printf("5 - Caeser shift!\n");
	printf("6 - Show plaintext\n");
	printf("7 - Help\n");
	printf("8 - Exit\n");
	printf("Enter option:  ");
	scanf("%d", &Option);
	printf("You chose \%d \n",Option);
	return 0;

}
