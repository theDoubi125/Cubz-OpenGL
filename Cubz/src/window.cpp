#include <glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <gl\GLU.h>
#include <iostream>
#include <imgui.h>

#include "input.h"
#include "window.h"
#include "shader.h"
#include "scene.h"

#include <imgui.cpp>
#include <imgui_demo.cpp>
#include <imgui_draw.cpp>
#include <imgui_internal.h>
#include <imconfig.h>
#include "imgui_impl_glfw_gl3.h"
#include "entity.h"
#include "mesh_render.h"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

Window* Window::m_currentWindow(NULL);

Window::Window(std::string title, ivec2 size) : m_size(size), m_title(title), m_window(NULL), m_isOpen(false), m_scene(new Scene())
{

}

Window::~Window()
{
	close();
}

const Window* Window::getCurrentWindow()
{
	return m_currentWindow;
}

void Window::open()
{
	close();
	m_window = glfwCreateWindow(m_size.x, m_size.y, m_title.c_str(), NULL, NULL);
	glfwMakeContextCurrent(m_window);
	ImGui_ImplGlfwGL3_Init(m_window, true);
	m_isOpen = true;
	if (!gladLoadGL())
	{
		std::cout << "glad load failed" << std::endl;
	}

	Entity::registerComponents();
	MeshRenderer::registerMeshes();

	std::ifstream descrFile("resources/configs/scenes/debugScene.json");
	json descr;
	descrFile >> descr;
	m_scene->init(descr);
}

void Window::close()
{
	if (m_window != NULL)
	{
		glfwDestroyWindow(m_window);
		m_window = NULL;
	}
	m_isOpen = false;
	ImGui_ImplGlfwGL3_Shutdown();
}

void Window::update(float deltaTime)
{
	m_currentWindow = this;
	ImGui_ImplGlfwGL3_NewFrame();

	m_scene->update(deltaTime);
	if (m_debugWindow)
	{
		m_scene->debugUI();
	}
		
	if (glfwWindowShouldClose(m_window))
		close();
}

void Window::onKeyPressed(int key)
{
	m_debugWindow = !m_debugWindow;
}

bool Window::isOpen() const
{
	return m_isOpen;
}

bool show_test_window = true;
bool show_another_window = false;

void Window::render()
{
	if (!m_isOpen)
		return;

	int display_w, display_h;
	glfwGetFramebufferSize(m_window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glUseProgram(m_shader->getProgramId());
	m_scene->render();
	//glUseProgram(0);

	/*	glBindVertexArray(m_vaoID);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
	glDisableVertexAttribArray(0);*/

	/*
	{
		static float f = 0.0f;
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::ColorEdit3("clear color", (float*)&clear_color);
		if (ImGui::Button("Test Window")) show_test_window ^= 1;
		if (ImGui::Button("Another Window")) show_another_window ^= 1;
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	// 2. Show another simple window, this time using an explicit Begin/End pair
	
	{
		ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello");
		ImGui::End();
	}

	// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	if (show_test_window)
	{
		ImGui::SetNextWindowPos(ImVec2(200, 20), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}*/
	ImGui::Render();

	glfwSwapBuffers(m_window);
}

GLFWwindow* Window::glwfWindow() const
{
	return m_window;
}
