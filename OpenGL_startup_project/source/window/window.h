#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Seden {
	class win {
	public:
		static void init(int width, int height, const char* title);
		static void terminate();
		static bool isRunning();
		static void clear();
		static void display();

		static glm::vec2 getResolution();
		static GLFWwindow* getWindowRef();
		static float getDeltaTime();

		static void initGui();
		static void clearGui();
		static void drawGui();
		static void closeGui();
		static void terminateGui();

		win() = delete;

		static bool running;
	private:
		static GLFWwindow* window;
		static float dt;
		static int width;
		static int height;
	};

};