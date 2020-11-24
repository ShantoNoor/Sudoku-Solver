#ifndef __Message__
#define __Message__

#include <string>
#include <SDL.h>

class Message
{
private:
    std::string m_id;
    int m_width, m_height;
    SDL_Rect m_rect;

public:
    void setConfig(std::string id);
    void render();

};

#endif // __Message__
