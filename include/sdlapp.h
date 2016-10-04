#pragma once

namespace sdlapp {
	struct SDLWindowDestroyer
	{
		void operator()(SDL_Window* w) const
		{
			SDL_DestroyWindow(w);
		}
	};
	using Window = SDL_Window;
	using WindowPtr = UniquePtr<Window, SDLWindowDestroyer>;
	using Event = SDL_Event;
};

#include "scene.h"
#include <BaseApp.h>



namespace sdlapp {

using Window = SDL_Window;
using Event = SDL_Event;


class SDLApp : public BaseApp {
public:
	using BaseApp::BaseApp;
	~SDLApp();

// 	virtual void OnStart() override {}
// 	virtual void OnTick() override {}
	virtual void OnDraw() {}
// 	virtual void OnQuit() override;
// 	virtual void OnForceQuit() override;
// 
	virtual bool HandleEvent(const Event & ev) { return false; }
// 
// 	void AddFont(const String & name, u32 default_size = 16,
// 		sf::Color outline_color = {0,0,0,255}, float outline_size = 1.f);
 	void SetScene(UniquePtr<Scene> scene);
 	auto * GetScene()		const { return _cur_scene.get(); }
 
 	void SetResolution(Point<i32> resolution, bool update = true) { _resolution = resolution; }
 	auto GetResolution()	const { return _cur_resolution; }
// 	
 	void SetFullscreen(bool enabled, bool update_wnd = true);
 	bool IsFullscreen()	const { return _fullscreen; }
 	bool IsFocused()		const { return _is_focused; }
 	bool IsDebugDraw()	const { return _is_debug_draw; }
 	void SetDebugDraw(bool enabled)	{ _is_debug_draw = enabled; }
 
// 	void SetVSync(bool enabled);
// 	void SetFramerate(u32 framerate)			{ _framerate = framerate; }
// 	void SetUnfocusedSleep(u32 duration)	{ _unfocused_sleep_duration = duration; }
// 	auto GetViewCenter()					const { return _view_center; }
// 	void SetViewCenter(sf::Vector2f center);
// 	void SetZoom(float zoom);
//
	WindowPtr _wnd;
// 
// private:
// 	struct Font {
// 		sf::Font font;
// 		u32 size;
// 		String name;
// 		sf::Color outline_color;
// 		float outline_size;
// 	};
// 
// public:
// 	Vector<Font> _fonts;
// 
 private:
// 	static constexpr char * kResourcesFolder = "../resources/";
// 
 	void Setup() override;
	void Loop() override;

 	void CreateWnd();
// 	void UpdateView();
// 
 	bool _fullscreen = true;
 	bool _borderless = true;
	bool _is_focused = true;
 	bool _is_debug_draw = false;
	Point<i32> _cur_resolution;
 	Point<i32> _resolution{800,600};

	u32 _tick_sleep = 1;
	u32 _unfocused_sleep_duration = 5;
	u32 _framerate = 60;

	UniquePtr<Scene> _cur_scene;
// 	sf::Vector2f _view_center;
// 	float _zoom = 1.f;
};



};