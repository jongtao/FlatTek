#include "mouse_test.h"


void MouseTest::init(void)
{
	attach_system();
	input->map_key("CLICK 1", Input::MOUSE, 1);
	input->map_key("CLICK 2", Input::MOUSE, 2);
	input->map_key("CLICK 3", Input::MOUSE, 3);
	input->map_key("ESC", Input::KEYBOARD, Input::KEY_ESCAPE);
}


bool MouseTest::update()
{
	// Test mouse axes
	struct Input::MousePosDouble my_mouse = input->get_mouse_norm();

	std::cout << "my_mouse: " <<
		my_mouse.x << ", " << my_mouse.y << ", " <<
		my_mouse.z << ", " << my_mouse.w << ", " <<
		my_mouse.in_display << ", " << my_mouse.display_name << std::endl;

	if_key_print(input, "CLICK 1");
	if_key_print(input, "CLICK 2");
	if_key_print(input, "CLICK 3");

	if(input->get_key("ESC"))
		scene_manager->req_halt();

	return true;
}
