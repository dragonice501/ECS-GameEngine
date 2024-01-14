#include "Engine/Engine.h"

int main(int argv, char* argc[])
{
	if (Engine::Instance().Init())
	{
		Engine::Instance().Run();
	}

	return 0;
}