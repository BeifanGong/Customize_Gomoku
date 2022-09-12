// TicTacToeGame.cpp
//
// This file defines the methods of TicTacToe class

#include <string>
#include <sstream>
#include <iomanip>
#include "TicTacToeGame.h"

using namespace std;

const string init = " ";
const string X = "X";
const string O = "O";

bool TicTacToeGame::done() {
    //check for 3 in a row
    for(size_t row = 1; row < Height-1; ++row){
        string first = board[Width * row + 1].name;
        string second = board[Width * row + 2].name;
        string third = board[Width * row + 3].name;
        if(first != init && first == second && first == third){
            winner = first;
            return true;
        }
    }

    //check for 3 in a col
    for(size_t col = 1; col < Width-1; ++col){
        string first = board[Width * 1 + col].name;
        string second = board[Width * 2 + col].name;
        string third = board[Width * 3 + col].name;
        if(first != init && first == second && first == third){
            winner = first;
            return true;
        }
    }

    //check for 3 in a diagonal
    if(board[Width * 1 + 1].name != init && board[Width * 1 + 1].name == board[Width * 2 + 2].name
       && board[Width * 1 + 1].name == board[Width * 3 + 3].name){
        winner = board[Width * 1 + 1].name;
        return true;
    }

    if(board[Width * 1 + 3].name != init && board[Width * 1 + 3].name == board[Width * 2 + 2].name
       && board[Width * 1 + 3].name == board[Width * 3 + 1].name){
        winner = board[Width * 1 + 3].name;
        return true;
    }

    return false;
}

bool TicTacToeGame::draw() {
    if(done()){
        return false;
    }

    for(size_t row = 1; row < Height-1; ++row){
        for(size_t col = 1; col < Width-1; ++col){
            if(board[Width * row + col].name == init){
                return false;
            }
        }
    }
    return true;
}

int TicTacToeGame::turn() {
    unsigned int row;
    unsigned int col;

    GamePiece X_p;
    GamePiece O_p;

    X_p.name = "X";
    X_p.display = "X";
    O_p.name = "O";
    O_p.display = "O";
    cout << "Player " << player << "\'s turn." << endl;
    if(auto_player){
        autoPlay();
    }
    else{
        if(prompt(row, col) == quit){
            return quit;
        }
        while(board[Width * row + col].name != init){
            cout << "Already taken, use another position." << endl;
            if(prompt(row, col) == quit) {
                return quit;
            }
        }
        if(player == X){
            board[Width * row + col] = X_p;
        }
        else{
            board[Width * row + col] = O_p;
        }
        if(auto_play){
            auto_player = true;
        }

    }
    print();
    cout << "Player " << player << ": ";

    ostringstream oss;
    for(size_t y = 0; y < Height; ++y){
        for(size_t x = 0; x < Width; ++x){
            if(board[Width * y + x].name == player){
                oss << x << "," << y << "; ";
            }
        }
    }
    //removing the last ";"
    string temp = oss.str();
    for(size_t i = 0; i < temp.size()-2; ++i){
        cout << temp[i];
    }
    cout << endl;
    cout << endl;
    if(player == X){
        player = O;
    }
    else{
        player = X;
    }
    ++turns;
    return success;
}

TicTacToeGame::TicTacToeGame(bool auto_play) : GameBase(5, 5), player(X), auto_player(false){
    this->auto_play = auto_play;
    max_length = 1;
}

void TicTacToeGame::autoPlay() {
    int max = 0;
    unsigned int max_row = 1;
    unsigned int max_col = 1;
    for(size_t row = 1; row < 4; ++row){
        for(size_t col = 1; col < 4; ++col){
            if(board[Width*row + col].name == init){
                if(generateScore(row, col) >= max){
                    max = generateScore(row, col);
                    max_row = row;
                    max_col = col;
                }

            }
        }
    }
    board[Width*max_row + max_col].name = player;
    auto_player = false;
}

int TicTacToeGame::generateScore(unsigned int row, unsigned int col) {
    int score = 0;
    //if there're 2 opponent pieces, score is three, if there's only one, score is zero
    //if there's none, score is based on the number of own pieces, 2 points each
    const int two_oppo = 3;
    const int own = 2;
    const int one_oppo = 0;

    //calculate row
    int row_score = 0;
    bool oppo_exist_row = false; //represent whether there is an opponent game piece
    for(size_t x = 1; x < 4; ++x){
        if(board[Width*row + x].name == init){
            continue;
        }
        else if(board[Width*row + x].name == player){
            if(!oppo_exist_row){
                row_score += own;
            }
        }
        else{
            if(oppo_exist_row){
                row_score = two_oppo;
                oppo_exist_row = false;
            }
            else{
                row_score = one_oppo;
                oppo_exist_row = true;
            }
        }
    }
    score += row_score;

    //calculate col
    int col_score = 0;
    bool oppo_exist_col = false;
    for(size_t y = 1; y < 4; ++y){
        if(board[Width*y + col].name == init){
            continue;
        }
        else if(board[Width*y + col].name == player){
            if(!oppo_exist_col){
                col_score += own;
            }
        }
        else {
            if(oppo_exist_col){
                col_score = two_oppo;
                oppo_exist_col = false;
            }
            else{
                col_score = one_oppo;
                oppo_exist_col = true;
            }
        }
    }
    score += col_score;
    //calculate diagonal if it exists
    if(row - col == 2 || col - row == 2 || (col == 2 && row == 2)){ //(2,2)(1,3)(3,1)
        bool oppo_exist_dia1 = false;
        int dia_score1 = 0;
        size_t x = 1;
        size_t y = 3;
        int times = 0; //loop only execute 3 times for this diagonal
        while(times <= 2){
            if(board[Width*y + x].name == init){

            }
            else if(board[Width*y + x].name == player){
                if(!oppo_exist_dia1){
                    dia_score1 += own;
                }
            }
            else{
                if(oppo_exist_dia1){
                    dia_score1 = two_oppo;
                    oppo_exist_dia1 = false;
                }
                else{
                    dia_score1 = one_oppo;
                    oppo_exist_dia1 = true;
                }
            }
            ++times;
            ++x;
            --y;
        }
        score += dia_score1;
    }
    if(row == col){//(1,1)(2,2)(3,3)
        int dia_score2 = 0;
        bool oppo_exist_dia2 = false;
        for(size_t x = 1; x < 4; ++x){
            if(board[Width*x + x].name == init){
                continue;
            }
            else if(board[Width*x + x].name == player){
                if(!oppo_exist_dia2){
                    dia_score2 += own;
                }
            }
            else{
                if(oppo_exist_dia2){
                    dia_score2 = two_oppo;
                    oppo_exist_dia2 = false;
                }
                else{
                    dia_score2 = one_oppo;
                    oppo_exist_dia2 = true;
                }
            }
        }
        score += dia_score2;
    }

    return score;
}

void TicTacToeGame::print() {
    cout << *this << endl;
}

ostream& operator<<(ostream& o, TicTacToeGame& game){
    for(int row = game.Height-1; row >= 0; --row) {
        o << row;
        for (unsigned int col = 0; col < game.Width; ++col) {
            long long max = game.max_length;
            o << setw(max + 1) << game.board[row * game.Width + col].display;
        }
        o << endl;
    }
    o << init;
    for(unsigned int col = 0; col < game.Width; ++col){
        long long max = game.max_length;
        o << setw(max + 1) << col;
    }
    return o;
}