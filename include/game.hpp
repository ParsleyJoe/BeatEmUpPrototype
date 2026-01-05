#pragma once

struct ImGuiIO;

class Game
{
private:
	ImGuiIO* io = nullptr;

public:

	void Init();
	void ImGuiDrawBegin();
	void ImGuiDrawEnd();
	void Shutdown();
};
