#ifndef __Window__
#define __Window__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>

class Window
{
private:
    Window();
    static Window* s_window;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    bool m_running;
    bool m_isSolving;
    int m_screenWidth, m_screenHeight;
    SDL_Event m_event;
    bool m_error, m_unable;

public:
    bool init(const char* title, int width=-1, int height=-1);
    void load();
    void handleEvents();
    void update();
    void render();
    void close();

    //Getters and Setters
    inline static Window* get() { return s_window = (s_window != nullptr) ? s_window : new Window(); }
    inline bool isRunning() { return m_running; }
    inline SDL_Window* getWindow() { return m_window; }
    inline SDL_Renderer* getRenderer() { return m_renderer; }
    inline int getScreenWidth() { return m_screenWidth; }
    inline int getScreenHeight() { return m_screenHeight; }
    inline void setScreenWidth(int width) { m_screenWidth = width; }
    inline void setScreenHeight(int height) { m_screenHeight = height; }
    inline void setIsSolving(bool value) { m_isSolving = value; }
    inline bool getIsSolving() { return m_isSolving; }
    inline void setUnable(bool value) { m_unable = value; }

};

#endif
