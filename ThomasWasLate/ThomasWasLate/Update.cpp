#include "stdafx.h"
#include "Engine.h"


void Engine::update(float timedelta)
{
    if (m_Playing)
    {
        m_TimeRemaining -= timedelta;

        // The time is up?
        if (m_TimeRemaining < 0)
        {
            m_NewLevelRequired = true;
        }
    }
}
