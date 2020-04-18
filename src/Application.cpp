#include <iostream>
#include "puly/SubSystems.h"

SubSystems subSystems;

int main()
{
	subSystems.Init();

	std::cout << subSystems.configurator.GetValue("platform") << std::endl;

	subSystems.Shutdown();

	return 0;

}