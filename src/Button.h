#ifndef __Button__
#define __Button__

#include <SDL.h>
#include <string>

class Button
{
protected:
    SDL_Rect m_rect;
    std::string m_id;
    int textureX, textureY;
    SDL_Color m_bg;
    SDL_Color m_hover;
    SDL_Color m_clicked;
    SDL_Color m_disable;
    SDL_Color m_color;
    bool m_isDisabled;
    bool m_isPlayed;

public:
    Button();
    void render(int x, int y);
    void setConfig(std::string id, int width, int height);
    void setId(std::string id);
    bool isClicked(SDL_Event* e);
    void setDisable(bool value) { m_isDisabled = value; }
    bool getDisable() { return m_isDisabled; }

};

#endif // __Button__
