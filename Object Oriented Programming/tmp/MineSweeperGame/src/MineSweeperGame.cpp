//============================================================================
// Name        : Minesweeper.cpp
// Author      : Joshua Wheeler
// Version     : Comsc 140 -> C++
// Date  	   : March 20, 2013
// Description : A Program where the user may input a minesweeper game and then output
// a map of the Minesweeper answer key
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <map>
using namespace std;

class MineSweeper {
public:
	MineSweeper() {
		row_num = 0;
		col_num = 0;
		game_num = 0;
	}; //constructor initializes 0 rows, 0 columns, empty cell set
	void drawGame(); //calculates output from sweeper cell input.
	void setSize();
	int rowPart(int cell_index);
	int colPart(int cell_index); //Calculates rows and cells from array index
	int cellPosition(int row_part, int col_part); //Calculates cell position in array
												  //Rows and Columns are zero based
	void setCells(); //Sets the cells for minesweeper game.
	void run(); //Start running minesweeper games. Game ends on input 0 0 for num rows and cols.
	void newGame(); //Initializes a new game
private:
	int game_num;
	int row_num;
	int col_num; //zero based rows and columns
	vector<char> sweeperCells; //must be either '.' or '*', '.' indicates a safe square,
							   //and a '*' indicates mine
	void incrementAdjacentCells(int mine_ndx, char* sweeperMap);
	void incrementCell(int row_num, int col_num, char* sweeperMap);
};

int main() {
	MineSweeper minesweeper;
	minesweeper.run();
	return 0;
}

void MineSweeper::run() {
	char quit = 'n';
	while(quit-'q'){
		newGame();
		cout << "Do you still wanna play =D? Press q to quit!";
		cin >> quit;
	}
}

void MineSweeper::newGame() {
	game_num++;
	setSize();
	setCells();
	drawGame();
}

void MineSweeper::drawGame() {
	//Assuming size and vector already validly set.
	int numCells = sweeperCells.size();
	char sweeperMap[numCells];

	//Initialize sweeper map be setting all values to zero
	for(int i=0; i<numCells; i++) {
		sweeperMap[i] = '0';
	}

	//Set each cell by checking sweeperCells for mines, if a mine is found, increment
	//every corresponding adjacent cell in the sweeper map by one.
	//If the adjacent square is a mine, do not increment.
	for(int i=0; i<numCells; i++) {
		if(sweeperCells[i] == '*') {
			//The element is a mine, increment the cells around it and draw it on the map
			sweeperMap[i] = '*';
			incrementAdjacentCells(i, sweeperMap);
		}
	}

	cout << "Game " << game_num << endl;

	//Cells are set, Display Output
	for(int cur_row = 0; cur_row<row_num; cur_row++) {
		int cur_col = 0;
		while(cur_col < col_num) {
			int cell_ndx = cellPosition(cur_row, cur_col);
			cout << sweeperMap[cell_ndx] << " ";
			cur_col++;
		}
		cout << endl;
	}
	return;
}

//Increment the top left, top, top right, right, left, bottom left, bottom and bottom right
//cell values adjacent to the current mine position. If the adjacent cell is a mine or out of bounds,
//do not increment
void MineSweeper::incrementAdjacentCells(int mine_ndx, char* sweeperMap) {
	//Set positions
	int mine_row = rowPart(mine_ndx);
	int mine_col = colPart(mine_ndx);
	int top_row = mine_row - 1;
	int bottom_row = mine_row + 1;
	int left_col = mine_col - 1;
	int right_col = mine_col + 1;
	//Increment Top
	incrementCell(top_row, mine_col, sweeperMap);
	//Increment Top Left
	incrementCell(top_row, left_col, sweeperMap);
	//Increment Top Right
	incrementCell(top_row, right_col, sweeperMap);
	//Increment Bottom
	incrementCell(bottom_row, mine_col, sweeperMap);
	//Increment Bottom Left
	incrementCell(bottom_row, left_col, sweeperMap);
	//Increment Bottom Right
	incrementCell(bottom_row, right_col, sweeperMap);
	//Increment Right
	incrementCell(mine_row, right_col, sweeperMap);
	//Increment Left
	incrementCell(mine_row, left_col, sweeperMap);
	return;
}

void MineSweeper::incrementCell(int row_num, int col_num, char* sweeperMap) {
	int cell_ndx = cellPosition(row_num, col_num);
	if(cell_ndx != -1 && sweeperCells[cell_ndx] != '*') {
		//The position is valid and it is not a mine, increment this position
		*(sweeperMap + cell_ndx) = *(sweeperMap + cell_ndx) + 1;
	}
	return;
}

void MineSweeper::setSize() {
	cout
			<< "Please Enter the number of rows and columns for your Minesweeper map"
			<< endl;
	cin >> row_num >> col_num;
	if (row_num > 10 || row_num < 3 || col_num < 3 || col_num > 8) {
		cout << "Input out of range. Please try again. \n"
				<< "Row number must be between 3 and 10, \n"
				<< "Column number must be between 3 and 8" << endl;
		setSize();
	}
	return;
}

void MineSweeper::setCells() {
	if (row_num > 10 || row_num < 3 || col_num < 3 || col_num > 8) {
		//Rows and/or cols out of bounds. Show error, and return
		cout << "Error: Rows and Columns out of bounds!" << endl;
		return;
	} else {
		//Input is valid. Start entering data into cells
		string input_line;
		cout
				<< "Enter your minesweeper map. Press enter to start a new row once the current"
				<< "Row is complete. \n"
				<< "(A '.' defines a safe spot, a '*' defines a mine)" << endl;

		for (int i = 0; i <=row_num; i++) {
			getline(cin, input_line);
			for (unsigned int j = 0; j < input_line.size(); j++) {
				if (input_line[j] == '.' || input_line[j] == '*') {
					//Valid character, store into minesweeper map.
					if(sweeperCells.size() < (row_num*col_num)) {
						//only input character if it does not exceed the map size
						sweeperCells.push_back(input_line[j]);
					}
				}
			}
		}
	}
	return;
}

int MineSweeper::rowPart(int cell_index) {
	//Assuming valid row data
	return (cell_index/(row_num + 1));
}

int MineSweeper::colPart(int cell_index) {
	//Assuming valid col data
	return (cell_index % col_num);
}

int MineSweeper::cellPosition(int row_part, int col_part) {
	if((row_part > row_num) || (row_part < 0) || (col_part < 0) || (col_part > col_num)) {
		return -1; //indicates that there was an error calculating position
	}
	return (row_part * col_num) + col_part;
}
