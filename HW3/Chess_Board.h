#ifndef _chess_board_dac
#define _chess_board_dac

#include <iostream>
#include <ostream>

using namespace std;


class Chess_Board {
    friend ostream& operator<<(ostream& output, const Chess_Board& CB);
    // needs to be a friend to look at internal data...
  public:
    Chess_Board (int N);//
    bool goodMove(int i, int j); // Row i, col j is free from capture from existing queens
    void AddQueen(int i, int j); // add queen at (i,j)
    void RemoveQueen(int i, int j); // remove queen at (i,j)
    int getSize();
    void ClearBoard();
    void Solve() {
        DFS(0);
    }

  private:
    const static int Nmax = 50;
    int Nsize;
    int A[Nmax][Nmax]; // 0 where there are no queens, 1 where there are queens
    bool DFS(int row);
};

Chess_Board::Chess_Board(int N) { // no queens to start
    if (N > Nmax) {
        cout << "Too big of a board " << endl;
        exit(1);
    }
    Nsize = N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 0;
        }
    }
}

bool Chess_Board::DFS(int row) { // Add queen to row...
    bool found = false;
    int NN = getSize();
    //
    //This is the key function you need to write, which does DFS row by row looking for a placement
    // where previous queens cannot capture the current position.
    // This will use the goodMove function to check whether a queen position can be captured by
    // queens on the board in previous rows.
    //
    //
    if (row >= getSize()) return true;

    else {
        for (int col = 0; col < getSize(); col++) {
            if(goodMove(row, col)) {
                AddQueen(row, col);
                if(DFS(row + 1)) return true;
                else RemoveQueen(row, col);
            }
        }
    }
    return found;
}

void Chess_Board::AddQueen(int i, int j) {
    A[i][j] = 1;
}

void Chess_Board::RemoveQueen(int i, int j) {
    A[i][j] = 0;
}

bool Chess_Board::goodMove(int irow, int jcol) { // square is not captured by queens...
    int row, col, min;
    //
    //  This is the other function you have to create.  It checks whether the square in row irow, column
    //  jcol can be captured by the existing queens on the board in rows 0 .. irow-1.
    //
    //
    // check column above since lower checks are implicit in future
    for(int i = 0; i < irow; i++) {
        if(A[i][jcol] == 1) return false;
    }
    // check upper-right of diagonal since lower-left checks are implicit in future
    int j = jcol;
    for(int i = irow; i > -1; i--) {
        if(A[i][j] == 1) return false;
        j--;
        if(j < 0) break;
    }
    // check upper-left of diagonal since lower right checks are implicit in future
    j = jcol;
    for(int i = irow; i > -1; i--) {
        if(A[i][j] == 1) return false;
        j++;
        if(j >= getSize()) break;
    }
    // good to place
    return true;
}

int Chess_Board::getSize() {
    return Nsize;
}

void Chess_Board::ClearBoard() {
    for (int i = 0; i < Nsize; i++)
        for (int j = 0; j < Nsize; j++)
            A[i][j] = 0;
}

ostream& operator<<(ostream& output, const Chess_Board& CB) {

    for (int i = 0; i < CB.Nsize; i++) {
        for (int j = 0; j < CB.Nsize; j++) {
            output << " " << CB.A[i][j] ;
        }
        output << endl;
    }
    return output;
}

#endif