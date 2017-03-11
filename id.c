//  iDecipher!  a set of cryptographic tools by R. Austin
//
//  Homophonic test case:
//  Polyphonic test case:
//  Ceaser shift test case:
//
//  1 - enter cipher from stdin & save as user defined file
//  2 - read cipher text from user defined file ans save as user
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
//  3.1 develop key from file
//  3.1.1 - choose file for analysis
//  3.1.2 - define key character lengh (e.g. 1, 2; engima would be 1 character (E=x), others could be 2 (ER=x)
//  3.1.3 - list all occurences of key character
//  3.1.9 - save file for further analysis
//  3.1.10 - exit back to 3 menu
//
//  Will need some utilities such as make all cipher CAPS, remove spaces, etc.
//
//  Naming convention:  Function_Call, LocalVariable, GlobalVariableGlob, structuretype.object, LocalVariablePtr,
//
//  TO DO:
//
//  Eliminate all global variables (or as many as possible)
//  Use structures for ciphertext, ciphersize, and key


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Display_Menu();
void Main_Switch (int);
void * Enter_Cipher_Text();
void * Basic_Analysis(* ciphertext);
void Manual_Key_Entry();
void Display_Plaintext();
int Error_Trap(int, int, int);

struct key {			// Key structure:  cipher character, frequency, plain character, keysize; global declaration
	char cipherchar[128];
	int frequency[128];
	char plainchar[128];
	int keysize;
};				// Key1 will need to be a return

struct ciphertext {		// Cipher text structure:  cipher pointer & size.
	char *ciphertextptr;
	int ciphersize;
};

//struct key *KeyPointer1;	// Key pointer; change to return from function vs. global

int CharSiteSizeGlob = 128;	// ASCII character set size assumed; this needs to be global for now

int main()

{
	char Option[60];

	printf("Welcome to iDecipher!\n");
	Display_Menu();

	while (1)
	{
		if ( (Error_Trap(atoi(fgets(Option,60,stdin)), 1, 8) ) == 1)
		{
			Main_Switch(Option[0]);
			Display_Menu();
		}
		else
		{
			printf("Try entering a number 1 - 8\n");
			Display_Menu();
		}
	}
}

void Main_Switch(choice)

{
	// Top level program control

	switch (choice)
	{
		case '1':
			Enter_Cipher_Text();
			return;
		case '3':
			Basic_Analysis();
			return;
		//case '4':
		//	Manual_Key_Entry();
		//	return;
		case '8':
			printf("Later, Dude!\n");
			exit(0);
		default:
			printf("\nDEBUG - switch default\n");
			return;
	}
}

void * Enter_Cipher_Text()

//  1 - enter cipher from stdin, return a pointer & save as user defined file

{
	char CipherBuffer[1000] = { 0 };
	char c = 0;
	int n = 0;

	struct ciphertext Cipher1;	// Local variable to build out

	struct ciphertext *Cipher1Ptr;	// Pointer for ciphertext to return

	Cipher1.ciphersize = 0;
	Cipher1.ciphertextptr = NULL;

	free (Cipher1.ciphertextptr);

	printf ("Enter your cipher text here: ");

	while (c != '\n')
	{
		c = getc(stdin);
		CipherBuffer[n] = c;
		n++;					// TO DO:  Should this be ++n?
	}

	CipherBuffer[n] = '\0';				// A null on the end.

	Cipher1.ciphersize = n - 1;			// The null at the end is not part of the cipher

	Cipher1.ciphertextptr = (char *) malloc(Cipher1.ciphersize);

	if (Cipher1.ciphertextptr == NULL)
	{
		printf ("Whoa!  Something happened.  Let's try again.\n");
		return;
	}

	n = 0;

	printf ("\nYou entered: ");

	while (n <= Cipher1.ciphersize)
	{
		Cipher1.ciphertextptr[n] = CipherBuffer[n];
		putc(Cipher1.ciphertextptr[n],stdout);
		n++;
	}

	printf ("\n");

	// TO DO:  Need to save the text entered; user defined name

	Cipher1Ptr = &Cipher1;

	printf ("DEBUG - Cipher Pointer is at: 0x%x\n", Cipher1Ptr);

	return Cipher1Ptr;
}

void * Basic_Analysis(Cipher1)

// 3 - Develops key from user defined characteristics and does
// simple frquency analysis
// Loops through text ciphertext points at, notes all unique
// values and counts occurences
// Results in defining global key pointer
// TO DO - add ability to choose number of characters per cipher character, e.g. AXDE, is it A, X, D, E or AX, DE?

{
	int n = 0;
	int m = 0;

	struct key Key1;
	struct key *KeyPtr1;

	// Intialize the Key structure

	Key1.keysize = 0;
	for (n = 0; n < CharSiteSizeGlob; n ++)
	{
		Key1.cipherchar[n] = 0;
		Key1.frequency[n] = 0;
		Key1.plainchar[n] = 0;
	}

	printf ("Let's analyze!\n");

	for (n = 0; n < Cipher1.ciphersize; n++)	// Don't count the null at the end of ciphertext!
	{
		for (m = 0; m <= Key1.keysize; m++)
		{
			if (Cipher1.ciphertext[n] == Key1.cipherchar[m])
			{
				Key1.frequency[m]++;
				break;
			}
			else
			{
				if (m == Key1.keysize)
				{
					Key1.cipherchar[m] = Cipher1.ciphertext[n];
					Key1.keysize++;
					break;
				}
			}
		}
	}

	KeyPtr1 = &Key1;			// Save the Key as a pointer for future reference.

	printf ("\nDEBUG - keysize is %d \n", KeyPtr1 -> keysize);

	for (n = 0; n < Key1.keysize; n++
	{
		printf ("\nDEBUG - Cipher Character No. %d\t Is \t%c & Occurs \t%d times.\n",( n+1 ), KeyPtr1->cipherchar[n],( KeyPtr1->frequency[n]+1 ));
	}

	return KeyPtr1;
}


void Manual_Key_Entry()

// User manually enters a plaint for each cipher character and displays plaintext
// How to do this via the command line?  Display whole list and then ask one at a time?
// Display_Plaintext will be a separate function
{
}
//{

//	int n = 0;

//	printf ("OK, this is the hard way.\n");
//	printf ("Let's start by printing all we know:\n");
//	for (n = 0; n < keysize; n++)
//	{
//	printf ("Cipher Character No. %d\t Is \t%c & Occurs \t%d times.\n",( n+1 ), KeyPointer1->cipherchar[n],( KeyPointer1->frequency[n]+1 ));
//	}
	
//	printf ("\nNow let's go over this line by line...\n");
	
//	for (n = 0; n < keysize; n++)
//	{
//	printf ("Cipher Character No. %d\t Is \t%c & Occurs \t%d times.\n",( n+1 ), KeyPointer1->cipherchar[n],( KeyPointer1->frequency[n]+1 ));
//		printf ("What do you think the plain character is?  ");
//		Key1.plainchar[n] = getc(stdin);			//Need to error trap this; only one ASCII char!
//		printf ("DEBUG - you entered %c\n", KeyPointer1->plainchar[n]);
//	}

//}

void Display_Plaintext()

// Function to display plaintext for a given cipher text & key
// Note from VBA work:  this is a heavily used function!
// Also will need to output plaintext to various tools like frequency comparison & plain word check

{

}

void Display_Menu()

//  Displays the main menu

{
	printf("\n1 - Enter a cipher text\n");
	printf("2 - Read a cipher text from a file\n");
	printf("3 - Analyze an entered cipher text\n");
	printf("4 - Enter a key manually\n");
	printf("5 - Caeser shift!\n");
	printf("6 - Show plaintext\n");
	printf("7 - Help\n");
	printf("8 - Exit\n\n");
	printf("Enter an option, 1-8:  ");
	return;
}

int Error_Trap(Test, Lower_Bound, Upper_Bound)

//  Tests user input against upper and lower bounds; returns 1 if good & 0 if bad

{
	int Error = 0;		// Declare & initialize local variable	

	if (Test >= Lower_Bound && Test <= Upper_Bound)
	{
		Error = 1;
	}
	else
	{	
		Error = 0;
	}

	return Error;
}

