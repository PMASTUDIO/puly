#include <iostream>
#include "puly/SubSystems.h"
#include "puly/window/Window.h"

Window windows;
SubSystems subSystems;

int main()
{
	subSystems.Init();
	windows.Init(640, 480, "Hello Puly!!!");

	while (!windows.ShouldClose()) {
		windows.Update();
	}

	windows.Shutdown();
	subSystems.Shutdown();

	return 0;

}