//#include "raymath.h"
#include <game.hpp>

// ImGui
#include <imgui.h>
#include <rlImGui.h>
#include <imguiThemes.h>

#include <collission.hpp>

void Game::Start()
{
	background = LoadTexture("E:/RonitCodeStuff/GameDev/BeatEmUpPrototype/art/sprites/background.png");
	player.LoadTextures();
	enemy.LoadTextures();
}

void Game::Update()
{
	float dt = GetFrameTime();
	enemy.Update(dt, player);
	player.Update(dt);

	// Collisions
	CheckCollisions(enemy, player);
}

void Game::Draw()
{
	ClearBackground(RAYWHITE);
	DrawTexture(background, 0, 0, WHITE);

	enemy.Draw();
	player.Draw();

	float dist = Vector2Distance(player.GetPosition(), {enemy.hitBox.x, enemy.hitBox.y});
	ImGui::Text("Dist: %f", dist);
}

void Game::Init()
{
	SetConfigFlags( FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "raylib [core] example - basic window");

	rlImGuiSetup(true);

	ImGui::StyleColorsDark();
	imguiThemes::embraceTheDarkness();

	io = &ImGui::GetIO();
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io->FontGlobalScale = 2;

	ImGuiStyle &style = ImGui::GetStyle();
	if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		//style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 0.5f;
		//style.Colors[ImGuiCol_DockingEmptyBg].w = 0.f;
	}
}


void Game::ImGuiDrawBegin()
{
	rlImGuiBegin();

	ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
	ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	ImGui::PopStyleColor(2);
	ImGui::Begin("Test");


}

void Game::ImGuiDrawEnd()
{
	ImGui::End();
	rlImGuiEnd();

	if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

void Game::Shutdown()
{
	rlImGuiShutdown();
	CloseWindow();
}
