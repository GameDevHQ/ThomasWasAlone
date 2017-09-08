#include "stdafx.h"
#include "Engine.h"


void Engine::draw()
{
    // Rub out the last frame
    m_Window.clear(Color::White);

    if (!m_SplitScreen)
    {
        // Switch to background view
        m_Window.setView(m_BGMainView);
        // Draw the background
        m_Window.draw(m_BackgroundSprite);
        // Switch to m_MainView
        m_Window.setView(m_MainView);

        // Draw the game level
        m_Window.draw(m_VALevel, &m_TextureTiles);

        // Draw characters
        m_Window.draw(m_Thomas.getSprite());
        m_Window.draw(m_Bob.getSprite());

        // Draw the particle system
        if (m_ParticleSystem.isRunning())
        {
            m_Window.draw(m_ParticleSystem);
        }
    }
    else
    {
        // Split screen view is active

        // First draw Thomas' side of the screen
        // Switch to background view
        m_Window.setView(m_BGLeftView);
        // Draw the background
        m_Window.draw(m_BackgroundSprite);
        // Switch to m_LeftView
        m_Window.setView(m_LeftView);

        // Draw the game level
        m_Window.draw(m_VALevel, &m_TextureTiles);

        // Draw characters
        m_Window.draw(m_Bob.getSprite());
        m_Window.draw(m_Thomas.getSprite());

        // Draw the particle system
        if (m_ParticleSystem.isRunning())
        {
            m_Window.draw(m_ParticleSystem);
        }

        // Now draw Bob's side of the screen
        // Switch to background view
        m_Window.setView(m_BGRightView);
        // Draw the background
        m_Window.draw(m_BackgroundSprite);
        // Switch to m_RightView
        m_Window.setView(m_RightView);

        // Draw the game level
        m_Window.draw(m_VALevel, &m_TextureTiles);

        // Draw characters
        m_Window.draw(m_Thomas.getSprite());
        m_Window.draw(m_Bob.getSprite());

        // Draw the particle system
        if (m_ParticleSystem.isRunning())
        {
            m_Window.draw(m_ParticleSystem);
        }
    }

    // Draw the game HUD
    // Switch to m_HudView
    m_Window.setView(m_HudView);

    // Draw the HUD
    m_Window.setView(m_HudView);
    m_Window.draw(m_HUD.getLevel());
    m_Window.draw(m_HUD.getTime());
    if (!m_Playing)
    {
        m_Window.draw(m_HUD.getMessage());
    }

    // Show everything we have just drawn
    m_Window.display();
}
