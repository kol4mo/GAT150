#include "ParticleSystem.h"
namespace hop {

    ParticleSystem g_particleSystem(10000);

    void hop::ParticleSystem::Update(float dt)
    {
        for (auto& particle : m_particles)
        {
            if (particle.m_isActive) particle.Update(dt);
        }
    }

    void hop::ParticleSystem::Draw(Renderer& renderer)
    {
        for (auto& particle : m_particles)
        {
            if (particle.m_isActive) particle.Draw(renderer);
        }
    }

    hop::Particle* hop::ParticleSystem::GetFreeParticle()
    {
        for (auto& particle : m_particles)
        {
            if (!particle.m_isActive) return &particle;
        }
        return nullptr;
    }
}
