#include "stdafx.h"
#include "ParticleSystem.h"


void ParticleSystem::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_Vertices, states);
}


void ParticleSystem::init(int count)
{
    m_Vertices.setPrimitiveType(Points);
    m_Vertices.resize(count);

    for (int i = 0; i < count; i++)
    {
        srand(time(0) + i);
        float angle = (rand() % 360) * 3.14f / 180.f;
        float speed = (rand() % 600) + 600.f;
        Vector2f direction;
        direction = Vector2f(cos(angle) * speed, sin(angle) * speed);
        m_Particles.emplace_back(Particle(direction));
    }
}


void ParticleSystem::emitParticles(Vector2f position)
{
    m_IsRunning = true;
    m_Duration = 2;

    int currentIndex = 0;
    for (auto i = m_Particles.begin(); i != m_Particles.end(); i++)
    {
        m_Vertices[currentIndex].color = Color::Yellow;
        (*i).setPosition(position);
        currentIndex++;
    }
}


void ParticleSystem::update(float timedelta)
{
    m_Duration -= timedelta;

    int currentIndex = 0;
    for (auto i = m_Particles.begin(); i != m_Particles.end(); i++)
    {
        (*i).update(timedelta);
        m_Vertices[currentIndex].position = (*i).getPosition();
        currentIndex++;
    }

    if (m_Duration < 0)
    {
        m_IsRunning = false;
    }
}


bool ParticleSystem::isRunning()
{
    return m_IsRunning;
}
