#pragma once

#include <stlxtypes.h>

namespace sdlapp {

class Scene {
public:
	Scene(RendererPtr & ren) : _ren(ren) {}
	virtual ~Scene() {}

	virtual void Tick() {};
	virtual void Draw() {};
	virtual bool HandleEvent(Event & ev) = 0;

protected:
	RendererPtr & _ren;
};


};