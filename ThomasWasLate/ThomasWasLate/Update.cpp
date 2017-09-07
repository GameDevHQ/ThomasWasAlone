#include "stdafx.h"
#include "Engine.h"


void Engine::update(float timedelta)
{
    // TODO: Move this part of code to a dedicated loadLevel() function later
    if (m_NewLevelRequired)
    {
        // Spawn Thomas and Bob
        m_Thomas.spawn(Vector2f(0.0f, 0.0f), GRAVITY);
        m_Bob.spawn(Vector2f(100.0f, 0.0f), GRAVITY);

        // Make sure spawn is called only once
        m_TimeRemaining = 10;
        m_NewLevelRequired = false;
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
