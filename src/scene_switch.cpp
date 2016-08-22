#include "scene_switch.h"


void First::init(void)
{
	std::cout << "Press RIGHT to go to next scene!" << std::endl;
	std::cout << "Press ESCAPE to halt!" << std::endl;

	attach_system();

	graphics->create_windowed_display("primary", "Scene Switch Test", true, 300, 300);

	input->map_key("UP", Input::KEYBOARD, Input::KEY_UP);
	input->map_key("DOWN", Input::KEYBOARD, Input::KEY_DOWN);
	input->map_key("LEFT", Input::KEYBOARD, Input::KEY_LEFT);
	input->map_key("RIGHT", Input::KEYBOARD, Input::KEY_RIGHT);
	input->map_key("ESC", Input::KEYBOARD, Input::KEY_ESCAPE);
}



bool First::update(void)
{
	if(input->get_key("ESC"))
		scene_manager->req_halt();

	if_key_print(input, "UP");
	if_key_print(input, "DOWN");
	if_key_print(input, "LEFT");
	if_key_print(input, "RIGHT");

	if(input->get_key("RIGHT"))
		scene_manager->req_change(new Second);

	return true;
}


void Second::init(void)
{
	std::cout << "Hi, I'm the second scene!" << std::endl;

	attach_system();
}


bool Second::update(void)
{
	if_key_print(input, "UP");
	if_key_print(input, "DOWN");
	if_key_print(input, "LEFT");
	if_key_print(input, "RIGHT");

	if(input->get_key("ESC"))
		scene_manager->req_halt();

	return true;
}


