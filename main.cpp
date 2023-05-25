#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

bool playMusic(const std::string& filename) {
    sf::Music music;
    if (!music.openFromFile("resources/" + filename))
        return false;

    // Display music informations
    std::cout << filename << ":" << std::endl;
    std::cout << " " << music.getDuration().asSeconds() << " seconds"       << std::endl;
    std::cout << " " << music.getSampleRate()           << " samples / sec" << std::endl;
    std::cout << " " << music.getChannelCount()         << " channels"      << std::endl;

    // Play it
    music.play();

    // Loop while the music is playing
    while (music.getStatus() == sf::Music::Playing) {
        // Leave some CPU time for other processes
        sf::sleep(sf::milliseconds(100));

        // Display the playing position
        std::cout << "\rPlaying... " << music.getPlayingOffset().asSeconds() << " sec        ";
        std::cout << std::flush;
    }
    std::cout << std::endl << std::endl;
    return true;
}

int main(int argc, char** argv) {
    
    //capturas de directivas
    for(int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    playMusic("orchestral.ogg");

    // Wait until the user presses 'enter' key
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');

    return EXIT_SUCCESS;
}