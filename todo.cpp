#include "todo.h"
#include <iostream>
using namespace std;
int Task::nextID = 0;
// Task Class 
Task::Task( const std::string& title,const std::string& description, int deadline)
    : mId(nextID++), mTitle(title), mTaskDescription(description), mDeadline(deadline), mStatus(false) {
}
Task::Task(){}
int Task::getId() const {
    return mId;
}
string Task::getTitle() const {
    return mTitle;
}
string Task::getDescription() const {
    return mTaskDescription;
}
bool Task::getStatus() const {
    return mStatus;
}
int Task::getDeadline() const{
    return mDeadline;
}

Task& Task::setStatus(const bool& status) {
    this->mStatus = status;
    return *this;
}

Task& Task::setId(const int& id){
    this->mId =  id;
    return *this;
}

Task& Task::setTitle(string const& title) {
   this->mTitle = title;
   return *this;
}

Task& Task::setDescription(string const& description) {
    this->mTaskDescription = description;
    return *this;
}

Task& Task::setDeadline(int const& deadline) {
    this->mDeadline = deadline;
    return *this;
}

string Task::toString() const {
    string task = "\n" + mTitle + " " + mTaskDescription + " " + (mStatus ? "Completed" : "Uncompleted") + " " + std::to_string(mDeadline);
    return task;
}


// TodoList class
TodoList::TodoList(){
    mTasks = mTaskStorage.loadTasksFromFile(fileName);
    for(auto itr: mTasks){
        if(mTaskMap.count(itr.getId())==0) {
            mTaskMap.insert({itr.getId(),itr});
        }
    }

}

TodoList::~TodoList(){
    mTaskStorage.saveTasksToFile(mTasks,fileName);
}
void TodoList::addTask(const string& title, const string& description, int deadline) {
    Task newTask(title, description, deadline);
    mTasks.push_back(newTask);
    int id = newTask.getId();
    mTaskMap.insert({id, newTask});
    mTaskStorage.saveTasksToFile(mTasks,fileName);
    // cout<<newTask.toString();

}

void TodoList::printAllTasks() const {
    for (const auto& itr : mTasks) {
        cout << itr.toString() << "\n";
    }
}

void TaskStorage::saveTasksToFile(const vector<Task>& tasks, const string& filename) {
    ofstream outFile(filename);
    json mTasksJsonArray;
    for(const Task& task: tasks) {
        json taskJson;
        taskJson["id"] = task.getId();
        taskJson["title"] =  task.getTitle();
        taskJson["description"] = task.getDescription();
        taskJson["status"] =  task.getStatus();
        taskJson["deadline"] = task.getDeadline();
        mTasksJsonArray.push_back(taskJson);
    }
    outFile<<mTasksJsonArray.dump(4);
    outFile.close();
}
vector<Task> TaskStorage::loadTasksFromFile(const std::string& filename) {
    vector<Task> tasks;
    json mTasksJsonArray;
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open file for reading.\n";
        goto exit;
    }

    
    inFile >> mTasksJsonArray;
    inFile.close();
    for (const auto& taskJson: mTasksJsonArray){
        Task mTask;
        mTask.setId(taskJson["id"])
             .setTitle(taskJson["title"])
             .setDescription(taskJson["description"])
             .setStatus(taskJson["status"])
             .setDeadline(taskJson["deadline"]);
        tasks.push_back(mTask);
    }
    exit:
    return tasks;
}


//Main function
int main(int argc, char* argv[]) {

    TodoList mTodoList;
    if (argc > 1) {
        string cmd = argv[1];
        
        if(getAction.count(cmd)!=0) {
            switch (getAction[cmd])
            {
            case Actions::ADD_TASK:
                cout<<"Added a new task";
                mTodoList.addTask(argv[2],argv[3],stoi(argv[4]));
                break;
            case Actions::COMPLETE_TASK:
                cout<<"Completed a task";
                break;
            case Actions::REMOVE_TASK:
                cout<<"Remove task";
                break;
            case Actions::EDIT_TASK:
                cout<<"Edit task";
                break;
            case Actions::VIEW_TASKS:
                mTodoList.printAllTasks();
                break;
            default:
                cout<<"Unknown task";
                break;
            }
        }
        else {
            cout<<"Unknow command";
        }
    }
    return 0;
}