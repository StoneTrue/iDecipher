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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void DisplayMenu();
void Main_Switch (int);
void * EnterCipherText();
void BasicAnalysis();
void Manual_Key_Entry();
void Display_Plaintext();

struct key {			// Key structure:  cipher character, frequency, plain character, keysize; global declaration
	char Cipher_Char[128];
	int Frequency[128];
	char Plain_Char[128];
	//int keysize;
} Key1;				// Key1 will need to be a return

struct ciphertext {		// Cipher text structure:  cipher pointer & size.
	char *Ciphertext_Ptr;
	int Ciphersize;
};

struct key *Key_Pointer1;	// Key pointer; change to return from function vs. global

int keysize = 0;		// Keysize; change to return from function vs. global

int char_set_size = 128;	// ASCII character set size assumed; this needs to be global for now
//int ciphersize = 0;

int main()

{
	char Option[60];

	printf("Welcome to iDecipher!\n");

	DisplayMenu();

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

		DisplayMenu();

	}

	printf("Later, dude!\n");

}

void Main_Switch(choice)

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
		case '4':
			Manual_Key_Entry();
			return;
		default :
			printf("DEBUG - switch default\n");
			return;
	}

}

void * EnterCipherText()

//  1 - enter cipher from stdin, return a pointer & save as user defined file

{
	char cipher_buffer[1000] = { 0 };
	char c = 0;
	int n = 0;

	struct ciphertext Cipher1;	// Local variable to build out

	struct ciphertext *Cipher1_Ptr;	// Pointer for ciphertext to return
	
	// char *ciphertext;		// Cipher text pointer; function returns this pointer

	Cipher1.Ciphersize = 0;

	//free (Cipher1.Ciphertext_Ptr);

	printf ("Enter your cipher text here: ");

	while (c != '\n')
	{
		c = getc(stdin);
		cipher_buffer[n] = c;
		n++;				// Should this be ++n?
	}

	cipher_buffer[n] = '\0';			// A null on the end.

	Cipher1.Ciphersize = n - 1;			// The null at the end is not part of the cipher

	Cipher1.Ciphertext_Ptr = (char *) malloc(Cipher1.Ciphersize);

	if (Cipher1.Ciphertext_Ptr == NULL)
	{
		printf ("Whoa!  Something happened.  Let's try again.");
		return;
	}

	n = 0;

	printf ("You entered: ");

	while (n <= Cipher1.Ciphersize)
	{
		Cipher1.Ciphertext_Ptr[n] = cipher_buffer[n];
		putc(Cipher1.Ciphertext_Ptr[n],stdout);
		n++;
	}

	printf ("\n");

	// Need to save the text entered; user defined name

	Cipher1_Ptr = &Cipher1;

	printf ("DEBUG - Cipher Pointer is at: 0x%x\n", Cipher1_Ptr);

	return Cipher1_Ptr;

}

void BasicAnalysis()

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

//	for (n = 0; n < char_set_size; n ++)
//	{
//		Key1.Cipher_Char[n] = 0;
//		Key1.Frequency[n] = 0;
//		Key1.Plain_Char[n] = 0;
//	}


//	printf ("Let's analyze!\n");

//	for (n = 0; n < ciphersize; n++)	// Don't count the null at the end of ciphertext!
//	{
//		for (m = 0; m <= keysize; m++)
//		{
//			if (ciphertext[n] == Key1.Cipher_Char[m])
//			{
//				Key1.Frequency[m]++;
//				break;
//			}
//			else
//			{
//				if (m == keysize)
//				{
//					Key1.Cipher_Char[m] = ciphertext[n];
//					keysize++;
//					break;
//				}
//			}
//		}
//	}

//	Key_Pointer1 = &Key1;			// Save the Key as a pointer for future reference.

//	printf ("DEBUG - keysize is %d \n",keysize);

//	for (n = 0; n < keysize; n++)
//	{
//		printf ("DEBUG - Cipher Character No. %d\t Is \t%c & Occurs \t%d times.\n",( n+1 ), Key_Pointer1->Cipher_Char[n],( Key_Pointer1->Frequency[n]+1 ));
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
		printf ("Cipher Character No. %d\t Is \t%c & Occurs \t%d times.\n",( n+1 ), Key_Pointer1->Cipher_Char[n],( Key_Pointer1->Frequency[n]+1 ));
	}
	
	printf ("\nNow let's go over this line by line...\n");
	
	for (n = 0; n < keysize; n++)
	{
		printf ("Cipher Character No. %d\t Is \t%c & Occurs \t%d times.\n",( n+1 ), Key_Pointer1->Cipher_Char[n],( Key_Pointer1->Frequency[n]+1 ));
		printf ("What do you think the plain character is?  ");
		Key1.Plain_Char[n] = getc(stdin);		//Need to error trap this; only one ASCII char!
		printf ("DEBUG - you entered %c\n", Key_Pointer1->Plain_Char[n]);
	}

}

void Display_Plaintext()

// Function to display plaintext for a given cipher text & key
// Note from VBA work:  this is a heavily used function!
// Also will need to output plaintext to various tools like frequency comparison & plain word check

{

}

void DisplayMenu()

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

