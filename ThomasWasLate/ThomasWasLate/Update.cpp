#include "stdafx.h"
#include <sstream>
#include "Engine.h"


void Engine::update(float timedelta)
{
    if (m_NewLevelRequired)
    {
        loadLevel();
    }

    if (m_Playing)
    {
        // Update each character
        m_Thomas.update(timedelta);
        m_Bob.update(timedelta);

        // Detect collision
        if (detectCollisions(m_Thomas) && detectCollisions(m_Bob))
        {
            m_NewLevelRequired = true;
            m_SoundManager.playReachGoal();
        }
        else
        {
            detectCollisions(m_Bob);
        }

        // Let Thomas and Bob jump on each others heads
        if (m_Bob.getFeet().intersects(m_Thomas.getHead()))
        {
            m_Bob.stopFalling(m_Thomas.getHead().top);
        }
        else if (m_Thomas.getFeet().intersects(m_Bob.getHead()))
        {
            m_Thomas.stopFalling(m_Bob.getHead().top);
        }

        m_TimeRemaining -= timedelta;

        // The time is up?
        if (m_TimeRemaining < 0)
        {
            m_NewLevelRequired = true;
        }
    }

    // Check if a fire sound needs to be played
    for (auto it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++)
    {
        // Where is this emitter?
        float posX = (*it).x;
        float posY = (*it).y;

        // Is the emiter near the player? 
        // Make a 500 pixel rectangle around the emitter
        FloatRect localRect(posX - 250, posY - 250, 500, 500);

        // Is the player inside localRect?
        if (m_Thomas.getPosition().intersects(localRect))
        {
            m_SoundManager.playFire(Vector2f(posX, posY), m_Thomas.getCenter());
        }
    }

    // Set the appropriate view around the appropriate character
    if (m_SplitScreen)
    {
        m_LeftView.setCenter(m_Thomas.getCenter());
        m_RightView.setCenter(m_Bob.getCenter());
    }
    else
    {
        // Centre full screen around appropriate character
        if (m_Character1)
        {
            m_MainView.setCenter(m_Thomas.getCenter());
        }
        else
        {
            m_MainView.setCenter(m_Bob.getCenter());
        }
    }

    // Update the HUD every m_TargetFramesPerHUDUpdate frames
    m_FramesSinceLastHUDUpdate++;
    if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
    {
        std::stringstream ssTime;
        std::stringstream ssLevel;

        // Update the time text
        ssTime << (int)m_TimeRemaining;
        m_HUD.setTime(ssTime.str());

        // Update the level text
        ssLevel << "Level:" << m_LevelManager.getCurrentLevel();
        m_HUD.setLevel(ssLevel.str());
        m_FramesSinceLastHUDUpdate = 0;
    }

    if (m_ParticleSystem.isRunning())
    {
        m_ParticleSystem.update(timedelta);
    }
}
