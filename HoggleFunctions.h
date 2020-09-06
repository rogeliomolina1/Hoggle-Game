#ifndef HOGGLEFUNCTIONS_H_INCLUDED
#define HOGGLEFUNCTIONS_H_INCLUDED
#include "lexicon.h"
#include "lpclib.h"
#include "hgraphics.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

string NumberToString ( int Number );

bool WordSolver(int r, int c, vector<int>&rows,vector<int>&columns,
                string remain);
void ComputerTurn(int r, int c, vector<int>rows,vector<int>columns,
                  string word, Lexicon*lex,vector<string>&playedWords);

#endif // HOGGLEFUNCTIONS_H_INCLUDED
