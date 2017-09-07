#include "stdafx.h"
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
}
