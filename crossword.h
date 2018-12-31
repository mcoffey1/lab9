// crossword.h
// Matthew Coffey

const int SIZE = 15;
class Crossword{
	public:
		Crossword();
		~Crossword();
		bool addFirstWord(string, vector<int>&);
		bool addWord(string, vector<int>&);
		void displaySol();
		void displayBlank();
		void displaySol(string);
		void displayBlank(string);
	private:
		char board[SIZE][SIZE];
};
