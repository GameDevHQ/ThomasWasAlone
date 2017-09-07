#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;


class PlayableCharacter
{
protected:
    Sprite m_Sprite;
    float m_JumpDuration;

    // Is character currently jumping or falling
    bool m_IsJumping;
    bool m_IsFalling;

    // Which directions is the character currently moving in
    bool m_LeftPressed;
    bool m_RightPressed;

    // How long has this jump lasted so far
    float m_TimeThisJump;

    // Has the player just initialted a jump
    bool m_JustJumped = false;
private:
    Texture m_Texture;
    Vector2f m_Position;
    float m_Gravity;
    
    // Current speed of the character
    float m_Speed = 400;
    
    // Where are the characters various body parts?
    FloatRect m_Feet;
    FloatRect m_Head;
    FloatRect m_Right;
    FloatRect m_Left;
public:
    void spawn(Vector2f startPosition, float gravity);
    void update(float elapsedTime);
    bool virtual handleInput() = 0;
    
    Vector2f getCenter();
    FloatRect getPosition();

    // A rectangle representing the position of different parts of the sprite
    FloatRect getFeet();
    FloatRect getHead();
    FloatRect getRight();
    FloatRect getLeft();

    Sprite getSprite();

    // Make the character stand firm
    void stopFalling(float position);
    void stopRight(float position);
    void stopLeft(float position);
    void stopJump();
};
