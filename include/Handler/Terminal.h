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
    int minRange;
    int cursorPos;
    int maxRange;
    void updateLoop();
    void clearTerminal();

public:
    Terminal() : lines({}), minRange(0), maxRange(5000), cursorPos(0), running(false) {}
    ~Terminal() {if (running) {stop();}}
    bool isRunning() {return running;}
    void minRangePos() {cursorPos = minRange = lines.size();}
    void maxRangePos() {maxRange = lines.size()-1;}
    int getCursorPos() {return cursorPos;}
    int getSize() {return lines.size();}
    std::string getLine(int index);
    std::vector<std::string>& getBuffer() {return lines;}
    void forwardCursor();
    void backwardsCursor();
    bool setLine(int index, std::string line);
    void addLine(const std::string& line);
    void highlightLine(int index);
    void print();
    void cut(int index);
    void start();
    void stop();
};

#endif  // TERMINAL_H