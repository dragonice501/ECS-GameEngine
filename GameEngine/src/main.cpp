#include "Engine.h"

#include <iostream>
#include <string>
#include <SDL.h>
#include <sol.hpp>

int nativeCube(int n)
{
	return n * n * n;
}

void TestLua()
{
	sol::state lua;
	lua.open_libraries(sol::lib::base);

	// Expose and bind a function for Lua script
	lua["cube"] = nativeCube;

	std::string path = SDL_GetBasePath();
	path += "assets\\scripts\\myscript.lua";
	lua.script_file(path);

	// Get value from Lua global variable
	int someVariable = lua["someVariable"];
	std::cout << "The value of someVariable in C++ is " << someVariable << std::endl;

	// Get value from Lua table
	bool isFullscreen = lua["config"]["fullscreen"];

	sol::table config = lua["config"];
	int width = config["resolution"]["width"];
	int height = config["resolution"]["height"];

	std::cout << "We read the value fullscreen: " << isFullscreen << std::endl;
	std::cout << "Width: " << width << std::endl;
	std::cout << "Height: " << height << std::endl;

	// Invoke Lua function
	sol::function factorial = lua["factorial"];
	int functionResult = factorial(5);
	std::cout << "The lua script calculated 5! as " << functionResult << std::endl;
}

int main(int argv, char* argc[])
{
	if (Engine::Instance().Init())
	{
		Engine::Instance().Run();
	}

	Engine::Instance().Shutdown();

	//TestLua();

	return 0;
}