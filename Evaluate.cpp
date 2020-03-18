//
// Created by ChromeIve on 2/18/2020.
//

#include "Gomoku.h"
#include <ctime>
#include <iostream>

using namespace std;
#define WIN 100000000
const int static SCORES1[10] = {100000, 400, 500, 100, 90, 5, 10, 9, 2, 0};    //活四、低死四、冲四、活三、跳三、死三、活二、低活二、死二、无威胁
const int static SCORES2[10] = {102000, 410, 520, 120, 95, 5, 10, 9, 2, 0};    //活四、低死四、冲四、活三、跳三、死三、活二、低活二、死二、无威胁
extern int board[MAX_BOARD][MAX_BOARD];
extern vector<piece> pieces;

//TODO:delete this!
void printShapes(int s[11]) {
//    cout<<endl<<"[";
//    for (int i = 0; i < 11; ++i) {
//        cout<<s[i]<<", ";
//    }
//    cout<<"] "<<endl;
}

int Game::Count(int x, int y, int color, int mode, int colors[]) {//front:W,SW,S,SE;back:E,NE,N,NW;
    int colorfront1 = -1, colorfront2 = -1, colorback1 = -1, colorback2 = -1, colorfront3 = -1, colorback3 = -1, colorfront4 = -1, colorback4 = -1;
    int count = 1;
    switch (mode) {
        case 1:
            //纵向
            for (int i = 1; i <= 4; i++) {
                if (x - i >= 0 && board[x - i][y] == color)
                    count++;
                else {
                    if (x - i < 0);
                    else if (x - i - 1 < 0) {
                        colorfront1 = board[x - i][y];
                    } else if (x - i - 2 < 0) {
                        colorfront1 = board[x - i][y];
                        colorfront2 = board[x - i - 1][y];
                    } else if (x - i - 3 < 0) {
                        colorfront1 = board[x - i][y];
                        colorfront2 = board[x - i - 1][y];
                        colorfront3 = board[x - i - 2][y];
                    } else {
                        colorfront1 = board[x - i][y];
                        colorfront2 = board[x - i - 1][y];
                        colorfront3 = board[x - i - 2][y];
                        colorfront4 = board[x - i - 3][y];
                    }
                    break;
                }
            }
            for (int i = 1; i <= 4; i++) {
                if (x + i < MAX_BOARD && board[x + i][y] == color)
                    count++;
                else {
                    if (x + i >= MAX_BOARD);
                    else if (x + i + 1 >= MAX_BOARD) {
                        colorback1 = board[x + i][y];
                    } else if (x + i + 2 >= MAX_BOARD) {
                        colorback1 = board[x + i][y];
                        colorback2 = board[x + i + 1][y];
                    } else if (x + i + 3 >= MAX_BOARD) {
                        colorback1 = board[x + i][y];
                        colorback2 = board[x + i + 1][y];
                        colorback3 = board[x + i + 2][y];
                    } else {
                        colorback1 = board[x + i][y];
                        colorback2 = board[x + i + 1][y];
                        colorback3 = board[x + i + 2][y];
                        colorback4 = board[x + i + 3][y];

                    }
                    break;
                }
            }
            break;
        case 2:
            //横向
            for (int i = 1; i <= 4; i++)//front
            {
                if (y - i >= 0 && board[x][y - i] == color)
                    count++;
                else {
                    if (y - i < 0)
                        colorfront1 = -1;
                    else if (y - i - 1 < 0) {
                        colorfront1 = board[x][y - i];
                    } else if (y - i - 2 < 0) {
                        colorfront1 = board[x][y - i];
                        colorfront2 = board[x][y - i - 1];
                    } else if (y - i - 3 < 0) {
                        colorfront1 = board[x][y - i];
                        colorfront2 = board[x][y - i - 1];
                        colorfront3 = board[x][y - i - 2];
                    } else {
                        colorfront1 = board[x][y - i];
                        colorfront2 = board[x][y - i - 1];
                        colorfront3 = board[x][y - i - 2];
                        colorfront4 = board[x][y - i - 3];
                    }
                    break;
                }
            }
            for (int i = 1; i <= 4; i++)//back
            {
                if (y + i < MAX_BOARD && board[x][y + i] == color)
                    count++;
                else {
                    if (y + i >= MAX_BOARD);
                    else if (y + i + 1 >= MAX_BOARD) {
                        colorback1 = board[x][y + i];
                    } else if (y + i + 2 >= MAX_BOARD) {
                        colorback1 = board[x][y + i];
                        colorback2 = board[x][y + i + 1];
                    } else if (y + i + 3 >= MAX_BOARD) {
                        colorback1 = board[x][y + i];
                        colorback2 = board[x][y + i + 1];
                        colorback3 = board[x][y + i + 2];
                    } else {
                        colorback1 = board[x][y + i];
                        colorback2 = board[x][y + i + 1];
                        colorback3 = board[x][y + i + 2];
                        colorback4 = board[x][y + i + 3];
                    }
                    break;
                }
            }
            break;
        case 3:
            //右斜
            for (int i = 1; i <= 4; i++) {
                if (x - i >= 0 && y + i < MAX_BOARD && board[x - i][y + i] == color)
                    count++;
                else {
                    if (x - i < 0 || y + i >= MAX_BOARD)
                        colorfront1 = -1;//NW
                    else if (x - i - 1 < 0 || y + i + 1 >= MAX_BOARD) {
                        colorfront1 = board[x - i][y + i];
                    } else if (x - i - 2 < 0 || y + i + 2 >= MAX_BOARD) {
                        colorfront1 = board[x - i][y + i];
                        colorfront2 = board[x - i - 1][y + i + 1];
                    } else if (x - i - 3 < 0 || y + i + 3 >= MAX_BOARD) {
                        colorfront1 = board[x - i][y + i];
                        colorfront2 = board[x - i - 1][y + i + 1];
                        colorfront3 = board[x - i - 2][y + i + 2];
                    } else {
                        colorfront1 = board[x - i][y + i];
                        colorfront2 = board[x - i - 1][y + i + 1];
                        colorfront3 = board[x - i - 2][y + i + 2];
                        colorfront4 = board[x - i - 3][y + i + 3];
                    }
                    break;
                }
            }
            for (int i = 1; i <= 4; i++) {
                if (y - i >= 0 && x + i < MAX_BOARD && board[x + i][y - i] == color)
                    count++;
                else {
                    if (x + i >= MAX_BOARD || y - i < 0)
                        colorback1 = -1;//SE
                    else if (x + i + 1 >= MAX_BOARD || y - i - 1 < 0) {
                        colorback1 = board[x + i][y - i];
                    } else if (x + i + 2 >= MAX_BOARD || y - i - 2 < 0) {
                        colorback1 = board[x + i][y - i];
                        colorback2 = board[x + i + 1][y - i - 1];
                    } else if (x + i + 3 >= MAX_BOARD || y - i - 3 < 0) {
                        colorback1 = board[x + i][y - i];
                        colorback2 = board[x + i + 1][y - i - 1];
                        colorback3 = board[x + i + 2][y - i - 2];
                    } else {
                        colorback1 = board[x + i][y - i];
                        colorback2 = board[x + i + 1][y - i - 1];
                        colorback3 = board[x + i + 2][y - i - 2];
                        colorback4 = board[x + i + 3][y - i - 3];
                    }
                    break;
                }
            }
            break;
        case 4:
            //左斜
            for (int i = 1; i <= 4; i++) {
                if (x - i >= 0 && y - i >= 0 && board[x - i][y - i] == color)
                    count++;
                else {
                    if (x - i < 0 || y - i < 0)
                        colorfront1 = -1;//SW
                    else if (x - i - 1 < 0 || y - i - 1 < 0) {
                        colorfront1 = board[x - i][y - i];
                    } else if (x - i - 2 < 0 || y - i - 2 < 0) {
                        colorfront1 = board[x - i][y - i];
                        colorfront2 = board[x - i - 1][y - i - 1];
                    } else if (x - i - 3 < 0 || y - i - 3 < 0) {
                        colorfront1 = board[x - i][y - i];
                        colorfront2 = board[x - i - 1][y - i - 1];
                        colorfront3 = board[x - i - 2][y - i - 2];
                    } else {
                        colorfront1 = board[x - i][y - i];
                        colorfront2 = board[x - i - 1][y - i - 1];
                        colorfront3 = board[x - i - 2][y - i - 2];
                        colorfront4 = board[x - i - 3][y - i - 3];
                    }
                    break;
                }
            }
            for (int i = 1; i <= 4; i++) {
                if (x + i < MAX_BOARD && y + i < MAX_BOARD && board[x + i][y + i] == color)
                    count++;
                else {
                    if (x + i >= MAX_BOARD || y + i >= MAX_BOARD)
                        colorback1 = -1;//NW
                    else if (x + i + 1 >= MAX_BOARD || y + i + 1 >= MAX_BOARD) {
                        colorback1 = board[x + i][y + i];
                    } else if (x + i + 2 >= MAX_BOARD || y + i + 2 >= MAX_BOARD) {
                        colorback1 = board[x + i][y + i];
                        colorback2 = board[x + i + 1][y + i + 1];
                    } else if (x + i + 3 >= MAX_BOARD || y + i + 3 >= MAX_BOARD) {
                        colorback1 = board[x + i][y + i];
                        colorback2 = board[x + i + 1][y + i + 1];
                        colorback3 = board[x + i + 2][y + i + 2];
                    } else {
                        colorback1 = board[x + i][y + i];
                        colorback2 = board[x + i + 1][y + i + 1];
                        colorback3 = board[x + i + 2][y + i + 2];
                        colorback4 = board[x + i + 3][y + i + 3];
                    }
                    break;
                }
            }
            break;
    }
    colors[0] = colorfront1;
    colors[1] = colorfront2;
    colors[2] = colorfront3;
    colors[3] = colorfront4;
    colors[4] = colorback1;
    colors[5] = colorback2;
    colors[6] = colorback3;
    colors[7] = colorback4;
    //TODO:
    //if(x==4&&y==7&&count==4) cout<<endl<<"????"<<colorfront1<<colorback1<<endl;
    return count;
}

int Game::judgeLine(int x, int y, int mode, int color) {
    int colors[8];
    int count = this->Count(x, y, color, mode, colors);
    int colorleft = colors[0], colorleft1 = colors[1], colorleft2 = colors[2], colorleft3 = colors[3], colorright = colors[4],
            colorright1 = colors[5], colorright2 = colors[6], colorright3 = colors[7];
    //If tree:
    if (count >= 5)
        return WIN5;
    if (count == 4) {
        if (colorleft == 0 && colorright == 0)
            return A4;
        else if (colorleft == 3 - color && colorright == 3 - color)
            return NONE;
        else if (colorleft == 0 || colorright == 0)
            return C4;
    }

    if (count == 3) {

        if (colorleft == 0 && colorright == 0) {
            if (colorleft1 == 3 - color && colorright1 == 3 - color)
                return D3;
            else if (colorleft1 == color || colorright1 == color)
                return LC4;
            else if (colorleft1 == 0 || colorright1 == 0)
                return A3;

        } else if (colorleft == 3 - color && colorright == 3 - color) {
            return NONE;
        } else if (colorleft == 0 || colorright == 0) {
            if (colorleft == 3 - color) {
                if (colorright1 == 3 - color)
                    return NONE;
                if (colorright1 == 0)
                    return D3;
                if (colorright1 == color)
                    return LC4;
            }
            if (colorright == 3 - color) {
                if (colorleft1 == 3 - color)
                    return NONE;
                if (colorleft1 == 0)
                    return D3;
                if (colorleft1 == color)
                    return LC4;
            }
        }
    }

    if (count == 2) {

        if (colorleft == 0 && colorright == 0) {
            if ((colorright1 == 0 && colorright2 == color) ||
                (colorleft1 == 0 && colorleft2 == color))
                return D3;
            else if (colorleft1 == 0 && colorright1 == 0)
                return A2;

            if ((colorright1 == color && colorright2 == 3 - color) ||
                (colorleft1 == color && colorleft2 == 3 - color))
                return D3;

            if ((colorright1 == color && colorright2 == color) ||
                (colorleft1 == color && colorleft2 == color))
                return LC4;

            if ((colorright1 == color && colorright2 == 0) ||
                (colorleft1 == color && colorleft2 == 0))
                return J3;

        } else if (colorleft == 3 - color && colorright == 3 - color) {
            return NONE;
        } else if (colorleft == 0 || colorright == 0) {
            if (colorleft == 3 - color) {
                if (colorright1 == 3 - color || colorright2 == 3 - color) {
                    return NONE;
                } else if (colorright1 == 0 && colorright2 == 0) {
                    return D2;
                } else if (colorright1 == color && colorright2 == color) {
                    return LC4;
                } else if (colorright1 == color || colorright2 == color) {
                    return D3;
                }
            }
            if (colorright == 3 - color) {
                if (colorleft1 == 3 - color || colorleft2 == 3 - color) {
                    return NONE;
                } else if (colorleft1 == 0 && colorleft2 == 0) {
                    return D2;
                } else if (colorleft1 == color && colorleft2 == color) {
                    return LC4;
                } else if (colorleft1 == color || colorleft2 == color) {
                    return D3;
                }
            }
        }
    }
    if (count == 1) {

        if (colorleft == 0 && colorleft1 == color &&
            colorleft2 == color && colorleft3 == color)
            return LC4;
        if (colorright == 0 && colorright1 == color &&
            colorright2 == color && colorright3 == color)
            return LC4;
        if (colorleft == 0 && colorleft1 == color &&
            colorleft2 == color && colorleft3 == 0 && colorright == 0)
            return J3;
        if (colorright == 0 && colorright1 == color &&
            colorright2 == color && colorright3 == 0 && colorleft == 0)
            return J3;
        if (colorleft == 0 && colorleft1 == color &&
            colorleft2 == color && colorleft3 == 3 - color && colorright == 0)
            return D3;
        if (colorright == 0 && colorright1 == color &&
            colorright2 == color && colorright3 == 3 - color && colorleft == 0)
            return D3;
        if (colorleft == 0 && colorleft1 == 0 &&
            colorleft2 == color && colorleft3 == color)
            return D3;
        if (colorright == 0 && colorright1 == 0 &&
            colorright2 == color && colorright3 == color)
            return D3;
        if (colorleft == 0 && colorleft1 == color &&
            colorleft2 == 0 && colorleft3 == color)
            return D3;
        if (colorright == 0 && colorright1 == color &&
            colorright2 == 0 && colorright3 == color)
            return D3;
        if (colorleft == 0 && colorleft1 == color &&
            colorleft2 == 0 && colorleft3 == 0 && colorright == 0)
            return LA2;
        if (colorright == 0 && colorright1 == color &&
            colorright2 == 0 && colorright3 == 0 && colorleft == 0)
            return LA2;
        if (colorleft == 0 && colorleft1 == 0 &&
            colorleft2 == color && colorleft3 == 0 && colorright == 0)
            return LA2;
        if (colorright == 0 && colorright1 == 0 &&
            colorright2 == color && colorright3 == 0 && colorleft == 0)
            return LA2;
    }
    return NONE;
}

int Game::simpleJudgeline(int x, int y, int mode, int color) {
    int colors[4];
    int count = this->Count(x, y, color, mode, colors);

    int colorleft = colors[0], colorleft1 = colors[1], colorright = colors[2], colorright1 = colors[3];
    if (count < 3) return NONE;
    //If tree:
    if (count >= 5)//中心线5连
        return WIN5;//5连珠
    if (count == 4)//中心线4连
    {
        if (colorleft == 0 && colorright == 0)//两边断开位置均空
            return A4;//活四
        else if (colorleft == 0 || colorright == 0)//两边断开位置只有一个空
            return C4;//死四
    }

    if (count == 3) {//中心线3连
        if (colorleft == 0 && colorright == 0)//两边断开位置均空
        {
            if (colorleft1 == color || colorright1 == color)//只要一个为自己的棋子
                return LC4;
            else if (colorleft1 == 0 || colorright1 == 0)//只要有一个空
                return A3;
        } else if (colorleft == 0 || colorright == 0)//两边断开位置只有一个空
        {
            if (colorright1 == color)
                return LC4;
        }
        if (colorright == 3 - color) {//右边被对方堵住
            if (colorleft1 == color)//左边还有自己的棋子
                return LC4;
        }
    }
    return NONE;
}

int Game::judgePoint(int x, int y, int color) {
    int score = 0;
    int shapes[11] = {0};//各棋形数目
    for (int i = 1; i <= 4; ++i) {
        int temp;
        if (!(temp = this->judgeLine(x, y, i, color))) {
            return WIN;
        } else {
            shapes[temp]++;
        }
    }
    for (int i = 1; i <= 11; i++) {
        if (i <= 4 && shapes[i]) {
            if (color == 1)
                score += pow(SCORES1[i - 1], shapes[i]);
            else
                score += pow(SCORES2[i - 1], shapes[i]);
        } else {
            if (color == 1)
                score += SCORES1[i - 1] * shapes[i];
            else
                score += SCORES2[i - 1] * shapes[i];
        }
    }
    return score;
}

void Game::checkPoint(int x, int y, int color, bool shapes[6]) {
    for (int i = 1; i <= 4; i++) {
        int temp = this->simpleJudgeline(x, y, i, color);
        switch (temp) {
            case WIN5:
                shapes[(color - 1) * 3] = true;
                break;
            case A4:
            case LC4:
            case C4:
                shapes[(color - 1) * 3 + 1] = true;
                break;
            case A3:
                shapes[(color - 1) * 3 + 2] = true;
                break;
        }
    }
}

int Game::Evaluate() {
    vector<piece>::iterator it;
    int score = 0;
    for (it = pieces.begin(); it != pieces.end(); it++) {
        score += pow(-1, it->color + 1) * judgePoint(it->x, it->y, it->color);
    }
//    piece back = pieces.back();
//    if(back.x==6&&back.y==7) {
//        cout<<endl<<"FIND6,7! "<<endl;
//        for (it = pieces.begin(); it != pieces.end(); it++)
//        {
//            cout<<"("<<it->x<<","<<it->y<<") :";
//            cout<< judgePoint(it->x, it->y, it->color)<<endl;
//        }
//    }
    return score;
}


