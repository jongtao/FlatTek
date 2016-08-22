#include "FlatTek/engine.h"
#include "FlatTek/scene.h"

#include <iostream>

#include "scene_switch.h"
#include "mouse_test.h"





int main(void)
{
	double tickrate = 1.0/60.0;

	try
	{
		Engine engine(tickrate);
		engine.run(new MouseTest);
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
