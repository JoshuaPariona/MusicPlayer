#include <Handler/Directive.h>
#include <Handler/Config.h>
#include <filesystem>

namespace fs = std::filesystem;

void Directive::printVersion() {
    std::cout << "Version: 1.0" << std::endl;
}

void Directive::printHelp() {
    std::cout << "Help message" << std::endl;
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
