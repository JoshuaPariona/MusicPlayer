# Proyecto Music Player

Proyecto como parte de la asignatura Estructura de Datos.

Este proyecto es un reproductor de música que permite reproducir archivos de audio en diversos formatos (flac, ogg, wav), mp3 no disponible. A continuación, se detallan los pasos para configurar el proyecto correctamente.

La compilacion de este proyecto esta destinado solo a sistemas windows.

El compilador debe permitir el standar 17 o mayor

# Requerimientos

1. SFML - Libreria grafica y de audio

## Configuración del entorno de desarrollo

1. Asegúrate de tener instalado un compilador de C++ en tu sistema. Puedes utilizar MinGW, GCC o cualquier otro compilador compatible.

2. Agrega el directorio `/bin` al "PATH" del sistema. Esto permitirá que el sistema encuentre los ejecutables del compilador.

## Configuración de la ruta del compilador en Visual Studio Code

1. Abre el archivo `.vscode/task.json` en tu proyecto.

2. Ubica las secciones correspondientes a las tareas de compilación y enlace. Estas tareas suelen llamarse "C/C++: g++.exe compile active file" y "C/C++: g++.exe build active file".

3. Remplaza "command": "C:\\msys64\\mingw64\\bin\\g++.exe", a la ruta de tu compilador.

## Compilacion

1. Ejecuta la tarea principla de `.vscode/task.json`, con etiqueta: "C/C++: g++.exe build active file"

2. Espera a que termine la compilación y se generará un archivo ejecutable

## Uso

1. Abre una terminal o en el mismo terminal de vscode, y dirigete hacia la ubicacion de "player.exe", y digita los siguiente > player <album_path>

2. Ejecuta player --help para mas información del funcionamiento.