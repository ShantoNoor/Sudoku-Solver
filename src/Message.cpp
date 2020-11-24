#include "Message.h"
#include "Graphics.h"
#include "Window.h"

void Message::setConfig(std::string id)
{
    m_id = id;
    SDL_QueryTexture(Graphics::get()->getTexture(m_id), NULL, NULL, &m_width, &m_height);
    m_rect.w = m_width + 10;
    m_rect.h = m_height + 10;
    m_width = (676+250-m_width) / 2;
    m_height = (576-m_height) / 2;
    m_rect.x = (676+250-m_rect.w) / 2;
    m_rect.y = (576-m_rect.h) / 2;
}

void Message::render()
{
    SDL_SetRenderDrawColor(Window::get()->getRenderer(), 0, 0, 0, 255);
    SDL_RenderFillRect(Window::get()->getRenderer(), &m_rect);
    Graphics::get()->render(m_id, m_width, m_height);
}
