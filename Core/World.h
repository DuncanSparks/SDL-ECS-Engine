#pragma once

#include "Entity.h"
#include "Component.h"
#include "System.h"

#include <SDL2/SDL_events.h>

#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <cstdint>

#include "Window.h"
#include "Vocter.h"

#ifdef ECS_DEBUG
#include <iostream>
#endif


class World {
private:
	static unsigned long EntityCounter;

	Vocter<Entity*> entity_list;
	std::unordered_map<std::type_index, Vocter<Component*>> component_map;
	Vocter<System*> system_list;

	SDL_Event event_handler;

	std::uint64_t dt_now;
	std::uint64_t dt_last;
	double delta_time_;

	Window* window;

	bool quit;

public:
	World();
	~World();

	void add_entity(Entity* ent);

	template <typename C>
	void add_component(C* comp) {
		component_map[typeid(C)].push_back(comp);

		#ifdef ECS_DEBUG
		std::cout << "[ECS] Added component (" << typeid(C).name() << ")\n";
		#endif
	}

	void add_system(System* system);

	void destroy_entity(Entity* ent);

	void destroy_component(Component* comp);

	template <typename C>
	const Vocter<C*>& get_components() {
		return *reinterpret_cast<Vocter<C*>*>(&component_map.at(typeid(C)));
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
