#include "pisqpipe.h"
#include <windows.h>
#include "Gomoku.h"
#include <ctime>
const char *infotext = "name=\"Junk\", author=\"ysl&yaa\", version=\"0.0\", country=\"Czech Republic\", www=\"http://petr.lastovicka.sweb.cz\"";

int board[MAX_BOARD][MAX_BOARD] = {{0}};
vector<piece> pieces;
static unsigned seed;
Game game;

bool isFree(int x, int y) {
    return (board[x][y]==0 && -1<x && x<height && -1<y && y<width);
}

void brain_init() {
    if (width < 5 || height < 5) {
        pipeOut("ERROR size of the board");
        return;
    }
    if (width > MAX_BOARD || height > MAX_BOARD) {
        pipeOut("ERROR Maximal board size is %d", MAX_BOARD);
        return;
    }
    srand(time(NULL));
    game.Init_zobrist();
    seed = start_time;
    pipeOut("OK");
}

void brain_restart() {
    int x, y;
    for (x = 0; x < width; x++) {
        for (y = 0; y < height; y++) {
            board[x][y] = 0;
        }
    }
    pipeOut("OK");
}

void brain_my(int y, int x) {
    if (isFree(x,y)) {
        board[x][y] = 1;
        game.Border(x,y);
        game.Update_zobrist(1,x,y);
        pieces.push_back({x,y,1});
    } else {
        pipeOut("ERROR my move [%d,%d]", x, y);
    }
}

void brain_opponents(int y, int x) {
    game.Border(x,y);
    game.Update_zobrist(2,x,y);
    pieces.push_back({x,y,2});
    if (isFree(x, y)) {
        board[x][y] = 2;
    } else {
        pipeOut("ERROR opponents's move [%d,%d]", x, y);
    }
}

void brain_block(int x, int y) {
    if (isFree(x, y)) {
        board[x][y] = 3;
    } else {
        pipeOut("ERROR winning move [%d,%d]", x, y);
    }
}

int brain_takeback(int x, int y) {
    if (x >= 0 && y >= 0 && x < width && y < height && board[x][y] != 0) {
        game.Update_zobrist(board[x][y],x,y);
        pieces.pop_back();
        board[x][y] = 0;
        return 0;
    }
    return 2;
}

void brain_turn() {
    int x, y;
    do {
        if (pieces.size()) {
            game.negaMax(1, DEPTH, -INF, INF);
        }
        x = game.bestMove().x;
        y = game.bestMove().y;
    } while(!isFree(x,y));
    if (terminateAI) return;
    do_mymove(x, y);
}

void brain_end() {
}

#ifdef DEBUG_EVAL
#include <windows.h>

void brain_eval(int x,int y)
{
  HDC dc;
  HWND wnd;
  RECT rc;
  char c;
  wnd=GetForegroundWindow();
  dc= GetDC(wnd);
  GetClientRect(wnd,&rc);
  c=(char)(board[x][y]+'0');
  TextOut(dc, rc.right-15, 3, &c, 1);
  ReleaseDC(wnd,dc);
}

#endif
