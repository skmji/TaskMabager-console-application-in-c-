#include <iostream>
#include <queue>
#include <stack>
#include <fstream>
#include <string>
using namespace std;
/* **AUTHOR**
   **SANJAY KUMAR MAURY**
   **22BCA10531**
 */   
class Task {
public:
    int id;
    string description;
    int priority;
    int num; // For table, square, cube tasks

    Task(int id, string description, int priority, int num = 0)
        : id(id), description(description), priority(priority), num(num) {}

    virtual void performTask() {
        cout << "Performing Task ID: " << id << " | " << description << endl;
    }
};

class PrintTableTask : public Task {
public:
    PrintTableTask(int id, int num, int priority)
        : Task(id, "Print Table of " + to_string(num), priority, num) {}

    void performTask() override {
        cout << "Table of " << num << ":" << endl;
        for (int i = 1; i <= 10; i++) {
            cout << num << " x " << i << " = " << num * i << endl;
        }
    }
};

class PrintSquareTask : public Task {
public:
    PrintSquareTask(int id, int num, int priority)
        : Task(id, "Print Square of " + to_string(num), priority, num) {}

    void performTask() override {
        cout << "Square of " << num << ": " << num * num << endl;
    }
};

class PrintCubeTask : public Task {
public:
    PrintCubeTask(int id, int num, int priority)
        : Task(id, "Print Cube of " + to_string(num), priority, num) {}

    void performTask() override {
        cout << "Cube of " << num << ": " << num * num * num << endl;
    }
};

class PrintStarPatternTask : public Task {
public:
    PrintStarPatternTask(int id, int num, int priority)
        : Task(id, "Print Star Pattern of " + to_string(num), priority, num) {}

    void performTask() override {
        cout << "Star Pattern of " << num << " rows:" << endl;
        for (int i = 1; i <= num; i++) {
            for (int j = 1; j <= i; j++) {
                cout << "* ";
            }
            cout << endl;
        }
    }
};

class TaskManager {
public:
    struct ComparePriority {
        bool operator()(Task* a, Task* b) {
            return a->priority < b->priority; // Higher priority first
        }
    };

    priority_queue<Task*, vector<Task*>, ComparePriority> taskQueue;
    stack<Task*> undoStack;
    stack<Task*> redoStack;
    int taskCounter;

public:
    TaskManager() : taskCounter(0) {}

    void addTask(Task* task) {
        taskQueue.push(task);
        cout << "Task added successfully!" << endl;
    }

    void processTask() {
        if (taskQueue.empty()) {
            cout << "No tasks available to process." << endl;
            return;
        }

        Task* task = taskQueue.top();
        taskQueue.pop();
        task->performTask();
        undoStack.push(task);
    }

    void undoLastAction() {
        if (undoStack.empty()) {
            cout << "Nothing to undo." << endl;
            return;
        }
        Task* lastTask = undoStack.top();
        undoStack.pop();
        redoStack.push(lastTask);
        cout << "Undo: Last task undone." << endl;
    }

    void redoLastAction() {
        if (redoStack.empty()) {
            cout << "Nothing to redo." << endl;
            return;
        }
        Task* lastTask = redoStack.top();
        redoStack.pop();
        undoStack.push(lastTask);
        taskQueue.push(lastTask);
        cout << "Redo: Task re-added to queue." << endl;
    }

    void viewAllTasks() {
        if (taskQueue.empty()) {
            cout << "No tasks available." << endl;
            return;
        }

        priority_queue<Task*, vector<Task*>, ComparePriority> tempQueue = taskQueue;
        cout << "Tasks in queue:" << endl;
        while (!tempQueue.empty()) {
            Task* task = tempQueue.top();
            tempQueue.pop();
            cout << "Task ID: " << task->id << ", Description: " << task->description << ", Priority: " << task->priority << endl;
        }
    }
};

void displayMenu() {
    cout << "\nTask Manager Menu:" << endl;
    cout << "1. Add Task to Print Table of a Number" << endl;
    cout << "2. Add Task to Print Square of a Number" << endl;
    cout << "3. Add Task to Print Cube of a Number" << endl;
    cout << "4. Add Task to Print Star Pattern" << endl;
    cout << "5. Process Highest Priority Task" << endl;
    cout << "6. View All Tasks" << endl;
    cout << "7. Undo Last Action" << endl;
    cout << "8. Redo Last Action" << endl;
    cout << "9. Exit" << endl;
}

int main() {
    TaskManager manager;
    int choice, number, priority;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the number for the table: ";
                cin >> number;
                cout << "Enter the task priority: ";
                cin >> priority;
                manager.addTask(new PrintTableTask(++manager.taskCounter, number, priority));
                break;

            case 2:
                cout << "Enter the number to find square: ";
                cin >> number;
                cout << "Enter the task priority: ";
                cin >> priority;
                manager.addTask(new PrintSquareTask(++manager.taskCounter, number, priority));
                break;

            case 3:
                cout << "Enter the number to find cube: ";
                cin >> number;
                cout << "Enter the task priority: ";
                cin >> priority;
                manager.addTask(new PrintCubeTask(++manager.taskCounter, number, priority));
                break;

            case 4:
                cout << "Enter the number of rows for the star pattern: ";
                cin >> number;
                cout << "Enter the task priority: ";
                cin >> priority;
                manager.addTask(new PrintStarPatternTask(++manager.taskCounter, number, priority));
                break;

            case 5:
                manager.processTask();
                break;

            case 6:
                manager.viewAllTasks();
                break;

            case 7:
                manager.undoLastAction();
                break;

            case 8:
                manager.redoLastAction();
                break;

            case 9:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}
