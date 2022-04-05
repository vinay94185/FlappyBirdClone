#include "AssetManager.h"
#include <utility>

namespace vlc
{
    #ifdef DATA_FILE
    AssetManager::AssetManager():DataLoder(DATA_FILE)
    {
        this -> DataLoder::LoadTable();
        _fontBuffer = NULL;
    }
    #else
    AssetManager::AssetManager() {}
    #endif

    void AssetManager::LoadTexture(std::string name,std::string file)
    {
        if(!_textures.count(name))
        {
        #ifndef DATA_FILE
            sf::Texture tex;
            if(tex.loadFromFile(file))
            {
                this -> _textures.insert(texture_type(name,tex));
            }
            else
            {
                throw std::runtime_error(std::string("failed to load : ") + name);
            }
        #else
        char *buffer = NULL;
        size_t filesize;
        this -> GetBuffer(file,&buffer,filesize);
        LoadTexture(name,buffer,filesize);
        delete[] buffer;
        #endif
        }
    }

    void AssetManager::LoadFont(std::string name,std::string file)
    {
        if(!_fonts.count(name))
        {
        #ifndef DATA_FILE
            sf::Font font;
            if(font.loadFromFile(file))
            {
                this -> _fonts.insert(font_type(name,font));
            }
            else
            {
                throw std::runtime_error(std::string("failed to load : ") + name);
            }
        #else
        // Font needs to ensure that the memory is still there event after loading
        // as long as the font is being used thus we aren't deleting buffer here
        _fontBuffer = NULL;
        size_t filesize;
        this -> GetBuffer(file,&_fontBuffer,filesize);
        LoadFont(name,_fontBuffer,filesize);
        #endif
        }
    }

    void AssetManager::LoadSound(std::string name,std::string file)
    {
        if(!_sounds.count(name))
        {
        #ifndef DATA_FILE

            sf::SoundBuffer soundbuf;
            if(soundbuf.loadFromFile(file))
            {
                this -> _sounds.insert(sound_type(name,soundbuf));
            }
            else
            {
                throw std::runtime_error(std::string("failed to load : ") + name);
            }
        #else
        char *buffer = NULL;
        size_t filesize;
        this -> GetBuffer(file,&buffer,filesize);
        if(buffer != NULL)
        LoadSound(name,buffer,filesize);
        delete[] buffer;
        #endif
        }
    }
// memory versions of same functions
    void AssetManager::LoadTexture(std::string name,const char* buffer,const size_t buffer_size)
    {
        if(!_textures.count(name) && buffer != NULL)
        {
            sf::Texture tex;
            if(tex.loadFromMemory(buffer,buffer_size))
            {
                this -> _textures.insert(texture_type(name,tex));
            }
            else
            {
                throw std::runtime_error(std::string("failed to load : ") + name);
            }
        }
    }

    void AssetManager::LoadFont(std::string name,const char* buffer,const size_t buffer_size)
    {
        if(!_fonts.count(name) && buffer != NULL)
        {
            sf::Font font;
            if(font.loadFromMemory(buffer,buffer_size))
            {
                this -> _fonts.insert(font_type(name,font));
            }
            else
            {
                throw std::runtime_error(std::string("failed to load : ") + name);
            }
        }
    }

    void AssetManager::LoadSound(std::string name,const char* buffer,const size_t buffer_size)
    {
        if(!_sounds.count(name) && buffer != NULL)
        {
            sf::SoundBuffer soundbuf;
            if(soundbuf.loadFromMemory(buffer,buffer_size))
            {
                this -> _sounds.insert(sound_type(name,soundbuf));
            }
            else
            {
                throw std::runtime_error(std::string("failed to load : ") + name);
            }
        }
    }

    sf::Texture &AssetManager::GetTexture(std::string name) { return this-> _textures.at(name); }
    sf::Font &AssetManager::GetFont(std::string name) { return this-> _fonts.at(name); }
    sf::SoundBuffer &AssetManager::GetSound(std::string name) { return this-> _sounds.at(name); }
}
