#include "Board.h"
#include "Define.h"
#include <fstream>
#include <functional>

int valueList[ROW][COL] = {{90,  -60, 10, 10, 10, 10, -60, 90},
                           {-60, -80, 5,  5,  5,  5,  -80, -60},
                           {10,  5,   1,  1,  1,  1,  5,   10},
                           {10,  5,   1,  1,  1,  1,  5,   10},
                           {10,  5,   1,  1,  1,  1,  5,   10},
                           {10,  5,   1,  1,  1,  1,  5,   10},
                           {-60, -80, 5,  5,  5,  5,  -80, -60},
                           {90,  -60, 10, 10, 10, 10, -60, 90}};

namespace std {
    template<>
    struct hash<Board> {
        size_t operator()(const Board &board) const {
            size_t seed = 0;
            for (int i = 0; i < ROW; i++)
                for (int j = 0; j < COL; j++) {
                    std::__hash_combine(seed, hash<bool>()(board.at(i, j).valid));
                    std::__hash_combine(seed, hash<bool>()(board.at(i, j).occupy));
                    int color = 1;
                    if (board.at(i, j).chessman.color == black)
                        color = 0;
                    std::__hash_combine(seed, hash<int>()(color));
                }
            return seed;
        }
    };
}


unordered_map<Board, std::pair<int, int>> transportationTable;

bool Board::isPossible(int row, int col, int color) {
    if (board[row][col].occupy || !board[row][col].valid)
        return false;
    return isFlippable(row, col, color, false);
}

bool Board::isFlippable(int row, int col, int color, bool flip) {
    // @param: flip -> true for flip, false for only detect flippable
    Color opponent;
    if (color == 1)
        opponent = white;
    else
        opponent = black;
    // search for up
    for (int i = row - 1; i >= 0; i--) {
        if (!board[i][col].occupy)
            break;
        if (board[i][col].chessman.color == opponent) {
            // find the first chessman that has the same color
            // flip all the chessman in between
            if (!flip && i != row - 1)
                return true;
            if (flip)
                for (int j = row - 1; j > i; j--)
                    board[j][col].chessman.flip();
            break;
        }
    }
    // search for down
    for (int i = row + 1; i < ROW; i++) {
        if (!board[i][col].occupy)
            break; // find empty point
        if (board[i][col].chessman.color == opponent) {
            if (!flip && i != row + 1)
                return true;
            if (flip)
                for (int j = row + 1; j < i; j++)
                    board[j][col].chessman.flip();
            break;
        }
    }
    // search for left
    for (int i = col - 1; i >= 0; i--) {
        if (!board[row][i].occupy)
            break;
        if (board[row][i].chessman.color == opponent) {
            if (!flip && i != col - 1)
                return true;
            if (flip)
                for (int j = col - 1; j > i; j--)
                    board[row][j].chessman.flip();
            break;
        }
    }
    // search for right
    for (int i = col + 1; i < COL; i++) {
        if (!board[row][i].occupy)
            break;
        if (board[row][i].chessman.color == opponent) {
            if (!flip && i != col + 1)
                return true;
            if (flip)
                for (int j = col + 1; j < i; j++)
                    board[row][j].chessman.flip();
            break;
        }
    }
    // search for diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (!board[i][j].occupy)
            break;
        if (board[i][j].chessman.color == opponent) {
            if (!flip && i != row - 1)
                return true;
            if (flip)
                for (int m = row - 1, n = col - 1; m > i && n > j; m--, n--)
                    board[m][n].chessman.flip();
            break;
        }
    }
    for (int i = row + 1, j = col + 1; i < ROW && j < COL; i++, j++) {
        if (!board[i][j].occupy)
            break;
        if (board[i][j].chessman.color == opponent) {
            if (!flip && i != row + 1)
                return true;
            if (flip)
                for (int m = row + 1, n = col + 1; m < i && n < j; m++, n++)
                    board[m][n].chessman.flip();
            break;
        }
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j < COL; i--, j++) {
        if (!board[i][j].occupy)
            break;
        if (board[i][j].chessman.color == opponent) {
            if (!flip && i != row - 1)
                return true;
            if (flip)
                for (int m = row - 1, n = col + 1; m > i && n < j; m--, n++)
                    board[m][n].chessman.flip();
            break;
        }
    }
    for (int i = row + 1, j = col - 1; i < ROW && j >= 0; i++, j--) {
        if (!board[i][j].occupy)
            break;
        if (board[i][j].chessman.color == opponent) {
            if (!flip && i != row + 1)
                return true;
            if (flip)
                for (int m = row + 1, n = col - 1; m < i && n > j; m++, n--)
                    board[m][n].chessman.flip();
            break;
        }
    }
    return false;
}

Board::Board() {
    roundCount = 0;
    board[3][3].occupy = true;
    board[3][3].chessman.setColor(0);
    board[3][4].occupy = true;
    board[3][4].chessman.setColor(1);
    board[4][3].occupy = true;
    board[4][3].chessman.setColor(1);
    board[4][4].occupy = true;
    board[4][4].chessman.setColor(0);
}

Board::Board(const Board &thatBoard) {
    roundCount = thatBoard.roundCount;
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            board[i][j] = thatBoard.board[i][j];
}

void Board::clear() {
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++) {
            board[i][j].valid = true;
            board[i][j].occupy = false;
            board[i][j].chessman.color = null;
        }
    board[3][3].occupy = true;
    board[3][3].chessman.setColor(0);
    board[3][4].occupy = true;
    board[3][4].chessman.setColor(1);
    board[4][3].occupy = true;
    board[4][3].chessman.setColor(1);
    board[4][4].occupy = true;
    board[4][4].chessman.setColor(0);
    transportationTable.clear();
    roundCount = 0;
}

void Board::clearRestricted() {
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            if (!board[i][j].valid)
                board[i][j].valid = true;
}

void Board::setRestricted(int row, int col) {
    if (row < 7)
        board[row + 1][col].valid = false;
    if (row > 0)
        board[row - 1][col].valid = false;
    if (col < 7)
        board[row][col + 1].valid = false;
    if (col > 0)
        board[row][col - 1].valid = false;
}

void Board::placeChessman(int row, int col, int color) {
    if (row == -1 && col == -1) {
        clearRestricted();
        return;
    }
    board[row][col].placeHere(color);
    clearRestricted();
    setRestricted(row, col);
    isFlippable(row, col, color, true);
}

vector<std::pair<int, int>> Board::allPossibleMoves(int color) {
    // @param: color -> my own color
    vector<std::pair<int, int>> result;
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++) {
            if (isPossible(i, j, color)) {
                // this position is a valid move
                std::pair<int, int> pair(i, j);
                result.push_back(pair);
            }
        }
    return result;
}

Board &Board::operator=(const Board &that) {
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            board[i][j] = that.board[i][j];
    return *this;
}

bool Board::operator==(const Board &that) const {
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            if (!(board[i][j] == that.board[i][j]))
                return false;
    return color == that.color;
}

int Board::calculateValue() {
    Color myColor = black;
    if (color == 1)
        myColor = white;
    int sum = 0;
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            if (board[i][j].occupy) {
                if (board[i][j].chessman.color == myColor)
                    sum += valueList[i][j];
                else
                    sum -= valueList[i][j];
            }
    return sum;
}

void Board::printOut(bool end, bool start) const {
    std::ofstream outfile("record.txt", std::ios::app);
    if (start)
        outfile << "new game start!" << std::endl;
    else {
        outfile << "step No." << roundCount << std::endl;
        if (!end) {
            for (int i = 0; i < ROW; i++) {
                for (int j = 0; j < COL; j++) {
                    if (board[i][j].chessman.color == black)
                        outfile << "b";
                    else if (board[i][j].chessman.color == white)
                        outfile << "w";
                    else {
                        if (board[i][j].valid)
                            outfile << "n";
                        else
                            outfile << "x";
                    }
                }
                outfile << std::endl;
            }
            outfile << "-----------------------------" << std::endl;
        } else {
            outfile << "one round end!" << std::endl;
            outfile << "=============================" << std::endl;
        }
    }
    outfile.clear();
    outfile.close();
}

int Algorithm::minMaxSearch(bool player, Board &board, int alpha, int beta, int depth, int color, int &returnRow,
                            int &returnCol) {
    // @param: player -> false for opponent's move, true for my move
    // @parm: alpha is initialed to the min value of int, beta is initialed to max value of int
    if (depth != SEARCHDEPTH) {
        auto ite = transportationTable.find(board);
        if (ite != transportationTable.end()) {
            if (ite->second.first >= beta)
                return ite->second.first; // lower bound is greater than beta
            if (ite->second.second <= alpha) // upper bound is less than alpha
                return ite->second.second;
            if (ite->second.first >= alpha)
                alpha = ite->second.first;
            if (ite->second.second <= beta)
                beta = ite->second.second;
        }
    }
    int result = 0;
    if (depth == 0)
        result = board.calculateValue();
    else if (player) {
        result = INT32_MIN;
        int tempAlpha = alpha;
        vector<std::pair<int, int>> allMoves = board.allPossibleMoves(color);
        if (allMoves.empty()) {
            Board temp(board);
            temp.clearRestricted();
            allMoves = temp.allPossibleMoves(color ^ 1);
            if (!allMoves.empty()) {
                int temp1 = 0, temp2 = 0;
                int val = minMaxSearch(!player, temp, tempAlpha, beta, depth - 1, color ^ 1, temp1, temp2);
                if (val > result)
                    result = val;
            }
        } else {
            bool setFlag = false;
            for (auto pair:allMoves) {
                /*Board temp(board);
                temp.placeChessman(pair.first, pair.second, color);
                int temp1 = 0, temp2 = 0;
                int val = minMaxSearch(!player, temp, alpha, beta, depth - 1, color ^ 1, temp1,
                                       temp2);
                if (val > alpha) {
                    alpha = val;
                    returnRow = pair.first;
                    returnCol = pair.second;
                }
                if (alpha > beta)
                    return alpha;*/
                if ((pair.first == 0 && pair.second == 0) || (pair.first == 7 && pair.second == 0) ||
                    (pair.first == 0 && pair.second == 7) || (pair.first == 7 && pair.second == 7)) {
                    returnRow = pair.first;
                    returnCol = pair.second;
                    break;
                }
                if (result >= beta)
                    break; // cut happens
                Board temp(board);
                temp.placeChessman(pair.first, pair.second, color);
                int temp1 = 0, temp2 = 0;
                int val = minMaxSearch(!player, temp, tempAlpha, beta, depth - 1, color ^ 1, temp1, temp2);
                if (val > result) {
                    result = val;
                    returnRow = pair.first;
                    returnCol = pair.second;
                }
                if (result > tempAlpha)
                    tempAlpha = result;
            }
        }
        // return alpha;
    } else {
        result = INT32_MAX;
        int tempBeta = beta;
        vector<std::pair<int, int>> allMoves = board.allPossibleMoves(color);
        if (allMoves.empty()) {
            Board temp(board);
            temp.clearRestricted();
            allMoves = temp.allPossibleMoves(color ^ 1);
            if (!allMoves.empty()) {
                int temp1 = 0, temp2 = 0;
                int val = minMaxSearch(player, temp, alpha, tempBeta, depth - 1, color ^ 1, temp1, temp2);
                if (val < result)
                    result = val;
            }
        } else {
            for (auto pair:allMoves) {
                /*Board temp(board);
                temp.placeChessman(pair.first, pair.second, color);
                int temp1 = 0, temp2 = 0;
                int val = minMaxSearch(player, board, alpha, beta, depth - 1, color ^ 1, temp1,
                                       temp2);
                if (val < beta) {
                    beta = val;
                    returnRow = pair.first;
                    returnCol = pair.second;
                }
                if (beta < alpha)
                    return beta;*/
                if (result <= alpha)
                    break; // cut happens
                Board temp(board);
                temp.placeChessman(pair.first, pair.second, color);
                int temp1 = 0, temp2 = 0;
                int val = minMaxSearch(player, temp, alpha, tempBeta, depth - 1, color ^ 1, temp1, temp2);
                if (val < result) {
                    result = val;
                    returnRow = pair.first;
                    returnCol = pair.second;
                }
                if (result < tempBeta)
                    tempBeta = result;
            }
        }
        // return beta;
    }

    // update transportation table
    // upper bound known
    if (result <= alpha) {
        std::pair<int, int> valuePair(INT32_MIN, result);
        std::pair<Board, std::pair<int, int>> newPair(board, valuePair);
        auto pair = transportationTable.insert(newPair);
        if (!pair.second)
            transportationTable[board].second = result;
    }
    // accurate min max value
    if (result > alpha && result < beta) {
        std::pair<int, int> valuePair(result, result);
        std::pair<Board, std::pair<int, int>> newPair(board, valuePair);
        auto pair = transportationTable.insert(newPair);
        if (!pair.second) {
            transportationTable[board].second = result;
            transportationTable[board].first = result;
        }
    }
    // lower bound known
    if (result > beta) {
        std::pair<int, int> valuePair(result, INT32_MAX);
        std::pair<Board, std::pair<int, int>> newPair(board, valuePair);
        auto pair = transportationTable.insert(newPair);
        if (!pair.second)
            transportationTable[board].first = result;
    }
    return result;
}

int Algorithm::MTD_f(bool player, Board &board, int &returnRow, int &returnCol, int guessVal, int color) {
    int val = guessVal;
    int upperbound = INT32_MAX, lowerbound = INT32_MIN;
    while (lowerbound < upperbound) {
        int beta = 0;
        if (val == lowerbound)
            beta = val + 1;
        else
            beta = val;
        val = minMaxSearch(player, board, beta - 1, beta, SEARCHDEPTH, color, returnRow, returnCol);
        if (val < beta)
            upperbound = val;
        else
            lowerbound = val;
    }
    return val;
}