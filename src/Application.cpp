#include "Application.h"

Application::Application(int width, int height)
	: m_running(false)
	, m_screenWidth(width)
	, m_screenHeight(height)
{
}

Application::~Application()
{

}

bool Application::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	m_window = SDL_CreateWindow("SDL2-GLEW-Starter", 100, 100, m_screenWidth, m_screenHeight, SDL_WINDOW_OPENGL);

	if (!m_window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	m_context = SDL_GL_CreateContext(m_window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	glGetError();

	return true;
}

void Application::Run()
{
	m_running = true;
	m_ticks = SDL_GetTicks();

	while (m_running)
	{
		ProcessInput();
		Update();
		Render();
	}
}

void Application::Shutdown()
{
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
}

void Application::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				m_running = false;
				break;
		}
	}
}

void Application::Update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticks + 16))
		;

	float deltaTime = (SDL_GetTicks() - m_ticks) / 1000.0f;
	if (deltaTime > 0.05f)
		deltaTime = 0.05f;

	m_ticks = SDL_GetTicks();

	// Update anything here...
}

void Application::Render()
{
	glClearColor(0.271f, 0.322f, 0.424f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw anything here...

	SDL_GL_SwapWindow(m_window);
}
