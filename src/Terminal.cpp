#include <Handler/Terminal.h>

#include <iostream>
#include <chrono>

void Terminal::forwardCursor() {
    if (cursorPos < maxRange && cursorPos < lines.size()-1)
        cursorPos++;
}

void Terminal::backwardsCursor() {
    if (cursorPos > minRange && cursorPos > 0)
        cursorPos--;
}

std::string Terminal::getLine(int index) {
    if (index >= 0 && index < lines.size()) {
        return lines[index];
    }
    return "";
}

bool Terminal::setLine(int index, std::string line) {
    if (index < 0 || index >= lines.size())
        return false;
    lines[index] = line;
    return true;
}

void Terminal::addLine(const std::string& line) {
    lines.push_back(line);
}

void Terminal::highlightLine(int index) {
    if (index >= 0 && index < lines.size())
        cursorPos = index;
}

void Terminal::cut(int index) {
    if (index >= lines.size() || index < 0)
        return;

    lines.resize(index);
}

void Terminal::print() {
    int i = 0;
    for (const std::string& line : lines) {
        std::cout << line;
        if (i == cursorPos)
            std::cout << " <";
        std::cout << std::endl; 
        i++;
    }
}

void Terminal::start() {
    if (!running) {
        running = true;
        updateThread = std::thread(&Terminal::updateLoop, this);
    }
}

void Terminal::stop() {
    if (running) {
        running = false;
        if (updateThread.joinable()) {
            updateThread.join();
        }
    }
}

void Terminal::updateLoop() {
    while (running) {
        // Refrescar el terminal aquí
        clearTerminal();

        // Imprimir las líneas
        print();

        // Esperar 100 ms antes de la próxima actualización
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Terminal::clearTerminal() {
    // Lógica para limpiar el terminal (depende del sistema operativo)
    system("cls"); //FIXME:lokokokook
    //std::cout << "\033[2J\033[H"; // Código ANSI para borrar la pantalla y colocar el cursor en la posición inicial
}