#pragma once

#include <stlxtypes.h>

namespace sdlapp {

class Scene {
public:
	Scene(WindowPtr & wnd) : _wnd(wnd) {}
	virtual ~Scene() {}

	virtual void Tick() {};
	virtual void Draw() {};
	virtual bool HandleEvent(Event & ev) = 0;

protected:
	WindowPtr & _wnd;
};


};