//
// Created by Kai Blahnik on 8/28/21.
//

#ifndef MINESWEEPER_BOMB_H
#define MINESWEEPER_BOMB_H

#include <iostream>

class Bomb {

public:

    int getRow() const {return r;}
    int getColumn() const {return c;}

    Bomb(int r_in, int c_in) {
        r = r_in;
        c = c_in;
    }

    friend bool operator==(const Bomb & bomb1, const Bomb & bomb2) {
        return bomb1.r == bomb2.r && bomb1.c == bomb2.c;
    }

    friend std::ostream & operator<<(std::ostream & strm, const Bomb & bomb) {
        return strm << "Bomb(" << bomb.r << ", " << bomb.c << ")";
    }

private:

    int r;
    int c;

};


#endif //MINESWEEPER_BOMB_H
