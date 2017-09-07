#include "stdafx.h"
#include "Engine.h"


void Engine::loadLevel()
{
    m_Playing = false;

    // Clear the memory
    for (int i = 0; i < m_LevelManager.getLevelSize().y; ++i)
    {
        delete[] m_ArrayLevel[i];
    }
    delete[] m_ArrayLevel;

    // Load the next 2d array with the map for the level
    // And repopulate the vertex array as well
    m_ArrayLevel = m_LevelManager.nextLevel(m_VALevel);

    // Prepare the sound emitters
    populateEmitters(m_FireEmitters, m_ArrayLevel);

    // Update the time, that required for this particular game level
    m_TimeRemaining = m_LevelManager.getTimeLimit();

    // Spawn characters
    m_Thomas.spawn(m_LevelManager.getStartPosition(), static_cast<float>(GRAVITY));
    m_Bob.spawn(m_LevelManager.getStartPosition(), static_cast<float>(GRAVITY));

    // And avoid to run this function one again, until reach the goal of the game level
    m_NewLevelRequired = false;
}
