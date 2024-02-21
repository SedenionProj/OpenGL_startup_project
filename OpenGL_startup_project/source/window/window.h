#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Seden {
public:
	static void init(int width, int height, const char* title);
	static void init(bool);
	static void terminate();
	static bool isRunning();
	static void clear();
	static void display();
	static void initGui();
	
	static void clearGui();
	static void drawGui();
	static void closeGui();
	static void terminateGui();

	Seden() = delete;

	static bool running;
private:
	static GLFWwindow* window;
	static int width;
	static int height;
};