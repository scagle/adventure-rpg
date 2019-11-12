#pragma once
// Forward Declarations
namespace game
{
    class Solid;
    class Character;
};
class SDL_Color;
class SDL_Rect;
class SDL_Renderer;


#include "dynamic_character.hpp" 

#include <vector>

namespace game
{
    class MainCharacter : public DynamicCharacter
    {
        public:
            MainCharacter();
            MainCharacter( SDL_Rect, SDL_Color, std::string );
            virtual ~MainCharacter() { }

            void checkPortals( std::vector< Solid >* );
            void checkNPCs( std::vector< Character* >* );
            std::vector< Character* > getAdjacentNPCs( std::vector< Character* >* characters );

            virtual void render( SDL_Renderer* renderer );
            virtual void update();
    };
};
