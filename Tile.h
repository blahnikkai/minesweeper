//
// Created by Kai Blahnik on 8/28/21.
//

#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H

#include <iostream>
#include <string>
#include "Bomb.h"
#include "BombContainer.h"

using std::string;

const string RESET = "\x1b[0m";
const string BLACK_FORE = "\x1b[30m";
const string RED_FORE = "\x1b[31m";
const string GREEN_FORE = "\x1b[32m";
const string BLUE_FORE = "\x1b[34m";
const string GRAY_FORE = "\x1b[90m";

class Tile {

public:

    Tile() {
        r = -1;
        c = -1;
        bomb = false;
        clicked = false;
        flagged = false;
        adj = -1;
    }

    Tile(const int & r_in, const int & c_in, const BombContainer & bc) {
        r = r_in;
        c = c_in;
        adj = 0;
        bomb = false;
        clicked = false;
        flagged = false;
//      goes through every bomb and checks if it is on the tile, in which case the tile becomes a bomb tile
//      if bomb is adjacent, increment adj, the number displayed for minesweeper
//      would be more efficient if bombs were added to the tiles in one outside loop, then another to count adjacent
//      bomb tiles, so only checking adjacent tiles. Probably insignificant unless we have many, many bombs
        for(const Bomb & b: bc.getBombs()) {
            if(withinRadius(b, 0)) {
                bomb = true;
                adj = -1;
                break;
            }
            else if (withinRadius(b, 1)) {
                ++adj;
            }
        }
    }

    bool withinRadius(const Bomb & b, const int & radius) const {
        return abs(r - b.getRow()) <= radius && abs(c - b.getColumn()) <= radius;
    }

    friend std::ostream & operator<<(std::ostream & strm, const Tile & t) {
        if(t.flagged)
            return strm << BLUE_FORE << 'F' << RESET;
        if(!t.clicked)
            return strm << BLACK_FORE << 'X' << RESET;
        if(t.bomb)
            return strm << RED_FORE << "●" << RESET;
        if(t.adj == 0)
            return strm << BLACK_FORE << "□" << RESET;
        return strm << t.adj;
    }

    bool getBomb() const { return bomb; }
    int getAdj() const { return adj; }
    bool getClicked() const { return clicked; }
    bool getFlagged() const { return flagged; }
    void click() {clicked = true;}
    void setFlag(bool flag) {flagged = flag;}

private:

    int r;
    int c;
    bool bomb;
    bool clicked;
    bool flagged;
    int adj;

};

#endif //MINESWEEPER_TILE_H
