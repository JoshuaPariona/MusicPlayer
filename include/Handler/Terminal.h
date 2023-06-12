#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <functional>
#include "Handler/Terminal.h"

class Terminal {
private:
    std::vector<std::string> lines;
    std::thread updateThread;
    bool running;
    int cursorPos;
    void updateLoop();
    void clearTerminal();

public:
    Terminal() : lines({}), cursorPos(0), running(false) {}
    ~Terminal() {if (running) { stop();}}
    bool isRunning() {return running;}
    void forwardCursor();
    void backwardsCursor();
    bool setLine(int index, std::string& line);
    void addLine(const std::string& line);
    void highlightLine(int index);
    void print();
    void start();
    void stop();
};

#endif  // TERMINAL_H