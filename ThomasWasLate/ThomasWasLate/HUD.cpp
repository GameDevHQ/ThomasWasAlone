#include "stdafx.h"
#include "HUD.h"


HUD::HUD()
{
    Vector2u resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    // Load the font
    m_Font.loadFromFile("Resources/Fonts/KOMIKAP.ttf");

    // Pause text
    m_StartText.setFont(m_Font);
    m_StartText.setCharacterSize(75);
    m_StartText.setFillColor(Color::White);
    m_StartText.setString("Press Enter when ready!");

    // Position the text
    FloatRect textRect = m_StartText.getLocalBounds();
    m_StartText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_StartText.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);

    // Time text
    m_TimeText.setFont(m_Font);
    m_TimeText.setCharacterSize(75);
    m_TimeText.setFillColor(Color::White);
    m_TimeText.setPosition(resolution.x - 150.f, 0);
    m_TimeText.setString("------");

    // Level text
    m_LevelText.setFont(m_Font);
    m_LevelText.setCharacterSize(75);
    m_LevelText.setFillColor(Color::White);
    m_LevelText.setPosition(25, 0);
    m_LevelText.setString("1");
}


Text HUD::getMessage()
{
    return m_StartText;
}


Text HUD::getLevel()
{
    return m_LevelText;
}


Text HUD::getTime()
{
    return m_TimeText;
}


void HUD::setLevel(String text)
{
    m_LevelText.setString(text);
}


void HUD::setTime(String text)
{
    m_TimeText.setString(text);
}
