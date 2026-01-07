#include <game.hpp>
#include <raylib.h>

// ImGui
#include <imgui.h>
#include <rlImGui.h>
#include <imguiThemes.h>

void Game::Start()
{
	player.LoadTextures();
}

void Game::Update()
{
	float dt = GetFrameTime();
	enemy.Update(dt, player);
	player.Update(dt);
}

void Game::Draw()
{
	ClearBackground(RAYWHITE);

	enemy.Draw();
	player.Draw();
}

void Game::Init()
{
	SetConfigFlags( FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "raylib [core] example - basic window");

	rlImGuiSetup(true);

	//you can use whatever imgui theme you like!
	//ImGui::StyleColorsDark();
	//imguiThemes::yellow();
	//imguiThemes::gray();
	imguiThemes::green();
	//imguiThemes::red();
	//imguiThemes::embraceTheDarkness();

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
