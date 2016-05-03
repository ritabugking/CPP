#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
using namespace std;

// The function can check if the input character is a correct direction.
bool isdirection(char dir) {
	if (dir == 'u' || dir == 'U' || dir == 'd' || dir == 'D' || dir == 'l' || dir == 'L' || dir == 'r' || dir == 'R')
		return true;
	else
		return false;
}

// The function can count the number of slash in a string from the first character to nth character of the string.
int countSlash(int n, string str) {

	int slash = 0;
	for (int k = 0; k < n; k++) {
		if (str[k] == '/')
			slash += 1;
	}
	return slash;
}

// The function can check if "dance" is a syntactically correct string.
bool hasCorrectSyntax(string dance) {

	// Go through dance string from the first charracter to the last character.
	for (int i = 0; i < dance.size(); i++) {

		// If the ith character is a digit,
		if (isdigit(dance[i])) {

			// If the ith character is not the last character of the string,
			if ((i + 1) != dance.size()) {
				// If the next character is neither a digit nor a direction, return false.
				if (!(isdigit(dance[i + 1])) && !isdirection(dance[i + 1]))
					return false;
				// If the next character is a digit
				else if (isdigit(dance[i + 1])) {
					// If the next character is the last character of the string, return false.
					if ((i + 2) == dance.size())
						return false;
					// If the character after two digits is not a direction, return false.
					else if (!isdirection(dance[i + 2]))
						return false;
					else {
						// If there is no character after two digits and a direction, return false.
						if ((i + 3) == dance.size())
							return false;
						// If the character after two digits and a direction is not a '/', return false.
						else if (dance[i + 3] != '/')
							return false;
					}
				}
				// If the next character is a character,
				else {
					// If the next character is the last character of the string, return false.
					if ((i + 2) == dance.size())
						return false;
					// If the character after a digit and a direction is not a '/', return false.
					else if (!(dance[i + 2] == '/'))
						return false;
				}
			}
			// If the ith character is the last character of the string, return false.
			else
				return false;
		}
		// If the ith character is a direction,
		else if (isdirection(dance[i])) {
			// If the ith character is not the last character of the string,
			if ((i + 1) != dance.size()) {
				// If the character after a direction is not a '/', return false,
				if (dance[i + 1] != '/')
					return false;
			}
			// If the ith character is the last character of the string, return false,
			else
				return false;
		}
		// If the ith character is a '/', skip this checking,
		else if (dance[i] == '/') {
			continue;
		}

		// If the ith character is neither a digit, nor a direction, nor a '/', return false.
		else
			return false;
	}
	// After going through all the characters within string, if no error happened, we can pretty sure the syntax is correct and return true.
	return true;
}

/*
The function can judge if the string is convertible.
If the string is convertible, the string will be converted and stored in instruction, the return value will be 0.
If the string is not convertible:
	If the string is not syntactically correct, the return value will be 1.
	If the string is syntatically correct:
		If the string ends prematurely, badBeat is set to one more than the number of beats in the string, and the return value will be 2.
		If there is a beat specifies a freeze of length less than 2, badBeat is set to the number of that beat, and the return value will be 3.
		If a freeze is in effect but a beat not consisting of only a slash is present, badBeat is set to the number of that beat, and the return value will be 4.
*/
int convertDance(string dance, string& instructions, int& badBeat) {

	string convert = "";
	// If the string is not syntactically correct, return 1.
	if (!hasCorrectSyntax(dance))
		return 1;

	// Syntatically correct while dance is empty string so we return 0 here.
	else if (dance == "") {
		instructions = "";
		return 0;
	}

	// While sytactically correct:
	else {
		// Go through dance string from the first charracter to the last character.
		for (int i = 0; i < dance.size(); i++) {

			// If the ith character is a digit,
			if (isdigit(dance[i])) {

				// If the i+1th character is a digit (If this beat is two digits),
				if (isdigit(dance[i + 1])) {

					// n=freeze of length
					int n = 0;
					n = (dance[i] - '0') * 10 + dance[i + 1] - '0'; // Convert a character to a number.

					int skipChar = 3; // skip the checking of two digit characters and one direction characters

																	// If freeze of length is less than 2, return 3.
					if (n == 0 || n == 1) {

						//  Count the number of '/' before ith position. The badBeat is set to the number of this beat.
						badBeat = countSlash(i, dance) + 1;
						return 3;
					}

					

					// If freeze of length is at least 2 but dance ends prematurely, return 2.
					else if ((i + skipChar + n) > dance.size()) {

						// badBeat is set to one more than the number of beats of the string.
						badBeat = countSlash(dance.size(), dance) + 1;
						return 2;

					}
					// If freeze is in effect, but a beat is not consisting of only a slash, return 4.
					else {

						// Use a for loop to check while in freeze effect, the position where should be occupied by a '/' is a '/' or other character.
						
						for (int j = 0; j < n; j++) {
						
							// If the position where should be occupied by a '/' is occupied by another character, badBeat is set to the number of that beat and return 4.
							if (dance[i + j + skipChar] != '/') {

								badBeat = countSlash(i + j + skipChar+1, dance) + 1;
								return 4;
							}
						}
					}

					// If this beat with enough '/' is convertible, convert the direction character to upper case and save it in variable "convert".				
					for (int m = 0; m < n; m++) {
						convert += toupper(dance[i + skipChar - 1]);

					}
					// Jump i to the next character and skip the beat with its '/' that we have just converted.
					i += (skipChar + n - 1);
				}

				// If the freeze of length is one digits,
				else {
					// n=freeze of length
					int n = 0;
					n = dance[i] - '0'; //convert a character to a number

					int skipChar = 2; // skip the checking of one digit character and one direction characters

					// If freeze of length is less than 2, return 3.
					if (n == 0 || n == 1) {

						//  Count the number of '/' before ith position. The badBeat is set to the number of this beat.
						badBeat = countSlash(i, dance) + 1;
						return 3;
					
					}
					//If freeze of length is at least 2 but dance ends prematurely, return 2.
					else if ((i + skipChar + n) > dance.size()) {

						// badBeat is set to one more than the number of beats in the string.
						badBeat = countSlash(dance.size(), dance) + 1;
						return 2;
					
					}
					// If freeze is in effect, but a beat is not consisting of only a slash, return 4.
					else {
						// Use a for loop to check while in freeze effect, the position where should be occupied by a '/' is a '/' or other character.
						for (int j = 0; j < n; j++) {
							// If the position where should be occupied by a '/' is occupied by another character, badBeat is set to the number of that beat and return 4.
							if (dance[i + j + skipChar] != '/') {

								badBeat = countSlash(i + j + skipChar + 1, dance) + 1;
								return 4;
							}
						}
					}
					// If this beat with enough '/' is convertible, convert it to upper csse and save it in variable "convert".
					for (int m = 0; m < n; m++) {
						convert += toupper(dance[i + skipChar - 1]);

					}
					// Jump i to the next character and skip the beat with its '/' that we have just converted.
					i += (n + skipChar - 1);
				}

			}
			// If the ith character is a '/', convert it to '.' and save it in variable "convert".
			else if (dance[i] == '/')
				convert += '.';
			// If the ith character is a direction, convert it to lower case and save it in variable "convert".
			else {
				convert += tolower(dance[i]);
				// Jump i to the next character and skip the beat with its '/' that we have just converted.
				i += 1;
			}
		}
	}

	// Save the converted string into variable instruction and return 0.
	instructions = convert;
	return 0;
}

int main() {

	// Test data
	assert(hasCorrectSyntax(""));
	assert(hasCorrectSyntax(""));
	assert(hasCorrectSyntax("u/"));
	assert(hasCorrectSyntax("0u/"));
	assert(hasCorrectSyntax("1u/"));
	assert(hasCorrectSyntax("01u/"));
	assert(hasCorrectSyntax("/u/"));
	assert(hasCorrectSyntax("3u/"));
	assert(hasCorrectSyntax("03u/"));
	assert(hasCorrectSyntax("3u///"));
	assert(hasCorrectSyntax("3u////"));
	assert(hasCorrectSyntax("u/d/"));
	assert(hasCorrectSyntax("R/L/U/D/"));
	assert(hasCorrectSyntax("3u//d/"));
	assert(hasCorrectSyntax("3u//d//"));
	assert(hasCorrectSyntax("3u//2R/D/"));
	assert(hasCorrectSyntax("3u/////2R//L/"));
	assert(hasCorrectSyntax("10u/"));

	assert(!hasCorrectSyntax(" /"));
	assert(!hasCorrectSyntax("u"));
	assert(!hasCorrectSyntax("0.5u/"));
	assert(!hasCorrectSyntax("0u"));
	assert(!hasCorrectSyntax("01u"));
	assert(!hasCorrectSyntax("3"));
	assert(!hasCorrectSyntax("3u"));
	assert(!hasCorrectSyntax("-3u/"));
	assert(!hasCorrectSyntax("3 u/"));
	assert(!hasCorrectSyntax("u3///"));
	assert(!hasCorrectSyntax("10u"));
	assert(!hasCorrectSyntax("999u/"));
	assert(!hasCorrectSyntax("ud/"));
	assert(!hasCorrectSyntax("u/d"));
	assert(!hasCorrectSyntax("/u"));
	assert(!hasCorrectSyntax("///////L"));
	assert(!hasCorrectSyntax("R/L/U/D"));

	string ins;
	int bb;
	ins = "WOW";  // so we can detect whether convertDance sets ins
	bb = -999;    // so we can detect whether convertDance sets bb
				  ////convertDance("10u///", ins, bb);
				  //convertDance("3r///", ins, bb);
				  //convertDance("3r//", ins, bb);
				  //convertDance("3r///2r/", ins, bb);
				  //convertDance("3r///2r//", ins, bb);
				  //convertDance("3r////2r//", ins, bb);
				  //convertDance("3r//u/2r//", ins, bb);
				  //convertDance("3r///u///u/2r//", ins, bb);
				  //convertDance("02u//", ins, bb);
				  //convertDance("10u/////////", ins, bb);
				  /*convertDance("10u//////////r/", ins, bb);
				  convertDance(" /", ins, bb);
				  cout << ins << endl;
				  cout << bb << endl;
				  cout << convertDance(" /", ins, bb) << endl;*/

	assert(convertDance("u/", ins, bb) == 0 && ins == "u"  &&  bb == -999);
	assert(convertDance("2u//", ins, bb) == 0 && ins == "UU"  &&  bb == -999);
	assert(convertDance("2U//", ins, bb) == 0 && ins == "UU"  &&  bb == -999);
	assert(convertDance("2u///", ins, bb) == 0 && ins == "UU."  &&  bb == -999);
	assert(convertDance("/u/", ins, bb) == 0 && ins == ".u"  &&  bb == -999);
	assert(convertDance("u/d/", ins, bb) == 0 && ins == "ud"  &&  bb == -999);
	assert(convertDance("u//d/", ins, bb) == 0 && ins == "u.d"  &&  bb == -999);
	assert(convertDance("/u//d/", ins, bb) == 0 && ins == ".u.d"  &&  bb == -999);
	assert(convertDance("u/d/l/r/", ins, bb) == 0 && ins == "udlr"  &&  bb == -999);
	assert(convertDance("u/3d///l//r/", ins, bb) == 0 && ins == "uDDDl.r"  &&  bb == -999);

	ins = "WOW";
	bb = -999;
	assert(convertDance(" /", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("u", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("A", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("u/a/", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("0u", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("01u", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("0.5u/", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("3", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("3u", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("3 u/", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("-3u///", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("u3///", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("10u", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("ud/", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("u/d", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("/u", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("///////L", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("R/L/U/D", ins, bb) == 1 && ins == "WOW"  &&  bb == -999);
	ins = "WOW";
	bb = -999;

	assert(convertDance("2u/", ins, bb) == 2 && ins == "WOW"  &&  bb == 2);
	ins = "WOW";
	bb = -999;
	assert(convertDance("2u//3d/", ins, bb) == 2 && ins == "WOW"  &&  bb == 4);
	ins = "WOW";
	bb = -999;
	assert(convertDance("2u//3d//", ins, bb) == 2 && ins == "WOW"  &&  bb == 5);
	ins = "WOW";
	bb = -999;
	assert(convertDance("2u//3d///10L/", ins, bb) == 2 && ins == "WOW"  &&  bb == 7);
	ins = "WOW";
	bb = -999;
	assert(convertDance("03u///2r//5L//", ins, bb) == 2 && ins == "WOW"  &&  bb == 8);
	ins = "WOW";
	bb = -999;

	assert(convertDance("0u/", ins, bb) == 3 && ins == "WOW"  &&  bb == 1);
	ins = "WOW";
	bb = -999;
	assert(convertDance("1u/", ins, bb) == 3 && ins == "WOW"  &&  bb == 1);
	ins = "WOW";
	bb = -999;
	assert(convertDance("/1u/", ins, bb) == 3 && ins == "WOW"  &&  bb == 2);
	ins = "WOW";
	bb = -999;
	assert(convertDance("2u//0D/", ins, bb) == 3 && ins == "WOW"  &&  bb == 3);
	ins = "WOW";
	bb = -999;
	assert(convertDance("2u//1D/", ins, bb) == 3 && ins == "WOW"  &&  bb == 3);
	ins = "WOW";
	bb = -999;
	assert(convertDance("2u//2D///1L/", ins, bb) == 3 && ins == "WOW"  &&  bb == 6);
	ins = "WOW";
	bb = -999;

	assert(convertDance("2u/r/", ins, bb) == 4 && ins == "WOW"  &&  bb == 2);
	ins = "WOW";
	bb = -999;
	assert(convertDance("2u//r/3l//d/", ins, bb) == 4 && ins == "WOW"  &&  bb == 6);
	ins = "WOW";
	bb = -999;
	assert(convertDance("2u//r/3L///2U/R//", ins, bb) == 4 && ins == "WOW"  &&  bb == 8);
	ins = "WOW";
	bb = -999;





	assert(convertDance("u//d/r///d/", ins, bb) == 0 && ins == "u.dr..d"  &&  bb == -999);
	ins = "WOW";
	bb = -999;
	assert(convertDance("u//d/3r///d/", ins, bb) == 0 && ins == "u.dRRRd"  &&  bb == -999);

	//ins = "WOW";  // so we can detect whether convertDance sets ins
	//bb = -999;    // so we can detect whether convertDance sets bb
	//assert(convertDance("5r//", ins, bb) == 2 && ins == "WOW"  &&  bb == 3);

	cout << "All tests succeeded" << endl;
	system("pause");

}