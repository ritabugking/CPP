#include <iostream>
#include <string>
#include <cassert>

using namespace std;

 
// Return the number of strings in the array that are equal to target.
int tally(const string a[], int n, string target) {
	
	int num = 0;
	if (n < 0 )		// If the size of input array is less than zero, return -1.
		return -1;
	for (int i = 0; i < n; i++) {	// Go through the whole array and check the number of string which is equal to target string.
		if (a[i] == target)
			num++;
	}
	return num;		// Return the number of target string in the array.
};

// Return the position of the first string in the array that is equal to target. Return −1 if there is no such string.
int findFirst(const string a[], int n, string target) {
	
	if ( n < 0 )  // If the size of input array is less than zero, return -1.
		return -1;
	for (int i = 0; i < n; i++) {	// Go through the whole array and find the first target string. If find it, return the position of the target string.
		if (a[i] == target)
			return i;
	}
	return -1;  // If there is no target string among array, return -1.
};

// Find the earliest occurrence in a of one or more consecutive strings that are equal to target.
// Set begin to the position of the first occurrence of target; set end to the last occurrence of target in that earliest consecutive sequence. Return true. 
// If n is negative or if no string in a is equal to target, leave begin and end unchanged and return false.
bool findFirstSequence(const string a[], int n, string target, int& begin, int& end) {
	
	if (n < 0)  // If the size of input array is less than zero, return -1.
		return -1;

	for (int i = 0; i < n; i++) {		// Go through the array and find the target.
		if (a[i] == target) {		// While finding the target, set "begin" and "end" equal to the position of target.
			begin = i;
			end = i;
			for (int j = i; j < n; j++) {	// Find the consecutive strings that are equal to target, and set "end" at the end of consecutive string.
				if (j!= n) {
					if (a[j] == target)
						end = j;
					else
						break;
				}
				else	
					break;
			}
			return true;
		}
	}
	return false;	// If no string in a is equal to target, return false.
};
// Return the position of a string in the array such that that string is <= every string in the array.
// If there is more than one such string, return the smallest position of such a string. Return −1 if the array has no elements.
int positionOfMin(const string a[], int n) {
	
	if (n <= 0 )  // If the size of input array less than or equal to zero, return -1. 
		return -1;
	int min = 0;
	for (int i = 1; i < n; i++) {	// Go through the array and find minimum string. 
		if (a[min] > a[i])
			min = i;
	}
	return min;		// Return the position of that string.
};

// Eliminate the item at position pos by copying all elements after it one place to the left.
// Put the item that was thus eliminated into the last position of the array.
// Return the original position of the item that was moved to the end.
int moveToEnd(string a[], int n, int pos) {
	
	if (n < 0 || pos > n-1)  // If the size of input array is less than zero, or pos is larger than the last position among array, return -1.
		return -1;
	string temp = a[pos];
	for (int i = pos; i < n-1; i++) {  // Move all elements after pos one place to the left.
		a[pos] = a[pos + 1];
	}
	a[n - 1] = temp;    // Put the item that was thus eliminated into the last position of the array.
	return pos;    // Return the original position of the item that was moved to the end.
};

// Eliminate the item at position pos by copying all elements before it one place to the right.
// Put the item that was thus eliminated into the first position of the array.
// Return the original position of the item that was moved to the beginning.
int moveToBeginning(string a[], int n, int pos) {
	
	if (n < 0 || pos > n - 1)  // If the size of input array is less than zero, or pos is larger than the last position among array, return -1.
		return -1;
	string temp = a[pos];
	for (int i = pos; i > 0; i--) {  // Move all elements after pos one place to the right.
		a[pos] = a[pos - 1];
	}
	a[0] = temp;   // Put the item that was thus eliminated into the first position of the array.
	return pos;    // Return the original position of the item that was moved to the end.
};

// Return the position of the first corresponding elements of a1 and a2 that are not equal. 
// n1 is the number of interesting elements in a1, and n2 is the number of interesting elements in a2.
// If the arrays are equal up to the point where one or both runs out, return the smaller of n1 and n2.
int disagree(const string a1[], int n1, const string a2[], int n2) {

	if (n1 < 0 || n2 < 0 )  // If the size of input array less than zero, return -1. 
		return -1;

	int equal=-1;  // First, initiate "equal" as the position of the first corresponding elements of a1 and a2 that are not equal. 
	int pos;

	if (n1 > n2)  // Set the smaller number among two arrays as the last position that need to be checked.
		pos = n2;
	else
		pos = n1;

	for (int i = 0; i < pos; i++) {  // Go through the two arrays and check if the element at each position is equal.
		if (a1[i] == a2[i]) {
			equal++;
		}
		else
			break;
	}
	return (equal + 1); // Return the position of the first corresponding elements of a1 and a2 that are not equal. If there is no equal element, return the first position which is 0.
};

// For every sequence of consecutive identical items in a, retain only one item of that sequence. Return the number of retained items.
int removeDups(string a[], int n) {
	
	if ( n < 0 )  // If the size of input array less than zero, return -1. 
		return -1;
	int total = n;  // Set total equal to the number of items in the array.
	int i = 0;
	for (i; i < total-1; i++){  // Go through the array, if there are identical items at position i and i+1, then delete the ith item and move all the item at the left side of i to one step right.
		if (a[i] == a[i + 1]) {
			for (int j = i; j < total - 1; j++)
				a[j] = a[j + 1];
			total--;  // Minus one from the number of items in the array.
			i--;  // Minus one from i so the loop can start from ith position again.
		}
	}
	return total;  // Return the number of retained items.
};

// If all n2 elements of a2 appear in a1, in the same order, then return true.
// Return false if a1 does not contain a2 as a subsequence. 
// Return false if this function is passed any bad arguments.
bool subsequence(const string a1[], int n1, const string a2[], int n2) {
	
	if ( n1 < 0 || n2 < 0 || n2 > n1)  // If the size of input array less than zero, or if n2 is larger than n1, return -1. 
		return false;
	if (n2 == 0)  // Since the empty sequence is a subsequence of any sequence, return true if n2 = 0.
		return true;
	int pos = 0;
	for (int i = 0; i < n2; i++) {	// Go through each element among the a2 array.
		for (int j = pos; j < n1; j++) {  // Go through a1 array and check if every element in a2 can be found among a1 in the same order.
			if (a2[i] == a1[j]) {
				pos = j + 1;
				break;
			}
			else if (i == n2 - 1 && j == n1 - 1) // If both of the arrays reach the last position without equal to the value at last position of each other, return false.
				return false;
		}
	}
	return true;  // If all n2 elements of a2 appear in a1 in the same order, return true.
};

// If a1 has n1 elements in nondecreasing order, and a2 has n2 elements in nondecreasing order, place in result all the elements of a1 and a2, arranged in nondecreasing order. 
// Return the number of all the elements in new array. 
// Return −1 if the result would have more than max elements or if a1 and/or a2 are not in nondecreasing order.
int mingle(const string a1[], int n1, const string a2[], int n2, string result[], int max) {
	
	if ( n1 < 0 || n2 < 0 || (n1+n2) > max)  // If the size of input array less than zero, or if the total number of items is larger than max, return -1. 
		return -1;
	for (int i = 0; i < n1-1; i++) {	// Return -1 if a1 is not in nondecreasing order.
		if (a1[i] > a1[i + 1])
			return -1;
	}
	for (int i = 0; i < n2 - 1; i++) {	// Return -1 if a2 is not in nondecreasing order.
		if (a2[i] > a2[i + 1])
			return -1;
	}

	int order_a1 = 0;	// Set order_a1 equal to the position of concerning element among a1.	
	int order_a2 = 0;	// Set order_a2 equal to the position of concerning element among a2.
	int order_result = 0;	// Set order_result equal to the position of concerning element among result.
	
	for (int i = 0; i < (n1 + n2); i++) {	// Go through the array until every elements among a1 and a2 are all append to the new array "result".
		if (order_a2 == n2) {	// If no element of array a2 can be reached, append the rest element among a1 to the result array. Return the number of all the elements in the new array.
			for (int j = order_a1; j < n1; j++) {
				result[order_result] = a1[j];
				order_result++;
			}
			return (n1 + n2);

		}
		if (order_a1 == n1) {	// If no element of array a1 can be reached, append the rest element among a2 to the result array. Return the number of all the elements in the new array.
			for (int j = order_a2; j < n2; j++) {
				result[order_result] = a2[j];
				order_result++;
			}
			return (n1 + n2);
		}
		// Compare the element among a1 and a2 and append the smaller element to the new array "result".
		if (a1[order_a1] > a2[order_a2]) {	
			result[order_result] = a2[order_a2];
			order_result++;
			order_a2++;
			
		}
		else {
			result[order_result] = a1[order_a1];
			order_result++;
			order_a1++;
			
		}
	}
	return (n1 + n2);	// Return the number of all the elements in new array. 

};

// Rearrange the elements of the array so that all the elements whose value is < divider come before all the other elements, and all the elements whose value is > divider come after all the other elements.
// Return the position of the first element that, after the rearrangement, is not < divider, or n if there are none.
int divide(string a[], int n, string divider) {
	
	if (n < 0)  // If the size of input array less than zero, return -1. 
		return -1;
	int pos = 0;
	string temp;
	for (int i = 0; i < n; i++) {	// Go through all the elements in array a.
		if (a[i] >= divider) {	// Find the first element which >= divider, and set "pos" equal to the position of this first element.
			pos = i;
			for (int j = i+1; j < n; j++) {		// If there is element at the right side of "pos" < divider, exchange this element with the element at "pos".
				if (a[j] < divider) {
					temp = a[i];
					a[i] = a[j];
					a[j] = temp;
					pos++;	// Move the "pos" one step forward toward the tail of the array.
					
				}
			}
		return pos;		// Return the position of the first element which is >= divider after arrangement.
		}	
	}
	return n;	// Return n if there is no element >= divider.
};
int main() {
	// Test
	string a1[1] = { "" };
	string a2[3] = { " ", " a ", " abc" };
	string a3[4] = { "!!!@@", "\n", """", "{}" };
	string h[7] = { "petyr", "jaime", "jon", "daenerys", "", "tyrion", "jon" };
	string a5[8] = { "petyr", "petyr", "jon", "petyr", "petyr", "petyr", "jon", "jon" };
	
	//assert(tally(a1, 7, "jon") == 0);  // cannot detect this error
	assert(tally(a1, 1, "jon") == 0);
	assert(tally(a1, 1, "") == 1);
	assert(tally(a1, 0, "") == 0);

	assert(tally(a2, 3, "") == 0);
	assert(tally(a2, 3, " ") == 1);
	assert(tally(a2, 3, "a") == 0);
	assert(tally(a2, 3, "abc") == 0);
	assert(tally(a2, 3, " abc") == 1);

	assert(tally(a3, 4, "\n") == 1);
	assert(tally(a3, 4, """") == 1);
	assert(tally(a3, 4, "{}") == 1);
	assert(tally(a3, 4, "!!!@@") == 1);
	
	assert(tally(h, 7, "jon") == 2);
	assert(tally(h, 7, "") == 1);
	assert(tally(h, 7, "theon") == 0);
	assert(tally(h, 0, "jon") == 0);

	//assert(findFirst(h, 10, "jon") == 2);  //cannot detect the error
	assert(findFirst(h, 2, "jon") == -1);
	assert(findFirst(h, 3, "jon") == 2);
	assert(findFirst(h, 7, "Jon") == -1);
	assert(findFirst(a1, 1, "") == 0);
	
	int bg;
	int en;
	//assert(findFirstSequence(h, 10, "daenerys", bg, en) && bg == 3 && en == 3); //cannot detect the error 
	assert(findFirstSequence(h, 7, "daenerys", bg, en) && bg == 3 && en == 3);
	assert(findFirstSequence(a5, 8, "petyr", bg, en) && bg == 0 && en == 1);
	assert(findFirstSequence(a5, 1, "petyr", bg, en) && bg == 0 && en == 0);
	assert(findFirstSequence(a5, 8, "jon", bg, en) && bg == 2 && en == 2);
	assert(!findFirstSequence(a5, 8, "Jon", bg, en));


	string g[4] = { "petyr", "jaime", "daenerys", "tyrion" };
	string a7[4] = { "aaaaa", "d", "  ", " " };
	//assert(positionOfMin(g, 10) == 2); //cannot detect the error 
	assert(positionOfMin(g, 4) == 2);
	assert(positionOfMin(h, 7) == 4);
	assert(positionOfMin(h, 0) == -1);
	assert(positionOfMin(a5, 8) == 2);
	assert(positionOfMin(a7, 2) == 0);
	assert(positionOfMin(a7, 3) == 2);
	assert(positionOfMin(a7, 4) == 3);

	string a8[4] = { "petyr", "jaime", "daenerys", "tyrion" };
	//assert(disagree(h, 10, g, 4) == 2);  //cannot detect the error 
	assert(disagree(h, 4, g, 4) == 2);
	assert(disagree(g, 3, g, 4) == 3);
	assert(disagree(h, 0, g, 4) == 0);

	//assert(subsequence(h, 10, g, 4));  //cannot detect the error 
	assert(subsequence(h, 7, g, 4));
	assert(!subsequence(h, 0, g, 4)); 
	assert(subsequence(h, 4, g, 0)); //the empty sequence is a subsequence of any sequence

	string a9[1] = { "petyr" };
	//assert(moveToEnd(a9, 10, 0) == 0 && a9[0] == "petyr"); //cannot detect the error 
	assert(moveToEnd(g, 0, 1) == -1);
	assert(moveToEnd(g, 4, 1) == 1 && g[1] == "daenerys" && g[3] == "jaime");
	assert(moveToEnd(a9, 1, 0) == 0 && a9[0] == "petyr");

	string f[4] = { "daenerys", "tyrion", "jon", "jaime" };
	//assert(moveToBeginning(f, 10, 2) == -1); //cannot detect the error 
	assert(moveToBeginning(f, 0, 2) == -1);
	assert(moveToBeginning(f, 4, 2) == 2 && f[0] == "jon" && f[2] == "tyrion");
	assert(moveToBeginning(a9, 1, 0) == 0 && a9[0] == "petyr");

	string e[5] = { "daenerys", "daenerys", "daenerys", "jon", "jon" };
	string a10[5] = { "daenerys", "jon", "daenerys", "jon", "daenerys" };
	//assert(removeDups(e, 10) == 2 && e[1] == "jon"); //cannot detect the error 
	assert(removeDups(e, 5) == 2 && e[1] == "jon");
	assert(removeDups(a10, 5) == 5 && e[1] == "jon");

	string x[4] = { "cersei", "jaime", "jaime", "theon" };
	string y[4] = { "daenerys", "jaime", "jon", "tyrion" };
	string z[10];
	//assert(mingle(x, 5, y, 4, z, 10) == 8 && z[5] == "jon"); //cannot detect the error 
	assert(mingle(x, 4, y, 4, z, 10) == 8 && z[5] == "jon");
	assert(mingle(x, 4, y, 0, z, 10) == 4 && z[1] == "jaime");

	//assert(divide(h, 10, "jon") == 3); //cannot detect the error 
	assert(divide(h, 7, "jon") == 3);
	assert(divide(h, 7, "z") == 7);
	assert(divide(h, 7, "") == 0);
	assert(divide(h, 0, "jon") == 0);

	cout << "All tests succeeded" << endl;
	
	system("pause");
}
