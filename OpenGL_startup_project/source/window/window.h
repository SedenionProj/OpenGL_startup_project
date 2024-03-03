#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <string>

namespace Seden {
	class win {
	public:
		win() = delete;

		static void init(int width, int height, const char* title);
		static void terminate();
		static bool isRunning();
		static void clear();
		static void display();

		static glm::vec2 getResolution();
		static GLFWwindow* getWindowRef();
		static float getDeltaTime();

		static void startRecording(const std::string& path, int fps = 60);
		static void stopRecording();
		static bool isRecording();

		static void initGui();
		static void clearGui();
		static void drawGui();
		static void closeGui();
		static void terminateGui();
		
		static bool running;
	private:
		static GLFWwindow* window;
		static float dt;
		static int m_width;
		static int m_height;
		static bool m_isRecording;
	};

};