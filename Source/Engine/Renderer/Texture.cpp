#include "Texture.h"
#include "Renderer.h"
#include "Core/logger.h"
#include "SDL2-2.28.0/include/SDL_image.h"

namespace hop {
    hop::Texture::~Texture()
    {
        if (m_texture) SDL_DestroyTexture(m_texture);
    }

    bool hop::Texture::Load(std::string filename, Renderer& renderer)
    {
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface)
        {
            WARNING_LOG("IMAGE not loaded");
            return false;
        }
        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
        SDL_FreeSurface(surface);
        if (!m_texture)
        {
            WARNING_LOG("surface not loaded");
            return false;
        }
        return true;
    }

    vec2 hop::Texture::GetSize()
    {
        // ASSERT texture is not null
        //ASSERT_LOG(m_texture != nullptr, "checking texture");
        SDL_Point point;
        // https://wiki.libsdl.org/SDL2/SDL_QueryTexture
        SDL_QueryTexture(m_texture,NULL, NULL, &point.x, &point.y);
        return vec2{ point.x, point.y };

    }
    bool Texture::Create(std::string filename, ...)
    {
        return false;
    }
}
