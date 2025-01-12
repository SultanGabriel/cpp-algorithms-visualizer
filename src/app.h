// app.h
#ifndef APP_H
#define APP_H

#include <SDL.h>
#include <stdexcept>

class App {
public:
    App();
    ~App();
    void Run();

private:
    SDL_Window* window;
    SDL_GLContext glContext;
    bool done;

    void Init();
    void Cleanup();
    void ProcessEvents();
    void Render();
};

#endif // APP_H

