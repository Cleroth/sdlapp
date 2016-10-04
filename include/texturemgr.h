#pragma once

#include <stlxtypes.h>

namespace sdlapp {

namespace TextureMgr {
	sf::Texture * Get(const String & name);
	sf::Texture * Get(const String & name, bool smooth, bool clamp_to_edge);
	void SetDefaultSmooth(bool value);
	void SetDefaultClampToEdge(bool value);

	void SetSmooth(bool value);
	void SetClampToEdge(bool value);

	using List = HashMap<String, UniquePtr<sf::Texture>>;
	const List & GetList();
};

/*
namespace Sprites {
	void LoadAll();

	SpriteFrame Get(const String & name);
	void Add(const String & name, sf::Texture * tex, Frame * frame);
	void Draw(sf::RenderTarget & tgt, const SpriteFrame & sprite_frame, WorldPos pos);
};*/


};