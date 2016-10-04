#pragma once

#include <stlxtypes.h>

namespace sdlapp {



class AnimationMgr {
public:
	struct Frame{
		sf::IntRect rect;
		sf::Vector2f pivot;
		// 	sf::IntRect src_rect;
		// 	sf::Vector2i src_size;
		//bool rotated;
	};

	struct Animation {
		sf::Texture * _texture;
		Vector<Frame> _frames;
	};

	static void LoadAll(const String & folder = "../resources/animations/"s);
	static const Animation * Get(const String & name);

private:

	static void LoadFile(const String & folder, const String & file);

	static HashMap<String, UniquePtr<Animation>> _animations;
};



};