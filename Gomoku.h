// Gomoku.h
//
// This file declares the Gomoku class with its insertion operator

#pragma once

#include "GameBase.h"
#include <iostream>
#include <string>

class Gomoku:public GameBase{
    friend std::ostream& operator<<(std::ostream&, const Gomoku&);
private:
    std::string player; //represent current player
    unsigned int condition; //represent how many consecutive pieces are needed to win the game
public:
    Gomoku(unsigned int, unsigned int, unsigned int);
    virtual void print() override;
    virtual bool done() override;
    virtual bool draw() override;
    virtual int turn() override;
};

std::ostream& operator<<(std::ostream&, const Gomoku&);
