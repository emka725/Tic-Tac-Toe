#include <iostream>

//  The 3x3 tic-tac-toe grid
char grid[3][3];
//  Determines the player who is currently moving
bool playerXTurn = true;

//  Prints the specified row of the grid
void printRow(char (&grid)[3][3], int r) {
  std::cout << grid[r][0] << "|" << grid[r][1] << "|" << grid[r][2] << std::endl;
}

//  Prints a grid row divider
void printDivider() {
  std::cout << "-+-+-" << std::endl;
}

//  Prints the entire grid
void printGrid() {
  printRow(grid, 0);
  printDivider();
  printRow(grid, 1);
  printDivider();
  printRow(grid, 2);
}

//  Determines if the specified player has won the game, given the tic-tac-toe grid
bool hasWon(char p, char (&grid)[3][3]) {
  //  Iterates through rows/columns of the grid simultaneously
  for (int i = 0; i < 3; i++) {
    //  Checks if the i'th row is filled by p
    if (grid[i][0] == p && grid[i][1] == p && grid[i][2] == p) return true;
    //  Checks if the i'th column is filled by p
    if (grid[0][i] == p && grid[1][i] == p && grid[2][i] == p) return true;
  }
  //  Checks if the diagonals are filled by p
  if (grid[0][0] == p && grid[1][1] == p && grid[2][2] == p) return true;
  if (grid[0][2] == p && grid[1][1] == p && grid[2][0] == p) return true;
  //  Otherwise, return false
  return false;
}

int main() {
  std::cout << "To move, enter an unclaimed grid position number (0-8)" << std::endl << std::endl;

  //  Initializes the grid with position values and prints it afterwards
  for (int i = 0; i < 9; i++) {
    int x = i % 3;
    int y = i / 3;
    grid[y][x] = i + 48;
  }
  printGrid();

  //  Game continues until 9 moves have been performed
  for (int numMoves = 0; numMoves < 9; numMoves++) {
    //  Computes the current player's character marker
    char playerChar = playerXTurn ? 'X' : 'O';

    //  Reads in the player's move and checks if input is valid
    int move;
    std::cout << std::endl << "Enter Player " << playerChar << "'s move: ";
    while (true) {
      //  Checks if input was an integer, ignores if not
      if (std::cin >> move) {
        //  Ignores input if not in the range [0, 8]
        if (move < 0 || move > 8) continue;
        //  Ignores input if grid position is already occupied
        char &gridChar = grid[move / 3][move % 3];
        if (gridChar == 'X' || gridChar == 'O') continue;
        //  If all checks have passed, overwrite the specified grid character with the player's character marker
        gridChar = playerChar;
        break;
      } else {
        std::cin.clear();
        std::cin.ignore();
      }
    }

    //  Prints the grid to show most recent move
    std::cout << std::endl;
    printGrid();

    //  If the player has won, print an appropriate message and terminate the program
    if (hasWon(playerChar, grid)) {
      std::cout << std::endl << "Game result: Player " << playerChar << " victory" << std::endl;
      return 0;
    }

    //  Update the current player variable
    playerXTurn = !playerXTurn;
  }
  
  //  If all 9 grid positions have been overwritten and nobody has yet won, the game ends in a draw
  std::cout << std::endl << "Game result: Draw" << std::endl;
  return 0;
}