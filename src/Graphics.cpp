#include "Graphics.h"
#include "Window.h"

Graphics* Graphics::s_graphics = nullptr;

bool Graphics::loadFont(std::string path, int size)
{
    m_font = nullptr;
    m_font = TTF_OpenFont( path.c_str(), size );
	if( m_font == nullptr )
	{
		SDL_Log( "Failed to load %s font! SDL_ttf Error: %s\n", path.c_str(), TTF_GetError() );
        return false;
	}
    return true;
}

bool Graphics::makeTextTexture(std::string id, std::string text, SDL_Color textColor)
{
    SDL_Surface* textSurface = nullptr;
    textSurface = TTF_RenderText_Solid( m_font, text.c_str(), textColor );
	if( textSurface == nullptr )
	{
		SDL_Log( "Unable to render text surface : %s! SDL_ttf Error: %s\n", text.c_str(), TTF_GetError() );
        SDL_FreeSurface( textSurface );
        return false;
	}
    SDL_Texture* textTexture = nullptr;
    textTexture = SDL_CreateTextureFromSurface( Window::get()->getRenderer(), textSurface );
    if( textTexture == nullptr )
    {
        SDL_Log( "Unable to create texture from rendered text : %s! SDL Error: %s\n", text.c_str(), SDL_GetError() );
        SDL_DestroyTexture(textTexture);
        return false;
    }
    SDL_FreeSurface( textSurface );
    Graphics::get()->setTexture(id, textTexture);
    textTexture = nullptr;
    SDL_DestroyTexture(textTexture);
    return true;
}

void Graphics::render( std::string id, int x, int y )
{
    SDL_Texture* texture = m_textureMap[id];
    SDL_Rect desRect;
    desRect.x = x;
    desRect.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &desRect.w, &desRect.h);
    SDL_RenderCopy( Window::get()->getRenderer(), m_textureMap[id], NULL, &desRect);
}

void Graphics::close()
{
    for(auto x : m_textureMap)
    {
        SDL_DestroyTexture(m_textureMap[x.first]);
    }
    m_textureMap.clear();
}
