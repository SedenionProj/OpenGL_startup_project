#include "window.h"
#include "../log.h"
#include <memory>

namespace Seden {
	bool win::running = true;
	bool win::m_isRecording = false;

	float currentFrame = glfwGetTime();
	float lastFrame = 0.0f;
	float win::dt = glfwGetTime();
	int win::m_width = 0;
	int win::m_height = 0;

	GLFWwindow* win::window = nullptr;

	FILE* ffmpeg = nullptr;
	std::unique_ptr<int[]> image;

	void win::init(int width, int height, const char* title)
	{
		m_width = width;
		m_height = height;

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

		if (m_isRecording) {
			glReadPixels(0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, image.get());
			fwrite(image.get(), sizeof(int) * m_width * m_height, 1, ffmpeg);
		}
	}

	glm::vec2 win::getResolution()
	{
		return glm::vec2(m_width, m_height);
	}

	float win::getDeltaTime()
	{
		return dt;
	}

	void win::startRecording(const std::string& path, int fps)
	{
		if (!m_isRecording) {
			image = std::make_unique<int[]>(m_width * m_height);
			
			std::string cmd = "ffmpeg -r " + std::to_string(fps) +
				" -f rawvideo -pix_fmt rgba -s " + std::to_string(m_width) + "x" + std::to_string(m_height) + " -i - " +
				"-threads 0 -preset fast -y -pix_fmt yuv420p -crf 21 -vf vflip " + path + ".mp4";

			ffmpeg = _popen(cmd.c_str(), "wb");
			m_isRecording = true;
		}
	}

	void win::stopRecording()
	{
		if (m_isRecording) {
			m_isRecording = false;
			_pclose(ffmpeg);
		}
	}

	bool win::isRecording()
	{
		return m_isRecording;
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