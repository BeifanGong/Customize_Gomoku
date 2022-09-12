// Gomoku.cpp
//
// This file defines the methods for Gomoku Game

#include "Gomoku.h"
#include "Custom_TTT.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

const string init = " ";
const string B = "B";
const string W = "W";
const string X = "X";
const string B_n = "Black Stone";
const string W_n = "White Stone";

Gomoku::Gomoku(unsigned int Width, unsigned int Height, unsigned int condition):GameBase(Width, Height), player(B), condition(condition){
    max_length = 2;
}

void Gomoku::print(){
    cout << *this << endl;
}

bool Gomoku::done(){
    vector<unsigned int> toLeft; //record how many consecutive pieces are to the left of the entry, starting from it
    vector<unsigned int> toUp; //record how many consecutive pieces are to the up of the entry, starting from it
    vector<unsigned int> toUpperLeft; //record how many consecutive pieces are to the upper left of the entry, starting from it
    vector<unsigned int> toUpperRight; //represent how many consecutive pieces are to the upper right of the entry, starting from it
    //initialize all records
    for(unsigned int row = 0; row < Height; ++row){
        for(unsigned int col = 0; col < Width; ++col){
            toLeft.push_back(0);
            toUp.push_back(0);
            toUpperLeft.push_back(0);
            toUpperRight.push_back(0);
        }
    }

    for(unsigned int row = 1; row < Height-1; ++row){
        for(unsigned int col = 1; col < Width-1; ++col){
            unsigned int index = Width * row + col;
            if(board[index].display != init && col > 0 && board[index-1].display == board[index].display){ //has a same left piece
                toLeft[index] = 1 + toLeft[index-1];
                if(toLeft[index] == condition-1){ //found n consecutive in a row
                    winner = board[index].display;
                    return true;
                }
            }
            if(board[index].display != init && row > 0 && board[index - Width].display == board[index].display){ //has a same up piece
                toUp[index] = 1 + toUp[index - Width];
                if(toUp[index] == condition-1){ //found n consecutive in a col
                    winner = board[index].display;
                    return true;
                }
            }
            if(board[index].display != init && row > 0 && col > 0 && board[index - Width - 1].display == board[index].display) { //has a same upperLeft piece
                toUpperLeft[index] = 1 + toUpperLeft[index - Width - 1];
                if(toUpperLeft[index] == condition-1){ //found n consecutive in main diagonal direction
                    winner = board[index].display;
                    return true;
                }
            }
        }
    }

    for(unsigned int row = 1; row < Height-1; ++row){
        for(unsigned int col = Width - 2; col > 0; --col){
            unsigned int index = Width * row + col;
            if(board[index].display != init && row > 0 && col < Width - 1 && board[index - Width + 1].display == board[index].display) { //has a same upperLeft piece
                toUpperRight[index] = 1 + toUpperRight[index - Width + 1];
                if(toUpperRight[index] == condition-1){ //found n consecutive in anti-diagonal direction
                    winner = board[index].display;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Gomoku::draw(){

    if(done()){
        return false;
    }

    //check for rows
    for(unsigned int row = 1; row < Height - 1; ++row){
        for(unsigned int col = 1; col < Width - condition; ++col){
            unsigned int index = Width * row + col;
            if(board[index].display == init){
                unsigned int B_count = 0;
                unsigned int W_count = 0;
                for(unsigned int scope = 1; scope < condition; ++scope){
                    if(board[index+scope].display == B){
                        ++B_count;
                    }
                    else if(board[index+scope].display == W){
                        ++W_count;
                    }
                }
                //found a row that can lead to non-draw
                if(!(B_count > 0 && W_count > 0)){
                    return false;
                }
            }
        }
    }
    //check for cols
    for(unsigned int row = 1; row < Height-condition; ++row){
        for(unsigned int col = 1; col < Width-1; ++col){
            unsigned int index = Width * row + col;
            if(board[index].display == init){
                unsigned int B_count = 0;
                unsigned int W_count = 0;
                for(unsigned int scope = 1; scope < condition; ++scope){
                    if(board[index+scope*Width].display == B){
                        ++B_count;
                    }
                    else if(board[index+scope*Width].display == W){
                        ++W_count;
                    }
                }
                //found a col that can lead to non-draw
                if(!(B_count > 0 && W_count > 0)){
                    return false;
                }
            }
        }
    }

    //check for diagonals
    for(unsigned int row = 1; row < Height-condition; ++row){
        for(unsigned int col = 1; col < Width-condition; ++col){
            unsigned int index = Width * row + col;
            if(board[index].display == init){
                unsigned int B_count = 0;
                unsigned int W_count = 0;
                for(unsigned int scope = 1; scope < condition; ++scope){
                    if(board[index+scope*Width+scope].display == B){
                        ++B_count;
                    }
                    else if(board[index+scope*Width+scope].display == W){
                        ++W_count;
                    }
                }
                //found a diagonal that can lead to non-draw
                if(!(B_count > 0 && W_count > 0)){
                    return false;
                }
            }
        }
    }

    //check for anti-diagonals
    for(unsigned int row = 1; row < Height-condition; ++row){
        for(unsigned int col = condition; col < Width-1; ++col){
            unsigned int index = Width * row + col;
            if(board[index].display == init){
                unsigned int B_count = 0;
                unsigned int W_count = 0;
                for(unsigned int scope = 1; scope < condition; ++scope){
                    if(board[index+scope*Width-scope].display == B){
                        ++B_count;
                    }
                    else if(board[index+scope*Width-scope].display == W){
                        ++W_count;
                    }
                }
                //found an anti-diagonal that can lead to non-draw
                if(!(B_count > 0 && W_count > 0)){
                    return false;
                }
            }
        }
    }

    return true;
}

int Gomoku::turn(){
    unsigned int row;
    unsigned int col;

    GamePiece B_p;
    GamePiece W_p;
    B_p.display = B;
    B_p.name = B_n;
    W_p.display = W;
    W_p.name = W_n;

    cout << "Player " << player << "\'s turn." << endl;
    if(prompt(row, col) == quit){
        return quit;
    }
    //found out that the place has already been occupied
    while(board[Width * row + col].name != init){
        cout << "Already taken, use another position." << endl;
        if(prompt(row, col) == quit) {
            return quit;
        }
    }
    //change player
    if(player == B){
        board[Width * row + col] = B_p;
    }
    else{
        board[Width * row + col] = W_p;
    }

    print();
    cout << "Player " << player << ": ";

    //find out how many same pieces
    ostringstream oss;
    for(size_t y = 1; y < Height-1; ++y){
        for(size_t x = 1; x < Width-1; ++x){
            if(board[Width * y + x].display == player){
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
    if(player == B){
        player = W;
    }
    else{
        player = B;
    }
    ++turns;
    return success;
}
ostream& operator<<(std::ostream& o, const Gomoku& game){
    long long max_ = game.max_length;
    for(unsigned int row = game.Height-2; row > 0; --row) {
        o << setw(max_) << row;
        for (unsigned int col = 1; col < game.Width-1; ++col) {
            o << setw(max_ + 1) << game.board[row * game.Width + col].display;
        }
        o << endl;
    }
    o << init << X;
    //print bottom boarder
    for(unsigned int col = 1; col < game.Width-1; ++col){
        long long max = game.max_length;
        o << setw(max + 1) << col;
    }
    return o;
}