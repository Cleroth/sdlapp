#include <texturemgr.h>

#define GL_CLAMP_TO_EDGE						0x812F
#define GL_TEXTURE_MAX_LEVEL              0x813D

namespace sdlapp {

namespace TextureMgr {
	HashMap<String, UniquePtr<sf::Texture>> _textures;
	bool _smooth = true;
	bool _clamp_to_edge = false;

	UniquePtr<sf::Texture> Load(const String & filename) {
		auto tex = MakeUnique<sf::Texture>();

		sf::Image image;
		if(!image.loadFromFile(filename)) {}

		if(!tex->loadFromImage(image))
			throw std::runtime_error("Failed to load texture " + filename);
		
		sf::Texture::bind(tex.get());

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 3);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, GL_NEAREST);

		// somehow this texture gets corrupted when a new texture
		// is made on this thread. glFlush fixes this.
		//glFlush();

		return tex;
	}


	sf::Texture * Get(const String & filename, bool smooth/* = true*/, bool clamp_to_edge) {
		auto & ptr = _textures[filename];

		if(!ptr) {
			ptr = Load(filename);
			ptr->setSmooth(smooth);
 			if(clamp_to_edge) {
 				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
 				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 			}
		}
		
		return ptr.get();
	}

	sf::Texture * Get(const String & filename) {
		return Get(filename, _smooth, _clamp_to_edge);
	}

	void SetDefaultSmooth(bool value) {
		_smooth = value;
	}

	void SetDefaultClampToEdge(bool value) {
		_clamp_to_edge = value;
	}

	const List & GetList() {
		return _textures;
	}

}

/*
namespace Sprites {
	HashMap<String, SpriteFrame> _sprites;
	Vector<UniquePtr<SpriteSheet>> _spritesheets;

	void LoadAll() {
		_spritesheets += MakeUnique<SpriteSheet>("golite");
	}

	SpriteFrame SmoldyAdventure::Sprites::Get(const String & name) {
		auto it = _sprites.Find(name);
		ASSERT(it != _sprites.end());

		return it->second;
	}

	void Add(const String & name, sf::Texture * tex, Frame * frame) {
		_sprites[name] = {tex, frame};
	}

	void Draw(sf::RenderTarget & tgt, const SpriteFrame & sprite_frame, WorldPos pos) {
		auto * frame = sprite_frame.second;
		sf::Sprite sprite(*sprite_frame.first, frame->rect);

		//auto it = std::next(std::begin(_sprites), random(0, _sprites.Size() - 1));
		//auto it = std::next(std::begin(_sprites), (Time::Now() / 250) % _sprites.Size());
		//sf::Sprite sprite(*sprite_frame.first, it->second.second->rect);

		pos -= frame->pivot;
		sprite.setPosition(pos);
		tgt.draw(sprite);
	}


};*/

};
