#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
    // Load the sound in to the buffers
    m_FireBuffer.loadFromFile("Resources/Sound/fire1.wav");
    m_FallInFireBuffer.loadFromFile("Resources/Sound/fallinfire.wav");
    m_FallInWaterBuffer.loadFromFile("Resources/Sound/fallinwater.wav");
    m_JumpBuffer.loadFromFile("Resources/Sound/jump.wav");
    m_ReachGoalBuffer.loadFromFile("Resources/Sound/reachgoal.wav");

    // Associate the sounds with the buffers
    m_Fire1Sound.setBuffer(m_FireBuffer);
    m_Fire2Sound.setBuffer(m_FireBuffer);
    m_Fire3Sound.setBuffer(m_FireBuffer);
    m_FallInFireSound.setBuffer(m_FallInFireBuffer);
    m_FallInWaterSound.setBuffer(m_FallInWaterBuffer);
    m_JumpSound.setBuffer(m_JumpBuffer);
    m_ReachGoalSound.setBuffer(m_ReachGoalBuffer);

    float attenuation = 15;
    m_Fire1Sound.setAttenuation(attenuation);
    m_Fire2Sound.setAttenuation(attenuation);
    m_Fire3Sound.setAttenuation(attenuation);

    float minDistance = 150;
    m_Fire1Sound.setMinDistance(minDistance);
    m_Fire2Sound.setMinDistance(minDistance);
    m_Fire3Sound.setMinDistance(minDistance);

    m_Fire1Sound.setLoop(true);
    m_Fire2Sound.setLoop(true);
    m_Fire3Sound.setLoop(true);
}


void SoundManager::playFire(Vector2f emitterLocation, Vector2f listenerLocation)
{
    Listener::setPosition(listenerLocation.x, listenerLocation.y, 0.0f);

    Sound* fireSound = nullptr;
    switch (m_NextSound)
    {
        case 1:
            fireSound = &m_Fire1Sound;
            break;
        case 2:
            fireSound = &m_Fire2Sound;
            break;
        case 3:
            fireSound = &m_Fire3Sound;
            break;
        default:
            fireSound = &m_Fire1Sound;
            break;
    }

    fireSound->setPosition(emitterLocation.x, emitterLocation.y, 0.0f);
    if (fireSound->getStatus() == Sound::Status::Stopped)
    {
        fireSound->play();
    }

    // Increment to the next fire sound
    m_NextSound++;

    // Go back to 1 when the third sound has been started
    if (m_NextSound > 3)
    {
        m_NextSound = 1;
    }
}


void SoundManager::playFallInFire()
{
    m_FallInFireSound.setRelativeToListener(true);
    m_FallInFireSound.play();
}


void SoundManager::playFallInWater()
{
    m_FallInWaterSound.setRelativeToListener(true);
    m_FallInWaterSound.play();
}


void SoundManager::playJump()
{
    m_JumpSound.setRelativeToListener(true);
    m_JumpSound.play();
}


void SoundManager::playReachGoal()
{
    m_ReachGoalSound.setRelativeToListener(true);
    m_ReachGoalSound.play();
}
