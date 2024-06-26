#include "raylib.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define screenWidth 800
#define screenHeight 600

enum screenLocation
{
    initialScreen = 0,
    gameScreen = 1,
    loseScreen = 2,
    winScreen = 3
};

enum gameDifficulty
{
    easy = 1,
    medium = 2,
    hard = 3
};

typedef struct
{
    int x;
    int y;
} pos;

void run();

void init();
void initOrder();

void render();

void render_initialScreen();
void render_gameScreen();
void render_loseScreen();
void render_winScreen();

void update();

void update_initialScreen();

void updatePlay(int currentPlay);

void drawBoard();
void animateBoard();