#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <vector>
#include <filesystem>
#include <DataStructs/GenericTree.h>
#include <../src/GenericTree.cpp>

class FileManager {
private:
    GenericTree<std::string> paths;
    std::vector<std::string> extension;
    void search(std::filesystem::path root, GenericTree<std::string>& parent);

public:
    FileManager(std::string root) : paths(root), extension({}) {}
    ~FileManager() {clean();}

    void typeFile(std::string ext) {extension.push_back(ext);}
    void startSearch();
    void clean() {extension.clear(); paths.deleteTree(paths);};
    GenericTree<std::string>& getTree() {return paths;};
};

#endif // FILEMANAGER_H