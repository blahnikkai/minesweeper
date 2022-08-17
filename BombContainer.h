//
// Created by Kai Blahnik on 9/2/21.
//

#ifndef MINESWEEPER_BOMBCONTAINER_H
#define MINESWEEPER_BOMBCONTAINER_H

#include <random>
#include <vector>
#include "Bomb.h"

using std::cout, std::vector;

class BombContainer {

public:

    vector<Bomb> getBombs() const {return bombs;}

    BombContainer(int num, int size) {
        boardSize = size;
        for(int i = 0; i < num; i++)
            bombs.push_back(generateBomb());
    }

    Bomb generateBomb() {
        int x = rand() % boardSize;
        int y = rand() % boardSize;
        Bomb newBomb{x, y};
        for(Bomb existingBomb: bombs) {
            if(newBomb == existingBomb)
                return generateBomb();
        }
        return newBomb;
    }

     friend std::ostream & operator<<(std::ostream & strm, const BombContainer & bc) {
        for(int i = 0; i < bc.bombs.size(); ++i) {
            strm << i << ": " << bc.bombs[i] << "\n";
        }
        return strm;
    }

private:

    vector<Bomb> bombs;
    int boardSize;

};
#endif //MINESWEEPER_BOMBCONTAINER_H