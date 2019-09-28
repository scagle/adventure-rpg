#pragma once
#include <SDL.h>
#include "container.hpp"
#include "enum/direction.hpp"

namespace game
{
    class InterfaceHandler
    {
        private:
        //static const std::unordered_map< std::string, Container > containers;
        //static const std::stack< Container* > container_stack;
        //static const std::set< std::string > visible_containers;
        //static const std::vector< SDL_Textures > text_textures;

        public:
        InterfaceHandler() { }
        virtual ~InterfaceHandler() { }

        virtual bool initContainers();
        virtual bool initTextTextures();

        virtual static void pushContainer(std::string);
        virtual void popContainer();                    // go "up" or "back"
        virtual void navigateContainer(Direction);      // move current option "selector" 
        virtual void selectContainer();                 // select option
        virtual Container* getContainer();
        virtual static bool inContainer();
        virtual void render( SDL_Renderer *renderer );
        virtual void update();

    }
};
