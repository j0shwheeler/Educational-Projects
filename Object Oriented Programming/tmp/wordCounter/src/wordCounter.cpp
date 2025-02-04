/*
 * main.cpp
 *
 *  Author: Joshua Wheeler
 *  Date: 4/2/2013
 *  Class: CS 140
 *  Description: Count the frequency of each word in a given text file
 */
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

using namespace std;

class WordFrequencyCounter {
public:
	WordFrequencyCounter();
	void readFileWordsToMultiMap(); //reads all the words in the txt file and stores them all lowercased
								  //into a vector without punctuation
	void countWordFrequency(); //count the frequency of words
	void outputWordFrequency(); //console display of word frequency

private:
	map<string, int> wordFrequencyMap;
};

int main() {
	WordFrequencyCounter wordCounter;
	wordCounter.readFileWordsToMultiMap();
	wordCounter.outputWordFrequency();
	return EXIT_SUCCESS;
}

WordFrequencyCounter::WordFrequencyCounter() {
	//silence is golden.
}

void WordFrequencyCounter::readFileWordsToMultiMap() {
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
					//The current character is an ascii integer, lowercase letter, uppercase letter or space
					if (curCharASCII >= 65 && curCharASCII <= 90) {
						//current character is in uppercase ASCII range, change curChar to lowercase using ASCII table
						curCharASCII = curCharASCII + 32;
						curChar = (char) curCharASCII;
					}

					if (curCharASCII != 32 && curCharASCII != 10) {
						//Start building a word
						word.append(1, curChar);
					} else {
						if (curCharASCII != 10) {
							wordFrequencyMap[word]++;
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


void WordFrequencyCounter::outputWordFrequency() {
	map<string, int>::iterator wordIterator;
	for(wordIterator = wordFrequencyMap.begin(); wordIterator !=  wordFrequencyMap.end(); wordIterator++) {
		cout << wordIterator->first << " " << wordIterator->second << endl;
	}
	return;
}
