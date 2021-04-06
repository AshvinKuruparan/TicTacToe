//TIC-TAC-TOE [game]

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 3;

void displayBoard(string b[][SIZE]);
bool userFirst();
bool currentPlayerWon(string b[][SIZE], string symbol);
void generateComputerMove(string board[SIZE][SIZE],int row, int col);

int main() {
  //construct board
  string board[SIZE][SIZE];

  int position_id = 1;
  for (int i=0; i< SIZE; i++) {
    for (int j=0; j < SIZE; j++) {
        board[i][j] = to_string(position_id);
      /*  stringstream ss;
        ss << position_id;
        board[i][j] = ss.str();
        */position_id++;
    }
  }

  //Initial game output
  cout << "Welcome to Tic-Tac-Toe" << endl;

  bool userTurn = userFirst();
  if (userTurn == true) {
    cout << "Player goes first!" << endl;
  } else {
    cout << "Computer goes first!" << endl;
  }

  //Loop for turn taking in game
  int positionsRemaining = SIZE * SIZE;
  bool userWon = false;
  bool computerWon = false;

  while ((positionsRemaining > 0)
        && (!userWon) && (!computerWon)) {
      displayBoard(board);

      //User's turn
      if (userTurn) {
        bool validMove = false;
        while (!validMove) {
          int position_id;
          cout << "Enter a position: ";
          cin >> position_id;
          if ((position_id <= (SIZE*SIZE))
              && (position_id > 0)) {
            int row = (position_id-1)/SIZE;
            int col = (position_id-1)%SIZE;
            //cout << "row = " << row << " col = " << col << endl;
            if ((board[row][col] != "X")
                && (board[row][col] != "O")) {
                  board[row][col] = "X";
                  validMove = true;
            } else {
              cout << "Position already used. Try again." << endl;
            }

          } else {
            cout << "Position invalid. Try again." << endl;
          }
        }
        positionsRemaining--;
        userWon = currentPlayerWon(board, "X");
        userTurn = false;
      }

      //Computer's turn
      else {
        int row, col;
        generateComputerMove(board, row, col);
        //board[row][col] = "O";
        positionsRemaining--;
        computerWon = currentPlayerWon(board, "O");
        userTurn = true;
      }
  }

  //Display game result
  displayBoard(board);
  if (userWon) {
    cout << "Congratulations! You have won!" << endl;
  } else if (computerWon) {
    cout << "The computer has won. Try again." << endl;
  } else {
    cout << "Out of moves. Try again." << endl;
  }
  return 0;
}




void displayBoard(string b[][SIZE]) {
  cout << "Tic-tac-toe board:" << endl << endl;
  for (int i=0; i< SIZE; i++) {
    for (int j=0; j < SIZE; j++) {
        cout << b[i][j] << "\t";
    }
    cout << endl;
  }
  cout << endl;
}

bool userFirst() {
  //set seed for random number generation
  srand(time(NULL));

  //generate a random number
  //0 for computer
  //1 for user
  int num = rand()%2;
  if (num == 0) {
    return false;
  }
  return true;
}

//Return true if player/computer with symbol (X or O) has won
bool currentPlayerWon(string b[][SIZE], string symbol) {
  //Horizontal case
  //Loop through each row
  for (int i=0; i < SIZE; i++) {
    bool rowWinDetected = true;
    //Check all positions in row and see if they are the same symbol
    for (int j = 0; j < SIZE; j++) {
      if (b[i][j] != symbol) {
        rowWinDetected = false;
      }
    }
    if (rowWinDetected) {
      return true;
    }
  }

  //Vertical case
  //Loop through each column
  for (int i=0; i < SIZE; i++) {
    bool colWinDetected = true;
    //Check all positions in column and see if they are the same symbol
    for (int j = 0; j < SIZE; j++) {
      if (b[j][i] != symbol) {
        colWinDetected = false;
      }
    }
    if (colWinDetected) {
      return true;
    }
  }

  //Diagonal case #1
  bool diagonal1WinDetected = true;
  for (int i=0; i < SIZE; i++) {
    if (b[i][i] != symbol) {
      diagonal1WinDetected = false;
    }
  }
  if (diagonal1WinDetected) {
    return true;
  }

  //Diagonal case #2
  bool diagonal2WinDetected = true;
  for (int i=0; i < SIZE; i++) {
    if (b[(SIZE-1)-i][i] != symbol) {
      diagonal2WinDetected = false;
    }
  }
  if (diagonal2WinDetected) {
    return true;
  }

  //otherwise win not diagonal2WinDetected
  return false;

}

void generateComputerMove(string board[SIZE][SIZE],int row, int col){
  bool validMove = false;

  //Loops until the best move can be made
  while (!validMove) {
    //Loop checks if the computer can win this move
    for (int y = 0; y < SIZE; y++){
      for (int x = 0; x < SIZE; x++){
        //Checks if the spot is already filled
        if ((board[y][x] != "X")&& (board[y][x] != "O")){
          string hold = board[y][x];
          board[y][x] = "O";

          //Checks if the computer will win
          if(currentPlayerWon(board, "O")){
            row = y;
            col = x;
            board[y][x] = "O";
            validMove = true;
            break;
          }
          else{
            board[y][x] = hold;
          }
        }
      }
    }

    //Loop checks if the computer can stop the user from winning 
    for (int y = 0; y < SIZE; y++){
      for (int x = 0; x < SIZE; x++){
        //Checks if the spot is already filled
        if ((board[y][x] != "X")&& (board[y][x] != "O")){
          string hold = board[y][x];
          board[y][x] = "X";

          //Checks if the spot would let the player win
          if(currentPlayerWon(board, "X")){
            board[y][x] = "O";
            validMove = true;
            break;
          }
          else{
            board[y][x] = hold;
          }

        }
      }
    }

    //Check a random spot and place an O there
    if(!validMove){
      row = rand()%SIZE;
      col = rand()%SIZE;
      if ((board[row][col] != "X")&& (board[row][col] != "O")) {
        board[row][col] = "O";
        validMove = true;
      }
    }
  }
}