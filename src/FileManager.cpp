#include <Handler/FileManager.h>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void FileManager::search(fs::path root, GenericTree<std::string>& parent) {
    if (fs::exists(root) && fs::is_directory(root)) {
        for (const auto& child : fs::directory_iterator(root)) {
            if (fs::is_directory(child.path())) {
                GenericTree<std::string> leaf(child.path().filename().string());
                search(child.path(), leaf);
                if (!leaf.getChildren().empty())
                    parent.getChildren().push_back(leaf);
            }
            else {
                for(std::string ext : extension) {
                    if (child.path().extension().string() == ext) {
                        parent.addChild(child.path().filename().string());
                        break;
                    }
                }
            }
        }
    }
}

void FileManager::startSearch() {
    fs::path directory = paths.getData();
    search(directory, paths);
}