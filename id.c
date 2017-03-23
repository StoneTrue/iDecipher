//  iDecipher!  a set of cryptographic tools by R. Austin
//
//  Menu Flow:
//  1 - Enter new cipher
//  2 - Open existing analysis .dat file
//  3 - Exit
//
//  1.1 - Load new cipher from file (.txt) & go to analysis
//  1.2 - Enter new cipher manually (stdin) & go to analysis - COMPLETED
//  1.3 - Back to top (if something entered, offer to save .dat)
//  1.4 - Exit (if something entered, offer to save .dat)
//
//  2.1 - Open existing analysis .dat file & go to analysis
//  2.2 - Back to top (if something entered, offer to save .dat)
//  2.3 - Exit (if something entered, offer to save .dat)
//
//  3 - analyze file chosen; default is most recent
//  analysis options are:
//  3.1 - develop key from user defined features and perform frequency analysis -COMPLETED
//  3.3 -  enter a plain key manually - COMPLETED
//  3.4 -  calculate possible keys from frequency analysis
//  3.5 -  calculate possible keys from user entered key
//  3.6 -  do a Caeser shift
//  3.7 -  wheels
//  3.8 -  check for defined plain words e.g. rockyou.txt
//  3.98 - Back to top (if something entered, offer to save .dat)
//  3.99 - Exit (if something entered, offer to save .dat)
//
//  Will need some utilities such as make all cipher CAPS, remove spaces, etc.
//
//  Naming convention:  Function_Call, LocalVariable, GlobalVariableGlob, structuretype.object, LocalVariablePtr
//
//  Note that n, m, Pick and similar items are counters or inputs and can be reused in the same function.
//
//  TO DO:  Implement menu & work flow structure above
//  TO DO:  open an existing cipher & key files for analysis; fix function inputs & remove unneeded
//  TO DO:  enter cipher from .txt file
//  TO DO:  crib-checker & plain-checker algorithms
//  TO DO:  reorder manual entry to asks most frequent first?  May reorder on key entry in the first place?


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ciphertext {		// Cipher text structure:  cipher pointer to ciphertext on heap & size.
	int ciphersize;
	char * ciphertextptr;
	char * plaintextptr;
};

struct key {			// Key structure:  cipher character, frequency, plain character, keysize; global declaration
	int keysize;
	char cipherchar[128];
	int frequency[128];
	char plainchar[128];
};

void Display_Menu();
void Enter_Cipher_Text(struct ciphertext *Cipher, struct key *Key);
void Open_Data_File(struct ciphertext *Cipher, struct key *Key);
void Basic_Analysis(struct ciphertext *Cipher, struct key *Key);
void Manual_Key_Entry(struct ciphertext *Cipher, struct key *Key);
void Display_Plaintext();
int Error_Trap(int, int, int);
void Save_Data_File (struct ciphertext *Cipher, struct key *Key);

int CharSiteSizeGlob = 128;	// ASCII character set size assumed

int main()

{
	char Option[10] = { 0 };
	int n = 0;

	//  Define & initialize Cipher1, Key1 here; used throughout

	struct ciphertext Cipher1;
	(Cipher1).ciphersize = 0;
	(Cipher1).ciphertextptr = NULL;
	(Cipher1).plaintextptr = NULL;

	struct key Key1;
	(Key1).keysize = 0;
	for (n = 0; n < CharSiteSizeGlob; n ++)
	{
		(Key1).cipherchar[n] = 0;
		(Key1).frequency[n] = 0;
		(Key1).plainchar[n] = 0;
	}

	printf("\nWelcome to iDecipher!\n");
	Display_Menu();

	while (1)
	{
		if ( Error_Trap(atoi(fgets(Option,10,stdin)), 1, 8) == 1)
		{
			switch (Option[0])
			{
				case '1':
					Enter_Cipher_Text(&Cipher1, &Key1);
					break;
				case '2':
					Open_Data_File(&Cipher1, &Key1);
					break;
				case '3':
					Basic_Analysis(&Cipher1, &Key1);
					break;
				case '4':
					Manual_Key_Entry(&Cipher1, &Key1);
					break;
				case '6':
					Display_Plaintext(&Cipher1, &Key1);
					break;
				case '8':
					printf("Later, Dude!\n");
					exit(0);
				default:
					printf("\nDEBUG - switch default\n");
					break;
			}

			Display_Menu();
		}
		else
		{
			printf("Try entering a number 1 - 8\n");
			Display_Menu();
		}
	}
}


void Enter_Cipher_Text(struct ciphertext *Cipher, struct key *Key)

//  Enter cipher from stdin, return a pointer & TO DO:  allow entry from file

{
	if ( (*Cipher).ciphertextptr != NULL )
	{
		char Pick[10] = { 0 };
		printf("\nThere is already a ciphertext in memory.\nProceed with a new entry (Y / N)?  ");
		fgets (Pick, 10, stdin);
		switch (Pick[0])
		{
			case 'Y':
				Save_Data_File(Cipher, Key);
				break;
			case 'y':
				Save_Data_File(Cipher, Key);
				break;
			case 'N':
				return;
			case 'n':
				return;
			default:
				printf("Not sure what you said...\n");
				return;
		}
	}

	(*Cipher).ciphersize = 0;
	(*Cipher).ciphertextptr = NULL;
	(*Cipher).plaintextptr = NULL;

	char CipherBuffer[1000] = { 0 };
	char c = 0;
	int n = 0;

	free ((*Cipher).ciphertextptr);

	printf ("Enter your cipher text here: ");

	while (c != '\n')
	{
		c = getc(stdin);
		CipherBuffer[n] = c;
		n++;					// TO DO:  Should this be ++n?
	}

	CipherBuffer[n] = '\0';				// A null on the end.

	(*Cipher).ciphersize = n - 1;			// The null at the end is not part of the cipher

	(*Cipher).ciphertextptr = (char *) malloc((*Cipher).ciphersize);
	(*Cipher).plaintextptr = (char *) malloc((*Cipher).ciphersize);

	if ( ( (*Cipher).ciphertextptr == NULL) || ( (*Cipher).plaintextptr == NULL) )
	{
		printf ("Whoa!  Something happened.  Let's try again.\n");
		return;
	}

	n = 0;

	printf ("\nYou entered: ");

	while (n <= (*Cipher).ciphersize)
	{
		(*Cipher).ciphertextptr[n] = CipherBuffer[n];
		putc((*Cipher).ciphertextptr[n],stdout);
		n++;
	}

	printf ("\n");

	printf ("DEBUG - Cipher Pointer is at: 0x%x\n", &Cipher);

	return;
}

void Open_Data_File(struct ciphertext *Cipher, struct key *Key)

//  Opens an existing cipher and key file for continued analysis; NOT DONE YET

{
	char FileName[32] = { 0 };
	int namelen, n = 0;
	FILE *fp;

	printf("Please enter the file name containing the cipher text:  ");
	fgets (FileName, 32, stdin);
	namelen = strlen (FileName);
	FileName[namelen - 1] = 0;

	fp = fopen (FileName, "r");
	if (fp == NULL)
	{
		printf("Looks like that was not the correct file name...\n");
		return;
	}
	fread (Cipher, sizeof(struct ciphertext), 1, fp);
	
	printf("DEBUG - Read cipher text from file %s is:  ", FileName);
	while (n <= (*Cipher).ciphersize)
	{
		putc((*Cipher).ciphertextptr[n],stdout);
		n++;
	}

	printf ("\nDEBUG - Cipher size is: %d\n", (*Cipher).ciphersize );

	return;
}

void Basic_Analysis(struct ciphertext *Cipher, struct key *Key)

// Develops key from user defined characteristics and does simple frquency analysis
// Loops through text ciphertext points at, notes all unique values and counts occurences
// Results in defining global key pointer
// TO DO - add ability to choose number of characters per cipher character, e.g. AXDE, is it A, X, D, E or AX, DE?

{
	if ( (*Key).keysize != 0 )
	{
		char Pick[10] = { 0 };
		printf("\nThere is already a key in memory.\nProceed with a new analysis (Y / N)?  ");
		fgets (Pick, 10, stdin);
		switch (Pick[0])
		{
			case 'Y':
				Save_Data_File(Cipher, Key);
				break;
			case 'y':
				Save_Data_File(Cipher, Key);
				break;
			case 'N':
				return;
			case 'n':
				return;
			default:
				printf("Not sure what you said...\n");
				return;
		}
	}

	int n = 0;
	int m = 0;

	(*Key).keysize = 0;
	for (n = 0; n < CharSiteSizeGlob; n ++)
	{
		(*Key).cipherchar[n] = 0;
		(*Key).frequency[n] = 0;
		(*Key).plainchar[n] = 0;
	}

	printf ("Let's analyze!\n");

	for (n = 0; n < (*Cipher).ciphersize; n++)		// Don't count the null at the end of ciphertext!
	{
		for (m = 0; m <= (*Key).keysize; m++)
		{
			if ((*Cipher).ciphertextptr[n] == (*Key).cipherchar[m])
			{
				(*Key).frequency[m]++;
				break;
			}
			else
			{
				if (m == (*Key).keysize)
				{
					(*Key).cipherchar[m] = (*Cipher).ciphertextptr[n];
					(*Key).keysize++;
					(*Key).frequency[m]++;
					break;
				}
			}
		}
	}

	printf ("\nDEBUG - Keysize is %d \n", (*Key).keysize);

	for (n = 0; n < (*Key).keysize; n++)
	{
		printf ("DEBUG - Cipher Character No. %d\t Is \t%c & Occurs \t%d times.\n",( n+1 ), (*Key).cipherchar[n], (*Key).frequency[n] );
	}

	return;
}


void Manual_Key_Entry(struct ciphertext *Cipher, struct key *Key)

// User manually enters a plain for each cipher character and displays plaintext
// Displays whole list and then asks one at a time

{
	// Option to break out and have all remaining entered as cipher characters.

	char Pick[10] = { 0 };

	if ( (*Key).plainchar[0] != 0 )				// Note - it COULD be zero; this is not the best test...
	{
		printf("\nThere arer already some plain characters in memory.\nProceed with a new analysis (Y / N)?  ");
		fgets (Pick, 10, stdin);
		switch (Pick[0])
		{
			case 'Y':
				Save_Data_File(Cipher, Key);			
				break;
			case 'y':
				Save_Data_File(Cipher, Key);
				break;
			case 'N':
				return;
			case 'n':
				return;
			default:
				printf("Not sure what you said...\n");
				return;
		}
	}

	int n = 0;

	for (n = 0; n < CharSiteSizeGlob; n ++)
	{
		(*Key).plainchar[n] = 0;
	}

	Pick[10] = 0;

	printf ("OK, this is the hard way.\n");
	printf ("Let's start by printing all we know:\n");

	for (n = 0; n < (*Key).keysize; n++)
	{
		printf ("Cipher Character No. %d\t Is \t%c & Occurs \t%d times.\n",( n+1 ), (*Key).cipherchar[n],( (*Key).frequency[n] ));
	}

	printf ("\nNow let's go over this line by line...\n");

	for (n = 0; n < (*Key).keysize; n++)
	{
		printf ("Cipher Character No. %d\t Is \t%c & Occurs \t%d times.\n",( n+1 ), (*Key).cipherchar[n],( (*Key).frequency[n] ));
		printf ("What do you think the plain character is?  ");

		fgets(Pick, 10, stdin);

		if ( ( Error_Trap(Pick[0], 32, 126) == 1 )  || ( (char)Pick[0] == 10 ) )
		{
			if ( (char)Pick[0] == 10 )
			{
				printf ("DEBUG - nothing entered.  Cipher character will be used.\n");
				(*Key).plainchar[n] = (*Key).cipherchar[n];
			}
			else
			{
				(*Key).plainchar[n] = Pick[0];
				printf ("DEBUG - you entered %c\n", (*Key).plainchar[n]);
			}
		}
		else
		{
			printf ("Only one printable ASCII character please.\n");
			n--;					// Do over!
		}
	}

	return;
}

void Display_Plaintext(struct ciphertext *Cipher, struct key *Key)

// Function to display plaintext for a given cipher text & key
// Note from VBA work:  this is a heavily used function!
// Also will need to output plaintext to various tools like frequency comparison & plain word check

{
	//  TO DO:  check if Cipher, Key.plainchar populated; otherwise break

	int n = 0;
	int m = 0;

	for (n = 0; n < (*Cipher).ciphersize; n++)
	{
		for (m = 0; m < (*Key).keysize; m++)
		{
			if ((*Cipher).ciphertextptr[n] == (*Key).cipherchar[m])
			{
				(*Cipher).plaintextptr[n] = (*Key).plainchar[m];
				break;
			}
		}
	}

	n = 0;

	printf ("\nThe plaintext is: ");

	while (n <= (*Cipher).ciphersize)
	{
		putc((*Cipher).plaintextptr[n],stdout);
		n++;
	}

	printf ("\n");

	return;
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

int Error_Trap(Test, LowerBound, UpperBound)

//  Tests user input against upper and lower bounds; returns 1 if good & 0 if bad

{
	int Error = 0;

	if (Test >= LowerBound && Test <= UpperBound)
	{
		Error = 1;
	}
	else
	{
		Error = 0;
	}

	return Error;
}

void Save_Data_File (struct ciphertext *Cipher, struct key *Key)

//  Saves the current cipher text & key details as user defined data file

{
	char FileName[32] = { 0 };
	int namelen, n = 0;
	FILE *fp;
	printf("Please enter a data file name (.dat will be appended automatically): ");
	fgets (FileName, 32, stdin);
	namelen = strlen (FileName);
	FileName[namelen - 1] = 0;
	strcat(FileName, ".dat");
	printf("DEBUG - File Name is %s \n", FileName);

	fp = fopen (FileName, "w");
	fprintf (fp, "%d \n", (*Cipher).ciphersize);			// Save the ciphersize to file
	fclose (fp);

	fp = fopen (FileName, "a");
	n = 0;
	while (n <= (*Cipher).ciphersize)				// Save the ciphertext to the file
	{
		fprintf (fp, "%c", (*Cipher).ciphertextptr[n]);
		n++;
	}
	fclose (fp);

	fp = fopen (FileName, "a");
	n = 0;
	while (n <= (*Cipher).ciphersize)				// Save the plaintext to the file
	{
		fprintf(fp, "%c", (*Cipher).plaintextptr[n]);
		n++;
	}
	fprintf (fp, "\n");
	fclose (fp);

	fp = fopen (FileName, "a");
	fprintf (fp, "%d", (*Key).keysize);				// Save the key size to file
	fprintf (fp, "\n");
	fclose (fp);

	fp = fopen (FileName, "a");
	n = 0;
	while (n <= (*Key).keysize)					// Save the cipher key character to the file
	{
		fprintf (fp, "%c", (*Key).cipherchar[n]);
		n++;
	}
	fprintf (fp, "\n");
	fclose (fp);

	fp = fopen (FileName, "a");
	n = 0;
	while (n < (*Key).keysize)					// Save the cipher character frequency to the file
	{
		fprintf(fp, "%d", (*Key).frequency[n]);
		n++;
	}
	fprintf (fp, "\n");
	fclose (fp);

	fp = fopen (FileName, "a");
	n = 0;
	while (n <= (*Key).keysize)					// Save the plain key character to the file
	{
		fprintf(fp, "%c", (*Key).plainchar[n]);
		n++;
	}
	fprintf (fp, "\n");
	fclose (fp);

	return;
}




