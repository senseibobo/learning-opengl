#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "UnityComponent.h"
#include "Game.h"
class GUIManager
{
public:
	static void Init();
	static void Render();
private:
	static void RenderCrosshair();
	static void RenderEndScreen();
	static void RenderScoreTopLeft();
	static std::unique_ptr<Texture2D> crashTexture;
};

