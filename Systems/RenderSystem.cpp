#include "RenderSystem.h"

#include "Core/World.h"
#include "Core/Vector2.h"
#include "Core/Math.h"
#include "Core/ECSSystem.h"

#include <cmath>

#include <SDL2/SDL_surface.h>

void RenderSystem::run(World& world) {
	if (world.components_exist_of_type<Sprite>()) {
		for (auto* spr : world.get_components<Sprite>()) {
			render_sprite(spr, spr->get_owner_component<Transform>(), world);
		}
	}

	if (world.components_exist_of_type<AnimatedSprite>()) {
		for (auto* spr : world.get_components<AnimatedSprite>()) {
			render_animated_sprite(spr, spr->get_owner_component<Transform>(), world);
		}
	}

	if (world.components_exist_of_type<BoxCollider>()) {
		for (auto* box : world.get_components<BoxCollider>()) {
			draw_collider(box, world);
		}
	}
}


void RenderSystem::render_sprite(Sprite* spr, Transform* tr, World& world) {
	if (tr) {
		Vector2 pos = tr->get_position_from_parent();
		float rot = tr->get_rotation();
		Vector2 scale = tr->get_scale();
		Vector2I size = spr->sprite_size();

		SDL_Rect pos_rect{spr->is_centered() ? static_cast<int>(pos.x - size.x) : static_cast<int>(pos.x), spr->is_centered() ? static_cast<int>(pos.y - size.y) : static_cast<int>(pos.y), static_cast<int>(size.x * scale.x), static_cast<int>(size.y * scale.y)};

		SDL_RenderCopyEx(Window::get_renderer(), spr->get_texture(), nullptr, &pos_rect, rot, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
	}
}


void RenderSystem::render_animated_sprite(AnimatedSprite* spr, Transform* tr, World& world) {
	if (tr && spr->has_animations()) {
		spr->add_anim_time(world.delta_time());
		if (spr->get_anim_time() >= 1.0 / spr->get_animation_speed()) {
			spr->advance_frame();
			spr->reset_anim_time();
		}

		Vector2 pos = tr->get_position_from_parent();
		float rot = tr->get_rotation();
		Vector2 scale = tr->get_scale();
		Vector2I size = spr->sprite_size();

		SDL_Rect pos_rect{ spr->is_centered() ? static_cast<int>(pos.x - size.x) : static_cast<int>(pos.x), spr->is_centered() ? static_cast<int>(pos.y - size.y) : static_cast<int>(pos.y), static_cast<int>(size.x * scale.x), static_cast<int>(size.y * scale.y) };
		SDL_RenderCopyEx(Window::get_renderer(), spr->current_frame_texture(), nullptr, &pos_rect, rot, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
	}
}


void RenderSystem::draw_collider(BoxCollider* coll, World& world) {
	SDL_SetRenderDrawColor(Window::get_renderer(), 0, 255, 0, 128);

	Vector2 pos = coll->get_owner_component<Transform>()->get_position_from_parent();

	SDL_SetRenderDrawBlendMode(Window::get_renderer(), SDL_BLENDMODE_BLEND);
	SDL_Rect draw_rect{pos.x, pos.y, coll->get_extent_x(), coll->get_extent_y()};
	SDL_RenderFillRect(Window::get_renderer(), &draw_rect);
	SDL_SetRenderDrawBlendMode(Window::get_renderer(), SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(Window::get_renderer(), 0, 0, 0, 255);
}
