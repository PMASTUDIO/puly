#include <iostream>
#include "puly/lowlevel/Configuration.h"

Puly::Configurations configurator;

int main()
{
	configurator.Init();
	
	std::cout << configurator.GetValue("platform") << std::endl;
	
	if (configurator.Delete("debugMode")){
		std::cout << "Debug Mode deleted" << std::endl;
	}

	configurator.Shutdown();

	return 0;

}