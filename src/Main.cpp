#include <iostream>
#include "puly/Application.h"

Puly::Application application;

int main()
{
	bool success = application.Init();

	if (!success) {
		return 0;
	}

	application.Run();
	application.Shutdown();

	return 0;
	
}