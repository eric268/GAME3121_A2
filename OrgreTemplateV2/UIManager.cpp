#include "UIManager.h"
#include "iomanip"
#include <string>
UIManager::UIManager()
{
	mTrayMgr = nullptr;
	m_playerRef = nullptr;

	mScoreLabel = nullptr;
	mScore = nullptr;

	mLivesLabel = nullptr;
	mLives = nullptr;
	m_FPSLabel = nullptr;
	m_FPS = nullptr;

	m_TimePerUpdateLabel = nullptr;
	m_TimePerUpdate = nullptr;
}

UIManager::UIManager(OgreBites::TrayManager* mT, DoodlePlayer* playerRef)
{
	fpsCounter = 0.0f;
	fpsTotal = 0.0f;
	timePerUpdateTotal = 0;
	timer = 0.0f;
	m_fSeconds = 59.0f;

	mTrayMgr = mT;
	m_playerRef = playerRef;

	mScoreLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Score", "Score:", 150);
	mScore = mTrayMgr->createLabel(TL_TOPLEFT, "score", std::to_string(m_playerRef->GetScore()), 150);

	mLivesLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Lives", "Lives:", 150);
	mLives = mTrayMgr->createLabel(TL_TOPLEFT, "lives", std::to_string(m_playerRef->GetLivesRemaining()), 150);

	m_FPSLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "FPS", "FPS:", 150);
	m_FPS = mTrayMgr->createLabel(TL_TOPRIGHT, "fps", std::to_string(0), 150);

	m_TimePerUpdateLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "Time/Update", "Time/Update:", 150);
	m_TimePerUpdate = mTrayMgr->createLabel(TL_TOPRIGHT, "time/update", std::to_string(0), 150);
}

UIManager::~UIManager()
{
	delete mTrayMgr;
	mTrayMgr = nullptr;

	delete mScoreLabel;
	mScoreLabel = nullptr;

	delete mScore;
	mScore = nullptr;

	delete mLivesLabel;
	mLivesLabel = nullptr;

	delete mLives;
	mLives = nullptr;

	delete m_FPSLabel;
	m_FPSLabel = nullptr;

	delete m_FPS;
	m_FPS = nullptr;

	delete m_TimePerUpdateLabel;
	m_TimePerUpdateLabel = nullptr;

	delete m_TimePerUpdate;
	m_TimePerUpdate	= nullptr;

	m_playerRef = nullptr;

}

OgreBites::Label* UIManager::GetScoreLabel()
{
	return mScoreLabel;
}

OgreBites::Label* UIManager::GetScore()
{
	return mScore;;
}

OgreBites::Label* UIManager::GetLivesLabel()
{
	return mLivesLabel;
}

OgreBites::Label* UIManager::GetLives()
{
	return mLives;;
}

OgreBites::Label* UIManager::GetTimePerUpdateLabel()
{
	return m_TimePerUpdateLabel;
}

OgreBites::Label* UIManager::GetTimePerUpdate()
{
	return m_TimePerUpdate;
}

OgreBites::Label* UIManager::GetFPSLabel()
{
	return m_FPSLabel;
}

OgreBites::Label* UIManager::GetFPS()
{
	return m_FPS;
}

void UIManager::SetScoreLabel(OgreBites::Label* label)
{
	mScoreLabel = label;
}

void UIManager::SetScore(OgreBites::Label* label)
{
	mScore = label;
}

void UIManager::SetLivesLabel(OgreBites::Label* label)
{
	mLivesLabel = label;
}

void UIManager::SetLives(OgreBites::Label* label)
{
	mLives = label;
}
void UIManager::SetTimePerUpdateLabel(OgreBites::Label* label)
{
	m_TimePerUpdateLabel = label;
}
void UIManager::SetTimePerUpdate(OgreBites::Label* label)
{
	m_TimePerUpdate = label;
}
void UIManager::SetFPSLabel(OgreBites::Label* label)
{
	m_FPSLabel = label;
}
void UIManager::SetFPS(OgreBites::Label* label)
{
	m_FPS = label;
}
void UIManager::SetSeconds(float seconds)
{
	m_fSeconds = seconds;
}
void UIManager::UpdateGameOverLabels()
{
	if (!m_GameOverLabel && !m_RestartLabel && m_playerRef->GetGameOver())
	{
		m_GameOverLabel = mTrayMgr->createLabel(TL_CENTER, "Game Over Label", "Game Lost", 250);
		m_RestartLabel = mTrayMgr->createLabel(TL_CENTER, "Restart Label", "Press R to restart", 250);
		if (m_playerRef->GetGameWon())
			m_GameOverLabel->setCaption("Game Won");
	}

}
void UIManager::DeleteGameOverLabels()
{
	//m_RestartLabel->setCaption("");
	//m_GameOverLabel->setCaption("");

	//mTrayMgr->clearTray(TL_CENTER);
	mTrayMgr->destroyAllWidgetsInTray(TL_CENTER);
	m_RestartLabel = nullptr;
	m_GameOverLabel = nullptr;

}
void UIManager::CalculateFPS(const Ogre::FrameEvent& evt)
{
	timer += evt.timeSinceLastFrame;
	if (evt.timeSinceLastFrame != 0)
	{
		fpsTotal += 1.0f / evt.timeSinceLastFrame;
		timePerUpdateTotal += evt.timeSinceLastFrame;
	}
	fpsCounter++;

	if (timer >= 1)
	{
		float finalFPS = fpsTotal / fpsCounter;
		m_FPS->setCaption(std::to_string(finalFPS));

		float finalTimePerUpdate = timePerUpdateTotal / fpsCounter;
		m_TimePerUpdate->setCaption(std::to_string(finalTimePerUpdate * 1000) + " ms");

		timePerUpdateTotal = 0.0f;
		timer = 0.0f;
		fpsTotal = 0.0f;
		fpsCounter = 0.0f;
	}
}

bool UIManager::frameStarted(const Ogre::FrameEvent& evt)
{
	if (m_playerRef->GetPointEarned())
	{
		mScore->setCaption(std::to_string(m_playerRef->GetScore()));
		m_playerRef->SetPointEarned(false);
	}
	if (m_playerRef->GetLifeLost())
	{
		mLives->setCaption(std::to_string(m_playerRef->GetLivesRemaining()));
		m_playerRef->SetLifeLabel(false);
	}

	UpdateGameOverLabels();

	CalculateFPS(evt);

	return true;
}
