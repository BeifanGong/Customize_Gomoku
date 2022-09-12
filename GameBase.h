// GameBase.h
//
// This file declares the GameBase abstract class

#pragma once

#include <vector>
#include "GamePiece.h"
#include "Custom_TTT.h"

class GameBase{
protected:
    unsigned int Width;
    unsigned int Height;
    unsigned int max_length;
    unsigned int turns; //represent turns played
    std::string winner; //represent winner
    std::vector<GamePiece> board;

public:
    virtual bool done() = 0;
    virtual bool draw() = 0;
    virtual int prompt(unsigned int&, unsigned int&);
    virtual int turn() = 0;
    virtual int play();
    virtual void print() = 0;
    static GameBase* getGame(int, char**);
    virtual ~GameBase() = default;

    GameBase(unsigned int, unsigned int);
};
