#include <stdbool.h>
#include <SDL.h>

#include "graphics/Graphics.h"
#include "graphics/Font.h"

bool isRunning = false;

bool Init()
{
	return Graphics::OpenWindow();
}

void Setup()
{

}

void Destroy()
{

}

void Input()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
			case SDL_QUIT:
			{
				isRunning = false;
			}
			case SDL_KEYDOWN:
			{
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
					isRunning = false;
			}
		}
	}
}

void Update()
{

}

void Render()
{
	Graphics::ClearScreen(0xFF111122);

	Graphics::DrawString(Graphics::ScreenWidth() * 0.5f - Font::GetStringFontLength("Hello World") * 0.5f, Graphics::ScreenHeight() * 0.5f, "Hello World", 0xFFFF0000, false);

	Graphics::RenderFrame();
}

int main(int argv, char* argc[])
{
	isRunning = Init();
	Setup();

	while (isRunning)
	{
		Input();
		Update();
		Render();
	}

	Destroy();

	return 0;
}