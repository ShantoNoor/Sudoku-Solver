#ifndef __Graphics__
#define __Graphics__

#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <string>

class Graphics
{
private:
    Graphics(){}
    static Graphics* s_graphics;
    TTF_Font* m_font;
    std::unordered_map<std::string, SDL_Texture*> m_textureMap;

public:
    //Renders texture at given point
    bool load(std::string id, std::string path, bool setColorKey = false, int r = 0, int g = 0, int b = 0, int a = 0);
    bool loadFont(std::string path, int size);
    bool makeTextTexture(std::string id, std::string text, SDL_Color textColor);
    void render( std::string id, int x, int y );
    void close();

    //Getters and Setters
    static Graphics* get(){ return s_graphics = (s_graphics != nullptr) ? s_graphics : new Graphics(); }
    void setTexture(std::string id, SDL_Texture* texture) { m_textureMap[id] = texture; }
    SDL_Texture* getTexture(std::string id) { return m_textureMap[id]; }

};

#endif
