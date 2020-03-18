//
// Created by ChromeIve on 2/15/2020.
//
#ifndef GOMUKU_GOMOKU_H
#define GOMUKU_GOMOKU_H

#include <vector>
#include <unordered_map>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>

//constants:
#define MAX_BOARD 15
#define WIN5 0
#define A4 1
#define LC4 2
#define C4 3
#define A3 4
#define J3 5
#define D3 6
#define A2 7
#define LA2 8
#define D2 9
#define NONE 10
#define INF 9999999
#define DEPTH 6
#define EX_DEP 12
#define HASH 6
using std::vector;
//data types:

class pt {
public:
    int x;
    int y;

    bool operator==(const pt point) {
        return point.x == this->x && point.y == this->y;
    }
};

typedef struct pieces {
    int x;
    int y;
    int color;
} piece;

typedef struct points {
    int x;
    int y;
    int score;
} point;//used in Generate()

typedef unsigned long long U64;


//short functions:
bool isNeighbor(int x, int y);

bool isFree(int x, int y);

//TODO: Get the bugs fucked up and delete this func below;
using namespace std;

//Game class:
class Game {
private:
    pt _bestMove;
    U64 hash_keys[3][MAX_BOARD][MAX_BOARD];
    U64 hash_key;
    unordered_map<U64, int> hash_map;
    int left, right, up, down;//border of pieces.
public:
    Game();

    vector<point> Generate(int color);

    int Count(int x, int y, int color, int mode, int colors[]);


    int judgeLine(int x, int y, int mode, int color);

    int judgePoint(int x, int y, int color);

    int Evaluate();

    void Init_zobrist();

    void Update_zobrist(int color, int x, int y);

    int simpleJudgeline(int x, int y, int mode, int color);

    void checkPoint(int x, int y, int color, bool shapes[6]);

    int negaMax(int color, int depth, int alpha, int beta);

    void Border(int, int);

    pt bestMove();

    ~Game() = default;

};


#endif //GOMUKU_GOMOKU_H
