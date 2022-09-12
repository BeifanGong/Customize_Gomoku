// TicTacToe.h
//
// This file defines the TicTacToe Class

#pragma once

#include <vector>
#include <iostream>

#include "GameBase.h"
#include "Custom_TTT.h"

class TicTacToeGame:public GameBase{
    friend std::ostream& operator<<(std::ostream&, TicTacToeGame&);
private:
    std::string player; //represent player
    bool auto_play; //represent whether the game will autoplay or not
    bool auto_player; //represent whether it is autoplayer's turn
    int generateScore(unsigned int, unsigned int); //generate a given score for a particular position used to determine the move of autoplayer

public:
    bool done() override;
    bool draw() override;
    int turn() override;
    void autoPlay();
    TicTacToeGame(bool auto_play);
    virtual void print() override;
};

std::ostream& operator<<(std::ostream&, TicTacToeGame&);

