//  iDecipher!  a set of cryptographic tools by R. Austin
//
//
//  Naming convention:  Function_Call, LocalVariable, GlobalVariableGlob, structuretype.object, LocalVariablePtr
//  Note that n, m, Pick and similar items are counters or inputs and can be reused in the same function.
//
//  TO DO:  open data file reads frequency as char, not int, and displays ASCII (whoops)
//  TO DO:  some menu flow issues, e.g. move to analysis directly from main and cipher entry (in case the user backs up by accident)
//  TO DO:  crib-checker & plain-checker algorithms
//  TO DO:  break up into multiple .c, .h, with a makefile
//  TO DO:  utilities such as make all cipher CAPS, remove spaces, etc.
//  TO DO:  reorder manual entry to asks most frequent first?  May reorder on key entry in the first place?


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Global variable declarations

struct cipherdata {			// Cipher data structure:  size and pointers to ciphertext / plaintext on heap; move to .h file
	int ciphersize;
	int keysize;
	char cipherchar[128];
	int frequency[128];
	char plainchar[128];
	char * ciphertextptr;
	char * plaintextptr;
};

int CharSiteSizeGlob = 128;	// ASCII character set size assumed

//  Function prototypes

void Enter_New_Cipher(struct cipherdata *Cipher);
void Load_Cipher_From_File(struct cipherdata *Cipher);
void Enter_Cipher_Text(struct cipherdata *Cipher);
void Open_Data_File(struct cipherdata *Cipher);
void Choose_Analysis(struct cipherdata *Cipher);
void Basic_Analysis(struct cipherdata *Cipher);
void Manual_Key_Entry(struct cipherdata *Cipher);
void Display_Plaintext(struct cipherdata *Cipher);
int Error_Trap(int, int, int);
void Save_Data_File (struct cipherdata *Cipher);
void Clear_Data_File (struct cipherdata *Cipher);
void Exit_Program(struct cipherdata *Cipher);

// Command line display menus; move to separate *.c file
void Display_Main_Menu();
void Display_Enter_New_Cipher_Menu();
void Display_Open_Ex_Analysis_Menu();
void Display_Analysis_Menu();


//  Main starts here

int main()

{
	char Option[10] = { 0 };
	int n = 0;

	//  Define & initialize Cipher1; used throughout

	struct cipherdata Cipher1;
	Clear_Data_File(&Cipher1);

	printf("\nWelcome to iDecipher!\n");
	Display_Main_Menu();

	while (1)
	{
		if ( Error_Trap(atoi(fgets(Option,10,stdin)), 1, 3) == 1)
		{
			switch (Option[0])
			{
				case '1':
					Enter_New_Cipher(&Cipher1);
					break;
				case '2':
					Open_Data_File(&Cipher1);
					Choose_Analysis(&Cipher1);
					break;
				case '3':
					Exit_Program(&Cipher1);
				default:
					printf("\nDEBUG - switch default\n");
					break;
			}

			Display_Main_Menu();
		}
		else
		{
			printf("Try entering a number 1 - 3\n");
			Display_Main_Menu();
		}
	}
}

void Enter_New_Cipher(struct cipherdata *Cipher)

{
	Display_Enter_New_Cipher_Menu();

	char Option[10] = { 0 };

	while (1)
	{
		if ( Error_Trap(atoi(fgets(Option,10,stdin)), 1, 4) == 1)
		{
			switch (Option[0])
			{
				case '1':
					Load_Cipher_From_File(Cipher);
					Choose_Analysis(Cipher);
					break;
				case '2':
					Enter_Cipher_Text(Cipher);
					Choose_Analysis(Cipher);
					break;
				case '3':
					return;
				case '4':
					Exit_Program(Cipher);
				default:
					printf("\nDEBUG - switch default\n");
					break;
			}

			Display_Enter_New_Cipher_Menu();
		}
		else
		{
			printf("Try entering a number 1 - 4\n");
			Display_Enter_New_Cipher_Menu();
		}
	}
}

void Load_Cipher_From_File(struct cipherdata *Cipher)

//  Enter cipher from .txt file

{
	if ( (*Cipher).ciphertextptr != NULL )
	{	Save_Data_File(Cipher);			// Offer to save data
		Clear_Data_File(Cipher);		// Clear all data
	}	

	char CipherBuffer[10000] = { 0 };
	char c = 0;

	char FileName[32] = { 0 };
	int namelen, n = 0;
	FILE *fp;
	printf("Please enter the file name to retrieve (.txt will be appended automatically): ");
	fgets (FileName, 32, stdin);
	namelen = strlen (FileName);
	FileName[namelen - 1] = 0;
	strcat(FileName, ".txt");
	printf("DEBUG - File Name is %s \n", FileName);

	fp = fopen (FileName, "r+");
	if (fp == 0)
	{
		printf("Did you get the filename right?  Try again...\n");
		return;
	}

	int Test = feof (fp);
	while (Test != 1)
	{
		c = getc(fp);
		CipherBuffer[n] = c;
		n++;					// TO DO:  Should this be ++n?
		Test = feof (fp);
	}

	CipherBuffer[n] = '\0';				// A null on the end.

	(*Cipher).ciphersize = n - 2;			// The null at the end is not part of the cipher

	printf("DEBUG - ciphersize is %d", (*Cipher).ciphersize);

	(*Cipher).ciphertextptr = (char *) malloc((*Cipher).ciphersize);
	(*Cipher).plaintextptr = (char *) malloc((*Cipher).ciphersize);

	if ( ( (*Cipher).ciphertextptr == NULL) || ( (*Cipher).plaintextptr == NULL) )
	{
		printf ("Whoa!  Something happened.  Let's try again.\n");
		return;
	}

	n = 0;

	printf ("\nDEBUG - cipher text is: ");

	while (n <= (*Cipher).ciphersize)
	{
		(*Cipher).ciphertextptr[n] = CipherBuffer[n];
		putc((*Cipher).ciphertextptr[n],stdout);
		n++;
	}

	printf ("\n");

	return;
}

void Enter_Cipher_Text(struct cipherdata *Cipher)

//  Enter cipher from stdin, return a pointer

{
	if ( (*Cipher).ciphertextptr != NULL )
	{	Save_Data_File(Cipher);			// Offer to save data
		Clear_Data_File(Cipher);		// Clear all data
	}	

	char CipherBuffer[10000] = { 0 };
	char c = 0;
	int n = 0;

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

	return;
}

void Open_Data_File(struct cipherdata *Cipher)

//  Opens an existing cipher and key file for continued analysis

{
	if ( (*Cipher).ciphertextptr != NULL )
	{	Save_Data_File(Cipher);			// Offer to save data
		Clear_Data_File(Cipher);		// Clear all data
	}	

	char FileName[32] = { 0 };
	char c =  0;
	int namelen, n = 0;
	FILE *fp;
	printf("Please enter the data file name to retrieve (.dat will be appended automatically): ");
	fgets (FileName, 32, stdin);
	namelen = strlen (FileName);
	FileName[namelen - 1] = 0;
	strcat(FileName, ".dat");
	printf("\nDEBUG - File Name is %s \n", FileName);

	fp = fopen (FileName, "r+");
	if (fp == 0)
	{
		printf("Did you get the filename right?  Try again...\n");
		return;
	}

	fscanf(fp, "%d", &( (*Cipher).ciphersize) );				// Read the cipher size from file
	printf("DEBUG - ciphersize is %d\n", (*Cipher).ciphersize );

	(*Cipher).ciphertextptr = (char *) malloc((*Cipher).ciphersize);	// Allocate heap for cipher and plain text
	(*Cipher).plaintextptr = (char *) malloc((*Cipher).ciphersize);

	if ( ( (*Cipher).ciphertextptr == NULL) || ( (*Cipher).plaintextptr == NULL) )
	{
		printf ("Whoa!  Something happened.  Let's try again.\n");
		return;
	}

	fseek (fp, 2, SEEK_CUR);
	n = 0;
	printf ("DEBUG - Cipher text is: ");
	while ( n < (*Cipher).ciphersize )					// Read the cipher text from the file & put it on the heap
	{
		(*Cipher).ciphertextptr[n] = fgetc(fp);
		putc((*Cipher).ciphertextptr[n],stdout);
		n++;
	}
	printf ("\n");

	fseek (fp, 1, SEEK_CUR);
	n = 0;
	printf ("DEBUG - Plain text is: ");
	while (n < (*Cipher).ciphersize)					// Read the plain text from the file & put it on the heap
	{
		(*Cipher).plaintextptr[n] = fgetc(fp);
		putc((*Cipher).plaintextptr[n],stdout);
		n++;
	}
	printf ("\n");

	fseek (fp, 1, SEEK_CUR);
	fscanf(fp, "%d", &( (*Cipher).keysize) );				// Read the key size from file
	printf("DEBUG - keysize is %d \n", (*Cipher).keysize );

	fseek (fp, 1, SEEK_CUR);
	n = 0;
	printf ("DEBUG - Cipher key characters are: ");
	while (n < (*Cipher).keysize)						// Read the cipher key characters from the file
	{
		fscanf( fp, "%c", c);
		if (&c != " ")
		{
			(*Cipher).cipherchar[n] = c;
			printf( "%c ", (*Cipher).cipherchar[n] );
			n++;
		}
	}
	printf ("\n");

	fseek (fp, 2, SEEK_CUR);
	n = 0;
	printf ("DEBUG - Frequency of key characters is: ");
	while (n < (*Cipher).keysize)						// Read the frequency of cipher key character from the file
	{
		(*Cipher).frequency[n] = (int) fgetc(fp);
		putc( (*Cipher).frequency[n], stdout);
		n++;
	}
	printf ("\n");

	fseek (fp, 1, SEEK_CUR);
	n = 0;
	printf ("DEBUG - Plain key characters are: ");
	while (n < (*Cipher).keysize)						// Read the plain key characters from the file
	{
		(*Cipher).plainchar[n] = fgetc(fp);
		putc((*Cipher).plainchar[n], stdout);
		n++;
	}
	printf ("\n");

	fclose (fp);
	return;
}

void Choose_Analysis(struct cipherdata *Cipher)

{
	Display_Analysis_Menu();

	char Option[10] = { 0 };

	while (1)
	{
		if ( Error_Trap(atoi(fgets(Option,10,stdin)), 1, 9) == 1)
		{
			switch (Option[0])
			{
				case '1':
					Basic_Analysis(Cipher);
					break;
				case '2':
					Manual_Key_Entry(Cipher);
					break;
				case '8':
					return;
				case '9':
					Exit_Program(Cipher);
				default:
					printf("\nDEBUG - switch default\n");
					break;
			}

			Display_Analysis_Menu();
		}
		else
		{
			printf("Try entering a number 1 - 9\n");
			Display_Analysis_Menu();
		}
	}
}

void Basic_Analysis(struct cipherdata *Cipher)

// Develops key from user defined characteristics and does simple frquency analysis
// Loops through text ciphertext points at, notes all unique values and counts occurences
// Results in defining global key pointer
// TO DO - add ability to choose number of characters per cipher character, e.g. AXDE, is it A, X, D, E or AX, DE?

{
	if ( (*Cipher).keysize != 0 )
	{	Save_Data_File(Cipher);			// Offer to save data
		Clear_Data_File(Cipher);		// Clear all data
	}

	int n = 0;
	int m = 0;

	printf ("Let's analyze!\n");

	for (n = 0; n < (*Cipher).ciphersize; n++)		// Don't count the null at the end of ciphertext!
	{
		for (m = 0; m <= (*Cipher).keysize; m++)
		{
			if ((*Cipher).ciphertextptr[n] == (*Cipher).cipherchar[m])
			{
				(*Cipher).frequency[m]++;
				break;
			}
			else
			{
				if (m == (*Cipher).keysize)
				{
					(*Cipher).cipherchar[m] = (*Cipher).ciphertextptr[n];
					(*Cipher).keysize++;
					(*Cipher).frequency[m]++;
					break;
				}
			}
		}
	}

	printf ("\nDEBUG - Keysize is %d \n", (*Cipher).keysize);

	for (n = 0; n < (*Cipher).keysize; n++)
	{
		printf ("DEBUG - Cipher Character No. %d\t Is \t%c & Occurs \t%d times.\n",( n+1 ), (*Cipher).cipherchar[n], (*Cipher).frequency[n] );
	}

	return;
}

void Manual_Key_Entry(struct cipherdata *Cipher)

// User manually enters a plain for each cipher character and displays plaintext
// Displays whole list and then asks one at a time

{
	// Option to break out and have all remaining entered as cipher characters.

	if ( (*Cipher).plainchar[0] != 0 )		// COULD be zero; bad test
	{	Save_Data_File(Cipher);			// Offer to save data
		Clear_Data_File(Cipher);		// Clear all data
	}

	char Pick[10] = { 0 };
	int n = 0;

	for (n = 0; n < CharSiteSizeGlob; n ++)
	{
		(*Cipher).plainchar[n] = 0;
	}

	Pick[10] = 0;

	printf ("OK, this is the hard way.\n");
	printf ("Let's start by printing all we know:\n");

	for (n = 0; n < (*Cipher).keysize; n++)
	{
		printf ("Cipher Character No. %d\t Is \t%c & Occurs \t%d times.\n",( n+1 ), (*Cipher).cipherchar[n],( (*Cipher).frequency[n] ));
	}

	printf ("\nNow let's go over this line by line...\n");

	for (n = 0; n < (*Cipher).keysize; n++)
	{
		printf ("Cipher Character No. %d\t Is \t%c & Occurs \t%d times.\n",( n+1 ), (*Cipher).cipherchar[n],( (*Cipher).frequency[n] ));
		printf ("What do you think the plain character is?  ");

		fgets(Pick, 10, stdin);

		if ( ( Error_Trap(Pick[0], 32, 126) == 1 )  || ( (char)Pick[0] == 10 ) )
		{
			if ( (char)Pick[0] == 10 )
			{
				printf ("DEBUG - nothing entered.  Cipher character will be used.\n");
				(*Cipher).plainchar[n] = (*Cipher).cipherchar[n];
			}
			else
			{
				(*Cipher).plainchar[n] = Pick[0];
				printf ("DEBUG - you entered %c\n", (*Cipher).plainchar[n]);
			}
		}
		else
		{
			printf ("Only one printable ASCII character please.\n");
			n--;					// Do over!
		}
	}

	Display_Plaintext(Cipher);

	return;
}

void Display_Plaintext(struct cipherdata *Cipher)

// Function to display plaintext for a given cipher text & key
// Note from VBA work:  this is a heavily used function!
// Also will need to output plaintext to various tools like frequency comparison & plain word check

{
	//  TO DO:  check if Cipher.plainchar populated; otherwise break

	int n = 0;
	int m = 0;

	for (n = 0; n < (*Cipher).ciphersize; n++)
	{
		for (m = 0; m < (*Cipher).keysize; m++)
		{
			if ((*Cipher).ciphertextptr[n] == (*Cipher).cipherchar[m])
			{
				(*Cipher).plaintextptr[n] = (*Cipher).plainchar[m];
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

void Save_Data_File (struct cipherdata *Cipher)

//  Checks for entered data, asks, and saves the current cipher text & key details as user defined data file
//  TO DO:  Save only key, or only cipher, at user request.

{
	char Pick[10] = { 0 };

	printf("\nThere is already some data in memory.\nSave it (Y / N)?  ");
	fgets (Pick, 10, stdin);
	switch (Pick[0])
	{
		case 'Y':	
			break;
		case 'y':
			break;
		case 'N':
			return;
		case 'n':
			return;
		default:
			printf("Not sure what you said...\n");
			return;
	}

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

	n = 0;
	while (n <= (*Cipher).ciphersize)				// Save the ciphertext to the file
	{
		fprintf (fp, "%c", (*Cipher).ciphertextptr[n]);
		n++;
	}

	n = 0;
	while (n <= (*Cipher).ciphersize)				// Save the plaintext to the file
	{
		fprintf(fp, "%c", (*Cipher).plaintextptr[n]);
		n++;
	}
	fprintf (fp, "\n");

	fprintf (fp, "%d", (*Cipher).keysize);				// Save the key size to file
	fprintf (fp, "\n");

	n = 0;
	while (n <= (*Cipher).keysize)					// Save the cipher key character to the file
	{
		fprintf (fp, "%c ", (*Cipher).cipherchar[n]);
		n++;
	}
	fprintf (fp, "\n");

	n = 0;
	while (n < (*Cipher).keysize)					// Save the cipher character frequency to the file
	{
		fprintf(fp, "%d ", (*Cipher).frequency[n]);
		n++;
	}
	fprintf (fp, "\n");

	n = 0;
	while (n <= (*Cipher).keysize)					// Save the plain key character to the file
	{
		fprintf(fp, "%c ", (*Cipher).plainchar[n]);
		n++;
	}
	fprintf (fp, "\n");

	fclose (fp);
	return;
}

void Clear_Data_File(struct cipherdata *Cipher)

//  Clears everything for new analysis

{
	int n = 0;

	free ((*Cipher).ciphertextptr);
	(*Cipher).ciphersize = 0;
	(*Cipher).keysize = 0;
	for (n = 0; n < CharSiteSizeGlob; n ++)
	{
		(*Cipher).cipherchar[n] = 0;
		(*Cipher).frequency[n] = 0;
		(*Cipher).plainchar[n] = 0;
	}
	(*Cipher).ciphertextptr = NULL;
	(*Cipher).plaintextptr = NULL;

}

void Exit_Program(struct cipherdata *Cipher)

//  Saves, clears & exits
{
	if ( (*Cipher).ciphertextptr != NULL)
	{
		Save_Data_File(Cipher);
	}
	Clear_Data_File(Cipher);
	printf("Later, Dude!\n");
	exit(0);
}

//  Menu displays follow

void Display_Main_Menu()

//  Displays the main menu

{
	printf("\n1 - Enter new cipher\n");
	printf("2 - Open existing analysis *.dat file\n");
	printf("3 - Exit\n");
	printf("\nPlease enter a selection, 1 - 3:  ");
	return;
}

void Display_Enter_New_Cipher_Menu()

//  Displays the new cipher entry menu

{
	printf("\n1 - Load new cipher from file (.txt) & go to analysis\n");
	printf("2 - Enter new cipher manually & go to analysis\n");
	printf("3 - Return to main menu\n");
	printf("4 - Exit\n");
	printf("\nPlease enter a selection, 1 - 4:  ");
	return;
}

void Display_Open_Ex_Analysis_Menu()

//  Displays the open existing analysis menu

{
	printf("\n1 - Open existing analysis .dat file & go to analysis\n");
	printf("2 - Return to main menu\n");
	printf("3 - Exit\n");
	printf("\nPlease enter a selection, 1 - 3:  ");
	return;
}

void Display_Analysis_Menu()

//  Displays the analysis menu

{
	printf("\n1 - Develop key from user defined features & perform frequency analysis\n");
	printf("2 - Enter a key manually\n");
	printf("3 - Calculate possible keys from frequency analysis\n");
	printf("4 - Caeser shift!\n");
	printf("5 - Check for defined plain words or cribs\n");
	printf("8 - Return to cipher entry menu\n");
	printf("9 - Exit\n");
	printf("\nPlease enter a selection, 1 - 9:  ");
	return;
}

