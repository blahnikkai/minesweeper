//
// Created by Kai Blahnik on 9/6/21.
//

#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

#include <vector>
#include <string>
#include <cassert>
#include "Tile.h"
#include "BombContainer.h"

using std::cout, std::vector, std::string, std::cin;

class Board {

public:

    Board(int size, const BombContainer & bc) {
        assert(size <= 100 && size >= 2);
//      resize top level vector, with each row being empty vector
        tiles.resize(size,{});
        for(int r = 0; r < size; r++) {
//          resize each of the contained vectors, with each tile being placeholder
            tiles[r].resize(size, Tile());
            for(int c = 0; c < size; c++) {
                tiles[r][c] = Tile(r, c, bc);
            }
        }
    }

    bool checkWin() const {
        for(const vector<Tile> & row: tiles) {
            for(const Tile & tile: row) {
                if(!tile.getBomb() && !tile.getClicked())
                    return false;
            }
        }
        return true;
    }

    bool request() {
        cout << "To clear a space, type a coordinate in the form 'r, c': \n"
                "To flag a space, type 'flag' before the coordinate";
        string s;
        getline(cin, s);
        int commaInd = s.find(',');
        if(commaInd == -1)
            return request();
        try {
            int flag_ind = s.find("flag");
            int start;
            if(flag_ind == -1) start = 0;
            else start = flag_ind + 4;
            int r = stoi(s.substr(start, commaInd));
            int c = stoi(s.substr(commaInd + 1));
            if(flag_ind != -1) {
                flag(r, c);
                return false;
            }
            else return reveal(r, c, true);
        }
        catch(std::invalid_argument &) {
            return request();
        }
    }

    bool reveal(int r, int c, bool player) {
        Tile & tile = tiles[r][c];
        if(r < 0 || r >= tiles.size() || c < 0 || c >= tiles.size()
            || tile.getClicked() || (tile.getFlagged()) && player)
            return false;
        tile.click();
        tile.setFlag(false);
        if(tile.getBomb())
            return true;
        if(tile.getAdj() == 0) {
            reveal(r - 1, c, false);
            reveal(r + 1, c, false);
            reveal(r, c - 1, false);
            reveal(r, c + 1, false);
            reveal(r - 1, c - 1, false);
            reveal(r + 1, c + 1, false);
            reveal(r + 1, c - 1, false);
            reveal(r - 1, c + 1, false);
        }
        return false;
    }

    void flag(int r, int c) {
        Tile & tile = tiles[r][c];
        if(tile.getClicked())
            return;
        tile.setFlag(!tile.getFlagged());
    }

    friend std::ostream & operator<<(std::ostream & strm, const Board & board) {
        strm << "   ";
        for(int c = 0; c < board.tiles.size(); ++c) {
            strm << c << " ";
            if(c < 10) {
                strm << " ";
            }
        }
        strm << "\n";
        int r = -1;
        for(const vector<Tile> & row: board.tiles) {
            strm << ++r << " ";
            if(r < 10)
                strm << " ";
            for(Tile t: row)
                strm << t << "  ";
            strm << "\n";
        }
        return strm;
    }

private:

    vector<vector<Tile>> tiles;

};

#endif //MINESWEEPER_BOARD_H
