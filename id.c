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
//  Change error trap in main to be a function per below
//  Use structures for ciphertext, ciphersize, and key (should this be one or two?)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Display_Menu();
void Main_Switch (int);
void * Enter_Cipher_Text();
void Basic_Analysis();
void Manual_Key_Entry();
void Display_Plaintext();

struct key {			// Key structure:  cipher character, frequency, plain character, keysize; global declaration
	char cipherchar[128];
	int frequency[128];
	char plainchar[128];
	//int keysize;
} Key1;				// Key1 will need to be a return

struct ciphertext {		// Cipher text structure:  cipher pointer & size.
	char *ciphertextptr;
	int ciphersize;
};

struct key *KeyPointer1;	// Key pointer; change to return from function vs. global

//int Keysize = 0;		// Keysize; change to return from function vs. global

int CharSiteSizeGlob = 128;	// ASCII character set size assumed; this needs to be global for now
//int ciphersize = 0;

int main()

{
	char Option[60];

	printf("Welcome to iDecipher!\n");

	Display_Menu();

	// Error trap; update as a function, Error_Trap(value,lower ascii, upper ascii)

	while (atoi(fgets(Option,60,stdin)) != 8)
	{

		if ((atoi(&Option[0])>=1) && (atoi(&Option[0]) <=8))
		{
			Main_Switch(Option[0]);
		}
		else
		{
			printf("Try entering a number 1 - 8\n");
		}

		Display_Menu();

	}

	printf("Later, dude!\n");

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
		case '4':
			Manual_Key_Entry();
			return;
		default :
			printf("DEBUG - switch default\n");
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
	
	// char *ciphertext;		// Cipher text pointer; function returns this pointer

	Cipher1.ciphersize = 0;

	//free (Cipher1.ciphertextptr);

	printf ("Enter your cipher text here: ");

	while (c != '\n')
	{
		c = getc(stdin);
		CipherBuffer[n] = c;
		n++;				// Should this be ++n?
	}

	CipherBuffer[n] = '\0';			// A null on the end.

	Cipher1.ciphersize = n - 1;			// The null at the end is not part of the cipher

	Cipher1.ciphertextptr = (char *) malloc(Cipher1.ciphersize);

	if (Cipher1.ciphertextptr == NULL)
	{
		printf ("Whoa!  Something happened.  Let's try again.");
		return;
	}

	n = 0;

	printf ("You entered: ");

	while (n <= Cipher1.ciphersize)
	{
		Cipher1.ciphertextptr[n] = CipherBuffer[n];
		putc(Cipher1.ciphertextptr[n],stdout);
		n++;
	}

	printf ("\n");

	// Need to save the text entered; user defined name

	Cipher1Ptr = &Cipher1;

	printf ("DEBUG - Cipher Pointer is at: 0x%x\n", Cipher1Ptr);

	return Cipher1Ptr;

}

void Basic_Analysis()

// 3 - Develops key from user defined characteristics and does
// simple frquency analysis
// Loops through text ciphertext points at, notes all unique
// values and counts occurences
// Results in defining global key pointer
// TO DO - add ability to choose number of characters per cipher character, e.g. AXDE, is it A, X, D, E or AX, DE?

{
//	int n = 0;
//	int m = 0;

	// Intialize the Key structure

//	for (n = 0; n < CharSiteSizeGlob; n ++)
//	{
//		Key1.cipherchar[n] = 0;
//		Key1.frequency[n] = 0;
//		Key1.plainchar[n] = 0;
//	}


//	printf ("Let's analyze!\n");

//	for (n = 0; n < ciphersize; n++)	// Don't count the null at the end of ciphertext!
//	{
//		for (m = 0; m <= keysize; m++)
//		{
//			if (ciphertext[n] == Key1.cipherchar[m])
//			{
//				Key1.frequency[m]++;
//				break;
//			}
//			else
//			{
//				if (m == keysize)
//				{
//					Key1.cipherchar[m] = ciphertext[n];
//					keysize++;
//					break;
//				}
//			}
//		}
//	}

//	KeyPointer1 = &Key1;			// Save the Key as a pointer for future reference.

//	printf ("DEBUG - keysize is %d \n",keysize);

//	for (n = 0; n < keysize; n++)
//	{
//		printf ("DEBUG - Cipher Character No. %d\t Is \t%c & Occurs \t%d times.\n",( n+1 ), KeyPointer1->cipherchar[n],( KeyPointer1->frequency[n]+1 ));
//	}
}


void Manual_Key_Entry()

// User manually enters a plaint for each cipher character and displays plaintext
// How to do this via the command line?  Display whole list and then ask one at a time?
// Display_Plaintext will be a separate function

{

	int n = 0;

	printf ("OK, this is the hard way.\n");
	printf ("Let's start by printing all we know:\n");
	for (n = 0; n < keysize; n++)
	{
		printf ("Cipher Character No. %d\t Is \t%c & Occurs \t%d times.\n",( n+1 ), KeyPointer1->cipherchar[n],( KeyPointer1->frequency[n]+1 ));
	}
	
	printf ("\nNow let's go over this line by line...\n");
	
	for (n = 0; n < keysize; n++)
	{
		printf ("Cipher Character No. %d\t Is \t%c & Occurs \t%d times.\n",( n+1 ), KeyPointer1->cipherchar[n],( KeyPointer1->frequency[n]+1 ));
		printf ("What do you think the plain character is?  ");
		Key1.plainchar[n] = getc(stdin);		//Need to error trap this; only one ASCII char!
		printf ("DEBUG - you entered %c\n", KeyPointer1->plainchar[n]);
	}

}

void Display_Plaintext()

// Function to display plaintext for a given cipher text & key
// Note from VBA work:  this is a heavily used function!
// Also will need to output plaintext to various tools like frequency comparison & plain word check

{

}

void Display_Menu()

//  Displays the main menu

{
	printf("1 - Enter a cipher text\n");
	printf("2 - Read a cipher text from a file\n");
	printf("3 - Analyze an entered cipher text\n");
	printf("4 - Enter a key manually\n");
	printf("5 - Caeser shift!\n");
	printf("6 - Show plaintext\n");
	printf("7 - Help\n");
	printf("8 - Exit\n");
	printf("Enter an option, 1-8:  ");
	return;
}

