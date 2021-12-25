/******************************************************************************
 * AUTHOR         : BRYCE BERWALD
 ******************************************************************************/

#include "main.h"

// Created enum type for game screens to be displayed to the user.
enum ScreenOption {
    Exit,
    PreGame,
    InGame,
};

// Created struct for falling rectangles.
struct RectangleBlocks {
    Rectangle block;
    bool falling;
    RectangleBlocks *next;
};

int main(int argc, char* argv[])
{
    // Change the current directory to the root of the project.
    char path_save[1024];
    char cwd[1024];
    char* p;
    if(!(p = strrchr(argv[0], '/')))
        getcwd(cwd, sizeof(cwd));
    else
    {
        *p = '\0';
        getcwd(path_save, sizeof(path_save));
        chdir(argv[0]);
        getcwd(cwd, sizeof(cwd));
        chdir(path_save);
    }
    string NEW_WORKING_DIR = string(cwd) + "/";
    chdir(NEW_WORKING_DIR.c_str());

    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "Tetris Remake | Made by: Bryce Berwald");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    int gameScreen = ScreenOption::PreGame;

    const int ARR_SIZE = 500;
    RectangleBlocks fallingBlocks[ARR_SIZE];

    int currentIndex = 0;

    // Variables used to move the current falling rectangle type.
    // Initialized to default coordinate values positioned at the top left corner of screen.
    float fallingX = 0;
    float fallingY = 0;

    // Created rectangle type for the floor.
    Rectangle floor = {0, 780, 1280, 20};

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ostringstream ss;
            string mouseValues;
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            ostringstream stream;
            string recValues;

            ClearBackground(WHITE);

            switch(gameScreen){
                case ScreenOption::Exit:
                    // Code for terminating the program.
                    CloseWindow();
                    break;
                case ScreenOption::PreGame:
                    // Code for the pre-game.
                    ClearBackground(GRAY);
        
                    ss << "Mouse X Value is: " << mouseX << endl;
                    ss << "Mouse Y Value is: " << mouseY << endl;

                    mouseValues = ss.str();
                    DrawText(mouseValues.c_str(), 0, 0, 24, WHITE);

                    DrawRectanglePro({screenWidth/2-100, screenHeight/2-50, 200, 50}, {0,0}, 0.0f, BLACK);
                    DrawText("Play Game", screenWidth/2-45, screenHeight/2-30, 18, WHITE);
                    break;
                case ScreenOption::InGame:
                    // Code for the in game menu.
                    ClearBackground(BLUE);

                    // Display counter data in top right corner of screen.
                    stream << "Total fall count: " << currentIndex+1;
                    recValues = stream.str();
                    DrawText(recValues.c_str(), 1050, 10, 20, WHITE);

                    // Draw the floor.
                    DrawRectanglePro(floor, {0,0}, 0.0f, BLACK);

                    // Initialize current array struct to these values.
                    fallingBlocks[currentIndex].falling = true;
                    fallingBlocks[currentIndex].block = {fallingX, fallingY, 50, 50};

                    // Draw array of falling rectangle structs that have been created already.
                    for(int i = 0; i < ARR_SIZE-1; i++){
                        DrawRectanglePro(fallingBlocks[i].block, {0,0}, 0.0f, RED);
                    }

                    // Move the current falling rectangle only.
                    if(fallingBlocks[currentIndex].falling){
                        fallingY += 5;
                    }

                    // Check for collisions against the floor.
                    if(CheckCollisionRecs(floor, fallingBlocks[currentIndex].block)){
                        fallingBlocks[currentIndex].falling = false;
                        currentIndex++;
                        fallingX = 0;
                        fallingY = 0;
                    }

                    // Check for collision against other rectangles.
                    for(int i = 0; i < currentIndex; i++){
                        if(CheckCollisionRecs(fallingBlocks[i].block, fallingBlocks[currentIndex].block)){
                            fallingBlocks[currentIndex].falling = false;
                            currentIndex++;
                            fallingX = 0;
                            fallingY = 0;
                        }
                    }

                    // Allow player to move rectangles from the right or to the left.
                    if(IsKeyPressed(KEY_LEFT)){
                        fallingX -= 50;
                    } else if (IsKeyPressed(KEY_RIGHT)){
                        fallingX += 50;
                    }

                    break;
                default:
                    // Code for error checking!!!
                    
                    break;
            }

            // For click location on pre game screen to start the game.
            if(gameScreen == 1 && (mouseX > 540 && mouseX < 740 && mouseY > 351 && mouseY < 401)){
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    gameScreen = ScreenOption::InGame;
                }
            }

        EndDrawing();
        //----------------------------------------------------------------------------------

    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}