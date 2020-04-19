#include <iostream>
#include "puly/Application.h"

Puly::Application application;

int main()
{
	application.Init();
	application.Run();
	application.Shutdown();

	return 0;

}