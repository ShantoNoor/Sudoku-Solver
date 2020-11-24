#include "Button.h"
#include "Graphics.h"
#include "Window.h"
#include "Sound.h"

Button::Button()
{
    m_bg = {81, 216, 139};
    m_hover = {44, 151, 221};
    m_clicked = {255, 87, 51};
    m_disable = {241, 197, 14};
    m_color = m_bg;
    m_isDisabled = false;
    m_isPlayed = false;
}

void Button::render(int x, int y)
{
    m_rect.x = x;
    m_rect.y = y;
    SDL_SetRenderDrawColor(Window::get()->getRenderer(), m_color.r, m_color.g, m_color.b, 255);
    SDL_RenderFillRect(Window::get()->getRenderer(), &m_rect);
    Graphics::get()->render( m_id, x+(m_rect.w-textureX)/2, y+(m_rect.h-textureY)/2 );
}
void Button::setConfig(std::string id, int width, int height)
{
    m_id = id;
    m_rect.w = width;
    m_rect.h = height;
    SDL_QueryTexture(Graphics::get()->getTexture(id), NULL, NULL, &textureX, &textureY);
}
bool Button::isClicked(SDL_Event* e)
{
    int x, y;
    SDL_GetMouseState( &x, &y );

    bool inside = true;
    if( x < m_rect.x ) inside = false;
    else if( x > m_rect.x + m_rect.w ) inside = false;
    else if( y < m_rect.y ) inside = false;
    else if( y > m_rect.y + m_rect.h ) inside = false;

    if(m_isDisabled) m_color = m_disable;
    else m_color = m_bg;

    if(inside && !m_isDisabled)
    {
        m_color = m_hover;
        if(m_isPlayed)
        {
            Sound::get()->playMusicFX("hover");
            m_isPlayed = false;
        }
        if(e->type == SDL_MOUSEBUTTONDOWN)
        {
            m_color = m_clicked;
            // here
            setDisable(true);
            return true;
        }
    }
    else
    {
        m_isPlayed = true;
    }
    return false;
}
