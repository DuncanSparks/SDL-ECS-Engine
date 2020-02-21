#include "Entity.h"

Entity::Entity() {}

Entity::~Entity() {
	/*for (auto pair : component_refs)
		delete pair.second;*/
}


unsigned long Entity::get_id() const {
	return id;
}


void Entity::set_id(unsigned long value) {
	id = value;
}


const std::unordered_map<std::type_index, Component*>& Entity::get_components() {
	return component_refs;
}
