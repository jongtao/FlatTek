#pragma once


/*
#include <list>
#include <unordered_map>
#include <string>
*/
#include <stdexcept>

#include "graphics.h"
#include "input.h"

class Engine;
class Input;
class Scene;


class SceneManager
{
	public:
		SceneManager(Engine* engine);

		void req_change(Scene* new_scene);
		void req_soft_change(Scene* new_scene); // doesn't delete scene's memory

		void req_halt();
		void req_soft_halt();

		Graphics* req_graphics();
		Input* req_input(void);
		//void req_audio();

	private:
		Engine* parent_engine;

		Scene* current_scene;
		Scene* next_scene;

		bool request_exists;
		bool change_requested;
		bool hard_requested;
		bool halt_requested;
		bool soft_halt_requested;

		void change(bool is_hard);
		void clear_scenes(void);

		bool update(void);
		void draw(void);

	friend class Engine;
};



class Scene
{
	public:
		virtual void init(void){}
		virtual bool update(void){return true;}
		virtual void draw(void){}

	protected:
		SceneManager* scene_manager;
		Graphics* graphics;
		Input* input;
		// std::list<GameObject> objects
		
		void attach_system(void);
	
	friend SceneManager;
};
