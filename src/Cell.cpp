#include "Cell.h"
#include "Graphics.h"
#include "Window.h"
#include <string>
#include "Sound.h"

Cell::Cell()
{
    m_bg = {213, 22, 55};
    m_hover = {44, 151, 221};
    m_done = {255, 87, 51};
    m_back = {241, 197, 14};
    m_color = m_bg;

    m_rect.x = m_rect.y = 0;
    m_rect.w = 50;
    m_rect.h = 50;
    m_numberId = 1;
    m_isDone = false;
    m_isPlayed = false;
}
void Cell::handleInput(SDL_Event* e)
{
    int x, y;
    SDL_GetMouseState( &x, &y );

    bool inside = true;
    if( x < m_rect.x ) inside = false;
    else if( x > m_rect.x + m_rect.w ) inside = false;
    else if( y < m_rect.y ) inside = false;
    else if( y > m_rect.y + m_rect.h ) inside = false;

    if(m_isDone) m_color = m_done;
    else m_color = m_bg;

    if(inside)
    {
        m_color = m_hover;
        if(m_isPlayed)
        {
            Sound::get()->playMusicFX("hover");
            m_isPlayed = false;
        }
        if(e->type == SDL_KEYDOWN)
        {
            switch(e->key.keysym.sym)
            {
                case SDLK_0: m_numberId = 0; break;
                case SDLK_1: m_numberId = 1; break;
                case SDLK_2: m_numberId = 2; break;
                case SDLK_3: m_numberId = 3; break;
                case SDLK_4: m_numberId = 4; break;
                case SDLK_5: m_numberId = 5; break;
                case SDLK_6: m_numberId = 6; break;
                case SDLK_7: m_numberId = 7; break;
                case SDLK_8: m_numberId = 8; break;
                case SDLK_9: m_numberId = 9; break;
            }
        }
    }
    else
    {
        m_isPlayed = true;
    }
}
void Cell::render(int x, int y)
{
    m_rect.x = x;
    m_rect.y = y;
    SDL_SetRenderDrawColor(Window::get()->getRenderer(), m_color.r, m_color.g, m_color.b, 255);
    SDL_RenderFillRect(Window::get()->getRenderer(), &m_rect);
    if(m_numberId != 0) Graphics::get()->render(std::to_string(m_numberId), x+21, y+3);
}
void Cell::setConfig(int width, int height, int numberId)
{
    m_rect.w = width;
    m_rect.h = height;
    m_numberId = numberId;
}
