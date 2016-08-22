#pragma once

#include <iostream>
#include <string>

#include "common_test.h"

#include "FlatTek/scene.h"


class First: public Scene
{
	public:
		void init(void);
		bool update(void);

	private:
};


class Second: public Scene
{
	public:
		void init(void);
		bool update(void);
};


