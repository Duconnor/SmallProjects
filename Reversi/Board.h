#ifndef REVERSI_BOARD_H
#define REVERSI_BOARD_H

#define SEARCHDEPTH 6

#include <iostream>
#include <vector>

using std::vector;

const int ROW = 8;
const int COL = 8;

enum Color {
    black, white, null
};

struct Chessman {
    Color color;

    Chessman() : color(null) {};

    Chessman(const Chessman &that) { color = that.color; };

    void flip() { color = color == black ? white : black; } // flip the color of this chessman

    void setColor(int color) { this->color = color == 1 ? white : black; } // param "color": 1 for white, 0 for black

    Chessman &operator=(Chessman that) {
        color = that.color;
        return *this;
    };
};

// Point表示棋盘上的点
struct Point {
    bool valid; // is this point valid now?
    bool occupy; // is this point occupied?
    Chessman chessman;

    Point() : valid(true), occupy(false) {}

    Point(const Point &that) {
        valid = that.valid;
        occupy = that.occupy;
        chessman = that.chessman;
    }

    void placeHere(int color) {
        occupy = true;
        chessman.setColor(color);
    }

    Point &operator=(Point that) {
        valid = that.valid;
        occupy = that.occupy;
        chessman = that.chessman;
        return *this;
    }
};

class Board {
private:
    Point board[ROW][COL];

    bool isPossible(int row, int col, int color); // is this position possible for the next move
    bool isFlippable(int row, int col, int color, bool flip); // can this chessman flip any other chessman
public:
    Board(); // initial a board

    ~Board() = default;

    Board(Board &thatBoard);

    void clear();

    void clearRestricted(); // clear all restricted points
    void setRestricted(int row, int col); // set the restricted points
    void placeChessman(int row, int col, int color); // place a chessman at the given position
    vector<std::pair<int, int>> allPossibleMoves(int color); // return all the possible next move
    void writeToFile(char *filename);

    Board &operator=(Board const &that);

    int calculateValue();

    void printOut(bool end = false, bool start = false);
};

// min max search with alpha beta
int minMaxSearch(bool player, Board &board, int alpha, int beta, int depth, int color, int &returnRow, int &returnCol);

// MTD(f)
int MTD_f(bool player, Board &board, int &returnRow, int &returnCol, int guessVal, int color);

#endif //REVERSI_BOARD_H
