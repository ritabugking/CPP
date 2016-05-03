#include <iostream>
#include <string>

using namespace std;

int main() {
	double marketValue;
	double tax = 0;
	int round_tax = 0;
	string identification;
	string state;

	//collect data and save them in variables
	cout << "Market value (in millions): ";
	cin >> marketValue;
	cin.ignore(10000, '\n');

	// to check if the input of market value is valid
	if (marketValue < 0) {
		cout << "---\n";
		cout << "The market value must be nonnegative.";
		return 1;
	}

	cout << "Identification: ";
	getline(cin, identification);

	// to check if the input of identification is valid
	if (identification == "") {
		cout << "---\n";
		cout << "You must enter a property identification.";
		return 1;
	}

	cout << "State: ";
	getline(cin, state);

	// to check if the input of state is valid
	if (state == "") {
		cout << "---\n";
		cout << "You must enter a state.";
		return 1;
	}

	cout << "---\n";

	// to calculate the value of tax from market value and location of property
	if (marketValue <= 200) {
		tax = marketValue*4.1 / 100;
	}

	else if (marketValue <= 500) {
		if (state == "NJ" || state == "NY") {
			tax = 200 * 4.1 / 100 + (marketValue - 200)*5.7 / 100;
		}
		else {
			tax = 200 * 4.1 / 100 + (marketValue - 200)*5.3 / 100;
		}
	}

	else {
		if (state == "NJ" || state == "NY") {
			tax = 200 * 4.1 / 100 + 300 * 5.7 / 100 + (marketValue - 500) * 6 / 100;
		}
		else {
			tax = 200 * 4.1 / 100 + 300 * 5.3 / 100 + (marketValue - 500) * 6 / 100;
		}
	}

	cout.setf(ios::fixed);  // set the decimal point to exactly three
	cout.precision(3);


	cout << "The tax for " << identification << " is $" << tax << " million.\n";

}