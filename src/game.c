#include "../lib/game.h"
int currentLocation;
int gameDifficulty;
int board[3][3];
int currentPlay;
pos order[10];
Rectangle text_EasyMode = {100, 100, 13 * 30, 30};
Rectangle text_MediumMode = {100, 150, 13 * 15, 30};
Rectangle text_HardMode = {100, 200, 13 * 13, 30};
Rectangle rect_board[3][3];
Color colors[3][3];
// MAIN FUNCTION>
void run()
{
    init();

    while (!WindowShouldClose())
    {
        update();
        render();
    }

    CloseWindow();
}
// INIT VARIABLES
void init()
{
    srand(time(NULL));
    currentLocation = initialScreen;
    InitWindow(screenWidth, screenHeight, "Memorizer - Raylib");
    SetTargetFPS(60);
    initOrder();
}
void initOrder()
{
    for (int x = 0; x < 10; x++)
    {
        order[x].x = rand() % 3;
        order[x].y = rand() % 3;
    }
    for (int w = 0; w < 3; w++)
    {
        for (int h = 0; h < 3; h++)
        {
            colors[w][h] = RED;
        }
    }
}
// RENDER FUNCTIONS
void render()
{
    BeginDrawing();
    {
        ClearBackground(RAYWHITE);

        switch (currentLocation)
        {
        case initialScreen:
            render_initialScreen();
            break;
        case gameScreen:
            render_gameScreen();
            break;
        case endScreen:
            render_endScreen();
            break;
        default:
            break;
        }

        EndDrawing();
    }
}
void render_initialScreen()
{
    DrawText("Memorizer", 300, 0, 50, BLACK);
    DrawText("-> Easy mode", 100, 100, 30, BLACK);
    DrawText("-> Medium mode", 100, 150, 30, BLACK);
    DrawText("-> Hard mode", 100, 200, 30, BLACK);
}
void render_gameScreen()
{
    DrawText("Follow the Order", 200, 0, 50, BLACK);
    drawBoard();
    animateBoard();
}
void render_endScreen()
{
    DrawText("At end Screen", 200, 300, 50, BLACK);
}
// UPDATE FUNCTIONS
void update()
{
    switch (currentLocation)
    {
    case initialScreen:
        update_initialScreen();
        break;

    default:
        break;
    }
}
void update_initialScreen()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(GetMousePosition(), text_EasyMode))
        {
            currentLocation = gameScreen;
            gameDifficulty = easy;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), text_MediumMode))
        {
            currentLocation = gameScreen;
            gameDifficulty = medium;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), text_HardMode))
        {
            currentLocation = gameScreen;
            gameDifficulty = hard;
        }
    }
}
void drawBoard()
{
    for (int w = 0; w < 3; w++)
    {
        for (int h = 0; h < 3; h++)
        {
            DrawRectangle(160 * w + 170, 160 * h + 80, 150, 150, colors[w][h]);
        }
    }
}
void animateBoard()
{
    static int frameCounter = 0;
    static int frameCounter2 = 0;
    static int currentOrderIndex = 0;
    const int framesPerColor = 60;

    frameCounter++;

    if (frameCounter >= framesPerColor && currentOrderIndex < 11)
    {
        colors[order[currentOrderIndex].x][order[currentOrderIndex].y] = BLUE;
        frameCounter2++;

        if (frameCounter2 >= framesPerColor)
        {
            colors[order[currentOrderIndex].x][order[currentOrderIndex].y] = RED;
            frameCounter = 0;
            frameCounter2 = 0;
            currentOrderIndex++;
        }
        // frameCounter = 0;
    }
}