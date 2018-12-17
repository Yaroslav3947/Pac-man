#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <cstddef>
#include <cstdio>
#include <ncurses.h>
#include <unistd.h>
#define COLOR_ROAD 1
#define COLOR_BORDER 2
#define COLOR_GAMEOVER 3
#define MAP_WIDTH 60
#define MAP_HEIGHT 20
#define KEY_ESC 27
#define KILLED 0
#define ALIVE 1
#define WON 2
using namespace std;
typedef vector<pair<char, short> > vPair;

#endif