#include <iostream>
#include "puly/lowlevel/Configuration.h"

Puly::Configurations configurator;

int main()
{
	configurator.Init();
	
	std::cout << configurator.GetValue("platform");

	configurator.Shutdown();

	return 0;

}