#include "Window.h"
#include "Graphics.h"
#include "Cell.h"
#include "SudokuSolver.h"
#include "Button.h"
#include "Message.h"
#include "Sound.h"

Window* Window::s_window = nullptr;
Cell grid[9][9];
SudokuSolver solver;
Button startButton, clearButton;
Message error, unable;

Window::Window()
{
	m_window = nullptr;
    m_renderer = nullptr;
    m_screenWidth = 1280;
    m_screenHeight = 720;
    m_running = true;
    m_isSolving = false;
    m_error = false;
    m_unable = false;
    m_isStarting = true;
}

void Window::load()
{
    if(!Graphics::get()->loadFont("font.ttf", 60)) m_running = false;
    if(!Graphics::get()->load("help", "help.png", false, 0, 0, 0, 240)) m_running = false;

    SDL_Color textColor = {255, 255, 255};
    for(int i = 1; i <= 9; i++)
    {
        std::string number = std::to_string(i);
        if(!Graphics::get()->makeTextTexture(number, number, textColor)) m_running = false;
    }
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            grid[i][j].setConfig(75, 75, 0);
        }
    }

    Graphics::get()->makeTextTexture("Start", "START", textColor);
    Graphics::get()->makeTextTexture("Solve", "SOLVE", textColor);
    Graphics::get()->makeTextTexture("Set", "SET", textColor);
    startButton.setConfig("Solve", 250, 338);

    Graphics::get()->makeTextTexture("Clear", "CLEAR", textColor);
    clearButton.setConfig("Clear", 250, 338);

    SDL_Color errorColor = {252, 3, 3};
    Graphics::get()->makeTextTexture("error", "PLEASE, ENTER A VALID BOARD!", errorColor);
    Graphics::get()->makeTextTexture("unable", "NO SOLUTION EXISTS!", errorColor);

    error.setConfig("error");
    unable.setConfig("unable");

    Sound::get()->loadMusicFX("hover", "MusicFX/hover.ogg");
    Sound::get()->loadMusicFX("clicked", "MusicFX/clicked.ogg");
    Sound::get()->loadMusicFX("error", "MusicFX/error.ogg");
    Sound::get()->loadMusicFX("solved", "MusicFX/solved.ogg");

    solver.setExample(grid);
}

void Window::handleEvents()
{
    while (SDL_PollEvent(&m_event))
    {
        if(m_event.type == SDL_QUIT)
        {
            m_running = false;
        }
        if(startButton.isClicked(&m_event))
        {
            if(m_isStarting)
            {
                m_isStarting = false;
                startButton.setDisable(false);
                clearButton.setDisable(false);
            }
            else if(solver.countNumberOfEmptyCells(grid) == 81)
            {
                solver.setExample(grid);
                startButton.setDisable(false);
            }
            else if(solver.checkValidity(grid) && !m_isStarting)
            {
                Sound::get()->playMusicFX("clicked");
                Window::get()->setIsSolving(true);
                clearButton.setDisable(true);
                Window::get()->update();
                solver.solve(grid, solver.countNumberOfEmptyCells(grid), 0);
            }
            else
            {
                Sound::get()->playMusicFX("error");
                m_error = true;
                startButton.setDisable(true);
            }
        }
        if(clearButton.isClicked(&m_event) && !m_isStarting)
        {
            Sound::get()->playMusicFX("clicked");
            startButton.setDisable(false);
            m_error = false;
            m_unable = false;
            Window::get()->update();
            solver.clearBoard(grid);
        }
        if(!startButton.getDisable() && !m_isStarting)
        {
            for(int i = 0; i < 9; i++)
            {
                for(int j = 0; j < 9; j++)
                {
                    grid[i][j].handleInput(&m_event);
                }
            }
        }
    }
}

void Window::update()
{
    handleEvents();
    if(!Window::get()->getIsSolving()) clearButton.setDisable(false);
    if(m_isStarting) { startButton.setId("Start"); clearButton.setDisable(true); }
    else if(solver.countNumberOfEmptyCells(grid) == 81) startButton.setId("Set");
    else startButton.setId("Solve");
    render();
}

void Window::render()
{
    //Clearing the renderer
    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
	SDL_RenderClear( m_renderer );

	//Code Here..

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            grid[i][j].render(75*j, 75*i);
        }
    }

    startButton.render(677, 0);
    clearButton.render(677, 339);

    // drawing grid
    for(int i = 0; i <= 9; i++)
    {
        SDL_SetRenderDrawColor(Window::get()->getRenderer(), 0, 0, 0, 255);
        if(i%3 == 0) SDL_SetRenderDrawColor(Window::get()->getRenderer(), 255, 255, 255, 255);
        SDL_RenderDrawLine(Window::get()->getRenderer(), 0, 75*i, 675, 75*i);
        SDL_RenderDrawLine(Window::get()->getRenderer(), 75*i, 0, 75*i, 675);
    }

    if(m_error) error.render();
    if(m_unable) unable.render();
	if(m_isStarting) Graphics::get()->render("help", 0, 0);

    //Update screen
	SDL_RenderPresent( m_renderer );
}

void Window::close()
{
    Graphics::get()->close();
    Sound::get()->free();
    //Destroy window
	SDL_DestroyRenderer( m_renderer );
	SDL_DestroyWindow( m_window );
	m_window = nullptr;
	m_renderer = nullptr;

	//Quit SDL subsystems
	Mix_Quit();
    TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Window::init(const char* title, int width, int height)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		SDL_Log( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			SDL_Log( "Warning: Linear texture filtering not enabled!" );
		}

		//setting window size
		if(width != -1) m_screenWidth = width;
		if(height != -1) m_screenHeight = height;

		//Create window
		m_window = SDL_CreateWindow( title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeight, SDL_WINDOW_SHOWN );
		if( m_window == NULL )
		{
			SDL_Log( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED ); // | SDL_RENDERER_PRESENTVSYNC
			if( m_renderer == NULL )
			{
				SDL_Log( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( m_renderer, 0, 0, 255, 255 );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					SDL_Log( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

                //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					SDL_Log( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

                //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					SDL_Log( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return m_running = success;
}
