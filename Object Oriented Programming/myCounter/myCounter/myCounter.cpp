/*
 * myCounter.cpp
 *
 *  Created on: Mar 4, 2013
 *  Author: Joshua Wheeler
 *  Date: 03/04/2013
 */

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/*
 * oldiesCounter
 */
class oldiesCounter {
//Everything necessary to use the object
public:
	oldiesCounter(); //Done
	oldiesCounter(int max_count_value); //Done
	//Start the program, Interface with user.
	void run() {
		cout << "Hello World!";
	}

//Everything necessary to define the object
private:
	//Define Private Properties
	int max_count_value;
	int current_value;
	int total_count;
	int current_exponent;

	//Define Private Behavior
	int increment(); //Done
	int incr1(); //Done
	int incr10(); //Done
	int incr100(); //Done
	int incr1000(); //Done
	bool overflow(); //Done. Check Total  value against max value.
	char getKey(); //Done
	void setKey(char keyMnemonic); //Done
	void displayMenu(); //Done
	int getValue();  //Done
	void setValue(int value); //Done
	int calcTotal(); //Done
};

/*
 * main() - Tests the myCounter Interface
 */
int main() {
	cout << "Hello World!!";
	return 0;
}

/*
 * oldiesCounter Obj
 * Class Constructors
 */
oldiesCounter::oldiesCounter() {
	//Max count value is 9999
	this->max_count_value = 9999;
	this->current_value = 0;
	this->total_count = 0;
	this->current_exponent = 0;
}

oldiesCounter::oldiesCounter(int maxValue) {
	this->max_count_value = maxValue;
	this->current_value = 0;
	this->total_count = 0;
	this->current_exponent = 0;
}

/*
 * oldiesCounter Obj
 * DisplayMenu() - Show the selection options
 */
void oldiesCounter::displayMenu() {
	cout
			<< "Enter a key, either a, s, d, f, followed by 1-9. or o for overflow\n"
			<< "a -> cents, s-> dimes, d->dollars, f->tens of dollars" << endl;
}

/* TO BE DONE
 * GetKey - Return a character a, s, d, f, o
 * a - cents
 * s - dimes
 * d - dollars
 * f - tens of dollars
 * o - set overflow flag
 */
char oldiesCounter::getKey() {
	//Tip for this input trick found on http://www.cplusplus.com/forum/articles/6046/
	char myChar = { 0 }; //Set character in buffer to a null character on default
	string input = ""; //Input from a string is safer for the user

	while (true) {
		getline(cin, input);
		if (input.length() == 1) {
			myChar = input[0];
			break;
		}
		cout << "Invalid character: Must be a,s,d,f,o" << endl;
	}

	return 's'; //Return dummy value for testing
	//return myChar;
}

/*
 * Updates class variable with the power of digit to raise when incrementing. (setting the key)
 * 1 - incr1
 * 2 - incr10
 * 3 - incr100
 * 4 - incr1000
 */
void oldiesCounter::setKey(char keyMnemonic) {
	switch (keyMnemonic) {
	case 'a':
		this->current_exponent = 1;
		break;
	case 's':
		this->current_exponent = 2;
		break;
	case 'd':
		this->current_exponent = 3;
		break;
	case 'f':
		this->current_exponent = 4;
		break;
	case 'o':
		this->overflow();
		break;
	default:
		cout
				<< "Error Setting Key: Input must be either a,s,d,f,o! Set it right, I believe in you!!!"
				<< endl;
		break;
	}
}

/* To Be Done: Gets value from user input after key is selected */
int oldiesCounter::getValue() {
	int myNumber = 0;
	string input = "";
	while (true) {
		getline(cin, input);

		stringstream myStream(input);
		if ((myStream >> myNumber) && (myNumber <= 9) && (myNumber >= 0))
			break;
		cout << "Invalid input: Number must be in range 0-9" << endl;
	}
	return 3; //Dummy input value for now
	//return myNumber;
}

/* Sets the value of 0 to 9 */
void oldiesCounter::setValue(int value) {
	if ((value < 0) || (value > 9)) {
		cout << "Error: Value out of range" << endl;
	} else {
		this->current_value = value * increment();
	}
}

/* Sets the overflow */
bool oldiesCounter::overflow() {
	if (this->calcTotal() > this->max_count_value) {
		return true;
	} else {
		return false;
	}
}

/* Updates the total count */
int oldiesCounter::calcTotal() {
	this->total_count = this->total_count + this->current_value;
	return total_count;
}

/* Increment 1's, 10's, 100's, or 1000's place */
int oldiesCounter::increment() {
	switch (this->current_exponent) {
	case 1:
		return incr1();
		break;
	case 2:
		return incr10();
		break;
	case 3:
		return incr100();
		break;
	case 4:
		return incr1000();
		break;
	default:
		cout << "Exponent Error: Power exceeds maximum range";
		return 0;
		break;
	}
	return 0;
}

//Increment Functions for a,s,f, d, f
int oldiesCounter::incr1() {
	return 1;
}

int oldiesCounter::incr10() {
	return 10;
}

int oldiesCounter::incr100() {
	return 100;
}

int oldiesCounter::incr1000() {
	return 1000;
}
