#include <iostream>
#include <string>
#include <cassert>

using namespace std;



//Return the number of strings in the array that are equal to target.[Of course, in this and other functions, if n is negative, the paragraph above that starts "Notwithstanding" trumps this by requiring that the function return −1.Also, in the description of this function and the others, when we say "the array", we mean the n elements that the function is aware of.] As noted above, case matters: Do not consider "jon" to be equal to "JoN".
int tally(const string a[], int n, string target) {
	int num = 0;
	//int size = sizeof(a) / sizeof(a[0]); // Calculate the size of array a.
	if (n < 0 )  // If the size of input array less than zero, or 
		return -1;
	for (int i = 0; i < n; i++) {
		if (a[i] == target)
			num++;
	}
	return num;
};
//Return the position of the first string in the array that is equal to target.Return −1 if there is no such string.As noted above, case matters: Do not consider "jOn" to be equal to "Jon".
int findFirst(const string a[], int n, string target) {
	//int size = sizeof(a) / sizeof(a[0]); // Calculate the size of array a.
	if ( n < 0 )  // If the size of input array less than zero, or 
		return -1;
	for (int i = 0; i < n; i++) {
		if (a[i] == target)
			return i;
	}
	return -1;
};
//Find the earliest occurrence in a of one or more consecutive strings that are equal to target; set begin to the position of the first occurrence of target, set end to the last occurrence of target in that earliest consecutive sequence, and return true.If n is negative or if no string in a is equal to target, leave begin and end unchanged and return false.Here's an example:
bool findFirstSequence(const string a[], int n, string target, int& begin, int& end) {

	for (int i = 0; i < n; i++) {
		if (a[i] == target) {
			begin = i;
			end = i;
			for (int j = i+1; j < n; j++) {
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
	return false;
};
//Return the position of a string in the array such that that string is <= every string in the array.If there is more than one such string, return the smallest position of such a string.Return −1 if the array has no elements.
int positionOfMin(const string a[], int n) {
	//int size = sizeof(a) / sizeof(a[0]); // Calculate the size of array a.
	if (n < 0 )  // If the size of input array less than zero, or 
		return -1;
	int min = 0;
	for (int i = 1; i < n; i++) {
		if (a[min] > a[i])
			min = i;
	}
	return min;
};
//Eliminate the item at position pos by copying all elements after it one place to the left.Put the item that was thus eliminated into the last position of the array.Return the original position of the item that was moved to the end.Here's an example:
int moveToEnd(string a[], int n, int pos) {
	//int size = sizeof(a) / sizeof(a[0]); // Calculate the size of array a.
	if (n < 0 )  // If the size of input array less than zero, or 
		return -1;
	string temp = a[pos];
	for (int i = pos; i < n-1; i++) {
		a[pos] = a[pos + 1];
	}
	a[n - 1] = temp;
	return pos;
};
//Eliminate the item at position pos by copying all elements before it one place to the right.Put the item that was thus eliminated into the first position of the array.Return the original position of the item that was moved to the beginning.Here's an example:
int moveToBeginning(string a[], int n, int pos) {
	//int size = sizeof(a) / sizeof(a[0]); // Calculate the size of array a.
	if (n < 0 )  // If the size of input array less than zero, or 
		return -1;
	string temp = a[pos];
	for (int i = pos; i > 0; i--) {
		a[pos] = a[pos - 1];
	}
	a[0] = temp;
	return pos;
};
//Return the position of the first corresponding elements of a1 and a2 that are not equal.n1 is the number of interesting elements in a1, and n2 is the number of interesting elements in a2.If the arrays are equal up to the point where one or both runs out, return the smaller of n1 and n2.Here's an example:
int disagree(const string a1[], int n1, const string a2[], int n2) {
	//int size_a1 = sizeof(a1) / sizeof(a1[0]); // Calculate the size of array a1.
	//int size_a2 = sizeof(a2) / sizeof(a2[0]); // Calculate the size of array a2.
	if (n1 < 0 || n2 < 0 )  // If the size of input array less than zero, or 
		return -1;
	int equal=-1;
	int pos;
	if (n1 > n2)
		pos = n2;
	else
		pos = n1;
	for (int i = 0; i < pos; i++) {
		if (a1[i] == a2[i]) {
			equal++;
		}
		else
			break;
	}
	return (equal + 1);
};
//For every sequence of consecutive identical items in a, retain only one item of that sequence.Suppose we call the number of retained items r.Then when this functions returns, elements 0 through r - 1 of a must contain the retained items(in the same relative order they were in originally), and the remaining elements may have whatever values you want.Return the number of retained items.Here's an example:
int removeDups(string a[], int n) {
	//int size = sizeof(a) / sizeof(a[0]); // Calculate the size of array a.
	if ( n < 0 )  // If the size of input array less than zero, or 
		return -1;
	int total = n;
	for (int i = 0; i < n-1; i++) {
		if (a[i] == a[i + 1])
			for (int j = i; j < total - 1; j++) {
				a[j] == a[j + 1];
				total--;
			}
	}
	return total;
};
//If all n2 elements of a2 appear in a1, in the same order(though not necessarily consecutively), then return true.Return false if a1 does not contain a2 as a subsequence. (Of course, the empty sequence is a subsequence of any sequence.) Return false (instead of −1) if this function is passed any bad arguments.Here's an example:
bool subsequence(const string a1[], int n1, const string a2[], int n2) {
	//int size_a1 = sizeof(a1) / sizeof(a1[0]); // Calculate the size of array a1.
	//int size_a2 = sizeof(a2) / sizeof(a2[0]); // Calculate the size of array a2.
	if ( n1 < 0 || n2 < 0 || n2 > n1)  // If the size of input array less than zero, or 
		return false;
	int pos = 0;
	for (int i = 0; i < n2; i++) {	
		for (int j = pos; j < n1; j++) {
			if (a2[i] == a1[j]) {
				pos = j + 1;
				break;
			}
			else if (i == n2 - 1 && j == n1 - 1)
				return false;
		}
	}
	return true;
};
//If a1 has n1 elements in nondecreasing order, and a2 has n2 elements in nondecreasing order, place in result all the elements of a1 and a2, arranged in nondecreasing order, and return the number of elements so placed. Return −1 if the result would have more than max elements or if a1 and/or a2 are not in nondecreasing order.
int mingle(const string a1[], int n1, const string a2[], int n2, string result[], int max) {
	//int size_a1 = sizeof(a1) / sizeof(a1[0]); // Calculate the size of array a1.
	//int size_a2 = sizeof(a2) / sizeof(a2[0]); // Calculate the size of array a2.
	if ( n1 < 0 || n2 < 0 || (n1+n2) > max)  // If the size of input array less than zero, or 
		return -1;
	for (int i = 0; i < n1-1; i++) {
		if (a1[i] > a1[i + 1])
			return -1;
	}
	for (int i = 0; i < n2 - 1; i++) {
		if (a2[i] > a2[i + 1])
			return -1;
	}
	int order_a1 = 0;
	int order_a2 = 0;
	int order_result = 0;
	result [max];
	for (int i = 0; i < (n1 + n2); i++) {
		if (a1[order_a1] > a2[order_a2]) {
			result [order_result]= a2[order_a2];
			order_result++;
			order_a2++;
			if (order_a2 == n2) {
				for (int j = order_a1; j < n1; j++) {
					result[order_result] = a1[j];
					order_result++;
				}
			}
		}
		else {
			result[order_result] = a1[order_a1];
			order_result++;
			order_a1++;
			if (order_a1 == n1) {
				for (int j = order_a2; j < n2; j++) {
					result[order_result] = a2[j];
					order_result++;
				}
			}
		}
	}
	return (n1 + n2);

};
//Rearrange the elements of the array so that all the elements whose value is < divider come before all the other elements, and all the elements whose value is > divider come after all the other elements.Return the position of the first element that, after the rearrangement, is not < divider, or n if there are none.Here's an example:
int divide(string a[], int n, string divider) {
	//int size = sizeof(a) / sizeof(a[0]); // Calculate the size of array a.
	if (n < 0)  // If the size of input array less than zero, or 
		return -1;
	int pos;
	string temp;
	for (int i = 0; i < n; i++) {
		if (a[i] > divider) {
			pos = i;
			for (int j = i+1; j < n; j++) {
				if (a[j] <= divider) {
					temp = a[i];
					a[i] = a[j];
					a[j] = temp;
					pos++;
				}
			}
			return pos;
		}
	}
	return n;
};
int main() {
	// Test
	string h[7] = { "petyr", "jaime", "jon", "daenerys", "", "tyrion", "jon" };
	
	assert(tally(h, 7, "jon") == 2);
	assert(tally(h, 7, "") == 1);
	assert(tally(h, 7, "theon") == 0);
	assert(tally(h, 0, "jon") == 0);
	assert(findFirst(h, 7, "jon") == 2);
	assert(findFirst(h, 2, "jon") == -1);
	int bg;
	int en;
	assert(findFirstSequence(h, 7, "daenerys", bg, en) && bg == 3 && en == 3);

	string g[4] = { "petyr", "jaime", "daenerys", "tyrion" };
	assert(positionOfMin(g, 4) == 2);
	assert(disagree(h, 4, g, 4) == 2);
	assert(subsequence(h, 7, g, 4));
	assert(moveToEnd(g, 4, 1) == 1 && g[1] == "daenerys" && g[3] == "jaime");

	string f[4] = { "daenerys", "tyrion", "jon", "jaime" };
	assert(moveToBeginning(f, 4, 2) == 2 && f[0] == "jon" && f[2] == "tyrion");

	string e[5] = { "daenerys", "daenerys", "daenerys", "jon", "jon" };
	assert(removeDups(e, 5) == 2 && e[1] == "jon");

	string x[4] = { "cersei", "jaime", "jaime", "theon" };
	string y[4] = { "daenerys", "jaime", "jon", "tyrion" };
	string z[10];
	assert(mingle(x, 4, y, 4, z, 10) == 8 && z[5] == "jon");

	assert(divide(h, 7, "jon") == 3);

	cout << "All tests succeeded" << endl;
	
	system("pause");
}
