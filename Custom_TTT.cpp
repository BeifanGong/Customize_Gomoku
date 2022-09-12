// Lab4.cpp
// This file contains the main method, which runs the games

#include <iostream>
#include "GameBase.h"

using namespace std;

int main(int argc, char* argv[])
{
    GameBase* game = GameBase::getGame(argc, argv);
    if(game == nullptr){
        return usage_message(argv[program_name], "<game_name> [dimension] [win_condition]");
    }
    else{
        int result = game->play();
        delete game;
        return result;
    }
}

int usage_message(const string& c1, const string& c2) {
    string message = "usage: ";
    message += c1;
    message += " ";
    message += c2;
    cout << message << endl;
    return wrong_argument;
}

