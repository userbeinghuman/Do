#include <iostream>
#include <vector>
#include <string>
#include "raylib/raylib.h"
#include "task.hpp"
#include "filehandler.hpp"
#include "ui.hpp"

#define SCALE 1
#define WINDOW_HEIGHT 600 * SCALE
#define WINDOW_WIDTH 300 * SCALE
#define TASK_WIDTH WINDOW_WIDTH * SCALE
#define TASK_HEIGHT 50 * SCALE
#define TASK_FONT_SIZE 30.0f * SCALE

//TODO: SERIOUS FLAW: SCALING BREAKS MOUSE CHECKBOX INPUT.

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Do");
    // SetWindowState(FLAG_WINDOW_UNDECORATED); step 1 (widget), will not enable now as i'm still debugging shit

    std::vector<Task> tasks;
    loadEverything("tasks.do", tasks); //Load tasks at start

    std::vector<Texture2D> textures;
    textures.push_back(LoadTexture("res/checked.png"));
    textures.push_back(LoadTexture("res/unchecked.png"));
    textures.push_back(LoadTexture("res/trash.png"));

    Font font = LoadFontEx("res/helvetica.otf", TASK_FONT_SIZE, NULL, 0);

    Color taskColor = {0, 150, 0, 255};
    bool minedOut = true;
    bool maxedOut = false;

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        //Debug Input Handling
        if(IsKeyDown(KEY_LEFT_CONTROL)) 
            if(IsKeyReleased(KEY_S))
                saveEverything("tasks.do", tasks);
            if(IsKeyReleased(KEY_L))
                loadEverything("tasks.do", tasks);
            if(IsKeyReleased(KEY_N))
                ui::createTask(tasks);
            

        //Input Handling
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            if(mouseX >= 0 && mouseX <= TASK_HEIGHT) { //Checking if mouse is inside of checkbox (x) [task_height is the same size as the checkbox]
                int clickedTaskIndex = mouseY / TASK_HEIGHT; 

                if(clickedTaskIndex < tasks.size()) { //Check if out of bounds
                    tasks[clickedTaskIndex].setIsChecked(!tasks[clickedTaskIndex].getIsChecked()); //invert checkbox status
                    saveEverything("tasks.do", tasks); //Save changes
                }
            }

            if(mouseX >= TASK_WIDTH - 50)
                deleteTask(tasks, mouseY / TASK_HEIGHT);
                saveEverything("tasks.do", tasks); //Save changes
        }

        //Hover Check (Kanye West & Drake Free Hover Los Angeles Charity Concert)
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        int hoverTaskIndex = -1;

        if(mouseX >= TASK_WIDTH - 50 && (mouseY / TASK_HEIGHT) < tasks.size())
            hoverTaskIndex = mouseY / TASK_HEIGHT; 
        // std::cout << "[DEBUG] main :: hoverTaskIndex = " << hoverTaskIndex << std::endl;jj

        //Rendering
        //TODO: move this to ui.hpp / renderTasks.cpp (will be useful for all other applications btw also i hate israel)
        for(int i = 0; i<tasks.size(); i++) {
            //TODO: work on this bullshit...
            if((int)taskColor.b == 0)
                minedOut = true;
                maxedOut = false;
            
            if((int)taskColor.b == 255)
                minedOut = false;
                maxedOut = true;
                
            if(minedOut) {
                int blue = (int)taskColor.b + 25;
                taskColor = {0, 150, (unsigned char)blue, 255};
                // taskColor.b += (unsigned char)25;
            }
            
            if(maxedOut) {
                int blue = (int)taskColor.b - 5;
                taskColor = {0, 150, (unsigned char)blue, 255};
                // taskColor.b -= (unsigned char)25;
            }
            // WaitTime(0.1);

            
            
            std::cout << "[DEBUG] :: main::renderLoop >> taskColor.b = " << (int)taskColor.b << " // i = " << i << std::endl;
            DrawRectangle(0, (TASK_HEIGHT * i), TASK_WIDTH, TASK_HEIGHT, taskColor);

            // int checkboxTextureIndex; 
            // if(tasks[i].getIsChecked())
            //     checkboxTextureIndex = 0;
            // else
            //     checkboxTextureIndex = 1;

            // DrawTextureEx(textures[checkboxTextureIndex], {0, (float)(TASK_HEIGHT * i)}, 0.0f, ((float)TASK_HEIGHT / textures[checkboxTextureIndex].width), WHITE);

            DrawRectangle(0 + 5, (TASK_HEIGHT * i) + 5, TASK_HEIGHT - 10, TASK_HEIGHT - 10, {225, 225, 225, 255});

            Color checkBoxColor;
            if(tasks[i].getIsChecked())
                checkBoxColor = {0, 30, 210, 255};
            else
                checkBoxColor = {100, 100, 100, 255};

            DrawRectangle(0 + 9, (TASK_HEIGHT * i) + 9, TASK_HEIGHT - 18, TASK_HEIGHT - 18, checkBoxColor);
            DrawTextEx(font, tasks[i].getName(), {(float)(TASK_HEIGHT + 15), (float)(TASK_HEIGHT * i)}, TASK_FONT_SIZE, 0.0f, WHITE);

            if(hoverTaskIndex > -1) {
                DrawRectangle(TASK_WIDTH - 50, TASK_HEIGHT * hoverTaskIndex, 50, TASK_HEIGHT, RED);
                DrawTextureEx(textures[2], {TASK_WIDTH - 50, (float)TASK_HEIGHT * hoverTaskIndex}, 0.0f, (float)30/(float)100, WHITE);
            }
        }

        EndDrawing();
    }

    //Freeing up memory (program end)
    for(Texture2D texture : textures)
        UnloadTexture(texture);
    textures.clear();

    UnloadFont(font);
    CloseWindow();

    return 0;
}