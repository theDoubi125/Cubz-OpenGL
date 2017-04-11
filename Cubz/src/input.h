#ifndef INPUT_INCLUDED
#define INPUT_INCLUDED

#include <GLFW\glfw3.h>
#include <vector>

class InputListener
{
public:
	InputListener();
	virtual ~InputListener();
	void startListening();
	virtual void onKeyPressed(int key) { }
	virtual void onKeyReleased(int key) { }
	virtual void onMouseMove(int x, int y) { }
	virtual void onButtonPressed(int button) { }
	virtual void onButtonReleased(int button) { }
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
	void onButtonEvent(int butotn, int event);
	void onMouseMoveEvent(int x, int y);

private:
	std::vector<InputListener*> m_listeners;
};

#endif INPUT_INCLUDED
