#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>
#include <string>
#include "UIManager.h"
#include "BackgroundObject.h"
#include "DoodlePlayer.h"
#include "PongPaddle.h"

using namespace Ogre;
using namespace OgreBites;

/// Class which initializes main game loop
/// 
/// Creates and initializes main game objects such as Pong ball, paddle, UI and window
class MainInitalizer
	: public ApplicationContext
	, public InputListener
{
private:
	PongPaddle* m_player1Pong;
	DoodlePlayer*   m_doodlePlayer;
	BackgroundObject* m_backgroundObject[2];
	UIManager* m_UIManager;
	SceneManager* scnMgr;
	Root* root;

public:
	Camera* cam;
	/// MainInitalizer Constructor
	MainInitalizer();

	/// MainInitalizer Destructor
	///
	/// Destroys all pointers owned and managed by MainInitalizer
	virtual ~MainInitalizer();

	/// Creates most game objects
	/// 
	/// Creates and initializes scene manager, root, camera, light, UI, frame listeners and main game objects 
	/// @see createScene() createCamera() CreateTraysAndLabels() createFrameListener()
	void setup();

	/// Checks if key has been pressed
	/// @param evt Gives information regarding which key has been pressed
	/// @note **A** - Moves paddle to the left
	/// @note **D** - Moves paddle to the right
	/// @note **R** - Restarts game
	/// @note **ESP** - Closes Window
	bool keyPressed(const KeyboardEvent& evt);

	/// Checks if key has been released
	/// @param evt Gives information regarding which key has been released
	/// @note **A** - Releases stops paddle from moving
	/// @note **D** - Releases stops paddle from moving
	bool keyReleased(const KeyboardEvent& evt);

	/// Creates game objects in scene
	/// 
	/// Creates base game objects such as plane, pong ball & paddle, lighting
	void createScene();


	/// Resets Game
	/// 
	/// Resets all game variables to starting values.
	/// Resets all game objects to starting values and positions
	/// Is done by pressing the *r* key
	void RestartGame();

	/// Creates all frame listeners
	/// 
	/// Creates frame listeners for the UI, pong ball and pong paddle
	/// Then adds them to the root
	void createFrameListener();

	/// Creates all UI elements
	/// 
	/// Creates the tray manager and initializes UIManager variables
	/// @see UIManager() To see which variables are initalized for the UI
	void CreateTraysAndLabels();
};


MainInitalizer::MainInitalizer()
	: ApplicationContext("GAME3121 Assignment 1 Eric Galway 101252535 Pong Game")
{
}

MainInitalizer::~MainInitalizer()
{
	delete m_player1Pong;
	m_player1Pong = nullptr;
	delete m_doodlePlayer;
	m_doodlePlayer = nullptr;
	delete m_UIManager;
	m_UIManager = nullptr;
	delete scnMgr;
	scnMgr = nullptr;
	delete root;
	root = nullptr;
}


void MainInitalizer::setup()
{
	// do not forget to call the base first
	ApplicationContext::setup();
	addInputListener(this);
	
	// get a pointer to the already created root
	root = getRoot();
	scnMgr = root->createSceneManager();

	// register our scene with the RTSS
	RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);

	createScene();
	CreateTraysAndLabels();
	createFrameListener();
}

bool MainInitalizer::keyReleased(const KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case 'a':
		m_player1Pong->SetVelocity(Ogre::Vector3(0, 0, 0));

		break;
	case 'd':
		m_player1Pong->SetVelocity(Ogre::Vector3(0, 0, 0));

		break;
	default:
		break;
	}
	return true;
}

bool MainInitalizer::keyPressed(const KeyboardEvent& evt)
{


	switch (evt.keysym.sym)
	{
	case SDLK_ESCAPE:
		getRoot()->queueEndRendering();
		break;
	case 'a':
		//m_doodlePlayer->GetSceneNode()->translate(Vector3(-10, 0, 0));
		//m_player1Pong->SetVelocity(Ogre::Vector3(-m_player1Pong->GetSpeed(), 0,0));
		break;
	case 'd':
		//m_doodlePlayer->GetSceneNode()->translate(Vector3(10, 0, 0));
		//m_player1Pong->SetVelocity(Ogre::Vector3(m_player1Pong->GetSpeed(), 0, 0));
		break;
	case 'w':
		//m_doodlePlayer->GetSceneNode()->translate(Vector3(0, 0, -10));
		m_doodlePlayer->SetVelocity(Ogre::Vector3(0, 0, -m_player1Pong->GetSpeed()));
		break;
	case 's':
		//m_doodlePlayer->GetSceneNode()->translate(Vector3(0, 0, 10));
		m_doodlePlayer->SetVelocity(Ogre::Vector3(0, 0, m_player1Pong->GetSpeed()));
	case 'r':
		//RestartGame();
		break;
	case 'q':
		m_player1Pong->GetSceneNode()->setPosition(Ogre::Vector3(-100, 0, m_doodlePlayer->GetSceneNode()->getPosition().z));
		break;
	default:
		break;
	}
	return true;
}


void MainInitalizer::createScene()
{
	Ogre::SceneNode* node = scnMgr->createSceneNode("Node1");
	scnMgr->getRootSceneNode()->addChild(node);

	scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

	scnMgr->setAmbientLight(ColourValue(1.0, 1.0, 1.0));

	Ogre::Light* light = scnMgr->createLight("Light1");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(1, -1, 0));

	// Set Light Color
	light->setDiffuseColour(1.0f, 1.0f, 1.0f);
	// Set Light Reflective Color
	light->setSpecularColour(1.0f, 1.0f, 0.0f);




	m_player1Pong = new PongPaddle(scnMgr->createSceneNode("Player1"),scnMgr);
	m_doodlePlayer = new DoodlePlayer(scnMgr->createSceneNode("Ball"), scnMgr, m_player1Pong);

	m_backgroundObject[0] = new BackgroundObject(scnMgr->createSceneNode("BackgroundNode1"), scnMgr, m_doodlePlayer, 0);
	m_backgroundObject[1] = new BackgroundObject(scnMgr->createSceneNode("BackgroundNode2"), scnMgr, m_doodlePlayer, 1);
	m_backgroundObject[1]->GetSceneNode()->setPosition(0, -10, -m_backgroundObject[1]->GetBackgroundZExtent());

	Ogre::Viewport* viewport = getRenderWindow()->addViewport(m_doodlePlayer->GetPlayerCamera());
	viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
	m_doodlePlayer->GetPlayerCamera()->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));

}

void MainInitalizer::CreateTraysAndLabels()
{
	OgreBites::TrayManager* mTrayMgr =  new OgreBites::TrayManager("InterfaceName", getRenderWindow());
	m_UIManager = new UIManager(mTrayMgr, m_player1Pong, m_doodlePlayer);
	scnMgr->addRenderQueueListener(mOverlaySystem);
}
void MainInitalizer::RestartGame()
{
	m_player1Pong->SetScore(0);
	m_player1Pong->SetLivesRemaining(5);
	m_player1Pong->SetLifeLabel(true);
	m_player1Pong->SetPointEarned(true);
	m_doodlePlayer->GetSceneNode()->setPosition(Ogre::Vector3(0, 0, 0));
	m_doodlePlayer->SetVelocity(Ogre::Vector3(0, 0, m_doodlePlayer->GetSpeed()));
}

void MainInitalizer::createFrameListener()
{
	Ogre::FrameListener* P1FrameListener = m_player1Pong;
	Ogre::FrameListener* DoodlePlayerFrameListener = m_doodlePlayer;
	Ogre::FrameListener* UIFrameListener = m_UIManager;
	Ogre::FrameListener* Background1FrameListener = m_backgroundObject[0];
	Ogre::FrameListener* Background2FrameListener = m_backgroundObject[1];

	mRoot->addFrameListener(P1FrameListener);
	mRoot->addFrameListener(DoodlePlayerFrameListener);
	mRoot->addFrameListener(UIFrameListener);
	mRoot->addFrameListener(Background1FrameListener);
	mRoot->addFrameListener(Background2FrameListener);
}

/// Main Function
/// 
/// Function where main game loop takes place
int main(int argc, char** argv)
{
	try
	{
		MainInitalizer app;
		app.initApp();
		app.getRoot()->startRendering();
		app.closeApp();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred during execution: " << e.what() << '\n';
		return 1;
	}
	return 0;
}

