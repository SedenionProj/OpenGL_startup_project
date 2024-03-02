#include "window.h"

namespace Seden {
	bool win::running = true;
	float currentFrame = glfwGetTime();
	float lastFrame = 0.0f;
	float win::dt = glfwGetTime();
	int win::width = 0;
	int win::height = 0;

	GLFWwindow* win::window = nullptr;

	void win::init(int width, int height, const char* title)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		window = glfwCreateWindow(width, height, title, NULL, NULL);
		glfwMakeContextCurrent(window);
		if (window == NULL)
		{
			glfwTerminate();
		}

		gladLoadGL();
		glViewport(0, 0, width, height);
	}

	void win::terminate()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void win::clear()
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void win::display()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
		currentFrame = glfwGetTime();
		dt = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}

	glm::vec2 win::getResolution()
	{
		return glm::vec2(width, height);
	}

	float win::getDeltaTime()
	{
		return dt;
	}

	GLFWwindow* win::getWindowRef()
	{
		return window;
	}

	bool win::isRunning()
	{
		return !glfwWindowShouldClose(window) && running;
	}

	void win::initGui() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init();
		ImGui::StyleColorsDark();
	}

	void win::clearGui()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void win::drawGui()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		
	}

	void win::closeGui()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void win::terminateGui()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}