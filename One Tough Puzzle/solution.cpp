#include <iostream>
#include <vector>
#define MATRIX_SIZE 3
#define NUM_OF_EDGES 4
using namespace std;

enum Direction {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

// Define the four suits
enum Suit {
  SPADE,
  HEART,
  CLUB,
  DIAMOND
};

// Define an interlock
struct Interlock {
  Suit suit;
  bool positive;
};

// Define a puzzle piece
struct Piece {
  int id;
  vector<Interlock> interlocks; //0 -> TOP, 1 -> RIGHT, 2 -> BOTTOM, 3 -> LEFT
  bool isUsed = false;
};

// Check if two interlocks can be connected
bool canConnect(const Interlock& a, const Interlock& b) {
  return a.suit == b.suit && a.positive != b.positive;
}

bool canConnect(const Piece& first, const Piece& second, int directionSecond) {
  if (directionSecond == TOP) {
    return canConnect(first.interlocks[BOTTOM], second.interlocks[TOP]);
  } else if (directionSecond == RIGHT) {
    return canConnect(first.interlocks[LEFT], second.interlocks[RIGHT]);
  } else if (directionSecond == BOTTOM) {
    return canConnect(first.interlocks[TOP], second.interlocks[BOTTOM]);
  }
  return canConnect(first.interlocks[RIGHT], second.interlocks[LEFT]);
}

// Rotate a piece
void rotatePiece(Piece& piece) {
  // Rotate the interlocks
  vector<Interlock> temp(piece.interlocks);
  for (int i = 0; i < piece.interlocks.size(); i++) {
    piece.interlocks[i] = temp[(i + NUM_OF_EDGES - 1) % piece.interlocks.size()];
  }
}

// Try to solve the puzzle
bool solvePuzzle(vector<Piece>& pieces, vector<Piece>& solution) {
  // If the solution is full, we have solved the puzzle
  if (solution.size() == pieces.size()) {
    return true;
  }

  // Try each piece
  for (int i = 0; i < pieces.size(); i++) {
    if (pieces[i].isUsed) continue;
    bool canBeConnected = false;
    Piece currentPiece = pieces[i];
    // Try all rotations of the current piece
    for (int j = 0; j < NUM_OF_EDGES; j++) {
        // Check if the current piece can be connected to the solution
        if (solution.size() == 0) {
            canBeConnected = true;
        } else {
            int nextPos = solution.size() % MATRIX_SIZE;

            if (nextPos == 0) {
                canBeConnected = canConnect(solution[solution.size()-MATRIX_SIZE], currentPiece, TOP);
            } else {
                if (solution.size() < MATRIX_SIZE) {
                    canBeConnected = canConnect(solution[solution.size()-1], currentPiece, LEFT);
                } else {
                    canBeConnected = canConnect(solution[solution.size()-1], currentPiece, LEFT) && canConnect(solution[solution.size()-MATRIX_SIZE], currentPiece, TOP);
                }
            }
        }

        if (canBeConnected) {
            pieces[i].isUsed = true;
            solution.push_back(currentPiece);

            if (solvePuzzle(pieces, solution)) {
                return true;
            } else {
                solution.pop_back();
                pieces[i].isUsed = false;
                canBeConnected = false;
            }
        }

        // Rotate the current piece
        rotatePiece(currentPiece);
    }
    if (canBeConnected) {
        solution.pop_back();
        pieces[i].isUsed = false;
    }
  }
  // No solution was found
  return false;
}

// Print the solution
void printSolution(const vector<Piece>& solution) {
  for (int i = 0; i < solution.size(); i++) {
    cout << "(id=" << solution[i].id << ")  ";
    for (int j = 0; j < solution[i].interlocks.size(); j++) {
      cout << (solution[i].interlocks[j].positive ? "+" : "-") << solution[i].interlocks[j].suit << " ";
    }
    cout << endl;
  }
}

int main() {
    #if 1
    vector<Piece> pieces = {
        {1, {Interlock{SPADE, true}, Interlock{HEART, true}, Interlock{CLUB, false}, Interlock{SPADE, false}}},
        {2, {Interlock{SPADE, false}, Interlock{HEART, false}, Interlock{CLUB, true}, Interlock{HEART, true}}},
        {3, {Interlock{DIAMOND, true}, Interlock{HEART, true}, Interlock{HEART, false}, Interlock{DIAMOND, false}}},
        {4, {Interlock{CLUB, true}, Interlock{CLUB, false}, Interlock{HEART, true}, Interlock{DIAMOND, false}}},
        {5, {Interlock{HEART, false}, Interlock{DIAMOND, false}, Interlock{SPADE, true}, Interlock{DIAMOND, false}}},
        {6, {Interlock{DIAMOND, false}, Interlock{CLUB, true}, Interlock{CLUB, false}, Interlock{HEART, true}}},
        {7, {Interlock{CLUB, false}, Interlock{DIAMOND, false}, Interlock{DIAMOND, true}, Interlock{CLUB, false}}},
        {8, {Interlock{HEART, true}, Interlock{CLUB, false}, Interlock{SPADE, false}, Interlock{SPADE, true}}},
        {9, {Interlock{SPADE, true}, Interlock{HEART, false}, Interlock{SPADE, false}, Interlock{DIAMOND, true}}}
    };
    #endif

    #if 0
    vector<Piece> pieces = {
        {1, {Interlock{DIAMOND, true}, Interlock{DIAMOND, false}, Interlock{CLUB, false}, Interlock{CLUB, true}}},
        {2, {Interlock{SPADE, true}, Interlock{DIAMOND, false}, Interlock{HEART, false}, Interlock{DIAMOND, true}}},
        {3, {Interlock{CLUB, true}, Interlock{HEART, false}, Interlock{SPADE, false}, Interlock{HEART, true}}},
        {4, {Interlock{HEART, true}, Interlock{CLUB, false}, Interlock{CLUB, false}, Interlock{DIAMOND, true}}},
        {5, {Interlock{CLUB, true}, Interlock{CLUB, false}, Interlock{DIAMOND, false}, Interlock{HEART, true}}},
        {6, {Interlock{SPADE, true}, Interlock{CLUB, false}, Interlock{HEART, false}, Interlock{SPADE, true}}},
        {7, {Interlock{HEART, true}, Interlock{HEART, false}, Interlock{DIAMOND, false}, Interlock{DIAMOND, true}}},
        {8, {Interlock{HEART, true}, Interlock{CLUB, false}, Interlock{SPADE, false}, Interlock{SPADE, true}}},
        {9, {Interlock{SPADE, true}, Interlock{HEART, false}, Interlock{SPADE, false}, Interlock{DIAMOND, true}}}
    };
    #endif

    vector<Piece> solution;
    if (solvePuzzle(pieces, solution)) {
        cout << "solution found\n";
        printSolution(solution);
    } else {
        cout << "solution not found(" << solution.size() << ")" << endl;
    }
    return 0;
}
