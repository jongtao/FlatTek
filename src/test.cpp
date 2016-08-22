#include "FlatTek/engine.h"
#include "FlatTek/scene.h"

#include <iostream>



class Second: public Scene
{
	public:
		void init()
		{
			attach_system();
			input->map_key("DOWN", Input::KEYBOARD, Input::KEY_DOWN);
			input->map_key("ESC", Input::KEYBOARD, Input::KEY_ESCAPE);
		}

		bool update()
		{
			if(input->get_key("DOWN"))
				std::cout << "DOWN" << std::endl;

			if(input->get_key("ESC"))
				scene_manager->req_halt();

			return true;
		}

	private:
};


class Init: public Scene
{
	public:
		void init()
		{
			attach_system();
			input->map_key("UP", Input::KEYBOARD, Input::KEY_UP);
			input->map_key("UP", Input::KEYBOARD, Input::KEY_W);
			input->map_key("CLICK", Input::MOUSE, 1);
		}


		bool update()
		{
			if(input->get_key("UP"))
				std::cout << "UP" << std::endl;


			// Test mouse axes
			struct Input::MousePosDouble my_mouse = input->get_mouse_norm();
			std::cout << "my_mouse: " << my_mouse.x << ", " << my_mouse.y << ", " <<
				my_mouse.z << ", " << my_mouse.w << ", " << my_mouse.in_display <<
				", " << my_mouse.display_name << std::endl;

			if(input->get_key("CLICK"))
			{
				std::cout << "CLICK" << std::endl;
				scene_manager->req_change(new Second);

			}

			return true;
		}


	private:
};



int main(void)
{
	double tickrate = 1.0/60.0;
	Init* my_code = new Init;

	try
	{
		Engine engine(tickrate);
		engine.run(my_code);
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
