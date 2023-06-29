#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h> //eventos de teclado
#include <filesystem>

#include <Handler/FileManager.h>
#include <Handler/Directive.h>
#include <Handler/Config.h>
#include <Handler/Terminal.h>
#include <Handler/Player.h>

void terminalEvent(Terminal& terminal, Player& player, int ch) {
    switch (ch) {
        case 72: // Flecha hacia arriba
            terminal.backwardsCursor();
            break;
        case 80: // Flecha hacia abajo
            terminal.forwardCursor();
            break;
        case 77: // Flecha hacia dercha
            player.jump();
            break;
        case 75: // Flecha hacia atras
            player.back();
            break;
        case 'q': // Carácter 'q' para salir del bucle
            player.stop_current();
            terminal.stop();
            break;
        case 'n': //next in playlist
            player.next();
            break;
        case 's': // play or resume music
            player.play_current();
            break;
        case 'p': // Pause music
            player.pause_current();
            break;
        case '\r': // Enter key, Select music
            player.load(terminal.getLine(terminal.getCursorPos()));
            break;
        case 'a': // Enqueue music;
            player.add_to_playlist(terminal.getLine(terminal.getCursorPos()));
            break;
        case 'f': // Enqueue back music;
            player.add_front_playlist(terminal.getLine(terminal.getCursorPos()));
            break;
        default:
            break;
    }
}

std::string getFilename(std::string path) {
    std::filesystem::path filePath(path);
    return "  " + filePath.filename().string();
}

void updateMusicInfo(Terminal& terminal, Player& player ,int namePos, int barPos, int playlistPos) {
    while (terminal.isRunning()) {
        terminal.setLine(namePos, player.getCurrentMusic());
        terminal.setLine(barPos, player.getProgressBar());
        terminal.cut(playlistPos);
        player.getPlayList().print(terminal.getBuffer(),&getFilename);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main(int argc, char** argv) {
    //capturas de directivas
    Directive d(argc,argv);
    d.init();

    if (!Config::ready_to_start)
        return EXIT_SUCCESS;
    
    FileManager fm(Config::album_path);
    fm.typeFile(".ogg");
    fm.typeFile(".wav");
    fm.typeFile(".flac");
    fm.startSearch();

    Terminal terminal;
    terminal.addLine("\tExplorador de Archivos");
    //Tree is the one to select
    terminal.minRangePos();
    fm.getTree().print(terminal.getBuffer());
    terminal.maxRangePos();
    // Not reachable
    terminal.addLine("___________________________________________________________");
    terminal.addLine("\tEn Reproduccion:");
    
    Player player(fm.getTree());
    int namePos = terminal.getSize();
    int barPos = namePos + 1;
    terminal.addLine(player.getCurrentMusic());
    terminal.addLine(player.getProgressBar());
    terminal.addLine("___________________________________________________________");
    terminal.addLine("\tPlay List:");
    int playlistPos = terminal.getSize();

    terminal.start(); 
    std::thread updateThread(updateMusicInfo, std::ref(terminal), std::ref(player), namePos, barPos, playlistPos);

    while (terminal.isRunning()) {
        terminalEvent(terminal, player, getch());
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    if (updateThread.joinable())
        updateThread.join();

    return EXIT_SUCCESS;
}