#pragma once

#include <allegro5/allegro.h>

#include <string>
#include <unordered_map>
#include <array>


//#define USING_JOYSTICK
//#define USING_TOUCH
#define USING_MOUSE


class Input
{
	public:
		#include "keycodes.h" // Giant list of keyboard keycode definitions

		#define NUM_DEVICES 3
		enum InputDevice { KEYBOARD, MOUSE, JOYSTICK };

		struct MousePos
		{
			int x, y; // position relative to 0,0 of display
			int z; // vertical mouse wheel. up is positive
			int w; // horizontal mouse wheel
			bool in_disp; // in display
		};

		struct MousePosDouble
		{
			double x, y; // position relative to 0,0 of display
			int z; // vertical mouse wheel. up is positive
			int w; // horizontal mouse wheel
			bool in_disp; // in display
		};

		// Construction
		Input(void);

		// Key instantiation
		void create_key(std::string user_binding);
		void destroy_key(std::string user_binding);

		// Key mapping
		bool map_key(std::string user_binding, int device, int keycode);
		void unmap_key(int device, int keycode);

		// Obtain input states
		bool get_key(std::string user_binding);
		struct Input::MousePos get_mouse(void);

		void set_disp(int width, int height);
		struct Input::MousePosDouble get_mouse_norm(void);

		// Clear all bindings
		void clear_all(void);


	private:
		// Device->keycode->string binding->keystate
		std::unordered_map<std::string, bool> keystate;
		std::array<std::unordered_map<int, std::string>, NUM_DEVICES> binding;

		struct MousePos mouse;

		int disp_width, disp_height;
		struct MousePosDouble mouse_norm;

		// Attach input subsystem to main engine
		void init(ALLEGRO_EVENT_QUEUE* event_queue);

		// Update helpers
		bool is_input(const ALLEGRO_EVENT* event);
		void update_state(int device, int keycode, bool new_state);
		void update_mouse_axes(const ALLEGRO_EVENT* event);

		// Update to be run by main loop
		void update(const ALLEGRO_EVENT* event);

		friend class Engine;
};
