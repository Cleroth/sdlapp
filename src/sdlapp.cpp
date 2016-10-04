#include <sdlapp.h>
#include <os/winconsole/console.h>
#include <io/json.h>
#include <os/time.h>

extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}


namespace sdlapp {

SDLApp::~SDLApp() {
}
// 
// void SDLApp::OnQuit() {
// 	if(!_config)
// 		return;
// 
// 	auto & app = (*_config)["app"];
// 
// 	app["fullscreen"] = _fullscreen;
// 	app["borderless"] = _borderless;
// 	if(!_fullscreen) {
// 		app["resolution_x"] = _resolution.x;
// 		app["resolution_y"] = _resolution.y;
// 	}
// 
// }
// 
// void SDLApp::OnForceQuit() {
// 	_wnd.reset();
// }
// 
void SDLApp::Setup() {
	BaseApp::Setup();

	try {
		auto app = _config->find("app");

		if(app != _config->end()) {
			_fullscreen = app->value("fullscreen", true);
			_borderless = app->value("borderless", true);
			_resolution.x = app->value("resolution_x", 800);
			_resolution.y = app->value("resolution_y", 600);
		}

	} catch(...) {
	}

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		throw 1;
	}

	CreateWnd();
}

void SDLApp::CreateWnd() {
	_wnd.reset(SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN));

	if(!_wnd){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		throw 2;
	}

// 	if (_fullscreen && _borderless)
// 	{
// 		// 	sf::ContextSettings settings;
// 		// 	settings.antialiasingLevel = 8;
// 		sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
// 		_cur_resolution = { (int)desktop.width, (int)desktop.height };
// 	} else {
// 		_cur_resolution = _resolution;
// 	}
// 
// 	u32 style;
// 	if(_fullscreen) {
// 		if(_borderless) {
// 			style = sf::Style::None;
// 			_cur_resolution.y += 2; // Fixes Windows considering it's fullscreen when res is same as desktop
// 		} else
// 			style = sf::Style::Fullscreen;
// 	} else 
// 		style = sf::Style::Default;
// 
// 	_wnd = MakeUnique<sf::RenderWindow>(sf::VideoMode(_cur_resolution.x, _cur_resolution.y), _name, style);
// 	_wnd->setVerticalSyncEnabled(true);
}
 
// void SDLApp::Loop() {
// 	Time::Update();
// 
// 	auto frame_time = Time::Now() - 1000 / _framerate;
// 	while(_running && g_con.IsRunning) {
// 		Time::Update();
// 
// 		UpdateView();
// 
// 
// 		OnTick();
// 		if(_cur_scene)
// 			_cur_scene->Tick();
// 
// 		sf::Event ev;
// 		while(_wnd->pollEvent(ev)) {
// 			switch(ev.type) {
// 			case sf::Event::MouseButtonPressed:
// 				if(!IsFullscreen() && !IsFocused())
// 					SetForegroundWindow(_wnd->getSystemHandle());
// 				break;
// 
// 			case sf::Event::Closed:
// 				_wnd->close();
// 				return;
// 
// 			case sf::Event::LostFocus:
// 				if(_fullscreen)
// 					ShowWindow(_wnd->getSystemHandle(), SW_MINIMIZE);
// 				_is_focused = false;
// 				break;
// 
// 			case sf::Event::GainedFocus:
// 				if(_fullscreen)
// 					ShowWindow(_wnd->getSystemHandle(), SW_RESTORE);
// 				_is_focused = true;
// 				break;
// 
//  			case sf::Event::Resized:
//  				_cur_resolution = {(int)ev.size.width, (int)ev.size.height};
// 				// SFML makes things twitch when zoomed in and resolution isn't even
// 				if(_cur_resolution.x % 2 != 0)
// 					_cur_resolution.x++;
// 				if(_cur_resolution.y % 2 != 0)
// 					_cur_resolution.y++;
// 				if(!_fullscreen)
// 					_resolution = _cur_resolution;
//  				UpdateView();
//  				break;
// 			}
// 			
// 
// 			if(HandleEvent(ev) || _cur_scene->HandleEvent(ev))
// 				continue;
// 
// 			if(ev.type == sf::Event::KeyPressed) {
// 				if(ev.key.code == sf::Keyboard::D && ev.key.control
// 					&& ev.key.shift && ev.key.alt) {
// 					_is_debug_draw = !_is_debug_draw;
// 				} else if(ev.key.code == sf::Keyboard::Return && ev.key.alt) {
// 					SetFullscreen(!_fullscreen);
// 				}
// 			}
// 		}
// 
// 		if(!_is_focused && _unfocused_sleep_duration > 0) {
// 			Sleep(_unfocused_sleep_duration);
// 			//continue;
// 		}
// 
// 		if (Time::Elapsed(frame_time, 1000 / _framerate)) {
// 			//_wnd->clear();
// 			if(_cur_scene)
// 				_cur_scene->Draw();
// 
// 			OnDraw();
// 			_wnd->display();
// 
// 			frame_time = Time::Now();
// 		}
// 
// 		if(_tick_sleep > 0)
// 			Sleep(_tick_sleep);
// 	}
// }
// 
// void SDLApp::AddFont(const String & name, u32 default_size,
// 	sf::Color outline_color, float outline_size) {
// 	sf::Font font;
// 	if(!font.loadFromFile(kResourcesFolder + "ui_assets/fonts/"s + name))
// 		throw std::domain_error("Failed to load font: " + name);
// 
// 	_fonts += Font{font, default_size, name, outline_color, outline_size};
// }
// 
// void SDLApp::SetScene(UniquePtr<Scene> scene) {
// 	_cur_scene = std::move(scene);
// }
// 
// void SDLApp::SetFullscreen(bool enabled, bool update_wnd /*= true*/) {
// 	_fullscreen = enabled;
// 
// 	if(update_wnd) {
// 		CreateWnd();
// 		// trigger a resized event
// 		_wnd->setSize({_wnd->getSize().x - 1, _wnd->getSize().y});
// 		_wnd->setSize({_wnd->getSize().x + 1, _wnd->getSize().y});
// 	}
// }
// 
// void SDLApp::SetVSync(bool enabled) {
// 	_wnd->setVerticalSyncEnabled(enabled);
// }
// 
// void SDLApp::SetViewCenter(sf::Vector2f center) {
// 	_view_center = center;
// 	UpdateView();
// }
// 
// void SDLApp::SetZoom(float zoom) {
// 	_zoom = zoom;
// 	UpdateView();
// }
// 
// void SDLApp::UpdateView() {
// 	auto view = _wnd->getDefaultView();
// 	view.setCenter(_view_center);
// 	view.setSize({(float)GetResolution().x, (float)GetResolution().y});
// 	view.zoom(_zoom);
// 	_wnd->setView(view);
// }


};