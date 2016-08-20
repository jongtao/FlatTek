#pragma once


/*
#include <list>
#include <unordered_map>
#include <string>
*/
#include <stdexcept>

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

		Input* req_input(void);
		//void req_audio();
		//void req_graphics();

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
		virtual void init(){}
		virtual bool update(){return true;}
		virtual void draw(){}

	protected:
		SceneManager* scene_manager;
		Input* input;
		// std::list<GameObject> objects
		
		void attach_system(void)
		{
			if(!scene_manager)
				throw std::runtime_error("Scene tried to attach to nonexistent manager");

			input = scene_manager->req_input();

			if(!input)
				throw std::runtime_error("Input attachment failed");
		}
	
	friend SceneManager;
};
