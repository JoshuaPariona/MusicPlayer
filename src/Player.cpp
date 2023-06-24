#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <mutex>
#include <Handler/Player.h>
#include <SFML/Audio.hpp>

void Player::updateLoop() {
    float total = music.getDuration().asSeconds();
    float offset = 0.0f;
    int len = 47;
    int part = 0;
    std::string bar = "";
    while (music.getStatus() == sf::Music::Playing) {
        bar = "";
        offset = music.getPlayingOffset().asSeconds();
        bar += secondsToMinutes(offset) + " [";
        part = (offset/total) * len;
        for(int i = 0; i < part; i++)
            bar += "=";
        for(int i = part; i < len; i++)
            bar += " ";
        bar += "] ";
        bar += secondsToMinutes(total);
        progressBar = bar;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    if (music.getStatus() == sf::Music::Stopped) {
        progressBar = "0:00 [                                               ] 0:00";
        next_to_play = true;
    }
}

std::string Player::trimString(const std::string& str) {
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) {
        ++start;
    }
    auto end = str.end();
    do {
        --end;
    } while (end != start && std::isspace(*end));
    return std::string(start, end + 1);
}

std::string Player::secondsToMinutes(float seconds) {
    float minutes = seconds / 60.0;
    int wholeMinutes = static_cast<int>(minutes);
    int secondsPart = static_cast<int>((minutes - wholeMinutes) * 60.0);
    return std::to_string(wholeMinutes) + ":" + std::to_string(secondsPart);
}

std::string Player::getPath(const std::string& filename, GenericTree<std::string>& parent) {
    if (parent.getData() == filename) {
        return parent.getData();
    } else {
        for (auto& child : parent.getChildren()) {
            std::string path = getPath(filename, child);
            if (!path.empty())
                return parent.getData() + '/' + path;
        }
    }
    return "";
}
void Player::load(const std::string& filename) {
    ready_to_play = false;
    std::string path = getPath(trimString(filename), path_tree);
    std::filesystem::path p = path;
    if (std::filesystem::exists(p) && !(std::filesystem::is_directory(p))) {
        if (music.getStatus() == sf::Music::Playing)
            music.stop();
        if (music.openFromFile(path)) {
            ready_to_play = true;
            currentMusic = trimString(filename);
        }
    }
}

void Player::play_current() {
    if (ready_to_play) {
        if (music.getStatus() == sf::Music::Stopped || music.getStatus() == sf::Music::Paused) {
            music.play();
            if (updateThread.joinable()) {
                updateThread.join();
            }
            updateThread = std::thread(&Player::updateLoop, this);
        }
    }
}

void Player::pause_current() {
    if (music.getStatus() == sf::Music::Playing)
        music.pause();
}

void Player::stop_current() {
    if (music.getStatus() == sf::Music::Playing) {
        music.stop();
    }
    if (updateThread.joinable()) {
        updateThread.join();
    }
}

void Player::add_to_playlist(const std::string& filename) {
    std::string path = getPath(trimString(filename), path_tree);
    std::filesystem::path p = path;
    if (std::filesystem::exists(p) && !(std::filesystem::is_directory(p))) {
        playlist.appendBack(path);
    }
}

void Player::next() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!playlist.empty()) {
        stop_current();
        next_to_play = false;
        ready_to_play = music.openFromFile(playlist.front());
        std::filesystem::path p = playlist.popFront();
        currentMusic = p.filename().string();
        play_current();
    }
    next_to_play = false;
}
