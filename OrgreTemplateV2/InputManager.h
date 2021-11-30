#pragma once
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"

using namespace Ogre;
using namespace OgreBites;

class InputManager : public ApplicationContext, public InputListener
{
	void setup();
	bool keyPressed(const KeyboardEvent& evt);
};

