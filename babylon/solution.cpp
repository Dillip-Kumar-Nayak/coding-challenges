#include <iostream>
#include <list>
#include <string>
#include <climits>

bool canCombine(const std::string& stack1, const std::string& stack2) {
    return (stack1.back() == stack2.back() || stack1.size() == stack2.size());
}

bool isGameOver(const std::list<std::string>& tiles) {
    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        auto next_it = std::next(it);
        if (next_it != tiles.end() && canCombine(*it, *next_it)) {
            return false; // There's a valid move
        }
    }
    return true; // No valid move found
}

int evaluate(const std::list<std::string>& tiles) {
    return isGameOver(tiles) ? (tiles.size() % 2 == 0 ? 1 : -1) : 0;
}

int minimax(std::list<std::string> tiles, int depth, int alpha, int beta, bool maximizingPlayer) {
    if (depth == 0 || isGameOver(tiles)) {
        return evaluate(tiles);
    }

    int bestValue = maximizingPlayer ? INT_MIN : INT_MAX;

    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        auto next_it = std::next(it);
        if (next_it != tiles.end() && canCombine(*it, *next_it)) {
            tiles.insert(it, *it + *next_it);
            it = tiles.erase(it);
            it = tiles.erase(it);

            int value = minimax(tiles, depth - 1, alpha, beta, !maximizingPlayer);

            if (maximizingPlayer) {
                bestValue = std::max(bestValue, value);
                alpha = std::max(alpha, value);
            } else {
                bestValue = std::min(bestValue, value);
                beta = std::min(beta, value);
            }

            if (beta <= alpha) {
                break; // Alpha-beta pruning
            }
        }
    }

    return bestValue;
}

bool playBabylon(std::list<std::string> tiles) {
    int bestMove = INT_MIN;

    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        auto next_it = std::next(it);
        if (next_it != tiles.end() && canCombine(*it, *next_it)) {
            tiles.insert(it, *it + *next_it);
            it = tiles.erase(it);
            it = tiles.erase(it);

            int moveValue = minimax(tiles, 3, INT_MIN, INT_MAX, false);

            bestMove = std::max(bestMove, moveValue);
        }
    }

    return (bestMove >= 0); // If the best move has a positive evaluation, the first player wins
}

int main() {
    //std::list<std::string> tiles = {"A", "B", "C", "D", "A", "B", "C", "D", "A", "B", "C", "D"};
    //std::list<std::string> tiles = {"W", "G", "GW"};
    //std::list<std::string> tiles = {"WW", "G", "G"};
    std::list<std::string> tiles = {"W", "G", "G", "W"};

    bool firstPlayerWins = playBabylon(tiles);

    if (firstPlayerWins) {
        std::cout << "The first player wins!" << std::endl;
    } else {
        std::cout << "The second player wins!" << std::endl;
    }

    return 0;
}

