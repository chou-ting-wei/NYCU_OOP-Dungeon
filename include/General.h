#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>  
#include <windows.h>  

inline void waitForKeypress() {
    _getch(); 
}

inline void moveToBottom() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(consoleHandle, &csbi);

    COORD bottomLeft = {0, (SHORT)(csbi.dwSize.Y - 1)};
    SetConsoleCursorPosition(consoleHandle, bottomLeft);
}


#elif defined(__unix__) || defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

inline void waitForKeypress() {
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    cin.get(); 

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); 
}

inline int getTerminalRows() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}

inline void moveToBottom() {
    int rows = getTerminalRows();
    
    // Move the cursor to the bottom-left corner
    cout << "\x1B[" << rows << ";1H";
}

#else
#error "OS not supported"
#endif

inline void clear() {
    cout << "\x1B[2J\x1B[H";
}

inline void typewriter(const std::string& text, unsigned int milliseconds) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(milliseconds));
    }
}

#endif // GENERAL_H_INCLUDED