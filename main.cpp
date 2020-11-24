#include "Window.h"

int main(int argc, char* argv[])
{
    Window::get()->init("Sudoku Solver", 676+250, 676);
    Window::get()->load();

    while(Window::get()->isRunning())
    {
        Window::get()->update();
    }

    Window::get()->close();

    return 0;
}
