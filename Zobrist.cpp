//
// Created by ChromeIve on 2/27/2020.
//
#include "Gomoku.h"
#include <ctime>

extern int board[MAX_BOARD][MAX_BOARD];

U64 _rand() {
    return rand() ^ ((U64) rand() << 15) ^ ((U64) rand() << 30) ^ ((U64) rand() << 45) ^ ((U64) rand() << 60);
}

void Game::Init_zobrist() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < MAX_BOARD; ++j) {
            for (int k = 0; k < MAX_BOARD; ++k) {
                this->hash_keys[i][j][k] = _rand();
            }
        }
    }
}

void Game::Update_zobrist(int color, int x, int y) {
    this->hash_key ^= this->hash_keys[color][x][y];
}
