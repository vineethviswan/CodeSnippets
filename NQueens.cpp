
#include <iostream>
#include <array>
#include <cstdlib>
#include <algorithm>

using namespace std;

class ChessBoard {
public:
	ChessBoard() {
		mSolutionCount = 0;
		mBoardSize = mBoard.size();

		//initialize array to 0
		fill(mBoard.begin(), mBoard.end(), 0);
	}

	void solve();
	void displayBoard();
	int getSolutionCount() { return mSolutionCount; }

private:
	array<int, 4> mBoard;
	int mSolutionCount;
	int mBoardSize;

	void placeQueens(const int &qnCount);
	bool isSafe(const int &row, const int &col);
};

void ChessBoard::solve() {
	placeQueens(0);
}

bool ChessBoard::isSafe(const int &x2, const int &y2) {

	for (int i = 0; i < x2; i++) {
		if ((mBoard[i] == y2) || (abs(static_cast<int>(i - x2)) == abs(static_cast<int>(mBoard[i] - y2))))
			return false;
	}
	return true;
}

void ChessBoard::placeQueens(const int &qnCount) {
	
	if (qnCount == mBoardSize) {
		displayBoard();
		mSolutionCount++;
		return;
	} else {
		for (int col = 0; col < mBoardSize; col++) {
			if (isSafe(qnCount, col)) {
				mBoard[qnCount] = col;
				placeQueens(qnCount + 1);
			}
		}
	}
}

void ChessBoard::displayBoard() {

	for (auto itr : mBoard)
		cout << itr << " ";
	cout << "\n";
}

int main() {

	ChessBoard cbApp;

	cbApp.solve();
	cout << "Number of Solutions - " << cbApp.getSolutionCount();
	//cbApp.displayBoard();

	return 0;
}
