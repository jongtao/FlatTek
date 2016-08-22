#include "input.h"


Input::Input(void):
	mouse({0,0,0,0,false}),
	mouse_norm({0.0,0.0,0,0,false}),
	disp_width(1), disp_height(1)
{};



void Input::create_key(std::string user_binding)
{
	keystate.insert({user_binding, false}); // only one key allowed in set
}



void Input::destroy_key(std::string user_binding)
{
	keystate.erase(user_binding);

	// Linear search to find and delete all bindings
	for(int i=NUM_DEVICES-1; i>=0; i--)
		for(auto it = binding[i].begin(); it != binding[i].end(); )
		{
			if(it->second == user_binding)
				it = binding[i].erase(it); // returned "it" is next valid iterator
			else
				it++;
		}
}



bool Input::map_key(std::string user_binding, int device, int keycode)
{
	if(device != KEYBOARD && device != MOUSE && device != JOYSTICK)
		return false;

	if(binding[device].count(keycode) == 1) // device already bound!
		return false;

	binding[device].insert({keycode, user_binding});
	create_key(user_binding); // creates key automatically if none found

	return true;
}



void Input::unmap_key(int device, int keycode)
{
	binding[device].erase(keycode);	
}



bool Input::get_key(std::string user_binding)
{
	return keystate[user_binding];
}



struct Input::MousePos Input::get_mouse(void)
{
	return mouse;
}



void Input::set_disp(int width, int height)
{
	disp_width = width;
	disp_height = height;
}



struct Input::MousePosDouble Input::get_mouse_norm(void)
{
	return mouse_norm;
}



void Input::clear_all(void)
{
	keystate.clear();

	for(int i=NUM_DEVICES-1; i>=0; i--)
		binding[i].clear();
}






void Input::init(ALLEGRO_EVENT_QUEUE* event_queue, Graphics graphics)
{
	if(!al_install_keyboard())
		throw std::runtime_error("Failed to install keyboard");
	
	if(!al_install_mouse())
		throw std::runtime_error("Failed to install mouse");

	this->graphics = graphics;

	// Listen for keyboard events
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	// Listen for mouse events
	al_register_event_source(event_queue, al_get_mouse_event_source());
}



bool Input::is_input(const ALLEGRO_EVENT* event)
{
	switch(event->type)
	{
#ifdef USING_JOYSTICK
		case ALLEGRO_EVENT_JOYSTICK_AXIS:
		case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
		case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
		case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
#endif // USING_JOYSTICK

		case ALLEGRO_EVENT_KEY_DOWN:
		case ALLEGRO_EVENT_KEY_UP:
		case ALLEGRO_EVENT_KEY_CHAR:

#ifdef USING_MOUSE
		case ALLEGRO_EVENT_MOUSE_AXES:
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		case ALLEGRO_EVENT_MOUSE_WARPED:
		case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
		case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
#endif // USING_MOUSE
		
#ifdef USING_TOUCH
		case ALLEGRO_EVENT_TOUCH_BEGIN:
		case ALLEGRO_EVENT_TOUCH_END:
		case ALLEGRO_EVENT_TOUCH_MOVE:
		case ALLEGRO_EVENT_TOUCH_CANCEL:
#endif // USING_TOUCH
	
			return true;
			break;
		default:
			return false;
	}
}



void Input::update_state(int device, int keycode, bool new_state)
{
	if(binding[device].count(keycode)) // only update if mapping exists
	{
		std::string user_binding = binding[device][keycode];
		keystate[user_binding] = new_state;
	}
}


void Input::update_mouse_axes(const ALLEGRO_EVENT* event)
{
	// assign name
	std::string name = graphics.get_name(event->mouse.display);
	mouse.display_name = name;
	mouse_norm.display_name = name;

	// assign integer position
	mouse.x = event->mouse.x;
	mouse.y = event->mouse.y;
	mouse.z = event->mouse.z;
	mouse.w = event->mouse.w;

	// get diplay dimensions
	int width = al_get_display_width(event->mouse.display);
	int height = al_get_display_height(event->mouse.display);

	// assign normalized position
	mouse_norm.x = (double)event->mouse.x / (double)width;
	mouse_norm.y = (double)event->mouse.y / (double)height;
	mouse_norm.z = event->mouse.z;
	mouse_norm.w = event->mouse.w;
}


void Input::update_mouse_display(const ALLEGRO_EVENT* event, bool new_state)
{
	mouse.in_display = new_state;
	mouse_norm.in_display = new_state;
}



void Input::update(const ALLEGRO_EVENT* event)
{
	switch(event->type)
	{
		// KEYBOARD
		case ALLEGRO_EVENT_KEY_DOWN:
			update_state(KEYBOARD, event->keyboard.keycode, true);
			break;
		case ALLEGRO_EVENT_KEY_UP:
			update_state(KEYBOARD, event->keyboard.keycode, false);
			break;
		// MOUSE BUTTONS
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			update_state(MOUSE, event->mouse.button, true);
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			update_state(MOUSE, event->mouse.button, false);
			break;
		// MOUSE POSITION 
		case ALLEGRO_EVENT_MOUSE_AXES:
			update_mouse_axes(event);
			break;
		case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
			update_mouse_display(event, true);
			update_mouse_axes(event);
			break;
		case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
			update_mouse_display(event, false);
			// maintain last "on display" reading
			break;
		default:
			; // Ignore unrecognized event
	}
}

