#include "stdafx.h"
#include "Engine.h"


Engine::Engine():
m_TextureManager(TextureManager::getInstance())
{
    // Get the display resolution
    Vector2f resolution;
    unsigned int modeWidth = VideoMode::getDesktopMode().width;
    unsigned int modeHeight = VideoMode::getDesktopMode().height;
    resolution.x = static_cast<float>(modeWidth);
    resolution.y = static_cast<float>(modeHeight);

    // Initialize the fullscreeen window and view
    m_Window.create(VideoMode(modeWidth, modeHeight), "Thomas was late", Style::Fullscreen);
    m_MainView.setSize(resolution);
    m_HudView.reset(FloatRect(0, 0, resolution.x, resolution.y));

    // Inititialize the split screen Views
    m_LeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
    m_RightView.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));
    m_BGLeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
    m_BGRightView.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

    // Set background of the game
    m_BackgroundTexture = m_TextureManager.getTexture("Resources/Graphics/background.png");
    m_BackgroundSprite.setTexture(m_BackgroundTexture);

    // Load the texture for the background vertex array
    m_TextureTiles = m_TextureManager.getTexture("Resources/Graphics/tiles_sheet.png");

    // Initialize the particle system
    m_ParticleSystem.init(PARTICLES_COUNT);
}


void Engine::run()
{
    // Timing...
    Clock clock;

    while (m_Window.isOpen())
    {
        Time timedelta = clock.restart();

        // Accumulate the time of the game session
        m_GameTimeTotal += timedelta;

        // Make a decimal fraction from the delta time
        float timedeltaAsSeconds = timedelta.asSeconds();

        // And lets make the corresponding calls for each part of the game
        input();
        update(timedeltaAsSeconds);
        draw();
    }
}
