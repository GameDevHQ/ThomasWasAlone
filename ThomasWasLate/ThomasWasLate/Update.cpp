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
