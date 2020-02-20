#pragma once

#include "Entity.h"
#include "Component.h"
#include "System.h"

#include <SDL2/SDL_events.h>

#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <cstdint>

#include "Window.h"


class World {
private:
	static unsigned long EntityCounter;

	std::vector<Entity*> entity_list;
	std::unordered_map<std::type_index, std::vector<Component*>> component_map;
	std::vector<System*> system_list;

	SDL_Event event_handler;

	std::uint64_t dt_now;
	std::uint64_t dt_last;
	double delta_time_;

	Window* window;

	bool quit;

public:
	World();
	~World();

	//const std::vector<Entity*>& get_entity_list() const;
	void add_entity(Entity* ent);
	void add_component(Component* comp);
	void add_system(System* system);


	template <typename C>
	const std::vector<C*>& get_components() {
		return *reinterpret_cast<std::vector<C*>*>(&component_map.at(typeid(C)));
	}

	template <typename C>
	void add_component(C* comp) {
		component_map[typeid(C)].push_back(comp);
	}

	void initialize_entities();
	void poll_events();
	void tick_delta_time();

	void process_systems();

	double delta_time() const;

	Window* get_window() const;
	void set_window(Window* value);

	bool game_quit() const;
};