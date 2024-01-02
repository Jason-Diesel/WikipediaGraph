#pragma once

class Settings {
public:
	static Settings& GetInst();

	Settings(Settings const&) = delete;
	void operator=(Settings const&) = delete;
private:
	Settings() {};
	static Settings s_Instance;

	bool fullscreen;
	float ScreenWidth, ScreenHeight;

};