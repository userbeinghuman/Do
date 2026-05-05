#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "raylib/raylib.h"

class Task {
    private:
        //Logic
        std::string name;
        std::string description;
        bool isChecked;

        Color bgColor; //Default = white/transparent //MOVE TO MAIN RENDER LOOP TO MAKE INDEPENDENT :PPP
        time_t endTime; //Default = 0
    public:
        //Constructors

        Task(const char *name, const char *description, Color bgColor);

        Task(const char *name, const char *description, bool isChecked, Color bgColor);

        Task(const Task& copy);
        
        //Getters
        const char *getName();

        const char *getDescription();

        bool getIsChecked();

        Color getBgColor();

        //Setters
        void setName(const char* name);

        void setDescription(const char *description);

        void setIsChecked(bool isChecked);
        
        void setBgColor(Color bgColor);
};

void deleteTask(std::vector<Task> &tasks, int index);