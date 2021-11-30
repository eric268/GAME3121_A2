#include "InputManager.h"
#include <iostream>
void InputManager::setup()
{
	ApplicationContext::setup();
	addInputListener(this);
}
bool InputManager::keyPressed(const KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case 'a':
		std::cout << "A Pressed" << std::endl;
		break;
	case 'd':
		std::cout << "D Pressed" << std::endl;
		break;
	}
	return true;
}