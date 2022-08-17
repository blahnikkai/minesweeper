#include <iostream>
#include <time.h>

#include "Board.h"

using std::cout;

const int BOARD_SIZE = 20;
const int BOMB_NUM = 50;

void playGame() {
    srand(time(nullptr));
    cout << std::boolalpha;

    BombContainer bombContainer{BOMB_NUM, BOARD_SIZE};
    cout << bombContainer << "\n";

    Board board{BOARD_SIZE, bombContainer};

    while(true) {
        cout << board << "\n";
        if(board.request()) {
            cout << board << "\n";
            cout << "          _ ._  _ , _ ._\n"
                    "        (_ ' ( `  )_  .__)\n"
                    "      ( (  (    )   `)  ) _)\n"
                    "     (__ (_   (_ . _) _) ,__)\n"
                    "         `~~`\\ ' . /`~~`\n"
                    "              ;   ;\n"
                    "              /   \\\n"
                    "_____________/_ __ \\_____________" << "\n";
            break;
        }
        if(board.checkWin()) {
            cout << board << "\nAll bombs defused. Phew! ε-(´・｀) ﾌ\n";
            break;
        }
    }
}

int main() {
    playGame();
    return 0;
}


