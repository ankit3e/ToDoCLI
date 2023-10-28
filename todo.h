#ifndef TODO_H
#define TODO_H

#include <string>
#include <vector>
#include <unordered_map>
#include<fstream>
#include<sstream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

class Task {
private:
    static int nextID;
    int mId;
    int mDeadline;
    string mTitle;
    string mTaskDescription;
    bool mStatus;

public:
    Task(const string& title, const string& description, int deadline);
    Task();
    bool getStatus() const;
    int getId() const;
    string getTitle() const;
    string getDescription() const;
    int getDeadline() const;
    Task& setId(const int& id);
    Task& setTitle(const string& title);
    Task& setDescription(const string& description);
    Task& setStatus(const bool& status);
    Task& setDeadline(const int& deadline);
    string toString() const;
    
};

enum class Actions{
    ADD_TASK,
    EDIT_TASK,
    REMOVE_TASK,
    COMPLETE_TASK,
    VIEW_TASKS
};
std::unordered_map<string,Actions> getAction{
    {"add",Actions::ADD_TASK},
    {"edit",Actions::EDIT_TASK},
    {"remove", Actions::REMOVE_TASK},
    {"complete", Actions::COMPLETE_TASK},
    {"view", Actions::VIEW_TASKS}
};

class TaskStorage{
    private:
        void saveTasksToFile(const vector<Task>& tasks, const string& filename);
        vector<Task> loadTasksFromFile(const std::string& filename);
        json mTasksJsonArray;
        friend class TodoList;
};

class TodoList {
private:
    std::vector<Task> mTasks;
    std::unordered_map<int, Task> mTaskMap;
    const string fileName = "tasks.json";
    TaskStorage mTaskStorage;

public:
    TodoList();
    ~TodoList();
    void addTask(const std::string& title, const std::string& description, int deadline);
    void printAllTasks() const;
};

#endif
