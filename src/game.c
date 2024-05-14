#include "../lib/game.h"
// LOGIC VARIABLES
int currentLocation;
int gameDifficulty;
int board[3][3];
int currentPlay;
bool plays[10];
bool rect_initd;
bool animationEnded;
bool mouseWasPressed;
pos order[10];
Rectangle text_EasyMode = {100, 100, 13 * 30, 30};
Rectangle text_MediumMode = {100, 150, 13 * 15, 30};
Rectangle text_HardMode = {100, 200, 13 * 13, 30};
Rectangle rect_board[3][3];
Color colors[3][3];
Sound sound;
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
    CloseAudioDevice();
}
// INIT VARIABLES
void init()
{
    animationEnded = false;
    mouseWasPressed = false;
    rect_initd = false;
    srand(time(NULL));
    currentLocation = initialScreen;
    InitWindow(screenWidth, screenHeight, "Memorizer - Raylib");
    InitAudioDevice();
    sound = LoadSound("./resources/sound.mp3");
    SetTargetFPS(60);
    // initOrder();
}
void initOrder()
{
    for (int x = 0; x < 3 * gameDifficulty; x++)
    {
        order[x].x = rand() % 3;
        order[x].y = rand() % 3;
        plays[x] = false;
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
        case loseScreen:
            render_loseScreen();
            break;
        case winScreen:
            render_winScreen();
            break;
        default:
            break;
        }

        EndDrawing();
    }
}
void render_winScreen()
{
    DrawText("YOU WON!!", 200, 300, 50, BLACK);
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

    if (animationEnded)
    {
        for (int x = 0; x < 10; x++)
        {
            updatePlay(x);
        }
    }
}

void render_loseScreen()
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
            initOrder();
        }
        else if (CheckCollisionPointRec(GetMousePosition(), text_MediumMode))
        {
            currentLocation = gameScreen;
            gameDifficulty = medium;
            initOrder();
        }
        else if (CheckCollisionPointRec(GetMousePosition(), text_HardMode))
        {
            currentLocation = gameScreen;
            gameDifficulty = hard;
            initOrder();
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
            if (!rect_initd)
            {
                Rectangle temp = {160 * w + 170, 160 * h + 80, 150, 150};
                rect_board[w][h] = temp;
            }
        }
    }
    rect_initd = true;
}
void animateBoard()
{
    static int frameCounter = 0;
    static int frameCounter2 = 0;
    static int currentOrderIndex = 0;
    const int framesPerColor = 60;

    frameCounter++;

    if (frameCounter >= framesPerColor && currentOrderIndex < 3 * gameDifficulty)
    {
        PlaySound(sound);
        colors[order[currentOrderIndex].x][order[currentOrderIndex].y] = BLUE;
        frameCounter2++;

        if (frameCounter2 >= framesPerColor)
        {
            colors[order[currentOrderIndex].x][order[currentOrderIndex].y] = RED;
            frameCounter = 0;
            frameCounter2 = 0;
            currentOrderIndex++;
        }
    }

    if (currentOrderIndex >= 3 * gameDifficulty)
    {
        animationEnded = true;
    }
}

void updatePlay(int currentPlay)
{
    if (!plays[currentPlay] && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !mouseWasPressed)
    {
        mouseWasPressed = true;
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                if (CheckCollisionPointRec(GetMousePosition(), rect_board[x][y]))
                {
                    printf("User clicked in rect: %d %d\n", x, y);
                    plays[currentPlay] = true;
                    if (order[currentPlay].x != x || order[currentPlay].y != y)
                        currentLocation = loseScreen;

                    plays[currentPlay] = true;
                    PlaySound(sound);
                    colors[x][y] = BLUE;
                    SetMouseCursor(MOUSE_CURSOR_ARROW);
                    int countdown = 10;
                    while (countdown > 0)
                    {
                        update();
                        render();
                        countdown--;
                    }
                    colors[x][y] = RED;
                    if (currentPlay == (3 * gameDifficulty) - 1)
                        currentLocation = winScreen;
                    return;
                }
            }
        }
    }
    else if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        mouseWasPressed = false;
    }
}
