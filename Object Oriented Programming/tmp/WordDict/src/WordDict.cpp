//============================================================================
// Name        : WordDict.cpp
// Author      : Joshua Wheeler
// Date	       : 4/8/2013
// Description : Read a list of words from file, sort list in alphabetical order and print
//				 list of words in lowercase. User may also add, delete or check words in dictionary
//============================================================================

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
using namespace std;

class wordList {
public:
	wordList() {
		/*silence is golden*/
	}
	;
	void getFilename(); //get the filename
	void storeWordsFromFile(); //put the list of words into the map container
	void doAction(char c); //user selects whether to add, check, delete or show words
	void showMenu();
private:
	map<string, int> wordMap; //stores the list of words
	string curWord;
	void showWords();
	void addWord();
	void deleteWord();
	void checkWord();
	void setCurWord();
};

int main() {
	wordList myDict;
	//Load the Initial Dictionary
	myDict.storeWordsFromFile();
	char option;
	while (option != 'q') {
		myDict.showMenu();
		cin >> option;
		myDict.doAction(option);
	}
	return EXIT_SUCCESS;
}

void wordList::doAction(char c) {
	switch (c) {
	case 'a':
		//add a word
		setCurWord();
		addWord();
		break;
	case 'o':
		//show the word list
		showWords();
		break;
	case 'd':
		//delete a word from the list
		setCurWord();
		deleteWord();
		break;
	case 'c':
		//check if a word exists
		setCurWord();
		checkWord();
		break;
	}
	return;
}

void wordList::addWord() {
	//add the word to the dictionary
	wordMap[curWord]++;
	return;
}

void wordList::deleteWord() {
	wordMap.erase(curWord);
	return;
}

void wordList::checkWord() {
	if(wordMap.count(curWord)) {
		cout << "The word" << curWord << "exists." << endl;
	} else {
		cout << "The word " << curWord << " does not exist" << endl;
	}
	return;
}

void wordList::setCurWord() {
	cout << "Enter the word to perform action on:" << endl;
	cin >> curWord;
}

void wordList::showMenu() {
	cout << "Please choose from on of the following options \n"
			<< "a -> Add a word, o -> Show word list, d -> Delete a word, c -> Check if word exists \n"
			<< "Press q to quit. "
			<< endl;
}

void wordList::showWords() {
	map<string, int>::iterator wordIterator;
	for (wordIterator = wordMap.begin(); wordIterator != wordMap.end();
			wordIterator++) {
		cout << wordIterator->first << endl;
	}
	return;
}

void wordList::storeWordsFromFile() {
	//Get the filename
	string path_to_file;
	cout << "Enter the file path of the text file to read " << endl;
	cin >> path_to_file;
	cout << endl << endl;

	//Open the file
	ifstream txtFile(path_to_file.c_str(), ios::in);

	//Read the file character by character and store as words into vector
	char curChar;
	int curCharASCII;
	string word;
	curChar = txtFile.get();
	if (txtFile.is_open()) {
		while (txtFile.good()) {
			if (txtFile.good()) {
				curCharASCII = (int) curChar;
				if ((curCharASCII >= 48 && curCharASCII <= 57)
						|| (curCharASCII >= 65 && curCharASCII <= 90)
						|| (curCharASCII >= 97 && curCharASCII <= 122)
						|| (curCharASCII == 32) || (curCharASCII == 10)) {
					//The current character is an ascii integer, lowercase letter, uppercase letter, space or newline
					if (curCharASCII >= 65 && curCharASCII <= 90) {
						//current character is in uppercase ASCII range, change curChar to lowercase using ASCII table
						curCharASCII = curCharASCII + 32;
						curChar = (char) curCharASCII;
					}

					if (curCharASCII != 32 && curCharASCII != 10) {
						//Start building a word
						word.append(1, curChar);
					} else {
						if (curCharASCII == 10 || curCharASCII == 32) {
							wordMap[word]++;
						}
						word = "";
					}
				}
			}
			curChar = txtFile.get();
		}
	} else {
		cout << "Could not find file..." << endl;
	}
	txtFile.close();
	return;
}
