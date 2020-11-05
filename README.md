# chat

This repository contains the source code for a client-server chat application developed as part of my Bachelor's thesis titled "Development of a Client-Server Chat Application". The thesis paper can be found here: <http://urn.fi/URN:NBN:fi:amk-201705107324>. The application was developed with C++ and SDL.

## Build Instructions

To build the application for Windows using MinGW:

1. Download `mingw-get-setup.exe` from https://osdn.net/projects/mingw/releases/
2. Run `mingw-get-setup.exe` and install MinGW
3. Open the MinGW Installation Manager GUI application from `\MinGW\libexec\mingw-get\guimain.exe`
4. Mark the following packages for installation from basic setup: 
    - `mingw-developer-toolkit-bin`
    - `mingw32-base-bin`
    - `mingw32-gcc-g++-bin`
    - `msys-base-bin`
5. Apply changes from the installation menu to install the packages
6. Open the MinGW MSYS shell from `\MinGW\msys\1.0\msys.bat`
7. Navigate to this repository. For example, `cd /c/code/chat`
8. Run `make` to build the program

## Screenshot
  
![](/img/chat.PNG)
