//  Main menu
// 1 - enter a cipher text from std in (e.g. user types ANDJDBFKSJVN)
// 2 - read a cipher text from a .txt or other file
// 3 - analyze a cipher text
// 4 - help
// 5 - exit
//
//  Homophonic test case:
//  Polyphonic test case:
//  Ceaser shift test case:
//  user chooses option - only can choose 1 - 5, anything else
//  results in being asked to enter 1 - 5
//  1 - enter cipher from stdin & save as user defined file
//  2 - read cioher text from user defined file ans save as user
//  defined file
//  3 - analyze file chosen; default is most recent
//  analysis options are:
//  3.1 - develop key from user defined features, eg number of
//  characters per key element and perform frequency analysis
//  3.3 -  enter a plain key manually
//  3.4 -  calculate possible keys from frequency analysis
//  3.5 -  calculate possible keys from user entered key
//  3.6 -  do a Caeser shift
//  3.7 -  wheels
//  3.8 -  check for defined plain words e.g. rockyou.txt
//  3.99 - exit analysis
//
//  3.1 develope key from file
//  3.1.1 - choose file for analysis
//  3.1.2 - define key character lengh (e.g. 1, 2; engima would be 1 character (E=x), others could be 2 (ER=x)
//  3.1.3 - list all occurences of key character
//  3.1.9 - save file for further analysis
//  3.1.10 - exit back to 3 menu


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Pick (int);
void EnterCipherText();
void BasicAnalysis();

char *ciphertext;
int char_set_size = 128;	// ASCII character set size assumed
int ciphersize = 0;		// Might need to be moved?

int main()

{
	char Option[60];

	//  Add below as "menu constant" to call anytime

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
	printf("Enter an option:  ");

	while (atoi(fgets(Option,60,stdin)) != 8)
	{

		if ((atoi(&Option[0])>=1) && (atoi(&Option[0]) <=8))
		{
			// printf("[DEBUG] You chose \%d \n",atoi(&Option[0]));
			Pick(Option[0]);
		}
		else
		{
			printf("Try entering a number 1 - 8\n");
		}
		printf("Enter an option:  ");
	}

	printf("Later, dude!\n");

}

void Pick(choice)

{
	// Top level program control

	switch (choice)
	{
		case '1':
			EnterCipherText();
			return;
		case '3':
			BasicAnalysis();
			return;
		default :
			printf("DEBUG - switch default\n");
			return;
	}

}

void EnterCipherText()

//  1 - enter cipher from stdin & save as user defined file

{
	char cipher_buffer[1000] = { 0 };
	char c = 0;
	int n = 0;

	ciphersize = 0;

	free (ciphertext);

	printf ("Enter your cipher text here: ");

	while (c != '\n')
	{
		c = getc(stdin);
		cipher_buffer[n] = c;
		n++;
	}

	cipher_buffer[n] = '\0';

	ciphersize = n;

	ciphertext = (char *) malloc(ciphersize);

	if (ciphertext == NULL)
	{
		printf ("Whoa!  Something happened.  Let's try again.");
		return;
	}

	n = 0;

	printf ("You entered: ");

	while (n <= ciphersize)
	{
		ciphertext[n] = cipher_buffer[n];
		putc(ciphertext[n],stdout);
		n++;
	}

	printf ("\n");

	// Need to save the text entered; user defined name

	return;

}

void BasicAnalysis()

// 3 - Develops key from user defined characteristics and does
// simple frquency analysis
// Loops through text ciphertext points at, notes all unique
// values and counts occurences
// Saves results in key file

{

	char key_buffer[char_set_size];
	int frequency_buffer[char_set_size];
	int n = 0;
	int m = 0;
	int keysize = 0;

	// Initialize buffers

	memset (key_buffer, 0, char_set_size * sizeof(char) );
	memset (frequency_buffer, 0, char_set_size * sizeof(int) );

	printf ("DEBUG - let's analyze!\n");
	for (n = 0; n <= ciphersize; n++)
	{
		for (m = 0; m <= keysize; m++)
		{
			if (ciphertext[n] == key_buffer[m])
			{
				frequency_buffer[m]++;
			}
			else
			{
				if (m == keysize)
				{
					key_buffer[m] = ciphertext[n];
					keysize++;
					break;
				}
			}
		}
	}

	// Need to allocate key_buffer and frequency_buffer to memory using malloc; structure?

	printf ("DEBUG - keysize is %d \n",keysize);

	for (n = 0; n<=keysize; n++)
	{
		printf ("DEBUG - Key Character No. %d Is %c & Occurs %d times.\n",( n+1 ),key_buffer[n],( frequency_buffer[n]+1 ));
	}

}
