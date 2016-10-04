#include <animationmgr.h>
#include <windows.h>
#include <io/json.h>
#include <os/winconsole/console.h> // for Bench
#include <bench.h>
#include <texturemgr.h>

namespace sdlapp {

HashMap<String, UniquePtr<AnimationMgr::Animation>> AnimationMgr::_animations;


void AnimationMgr::LoadAll(const String & folder /*= "../resources/animations/"s*/) {
	BENCHFN;
	char path[MAX_PATH];
	//char temp[MAX_PATH];
	bool is_CRC =0;
	WIN32_FIND_DATA fd;
	DWORD exc_attr = 0;
	sprintf_s( path, "%s/*", folder.c_str());
	
	HANDLE hFind = FindFirstFile( path, &fd);

	if(hFind == INVALID_HANDLE_VALUE)
		return;

	do
	{
/*		if(fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
			String dirname = fd.cFileName;
			std::transform(begin(dirname), end(dirname), begin(dirname), [](char c) { return c == '/' ? '\\' : c; });
			existing_dirs.emplace_back(dirname);

			if(fd.cFileName[0] != '.') {
				//New Subdirectory exists
				sprintf_s(temp, "%s\\%s\\", folder.c_str(), fd.cFileName);
				//printf("%s \n",temp);

				if(shortDir == "")
					sprintf_s(shortd, "%s", fd.cFileName);
				else
					sprintf_s(shortd, "%s\\%s", shortDir.c_str(), fd.cFileName);

				FindFiles(temp, false, shortd);
			}
		}
		else */
		if(fd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY && !(fd.dwFileAttributes & exc_attr)) {
			String lowercase = fd.cFileName;
			transform(begin(lowercase), end(lowercase), begin(lowercase), tolower);

			String ext = "";
			auto pos = lowercase.find_last_of('.');
			if(pos != String::npos && pos != lowercase.size())
				ext = lowercase.substr(pos + 1);

			if(ext != "json")
				continue;

			LoadFile(folder, fd.cFileName);
		}
	} while(FindNextFile(hFind, &fd));

	FindClose( hFind);
}

const AnimationMgr::Animation * AnimationMgr::Get(const String & name) {
	auto it = _animations.Find(name);

	if(it == _animations.end())
		throw std::domain_error("Unknown animation: " + name);

	return it->second.get();
}

void AnimationMgr::LoadFile(const String & folder, const String & file) {
	char txt[256];

	auto j = LoadJson(folder + file);

	auto addFrame = [](UniquePtr<Animation> & vec, detail::json & f) {
		Frame frame;

		frame.rect = {f["frame"]["x"], f["frame"]["y"], f["frame"]["w"], f["frame"]["h"]};
		auto src_rect = sf::IntRect{f["spriteSourceSize"]["x"], f["spriteSourceSize"]["y"],
			f["spriteSourceSize"]["w"], f["spriteSourceSize"]["h"]};
		auto src_size = sf::Vector2i{f["sourceSize"]["w"], f["sourceSize"]["h"]};
		auto pivot_pct = sf::Vector2f{f["pivot"]["x"], f["pivot"]["y"]};

		frame.pivot = {src_size.x * pivot_pct.x - src_rect.left, src_size.y * pivot_pct.y - src_rect.top};

		vec->_frames += frame;
	};

	auto frames = j["frames"];
	for(auto it = frames.begin(); it != frames.end(); ++it) {
		auto file_name = it.key();
		auto underscore = file_name.find_last_of('_');
		auto dot = file_name.find_last_of('.');
		auto frame_number = atoul(file_name.substr(underscore + 1, dot - underscore).c_str());
		
		if(frame_number != 0)
			continue;
		
		auto name = file_name.substr(0, underscore);
		auto & vec = _animations[name];
		vec = MakeUnique<Animation>();
		addFrame(vec, *it);

		auto texture_file = folder + j["meta"]["image"].get<String>();
		vec->_texture = TextureMgr::Get(texture_file);

		String ext = file_name.substr(dot + 1, file_name.size());
		while(true) {
			sprintf_s(txt, "%s_%.3u.%s", name.c_str(), vec->_frames.Size(), ext.c_str());
			auto it = frames.find(txt);

			if(it == frames.end())
				break;

			addFrame(vec, *it);
		}
	}

}

};