#ifndef DIRECTIVE_H
#define DIRECTIVE_H

#include <iostream>
#include <unordered_map>

class Directive {
private:
    char** argv;
    const int argc;
    std::unordered_map<std::string,void(*)()> directive_map;
    
    static void printVersion();
    static void printHelp();
    static void printCredits();

public:
    Directive(const int c, char** v);
    ~Directive() = default;

    void setDirectives();
    void init();
};

#endif