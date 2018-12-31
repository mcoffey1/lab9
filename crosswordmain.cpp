//crosswordmain.cpp
//Matthew Coffey
#include<string>
#include<vector>
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
#include "crossword.h"

void displayVec(vector<int>);
void displayClues(vector<int>, vector<string>&, vector<bool>);
int checkString(string&);
vector<string> sortStrings(string, vector<string>&);
vector<string> readStrings();
vector<string> readFile(string);
void outputFile(string, vector<int>, vector<string>&, vector<bool>);

int main (int argc, char* argv[]){
	if (argc > 3){
		cout << "Invalid arguments. Program failed." << endl;
		return 1;
	}
	vector<string> words;
	if (argc == 1){
		words = readStrings();
	}
	else if (argc == 2 || argc == 3){
		words = readFile(argv[1]);
	}	
	vector<int> starts;
	vector<bool> placed;
	Crossword board;
	placed.push_back(board.addFirstWord(words[0], starts));
	for (int i = 1; i < words.size(); i++){
		placed.push_back(board.addWord(words[i], starts));
	}
	if (argc == 1 || argc == 2){
		board.displaySol();
		board.displayBlank();
		displayClues(starts, words, placed);
	}
	else if (argc == 3){
		board.displaySol(argv[2]);
		board.displayBlank(argv[2]);
		outputFile(argv[2], starts, words, placed);
		
	}
	return 0;
}
void displayClues(vector<int> starts, vector<string>& words, vector<bool> placed){
	bool wordUsed = false;
	int wordIndex = 0;
	for (int it = 0; it < starts.size(); it++){
		wordUsed = false;
		cout << starts[it] << ", ";
		it++;
		cout << starts[it] << " ";
		it++;
		if (starts[it] == 0)
			cout << "ACROSS  ";
		else
			cout << "DOWN  ";
		while (!(wordUsed)){
			if (placed[wordIndex]){
				random_shuffle((words[wordIndex]).begin(), (words[wordIndex]).end());
				cout << words[wordIndex]<< endl;
				wordUsed = true;
				wordIndex++;
			}
			else {	
				wordIndex++;
			}
		}
	}

}
int checkString(string& str){
	for (auto it = str.begin(); it < str.end(); it++){
		*it=toupper(*it);
		if (!(*it <= 'Z' && *it >= 'A') || str.length() < 2 && str.length() > SIZE){
			cout << "Invalid string starting next phase: " << str << endl;
			return 1;
			break;
		}
	}
	return 0;
}
vector<string> sortStrings (string str, vector<string>& vec){
	bool inserted = false;
	for (auto it=vec.begin();  it < vec.end(); it++){
		if (str.length() > (*it).length()){
			vec.insert(it, str);
			inserted = true;
			break;
		}
	}
	if (!inserted){
		vec.push_back(str);
	}
	return vec;
}
vector<string> readStrings (){
	string str;
	vector<string> vec;
	cin >> str;
	if(checkString(str)==0){
		vec.push_back(str);
	}
	while (str.compare(".") != 0){
		cin >> str;
		if (checkString(str) == 0){
			sortStrings(str, vec);
		}
		if (vec.size() > 20){
			cout << "Too many elements. Using only the first 20." << endl;
		}
	}
	return vec;
}
	
vector<string> readFile(string fileName){
	string str;
	vector<string> vec;
	ifstream ifs;
	ifs.open(fileName);
	if (!ifs){
		cout << "Invalid file" << endl;
		return vec;
	}
	ifs >> str;
	while (str.compare(".") != 0){
		ifs >> str;
		if (checkString(str) == 0){
			sortStrings(str, vec);
		}
		if (vec.size() > 20){
			cout<< "Too many elements. Using only the first 20." << endl;
		}
	}
	return vec;
}
void outputFile(string fileName, vector<int> starts, vector<string>& words, vector<bool> placed){
	ofstream ofs;
	ofs.open(fileName, ios::app);
	bool wordUsed = false;
	int wordIndex = 0;
	for (int it = 0; it < starts.size(); it++){
		wordUsed = false;
		ofs << starts[it] << ", ";
		it++;
		ofs << starts[it] << " ";
		it++;
		if (starts[it] == 0)
			ofs << "ACROSS  ";
		else
			ofs << "DOWN  ";
		while (!(wordUsed)){
			if (placed[wordIndex]){
				random_shuffle((words[wordIndex]).begin(), (words[wordIndex]).end());
				ofs << words[wordIndex]<< endl;
				wordUsed = true;
				wordIndex++;
			}
			else {	
				wordIndex++;
			}
		}
	}

}			
