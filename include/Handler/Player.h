#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <thread>
#include <SFML/Audio.hpp>
#include <DataStructs/Deque.h>
#include <../src/Deque.cpp>
#include <DataStructs/GenericTree.h>
//#include <../src/GenericTree.cpp>

class Player {
private:
    sf::Music music;
    GenericTree<std::string>& path_tree;
    std::string progressBar;
    std::string currentMusic;
    Deque<std::string> playlist;
    std::thread updateThread;
    bool ready_to_play;
    float part;
    void updateLoop();
    std::string trimString(const std::string& str);
    std::string secondsToMinutes(float seconds);
    std::string getPath(const std::string& filename, GenericTree<std::string>& parent);

public:
    Player(GenericTree<std::string>& tree) : ready_to_play(false), path_tree(tree), part(0), currentMusic("Select a Music") {
        progressBar = "0:00 [                                               ] 0:00";
    }
    ~Player() = default;

    void load(const std::string& filename);

    void play_current();
    void pause_current();
    void stop_current();
    void add_to_playlist(const std::string& filename);
    void add_front_playlist(const std::string& filename);
    void jump();
    void back();
    void next();
    
    Deque<std::string>& getPlayList() {return playlist;}
    std::string getProgressBar() {return progressBar;}
    std::string getCurrentMusic() {return currentMusic;}
};

#endif  // PLAYER_H