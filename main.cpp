#include <SFML/Audio.hpp>
#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h> //eventos de teclado

#include <Handler/FileManager.h>
#include <Handler/Directive.h>
#include <Handler/Config.h>
#include <Handler/Terminal.h>

bool playMusic(const std::string& filename) {
    sf::Music music;
    if (!music.openFromFile("resources/" + filename))
        return false;

    // Display music informations
    std::cout << filename << ":" << std::endl;
    std::cout << " " << music.getDuration().asSeconds() << " seconds"       << std::endl;
    std::cout << " " << music.getSampleRate()           << " samples / sec" << std::endl;
    std::cout << " " << music.getChannelCount()         << " channels"      << std::endl;

    float total = music.getDuration().asSeconds();
    float offset = 0.0f;
    int len = 30;
    int part = 0;
    // Play it
    music.play();

    // Loop while the music is playing
    while (music.getStatus() == sf::Music::Playing) {
        // Leave some CPU time for other processes
        sf::sleep(sf::milliseconds(100));
        offset = music.getPlayingOffset().asSeconds();
        // Display the playing position
        std::cout << "\r" << std::fixed << std::setprecision(2) << offset << " ";
        std::cout << "[";

        part = (offset/total)*len;

        for(int i = 0; i < part; i++)
            std::cout << "=";
        for(int i = part; i < len; i++)
            std::cout << " ";
        
        std::cout << "] ";
        std::cout << std::fixed << std::setprecision(2) << total;
        std::cout << std::flush;
    }
    std::cout << std::endl << std::endl;
    return true;
}

void strprint(std::string str) {
    std::cout << str;
}

void terminalEvent(Terminal& system, int ch) {
    switch (ch) {
        case 72: // Flecha hacia arriba
            system.backwardsCursor();
            break;
        case 80: // Flecha hacia abajo
            system.forwardCursor();
            break;
        case 'q': // Carácter 'q' para salir del bucle
        case 'Q':
            system.stop();
            break;
        case 'a':
            system.addLine("linea+");
            break;
        default:
            // Otra tecla presionada, hacer algo si es necesario
            break;
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
    fm.typeFile(".mp3");
    fm.startSearch();

    fm.getTree().print(strprint);

    Terminal system;
    system.addLine("linea1");
    system.addLine("linea2");
    system.addLine("linea3");
    system.addLine("linea4");
    system.start();

    while (system.isRunning()) {
        terminalEvent(system, getch());
    }

    

    
    return EXIT_SUCCESS;
}