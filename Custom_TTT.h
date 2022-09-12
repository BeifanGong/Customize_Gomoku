// Lab4.h
//
// This file defines two enums, one with the program parameters, one with the possible return values, and declares a usage function

#pragma once

#include <string>
#include "Custom_TTT.h"

enum parameters{
    program_name = 0,
    instruction = 1,
    dim = 2,
    condition = 3,
    argument_num_nopar = 2,
    argument_num_onepar = 3,
    argument_num_twopar = 4
};

enum return_values{
    wrong_argument = -1,
    success = 0,
    quit = 1,
    game_draw = 2
};

int usage_message(const std::string& c1, const std::string& c2);
