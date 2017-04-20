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
	void stopListening();
	virtual void onKeyPressed(int key) { }
	virtual void onKeyReleased(int key) { }
	virtual void onMouseMove(int x, int y) { }
	virtual void onButtonPressed(int button) { }
	virtual void onButtonReleased(int button) { }
	virtual void onMouseWheel(int offset) { }
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
	void onWheelEvent(int offset);

private:
	std::vector<InputListener*> m_listeners;
};

#endif INPUT_INCLUDED
