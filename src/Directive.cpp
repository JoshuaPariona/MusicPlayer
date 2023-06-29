#include <Handler/Directive.h>
#include <Handler/Config.h>
#include <filesystem>

namespace fs = std::filesystem;

void Directive::printVersion() {
    std::cout << "Version: 1.0" << std::endl;
}

void Directive::printHelp() {
    std::cout << "Usage:" << std::endl;
    std::cout << "  player <folder_path>" << std::endl;
    std::cout << std::endl;
    std::cout << "Directives:" << std::endl;
    std::cout << "  --help     Display this help message" << std::endl;
    std::cout << "  --credits  Display project credits" << std::endl;
    std::cout << "  --version  Display the version of the program" << std::endl;
    std::cout << std::endl;
    std::cout << "Program options:" << std::endl;
    std::cout << "  H / Arrow Up     Move cursor upwards" << std::endl;
    std::cout << "  P / Arrow Down   Move cursor downwards" << std::endl;
    std::cout << "  q                Quit the program" << std::endl;
    std::cout << "  n                Play the next song in the playlist" << std::endl;
    std::cout << "  s                Play or resume music" << std::endl;
    std::cout << "  p                Pause music" << std::endl;
    std::cout << "  a                Enqueue music" << std::endl;
    std::cout << "  f                Enqueue music to the front" << std::endl;
    std::cout << "  Enter            Select music" << std::endl;
}


void Directive::printCredits() {
    std::cout << "Asignatura: Estructura de Datos" << std::endl;
    std::cout << "\tScrum master: Anaya, Eros" << std::endl;
    std::cout << "\tProgramador: Pariona, Joshua" << std::endl;
    std::cout << "\tDesarrollador: Sanchez, Sergio" << std::endl;
}

Directive::Directive(const int c, char** v) : argv(v), argc(c) {
    setDirectives();
}

void Directive::setDirectives() {
    directive_map["--version"] = &printVersion;
    directive_map["--help"] = &printHelp;
    directive_map["--credits"] = &printCredits;
}

void Directive::init() {
    for (int i = 0; i < argc; i++) {
        if (directive_map.count(std::string(argv[i])))
            directive_map[std::string(argv[i])]();
        else {
            fs::path p = std::string(argv[i]);
            if (fs::exists(p) && fs::is_directory(p)) {
                Config::album_path = p.string();
                Config::ready_to_start = true;
            }
        }
    }
}
