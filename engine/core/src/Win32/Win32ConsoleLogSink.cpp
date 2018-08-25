#include "OSE/System/ConsoleLogSink.h"

#include <Windows.h>
#include <iostream>

namespace OSE {

    static void resetConsole(HANDLE hConsole)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    }

    void ConsoleLogSink::error(const std::string & msg)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

        std::cout << msg << std::endl;
        resetConsole(hConsole);
    }

    void ConsoleLogSink::warning(const std::string & msg)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

        std::cout << msg << std::endl;
        resetConsole(hConsole);
    }

    void ConsoleLogSink::info(const std::string & msg)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

        std::cout << msg << std::endl;
        resetConsole(hConsole);
    }

    void ConsoleLogSink::debug(const std::string & msg)
    {
        std::cout << msg << std::endl;
    }

}