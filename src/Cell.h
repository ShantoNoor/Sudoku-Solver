#ifndef __Cell__
#define __Cell__

#include <SDL.h>
#include <iostream>

class Cell
{
private:
    SDL_Rect m_rect;
    int m_numberId;
    SDL_Color m_bg;
    SDL_Color m_hover;
    SDL_Color m_done;
    SDL_Color m_back;
    SDL_Color m_color;
    bool m_isDone;
    bool m_isPlayed;

public:
    Cell();
    void handleInput(SDL_Event* e);
    void render(int x, int y);
    void setConfig(int width, int height, int numberId);
    inline int getNumberId() { return m_numberId; }
    inline void setNumberId(int numberId) { m_numberId = numberId; }
    inline void done() { m_isDone = true; m_color = m_done; };
    inline void notDone() { m_isDone = false; m_color = m_bg; };
    inline void backed() { m_color = m_back; }

};

#endif
