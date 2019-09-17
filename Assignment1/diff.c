/*
Name: diff.c 
Author: Will St. Onge
Description: Program that tests the differences between 2 files character by character. There are 2 options for case sensitivity and characters only that will modify the conditions on the files.
 */

#define _CRT_SECURE_NO_WARNINGS // Don't want to bother with scanf_s warning

#include <stdio.h> // For io functions
#include <ctype.h> // For isalpha()

main()
{
	int numOfChars = 0, ignoredChars = 0, mismatchChars = 0; // Count for what I am looking for
	char caseSensitive = 'n', lettersOnly = 'n'; // conditions for testing
	char file1[20] = "file2a.txt", file2[20] = "file2b.txt"; // Hardcoded file names
	FILE* parent, * child; // file pointers

	// Get console inputs for how to test the files
	printf("Case insensitive? (Y/N) ");
	scanf(" %c", &caseSensitive);

	printf("Compare letters only? (Y/N) ");
	scanf(" %c", &lettersOnly);

	// Convert console inputs to lower case
	caseSensitive = tolower(caseSensitive);
	lettersOnly = tolower(lettersOnly);

	// Test yes/no inputs from console
	if (caseSensitive != 'y' && caseSensitive != 'n')
	{
		printf("Invalid input %c", caseSensitive);
		return 1;
	}
	else if (lettersOnly != 'y' && lettersOnly != 'n')
	{
		printf("Invalid input %c", lettersOnly);
		return 1;
	}

	// Output what will be done to compare the files
	if (caseSensitive == 'y' && lettersOnly == 'y')
	{
		printf("\nComparing %s to %s testing for case sensitivity and for letters only", file1, file2);
	}
	else if (caseSensitive == 'y' && lettersOnly == 'n')
	{
		printf("\nComparing %s to %s testing for case sensitivity and all characters only", file1, file2);
	}
	else if (caseSensitive == 'n' && lettersOnly == 'y')
	{
		printf("\nComparing %s to %s testing for letters only", file1, file2);
	}
	else if (caseSensitive == 'n' && lettersOnly == 'n')
	{
		printf("\nComparing %s to %s testing for all characters", file1, file2);
	}

	// Init file pointers
	fopen_s(&parent, &file1, "r");
	fopen_s(&child, &file2, "r");

	// Get the first character from each file
	char c1 = fgetc(parent);
	char c2 = fgetc(child);

	// Loop through ever character until EOF is reached
	while (c1 != EOF)
	{
		// Increment number of characters checked
		numOfChars++;

		// If we are only checking alpha and we get a non-alpha, increment the number of chars ignored
		if (lettersOnly == 'y' && (!isalpha(c1) || !isalpha(c2)))
			// If characters only is 'y' and the character is non-alphabetical, the character will be ignored and the ignored character count will be ignored.
			ignoredChars++;

		// Check to see if I need to ignore the case of the char or not and test similarity
		else if (caseSensitive == 'n')
			// Compare character inputs
			if (c1 != c2)
				// If they do not match, increment the number of mismatched characters
				mismatchChars++;
			else
				// Test lower case versions of character since case insensivity is 'y'
				if (tolower(c1) != tolower(c2))
					// If they do not match, increment the number of mismatched characters
					mismatchChars++;

		// Get next characters
		c1 = fgetc(parent);
		c2 = fgetc(child);
	}

	// Close the files
	fclose(parent);
	fclose(child);

	// Output information required to console
	printf("\n    File sizes:    %d characters", numOfChars);
	printf("\n    Mismatches:    %4.2f%%", ((double)mismatchChars / (double)numOfChars) * 100);
	printf("\n    Not Tested:    %4.2f%%", ((double)ignoredChars / (double)numOfChars) * 100);
}