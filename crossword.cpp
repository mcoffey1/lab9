// crossword.cpp
// Matthew Coffey
#include<fstream>
#include<vector>
#include<iostream>
#include<cstdlib>
using namespace std;
#include "crossword.h"

Crossword::Crossword(){
	for (int row = 0; row < SIZE; row++){
		for (int col = 0; col < SIZE; col++){
			board[row][col]='.';
		}
	}
}

Crossword::~Crossword(){} //destructor

bool Crossword::addFirstWord(string word, vector<int>& starts){
	int letter = 0;
	for (auto it = word.begin(); it < word.end(); it++){
		board[(SIZE/2)][(SIZE/2)-(word.length()/2)+letter]=*it;
		letter++;
	}
	int startRow = SIZE/2;
	int startCol = (SIZE/2)-(word.length()/2);
	starts.push_back(startRow);
	starts.push_back(startCol);
	starts.push_back(0);
	return true;
}

bool Crossword::addWord(string word, vector<int>& starts){
	bool horz= false;
	bool vert = false;
	bool placed = false;
	int startRow;
	int startCol;
	for (int row = 0; row < SIZE; row++){
		for (int col = 0; col < SIZE; col++){
			for (int i = 0; i < word.length(); i++){
				if (word[i] == board[row][col]){
					if (board[row][col-1] != '.' || board[row][col+1] != '.'){
						if (board[row-1][col] == '.' && board[row+1][col]== '.'){
							if (board[row-i-1][col] == '.' && board[row-i+word.length()][col]){
							for (int p = 0; p < word.length(); p++){
								if (board[row-i+p][col] == '.' && board[row-i+p][col-1] == '.' && board[row-i+p][col+1] == '.' && (row-i+p) >= 0 && (row-i+p)< SIZE){
									board[row-i+p][col] = word[p];
									placed = true;
									vert = true;
								}
								else if (p-i == 0){
									board[row-i+p][col] = word[p];
									placed = true;
									vert = true;
								}
								else{
									vert = false;
									placed = false;
									for (int q = 0; q < p; q++){
										if (q-i != 0){
											board[row-i+q][col] = '.';
										}
									}
									break;
								}	
							}
							}
						}
					}
					else if (board[row-1][col] != '.' || board[row+1][col] != '.'){
						if (board[row][col-i-1] && board[row][col-i+word.length()]){
						if (board[row][col-1] == '.' && board[row][col+1]=='.'){
							for (int p = 0; p < word.length(); p++){
								if (board[row][col-i+p] == '.' && board[row-1][col-i+p]=='.' && board[row+1][col-i+p] == '.' && (col-i+p) >= 0 && (col-i+p) < SIZE){
									board[row][col-i+p] = word[p];
									placed = true;
									horz = true;
								}
								else if (p-i == 0){
									board[row][col-i+p] = word[p];
									placed = true;
									horz = true;
								}
								else{
									horz = false;
									placed = false;
									for (int q = 0; q < p; q++){
										if (q-i != 0){
											board[row][col-i+q] = '.';
										}
									}
									break;
								}
							}
						}
					}
					}
				}
				if (horz){
					startRow = row;
					startCol = col - i;
				}
				else if (vert){
					startRow = row - i;
					startCol = col;
				}
				if (placed)
					break;
			}
			if (placed)
				break;
		}
		if (placed)
			break;
	}
	if (placed){
		starts.push_back(startRow);
		starts.push_back(startCol);
	}
	if (horz && placed){
		starts.push_back(0);
	}
	else if (vert && placed){
		starts.push_back(1);
	}
	return placed;
}

void Crossword::displaySol(){	
	for (int row = 0; row < SIZE; row++){
		for (int col = 0; col < SIZE; col++){
			cout << board[row][col];
		}
		cout<< endl;
	}
}
void Crossword::displaySol(string file){
	ofstream ofs;
	ofs.open(file);
	if (!ofs){
		cout << "Invalid file." << endl;
	}
	else{
		for (int row = 0; row < SIZE; row++){
			for (int col = 0; col < SIZE; col++){
				ofs << board[row][col];
			}
			ofs << endl;
		}
	}
	ofs.close();
}
void Crossword::displayBlank(){
	for (int row = 0; row < SIZE; row++){
		for (int col = 0; col < SIZE; col++){
			if (board[row][col] == '.'){
				cout << "#";
			}
			else
				cout << " ";
		}
		cout << endl;
	}
}
void Crossword::displayBlank(string file){
	ofstream ofs;
	ofs.open(file, ios::app);
	if(!ofs){
		cout << "Invalid file." << endl;
	}
	else{
		for (int row = 0; row < SIZE; row++){
			for (int col = 0; col < SIZE; col++){
				if (board[row][col] == '.'){
					ofs << "#";
				}
				else
					ofs << " ";
			}
			ofs << endl;
		}
	}
	ofs.close();
}

