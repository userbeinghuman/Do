#include "ui.hpp"

void ui::createTask(std::vector<Task> &tasks) {
    bool isCreated = false; //loop conditional var
    std::string str = "";

    //ui vars
    Font font = LoadFontEx("res/helvetica.otf", 30.0f, NULL, 0); //should i move shit around? dunno
    int textBoxWidth = 250;
    int textBoxHeight = 50;
    
    while(!isCreated && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        DrawTextPro(font, "Create New Task", {0, 0}, {0, 0}, 0.0f, 30.0f, 0.0f, BLACK);
        DrawRectangle(GetRenderWidth() / 2 - textBoxWidth / 2, GetRenderHeight() / 2 - textBoxHeight / 2, textBoxWidth, textBoxHeight, {75, 75, 75, 255});
        char pressedChar = GetCharPressed();

        if(pressedChar > 0)
            str += pressedChar;

        if(IsKeyPressed(KEY_BACKSPACE))
            if(str.length() > 0)
                str.pop_back();
        
        if(IsKeyReleased(KEY_ENTER) && str.length() > 0) {
            //TODO: MOVE COLOR TO GOOGLE.COM WHAT ???? AHHAHAHAHAH VUSBGJIWEBGU3239UROJWDNC S MAIN RENDER LOOP.ORG.RU.JP
            unsigned char color = tasks.size() * 15; //Calculating color
            tasks.push_back(Task(str.c_str(), "null", {(unsigned char)color, (unsigned char)color, 225, 255})); //Adding new task to tasks vector
            //TODO: strings with spaces break the file reader!! FIX!! empty description also breaks file reader thus needs fixing!! FIX!!

            saveEverything("tasks.do", tasks); //Saving changes to disk
            isCreated = true; //Ending loop
        }

        DrawTextPro(font, str.c_str(), {(float)GetRenderWidth() / 2 - textBoxWidth / 2, (float)GetRenderHeight() / 2 - textBoxHeight / 2}, {0, 0}, 0.0f, 30.0f, 0.0f, WHITE);
        EndDrawing();

        if(IsKeyDown(KEY_LEFT_CONTROL))
            if(IsKeyReleased(KEY_C)) 
                isCreated = true;
    }

    std::cout << "[DEBUG] ui::createTask >> Quitting...\n";
    UnloadFont(font);
}