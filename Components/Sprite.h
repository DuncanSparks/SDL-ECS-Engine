#pragma once

#include "Component.h"
#include "Transform.h"

#include <SDL2/SDL_image.h>

class Sprite : public Component {
private:
	SDL_Surface* image;
	Transform* transform;

public:
	Sprite(const char* image_file);
	~Sprite();

	SDL_Surface* get_image() { return image; }

	Transform* get_transform() { return transform; }
	void set_transform(Transform* value) { transform = value; }
};