#ifndef INPUT_INCLUDED
#define INPUT_INCLUDED

#include <GLFW\glfw3.h>
#include <vector>

class InputListener
{
public:
	InputListener();
	virtual ~InputListener();
	virtual void onKeyPressed(int key) { }
	virtual void onKeyReleased(int key) { }
};

class Input
{
private:
	Input();
public:
	~Input();

	static Input& instance;

	void update();

	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void onKeyEvent(int key, int event);

private:
	std::vector<InputListener*> m_listeners;
};

#endif INPUT_INCLUDED