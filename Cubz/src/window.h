#ifndef CUBZ_WINDOW_INCLUDED
#define CUBZ_WINDOW_INCLUDED

#include "vec.h"
#include <string>
#include <vector>
#include "input.h"

class Input;
struct GLFWwindow;
class Scene;

class Window : public InputListener
{
public:
	Window(std::string title, ivec2 size);
	~Window();

	void open();
	void close();

	void update(float deltaTime);
	void render();
	bool isOpen() const;

	virtual void onKeyPressed(int key);

	GLFWwindow *glwfWindow() const;

	static const Window* getCurrentWindow();

private:
	GLFWwindow *m_window;
	ivec2 m_size;
	std::string m_title;
	bool m_isOpen;
	Scene* m_scene;

	static Window* m_currentWindow;

	bool m_debugWindow;
};

#endif
