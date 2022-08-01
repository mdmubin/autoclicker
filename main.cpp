#include <chrono>
#include <iostream>

#include "NoWinAPI.h" // Disable every win32 api in <Windows.h>

// Enable only KB/M API in <Windows.h>
#undef NOVIRTUALKEYCODES
#undef NOKEYSTATES
#undef NOUSER

#include <Windows.h>


// std::chrono simplified
#define TIME_NOW          std::chrono::steady_clock::now()
#define ELAPSED(to, from) std::chrono::duration_cast<std::chrono::milliseconds>(to - from).count()


void init() {
    std::cout << "+-------------------------------------------------------------------------+\n";
    std::cout << "|                           MDM's Auto Clicker                            |\n";
    std::cout << "+-------------------------------------------------------------------------+\n";

    std::cout << "QUICKSTART:\n"
              << "\tPRESS [L] to start / stop\n\n";
}


inline void prompt(bool running) {
    std::cout << (running ? "\tThe Clicker Service is Running.      \r"
                          : "\tThe Clicker Service has been Stopped.\r");
}


void loop() {
    auto running   = false;
    auto startTime = TIME_NOW;

    INPUT mouseClickEvent   = {0};
    INPUT mouseReleaseEvent = {0};

    mouseClickEvent.type         = INPUT_MOUSE;
    mouseClickEvent.mi.dwFlags   = MOUSEEVENTF_LEFTDOWN;
    mouseReleaseEvent.type       = INPUT_MOUSE;
    mouseReleaseEvent.mi.dwFlags = MOUSEEVENTF_LEFTUP;

    while (true) {
        if (GetAsyncKeyState(VK_F10) & 0x8000) {
            while ((GetAsyncKeyState(VK_F10) & 0x8000));
            running = !running;
            prompt(running);
        }

        if (ELAPSED(TIME_NOW, startTime) > 100 && running) {
            SendInput(1, &mouseClickEvent, sizeof(INPUT));
            SendInput(1, &mouseReleaseEvent, sizeof(INPUT));
            startTime = TIME_NOW;
        }
    }
}


int main(int argc, const char **argv) {
    init();
    loop();
}
