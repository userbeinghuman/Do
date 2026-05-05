#include "task.hpp"

//Task Class
Task::Task(const char *name, const char *description, Color bgColor) { //Default Constructor
    this->name = name;
    this->description = description;
    this->bgColor = bgColor;
    this->isChecked = false;
}

Task::Task(const char *name, const char *description, bool isChecked, Color bgColor) {
    this->name = name;
    this->description = description;
    this->bgColor = bgColor;
    this->isChecked = isChecked;
}

Task::Task(const Task& copy) { //Copy constructor
    this->name = copy.name;
    this->description = copy.description;
    this->isChecked = copy.isChecked;
    this->bgColor = copy.bgColor;
}

//Getters
const char *Task::getName() {
    return name.c_str();
}

const char *Task::getDescription() {
    return description.c_str();
}

bool Task::getIsChecked() {
    return isChecked;
}

Color Task::getBgColor() {
    return bgColor;
}

//Setters
void Task::setName(const char* name) {
    this->name = name;
}

void Task::setDescription(const char *description) {
    this->description = description;
}

void Task::setIsChecked(bool isChecked) {
    this->isChecked = isChecked;
}

void Task::setBgColor(Color bgColor) {
    this->bgColor = bgColor;
}

void deleteTask(std::vector<Task> &tasks, int index) {
    if(index < 0) {
        std::cout << "[DEBUG] Task::deleteTask >> Invalid Index! (" << index << ")\n";
        return;
    }

    tasks.erase(tasks.begin() + index);
    std::cout << "[DEBUG] Task::deleteTask >> Delete Element @ Index [" << index << "]\n";
}