#pragma once

#include <iostream>
#include <string>

#include "common_test.h"

#include "FlatTek/scene.h"



class MouseTest: public Scene
{
	public:
		void init(void);
		bool update(void);
};

