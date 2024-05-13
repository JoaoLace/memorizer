#include "raylib.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define screenWidth 800
#define screenHeight 600

enum screenLocation
{
    initialScreen = 0,
    gameScreen = 1,
    endScreen = 2
};

enum gameDifficulty
{
    easy = 0,
    medium = 1,
    hard = 2
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
void render_endScreen();

void update();

void update_initialScreen();

void drawBoard();
void animateBoard();