#ifndef GAME_H
#define GAME_H

#include <vector>
#include <cmath>
#include <map>
using namespace std;

typedef vector<vector<int>> Board;
namespace TicTacToe {
    static int _GAME_NOT_ENDED = 25;
    static int computer = 1;
    static int human = -1;
    static map<int, char> player_map {
        { 1, 'X'},
        {-1, 'O'},
        { 0, ' '}
    };
    
    Board newGame() {
        Board board;
        board = *(new vector<vector<int>>(3));
        for (size_t i = 0; i < 3; i++) {
            board[i] = *(new vector<int>(3));
            for (size_t j = 0; j < 3; j++) {
                board[i][j] = 0;
            }
        }
        return board;
    }
    
    int gameEnd(Board& board) {
        int h = 0, v = 0, 
            l = 0, r = 0;
        int containsEmptyCells = false;
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                h += board[i][j];
                v += board[j][i];	
                if ( board[i][j] == 0 )
                    containsEmptyCells = true;
            }
            l += board[i][i];
            r += board[i][2-i];
            vector<int> values = {h, v, r, l};
            for (int value : values) {
                if ( abs(value) == 3 ) {
                    return value / 3;
                }
            }	
            v = 0; h = 0;
        }
        if ( containsEmptyCells ) 
            return _GAME_NOT_ENDED;
        return 0;
    }	
    
    int minmax(Board& board, int depth, bool isMax) {
    
        int game_state = gameEnd(board);
    
        if ( abs(game_state) != _GAME_NOT_ENDED ) {
            int score = 1000 - depth;
            return game_state * score;
        }
        
        int score = isMax ? INT_MIN : INT_MAX;
        for (size_t i = 0; i < 3; i++ ) {
            for (size_t j = 0; j < 3; j++ ) {
                if ( board[i][j] == 0 ) {
                    if ( isMax ) {
                        board[i][j] = computer; // maximizes the human's score
                        score = max(score, minmax(board, depth + 1, false));
                    } else {
                        board[i][j] = human; // minimizes the computer's score
                        score = min(score, minmax(board, depth + 1, true));
                    }
                    board[i][j] = 0;
                }
            }
        } 
        return score;
    }
    
    pair<int, int> play(Board board) {
        pair<int, int> pos;
        int currentScore = INT_MIN;
        for (size_t i = 0; i < 3; i++ ) {
            for (size_t j = 0; j < 3; j++ ) {
                if ( board[i][j] == 0 ) {
                    board[i][j] = computer;
                    int computedScore = minmax(board, 1, false); // min
                    board[i][j] = 0;
                    if ( currentScore < computedScore ) { // max (root)
                         currentScore = computedScore;
                         pos = {i, j};
                    }
                }
            }
        }
        return pos;
    }
}


#endif // GAME_H
