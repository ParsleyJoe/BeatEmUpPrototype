#pragma once
#include <player.hpp>
#include <enemy.hpp>

struct ImGuiIO;

class Game
{
private:
	ImGuiIO* io = nullptr;
	Player player;
	Enemy enemy;
	Texture2D background;
	
public:

	// Imgui and Window initialization
	void Init();

	// Texture Loading and objects initialization
	void Start();

	// Main Drawing Function
	void Draw();

	void Update();
	void ImGuiDrawBegin();
	void ImGuiDrawEnd();
	void Shutdown();
};
