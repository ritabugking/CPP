#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
 
using namespace std;
/*
This function can format text from a plain text file into neatly arranged paragraphs with a particular maximum allowed line length.
The parameters are:
lineLength = an int with the desired maximum line length.
inf = an already-opened input source you will read from.
outf = an already-opened output destination you will write to.
It will return:
0 if is successful.
1 if any input word portion is longer than the maximum line length
2 if the desired maximum line length is less than 1
*/
int format(int lineLength, istream& inf, ostream& outf)
{

	int returnType = 0;
	if (lineLength < 1 || lineLength > 400) {  // If the desired maximum line length is less than 1 or greater than 400, return 2.
		returnType = 2;
		return returnType;
	}

	char line[20000];  // Read the input text line by line
	char inStr[20000] = { '\0' }; // The input string

	while (inf.getline(line, 20000))   // Read the text from the input stream to a single string "line".
		strcat(inStr, line);  // Append the string in "line" after string "inStr".

	if (inStr == "")  // if the line length is valid but the input contains no words, format must return 0
		return 0;

	char outStr[20000] = { '\0' };  // The output string
	int pos_outStr = 0;  // The position of character in output string
	int pos_line = 0;  // The position of each formatted line

	bool newline = false; // A "#P#" appear
	bool mark = false;  // "." or "?" appear
	bool plus_ws = false;  // Add two white space in front of the word
	bool hyphen = false;  // "-" appear
	bool no_ws = false;	// Don't add white space in front of the word

	for (int i = 0; inStr[i] != '\0'; i++) {   // Transform the input string into the formatted output string

		char singleStr[20000] = { '\0' };  // Each single string in text
		int pos_singleStr = 0;   // The position of character in each single string
		while (inStr[i] != ' ' && inStr[i] != '\0') {  // Extract each single string
			singleStr[pos_singleStr] = inStr[i];
			if (mark) {              // If "." or "?" appear at the last word portion
				plus_ws = true;  // Add two white space in front of the word
				mark = false;
			}
			if (hyphen) {		// If "-" appear at the last word portion
				no_ws = true;  // Don't add white space in front of the word
				hyphen = false;
			}
			if (singleStr[pos_singleStr] == '.' || singleStr[pos_singleStr] == '?') { // If "." or "?" appear
				mark = true;  // Marked "." or "?" appear
				break;
			}
			if (singleStr[pos_singleStr] == '-') {  //If "-" appear
				hyphen = true;  // Marked "-" appear
				break;
			}
			pos_singleStr++;
			i++;
		}

		if (strlen(singleStr) > 0) {  // If the length of single string > 0
			if (strlen(singleStr) <= lineLength) { // If the length of single string <= the maximum line length
				if (strlen(singleStr) == 3 && singleStr[0] == '#' && singleStr[1] == 'P' && singleStr[2] == '#') {  // If the string is #P#
					if (pos_outStr == 0) {  // If #P# should be at the beginning of formatted text
						continue;	// Skip the formatting of this single string
					}
					else if (pos_line == 0) { // If #P# should be at the beginning of formatted line
						if (!newline) {
							outStr[pos_outStr] = '\n';	 // Add a new line in it		
							pos_outStr += 1;
							pos_line = 0;
							newline = true;
						}
					}
					else {	// If #P# should not be at the beginning of formatted line
						if (!newline) {
							outStr[pos_outStr] = '\n';  // Add two new line in it		
							outStr[pos_outStr + 1] = '\n';
							pos_outStr += 2;
							pos_line = 0;
							newline = true;
						}
					}
				}
				else {     // If the string is not #P#
					newline = false;
					if (pos_line != 0) {  // If the string should be at the beginning of formatted line
						if (plus_ws) {  // If the last word portion is "." or "?"
							if (strlen(singleStr) + 2 <= (lineLength - pos_line)) { // If this line still has enough space for 2 white space and the string
								outStr[pos_outStr] = ' ';  // Put the white space in the formatted text
								pos_outStr++;
								pos_line++;
								outStr[pos_outStr] = ' ';  // Put the 2nd white space in the formatted text
								pos_outStr++;
								pos_line++;
								plus_ws = false;
								for (int i = 0; singleStr[i] != '\0'; i++) {  // Put the string in the formatted text						
									outStr[pos_outStr] = singleStr[i];
									pos_outStr++;
									pos_line++;
								}
								if (pos_line == lineLength) {  // If this line doesn't have any space after putting the string
									outStr[pos_outStr] = '\n';  // Add a new line in it
									pos_outStr++;
									pos_line = 0;
								}

							}
							else {  // If this line doesn't have enough space for 2 white space and the string
								plus_ws = false;
								outStr[pos_outStr] = '\n';  // Add a new line in it
								pos_outStr++;
								pos_line = 0;
								for (int i = 0; singleStr[i] != '\0'; i++) {  // Add the string in it
									outStr[pos_outStr] = singleStr[i];
									pos_outStr++;
									pos_line++;
								}
								if (pos_line == lineLength) {  // If this line doesn't have any space after putting the string
									outStr[pos_outStr] = '\n';  // Add a new line in it
									pos_outStr++;
									pos_line = 0;
								}
							}
						}
						else if (no_ws) { // If the last word portion is "-" 
							if (strlen(singleStr) <= (lineLength - pos_line)) { // If this line still has enough space for the string
								no_ws = false;
								for (int i = 0; singleStr[i] != '\0'; i++) {  // Add the string in it					
									outStr[pos_outStr] = singleStr[i];
									pos_outStr++;
									pos_line++;
								}
								if (pos_line == lineLength) {  // If this line doesn't have any space after putting the string
									outStr[pos_outStr] = '\n';  // Add a new line in it
									pos_outStr++;
									pos_line = 0;
								}
							}
							else {  // If this line doesn't have enough space for 2 white space and the string
								no_ws = false;
								outStr[pos_outStr] = '\n';  // Add a new line in it
								pos_outStr++;
								pos_line = 0;
								for (int i = 0; singleStr[i] != '\0'; i++) {  // Add the string in it	
									outStr[pos_outStr] = singleStr[i];
									pos_outStr++;
									pos_line++;
								}
								if (pos_line == lineLength) {  // If this line doesn't have any space after putting the string
									outStr[pos_outStr] = '\n';  // Add a new line in it
									pos_outStr++;
									pos_line = 0;
								}
							}
						}
						else { // If the last word portion is nor ".", "?", or "-" 
							if (strlen(singleStr) + 1 <= (lineLength - pos_line)) { // If this line still has enough space for 1 white space and the string
								outStr[pos_outStr] = ' ';  // Add a white space in it
								pos_outStr++;
								pos_line++;
								for (int i = 0; singleStr[i] != '\0'; i++) {  // Add the string in it					
									outStr[pos_outStr] = singleStr[i];
									pos_outStr++;
									pos_line++;
								}
								if (pos_line == lineLength) {  // If this line doesn't have any space after putting the string
									outStr[pos_outStr] = '\n';  // Add a new line in it
									pos_outStr++;
									pos_line = 0;
								}
							}
							else {  // If this line doesn't have enough space for 1 white space and the string
								outStr[pos_outStr] = '\n';  // Add a new line in it
								pos_outStr++;
								pos_line = 0;
								for (int i = 0; singleStr[i] != '\0'; i++) {  // Add the string in it		
									outStr[pos_outStr] = singleStr[i];
									pos_outStr++;
									pos_line++;
								}
								if (pos_line == lineLength) {  // If this line doesn't have any space after putting the string
									outStr[pos_outStr] = '\n';  // Add a new line in it
									pos_outStr++;
									pos_line = 0;
								}
							}
						}
					}
					else {  // If the string should not be at the beginning of formatted line
						plus_ws = false;  // No matter if there is "." or "?" at the end of the last word portion, we don't need to add white space here.
						no_ws = false; // No matter if there is "-" at the end of the last word portion, we don't need to consider white space here.
						for (int i = 0; singleStr[i] != '\0'; i++) {  // Add the string in it	
							outStr[pos_outStr] = singleStr[i];
							pos_outStr++;
							pos_line++;
						}
						if (pos_line == lineLength) {  // If this line doesn't have any space after putting the string
							outStr[pos_outStr] = '\n';  // Add a new line in it
							pos_outStr++;
							pos_line = 0;
						}
					}
				}
			}

			else {  // If the length of single string > the maximum line length
				returnType = 1;  // Return 1
				outStr[pos_outStr] = '\n';  // Add a new line in it
				pos_outStr++;
				pos_line = 0; // It should be at the first position of the line
				plus_ws = false;  // No matter if there is "." or "?" at the end of the last word portion, we don't need to add white space here.
				no_ws = false; // No matter if there is "-" at the end of the last word portion, we don't need to consider white space here.
				int t = 0;
				for (int i = 0; i < strlen(singleStr) / lineLength; i++) {  // Count the number of lines should be full of string after formatted
					for (int j = 0; j < lineLength; j++) {       // Put the formatted long string in it
						outStr[pos_outStr] = singleStr[t];
						pos_outStr++;
						t++;
					}
					outStr[pos_outStr] = '\n';
					pos_outStr++;
				}

				for (t; singleStr[t] != '\0'; t++) {  // Put the last line of the long string in it
					outStr[pos_outStr] = singleStr[t];
					pos_outStr++;
					pos_line++;
				}
			}
		}
	}
	if (outStr[strlen(outStr) - 1] == '\n')  // Deal with the condition if the last string of text is #P#
		outStr[strlen(outStr) - 1] = '\0';
	if (outStr[strlen(outStr) - 1] == '\n')
		outStr[strlen(outStr) - 1] = '\0';

	outStr[strlen(outStr) - 1] = '\n';  // The last line of output must end with a newline

	outf << outStr;  // Sending the formatted text by using the output stream
	return returnType;
}

int main()
{
	ifstream infile("data.txt");
	if (!infile)
	{
		cerr << "Error: Cannot open data.txt!" << endl;
		return 1;
	}

	int returnValue = format(30, infile, cout);  // reads from the file data.txt

	system("pause");
}
