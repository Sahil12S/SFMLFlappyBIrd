#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace SSEngine
{
    class AssetManager
    {
    public:
        AssetManager() {}
        ~AssetManager() {}

        void LoadTexture ( std::string name, std::string fileName );
        sf::Texture& GetTexture ( std::string name );

        void LoadFont ( std::string name, std::string fileName );
        sf::Font& GetFont( std::string name );

        void LoadSound ( std::string name, std::string fileName );
        sf::SoundBuffer& GetSoundBuffer( std::string name );

    private:
        std::map<std::string, sf::Texture> m_Textures;
        std::map<std::string, sf::Font> m_Font;
        std::map<std::string, sf::SoundBuffer> m_SoundBuffer;
    };
}
