#include "Sound.h"
#include "SDL.h"

Sound* Sound::s_sound = nullptr;

bool Sound::loadMusicFX(std::string id, std::string path)
{
    Mix_Chunk *musicFX = nullptr;
    musicFX = Mix_LoadWAV( path.c_str() );
	if( musicFX == NULL )
	{
		SDL_Log( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}
    m_musicFXMap[id] = musicFX;
    return true;
}

void Sound::playMusicFX(std::string id)
{
    Mix_PlayChannel( -1, m_musicFXMap[id], 0 );
}

void Sound::free()
{
    for(auto x : m_musicFXMap)
    {
        Mix_FreeChunk(m_musicFXMap[x.first]);
    }
    m_musicFXMap.clear();
}
