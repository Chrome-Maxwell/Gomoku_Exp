//
// Created by ChromeIve on 2/15/2020.
//

#include "Gomoku.h"
#include <ctime>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

extern int board[MAX_BOARD][MAX_BOARD];
extern vector<piece> pieces;


Game::Game() {
    left = MAX_BOARD - 1;
    right = 0;
    up = 0;
    down = MAX_BOARD - 1;
    this->_bestMove = {MAX_BOARD / 2, MAX_BOARD / 2};
    //this->_bestMove = {5,6};

}

int cnt = 0;

int Game::negaMax(int color, int depth, int alpha, int beta) {
    if (depth == 0) {
#ifdef HASH
        if(this->hash_map.find(this->hash_key)!=this->hash_map.end()) {
            return hash_map.at(this->hash_key);
        }
        else {
            int val = pow(-1,DEPTH)*  this->Evaluate();
            this->hash_map.insert(pair<U64,int>(this->hash_key,val));
            return val;
        }
#else
        return pow(-1, DEPTH) * this->Evaluate();
#endif
    }

    int score = 0;
    int l,r,u,d;
    vector<point> list = this->Generate(color);
    vector<point>::iterator it;
    for (it = list.begin(); it != list.end(); it++) {
        int i = it->x;
        int j = it->y;
        if (!board[i][j]) {
            pieces.push_back({i, j, color});
            board[i][j] = color;
            l = this->left;
            r = this->right;
            u = this->up;
            d = this->down;
            this->Border(i,j);
            this->Update_zobrist(color, i, j);
            score = -negaMax(3 - color, depth - 1, -beta, -alpha);
            pieces.pop_back();
            board[i][j] = 0;
            this->left = l;
            this->right = r;
            this->up = u;
            this->down = d;
            this->Update_zobrist(color, i, j);
            if (score >= beta) return beta;
            if (score > alpha) {
                alpha = score;
                if (depth == DEPTH) {
                    this->_bestMove = {i, j};
                }
            }
        }
    }
    return alpha;
}

void Game::Border(int x, int y) {
    left = x < left ? x : left;
    right = x > right ? x : right;
    up = y > up ? y : up;
    down = y < down ? y : down;
}

bool isNeighbor(int x, int y) {
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i < 0 || i >= MAX_BOARD || j < 0 || j >= MAX_BOARD || (i == x && j == y))
                continue;
            if (board[i][j])
                return true;
        }
    }
    return false;
}

bool cmp(point x, point y) {
    return x.score > y.score;
}

vector<point> Game::Generate(int color) {
    vector<point> list;
    for (int i = max(left - 1, 0); i < min(right + 2, MAX_BOARD); i++) {
        for (int j = max(down - 1, 0); j < min(up + 2, MAX_BOARD); j++) {
            if (!isFree(i, j) || !isNeighbor(i, j))
                continue;
            int score = judgePoint(i, j, color);
            list.push_back({i, j, score});
        }
    }
    sort(list.begin(), list.end(), cmp);
    return list;
}

pt Game::bestMove() {
    return this->_bestMove;
}