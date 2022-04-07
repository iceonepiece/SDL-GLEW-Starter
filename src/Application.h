#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

class Application
{
public:
	Application(int width, int height);
	~Application();

	bool Initialize();
	void Run();
	void Shutdown();

private:
	bool m_running;
	int m_screenWidth;
	int m_screenHeight;
	int m_ticks;

	SDL_Window* m_window;
	SDL_GLContext m_context;

	void ProcessInput();
	void Update();
	void Render();
};
