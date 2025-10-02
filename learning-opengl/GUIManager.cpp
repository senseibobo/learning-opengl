#include "GUIManager.h"


std::unique_ptr<Texture2D> GUIManager::crashTexture = nullptr;

void GUIManager::Init()
{
	crashTexture = std::make_unique<Texture2D>("./unity_crash.png");
}

void GUIManager::Render()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
	if (Game::over)
	{
		RenderEndScreen();
	}
	else
	{
		RenderCrosshair();
		RenderScoreTopLeft();
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIManager::RenderCrosshair()
{
	ImGuiIO& io = ImGui::GetIO();
	ImDrawList* drawList = ImGui::GetForegroundDrawList();

	float cx = io.DisplaySize.x * 0.5f;
	float cy = io.DisplaySize.y * 0.5f;

	float size = 10.0f;
	ImU32 color = IM_COL32(255, 255, 255, 255);

	drawList->AddLine(ImVec2(cx - size / 2, cy), ImVec2(cx + size / 2, cy), color, 2.0f);
	drawList->AddLine(ImVec2(cx, cy - size / 2), ImVec2(cx, cy + size / 2), color, 2.0f);
}

void GUIManager::RenderEndScreen()
{
	ImGui::SetNextWindowPos(ImVec2(200, 200));
	ImGui::Begin("Score", NULL,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoScrollbar);

	ImVec2 imageSize = ImVec2(390, 239);
	ImGui::Image((void*)(intptr_t)crashTexture->ID, imageSize);

	ImDrawList* drawList = ImGui::GetForegroundDrawList();

	ImVec2 windowPos = ImGui::GetWindowPos();
	ImVec2 imagePos = ImGui::GetItemRectMin();

	char buffer[64];
	sprintf(buffer, "Score: %d", UnityComponent::score);

	ImVec2 textSize = ImGui::CalcTextSize(buffer);
	ImVec2 textPos = ImVec2(imagePos.x + (imageSize.x - textSize.x-10),
		imagePos.y + (imageSize.y - textSize.y) * 0.5f);

	drawList->AddText(textPos, IM_COL32(0, 0, 0, 255), buffer);

	ImGui::End();
}

void GUIManager::RenderScoreTopLeft()
{
	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::Begin("Stats", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Score: %d", UnityComponent::score);
	ImGui::End();
}
