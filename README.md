# Proyecto Music Player

Proyecto como parte de la asignatura Estructura de Datos.

Este proyecto es un reproductor de música que permite reproducir archivos de audio en diversos formatos. A continuación, se detallan los pasos para configurar el proyecto correctamente.

# Requerimientos

1. SFML - Libreria grafica y de audio

## Configuración del entorno de desarrollo

1. Asegúrate de tener instalado un compilador de C++ en tu sistema. Puedes utilizar MinGW, GCC o cualquier otro compilador compatible.

2. Agrega el directorio `/bin` al "PATH" del sistema. Esto permitirá que el sistema encuentre los ejecutables del compilador.

## Configuración de la ruta del compilador en Visual Studio Code

1. Abre el archivo `.vscode/task.json` en tu proyecto.

2. Ubica las secciones correspondientes a las tareas de compilación y enlace. Estas tareas suelen llamarse "C/C++: g++.exe compile active file" y "C/C++: g++.exe build active file".

3. Remplaza "command": "C:\\msys64\\mingw64\\bin\\g++.exe", a la ruta de tu compilador.

## Run && Debug en Visual Studio Code

1. Abre el archivo `.vscode/launch.json` en tu proyecto.

2. Ubica y remplaza "miDebuggerPath": "C:\\msys64\\mingw64\\bin\\gdb.exe", con la ruta de tu debugger gdb.

## Compilacion y Buildeo por terminal

1. En compliacion, usar "-c" e incluir el directorio `/include`:
                g++ -c main.cpp -Iruta/de/proyecto/MusicPlayer/include

2. Luego en linkeo usar "-o" y linkear: 
                g++ main.o -o main.exe -Lruta/de/proyecto/MusicPlayer/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

3. Asegurate que tu g++ y el directorio `/bin` pertenesca al path. si no usar la direccion completa del compilador.
