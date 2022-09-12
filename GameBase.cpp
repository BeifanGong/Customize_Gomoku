// Gamebase.cpp
//
// This file defines the methods in the GameBase class

#include <iostream>
#include <sstream>
#include "GameBase.h"
#include "TicTacToeGame.h"
#include "Gomoku.h"

using namespace std;

string init = " ";

int GameBase::prompt(unsigned int& row, unsigned int& col){
    string input;

    //prompt for an input string
    cout << "Please make a move: <col, row>" << endl;
    cout << "Enter \"quit\" to end the game" << endl;
    cin >> input;
    size_t index = input.find_first_of(",");
    //if the string does not contain quit or a comma, re-prompt
    while(input.compare("quit") != 0 && index == -1){
        cout << "Invalid input" << endl;
        cout << "Please make a move: <col, row>" << endl;
        cout << "Enter \"quit\" to end the game" << endl;
        cin >> input;
        index = input.find_first_of(",");
    }

    if(input.compare("quit") == 0){
        return quit;
    }
    else{
        input.replace(index, 1, " ");
        istringstream iss(input);
        //if extraction of coordinate fails or coordinate is invalid, re-prompt
        while(!(iss >> col) || !(iss >> row) || row >= Height - 1 || col >= Width -1 || row < 1 || col < 1){
            cout << "Invalid input" << endl;
            cout << "Please make a move: <col, row>" << endl;
            cout << "Enter \"quit\" to end the game" << endl;
            cin >> input;
            index = input.find_first_of(",");
            while(input.compare("quit") != 0 && index == -1){
                cout << "Invalid input" << endl;
                cout << "Please make a move: <col, row>" << endl;
                cout << "Enter \"quit\" to end the game" << endl;
                cin >> input;
                index = input.find_first_of(",");
            }
            if(input.compare("quit") == 0){
                return quit;
            }
            input.replace(index, 1, " ");
            iss = istringstream(input);
        }
        return success;
    }
}

int GameBase::play(){
    print();
    while(!done() && !draw() && (turn() != quit)){

    }
    if(done()){
        cout << winner << " won the game." << endl;
        return success;
    }
    else if(draw()){
        cout << turns << " turns played." << endl;
        cout << "Game is a draw." << endl;
        return game_draw;
    }
    else{
        cout << "Game quits." << endl;
        return quit;
    }
}

GameBase* GameBase::getGame(int argc, char **argv) {
    GameBase* game= nullptr;
    const int match = 0;
    //with only one parameter
    if(argc == argument_num_nopar){
        if(strcmp(argv[instruction], "TicTacToe") == match){
            game = new TicTacToeGame(false);
        }
        else if(strcmp(argv[instruction], "Gomoku") == match){
            game = new Gomoku(21,21,5);
        }
    }
    //with two parameters
    else if(argc == argument_num_onepar){
        if(strcmp(argv[instruction], "Gomoku") != match){
            cout << "You can only provide parameters for Gomoku." << endl;
            return game;
        }
        try{
            int dimension = stoi(argv[dim]);
            if(dimension < 3){
                cout << "Dimension must be greater than 3." << endl;
                return game;
            }
            else if(dimension < 5){
                game = new Gomoku(dimension+2, dimension+2, dimension);
            }
            else{
                game = new Gomoku(dimension+2, dimension+2, 5);
            }
        }
        catch (invalid_argument){
            return game;
        }
    }
    //with three parameters
    else if(argc == argument_num_twopar){
        if(strcmp(argv[instruction], "Gomoku") != match){
            cout << "You can only provide parameters for Gomoku." << endl;
            return game;
        }
        try{
            int dimension = stoi(argv[dim]);
            if(dimension < 3){
                cout << "Dimension must be greater than 3." << endl;
                return game;
            }
            int con = stoi(argv[condition]);
            if(con < 3){
                cout << "Winning conditions must be greater than 3." << endl;
                return game;
            }
            game = new Gomoku(dimension+2, dimension+2, con);
        }
        catch (invalid_argument){
            return game;
        }
    }
    return game;
}

GameBase::GameBase(unsigned Width, unsigned Height) : Width(Width), Height(Height), max_length(0), turns(0), winner(init){
    GamePiece empty;
    empty.name = init;
    empty.display = init;
    for (size_t i = 0; i < Width * Height; ++i) {
        board.push_back(empty);
    }
}
