#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "DataLoder.h"
#include "Definations.h"

namespace vlc
{
#ifdef DATA_FILE
    class AssetManager :private DataLoder
#else
    class AssetManager
#endif
    {
    public:
        AssetManager();
        ~AssetManager()
        {
            if(_fontBuffer != NULL) delete[] _fontBuffer;
        }

        void LoadTexture(std::string name,std::string file);
        void LoadFont(std::string name,std::string file);
        void LoadSound(std::string name,std::string file);
        // overloader version for loading from memory
        void LoadTexture(std::string name,const char* buffer,const size_t buffer_size);
        void LoadFont(std::string name,const char* buffer,const size_t buffer_size);
        void LoadSound(std::string name,const char* buffer,const size_t buffer_size);

        sf::Texture &GetTexture(std::string name);
        sf::Font &GetFont(std::string name);
        sf::SoundBuffer &GetSound(std::string name);

    private:
        std::map<std::string,sf::Texture> _textures;
        std::map<std::string,sf::Font> _fonts;
        std::map<std::string,sf::SoundBuffer> _sounds;
        #ifdef DATA_FILE
        char * _fontBuffer;
        #endif
        typedef std::map<std::string,sf::Texture>::value_type texture_type;
        typedef std::map<std::string,sf::Font>::value_type font_type;
        typedef std::map<std::string,sf::SoundBuffer>::value_type sound_type;
    };
}

#endif // ASSETMANAGER_H
