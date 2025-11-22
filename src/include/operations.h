#pragma once

#include <string_view>

// Input/output operations
const short READ       = 10;
const short WRITE      = 11;

// Load and store operations
const short LOAD       = 20;
const short STORE      = 21;

// Arithmetic operations
const short ADD        = 30;
const short SUBTRACT   = 31;
const short DIVIDE     = 32;
const short MULTIPLY   = 33;

// Transfer-of-control operations
const short BRANCH     = 40;
const short BRANCHNEG  = 41;
const short BRANCHZERO = 42;

const short HALT       = 43;

std::string_view opcode_to_str(int opcode);