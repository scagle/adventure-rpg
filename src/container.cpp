#include "container.hpp"

#include "enums/direction.hpp"
#include "enums/container_orientation.hpp"
#include "enums/container_type.hpp"
#include "globals.hpp"

#include "character.hpp"

namespace game
{
    Container::Container() : background(CONTAINER_BACKGROUND_COLOR), foreground(CONTAINER_FOREGROUND_COLOR)
    {
        initializeBox(0, 0);
    }

    Container::Container( std::vector< TextBox > tbs, std::vector< ButtonBox > bbs, Properties p )
        : text_boxes(tbs), button_boxes(bbs), properties(p),
          background(CONTAINER_BACKGROUND_COLOR), foreground(CONTAINER_FOREGROUND_COLOR)
    {
        initializeBox(0, 0);
    }

    Container::Container( std::vector< TextBox > tbs, std::vector< ButtonBox > bbs, 
                          ContainerType type, std::string id, Properties p )
        : text_boxes(tbs), button_boxes(bbs), type(type), id(id), properties(p), 
          background(CONTAINER_BACKGROUND_COLOR), foreground(CONTAINER_FOREGROUND_COLOR)

    {
        initializeBox(0, 0);
    }

    Container::Container( std::vector< TextBox > tbs, std::vector< ButtonBox > bbs, 
                          ContainerType type, int emit_x, int emit_y, Properties p )
        : text_boxes(tbs), button_boxes(bbs), type(type), properties(p),
          background(CONTAINER_BACKGROUND_COLOR), foreground(CONTAINER_FOREGROUND_COLOR)
    {
        initializeBox(emit_x, emit_y);
    }

    void Container::initializeBox(int emit_x, int emit_y)
    {
        for ( std::pair< PropertyType, int > property : *properties.getProperties() )
        {
            switch ( property.first )
            {
                case PropertyType::SIZE:
                    this->scale = (float)property.second / 100.0;
                    break;
                default:
                    break;
            }
        }

        switch (type)
        {
            case ContainerType::FLOATING:
                {
                    setEmittedPosition(emit_x, emit_y);
                    this->show_prompt = true;
                    break;
                }
            case ContainerType::SCREEN:
                this->box = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 8, SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / 4 }; 
                break;
            case ContainerType::FOOTER:
                this->box = { SCREEN_WIDTH / 4, SCREEN_HEIGHT - 100, SCREEN_WIDTH / 2, 100 }; 
                break;
        }
    }

    void Container::moveCursor( Direction dir )
    {
        switch (dir)
        {
            case Direction::UP    :
                if (orientation == ContainerOrientation::VERTICAL)
                    if (selected_index > 0)
                        selected_index--;
                break;
            case Direction::DOWN  :
                if (orientation == ContainerOrientation::VERTICAL)
                    if (selected_index < (int)button_boxes.size() - 1)
                        selected_index++;
                break;
            case Direction::LEFT  :
                if (orientation == ContainerOrientation::HORIZONTAL)
                    if (selected_index > 0)
                        selected_index--;
                break;
            case Direction::RIGHT :
                if (orientation == ContainerOrientation::HORIZONTAL)
                    if (selected_index < (int)button_boxes.size() - 1)
                        selected_index++;
                break;
            default:
                printf("Invalid Direction! game::Container::moveCursor()\n");
        }
    }

    void Container::setEmittedPosition(int emit_x, int emit_y)
    {
        const int floating_width = 300 * scale;
        const int floating_height = 150 * scale;
        const int floating_x = emit_x - floating_width / 2;
        const int floating_y = emit_y - floating_height;
        this->box = {floating_x, floating_y, floating_width, floating_height};
    }

    std::string Container::select()
    {
        if ( show_prompt )
        {
            show_prompt = false;
            return "";
        }
        if ( text_boxes.size() != 0 )
        {
            if ( ( unsigned int )text_index != ( text_boxes.size() - 1 ) )
            {
                text_index++;
                return "text_continue";
            }
        }
        return button_boxes[selected_index].getAction();
    }

    void Container::render( SDL_Renderer *renderer )
    {
        // Handle properties
        for ( std::pair< PropertyType, int > property : *(properties.getProperties()) )
        {
            switch ( property.first )
            {
                case PropertyType::NO_PROMPT:
                    show_prompt = false;
                    break;
                default:
                    break;
            }
        }
        if ( show_prompt == true )
        {
            renderPrompt( renderer );
            return;
        }

        // Draw Container background
        SDL_SetRenderDrawColor( renderer, background.r, background.g, background.b, background.a );
        SDL_RenderFillRect( renderer, &box ); 

        // Draw Text Boxes / Button Boxes
        if (text_boxes.size() == 0 && button_boxes.size() == 0)
        {
            printf("*** WARNING: Trying to render an empty Container\n");
            return;
        }
        else if ( button_boxes.size() == 0 ) // If just text (some dialog)
        {
            renderText( renderer ); // Render Text
        }
        else if ( text_boxes.size() == 0 ) // If just buttons (menu)
        {
            renderMenu( renderer ); // Render Buttons
        }
        else if ((unsigned int)text_index == text_boxes.size() - 1)  // If at last text box, display buttons (end dialog)
        {
            renderTextWithButtons( renderer );
        }
        else  // If has text and buttons, and not at the end, just display text (mid dialog)
        {
            renderText( renderer );
        }
    }

    void Container::renderPrompt( SDL_Renderer *renderer )
    {
        SDL_Rect border_box = { box.x + box.w / 2 + 5, box.y + box.h - 25, 10, 10 };
        SDL_Rect fill_box   = { box.x + box.w / 2 + 6, box.y + box.h - 24,  8,  8 };
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderFillRect( renderer, &border_box ); 
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_RenderFillRect( renderer, &fill_box ); 
    }

    void Container::renderMenu( SDL_Renderer *renderer )
    {
        int button_height = (box.h - (buffer * 2)) / button_boxes.size() ;
        for (unsigned int i = 0; i < button_boxes.size(); i++)
        {
            SDL_Rect button_rect = { box.x + buffer, 
                                     box.y + buffer + (button_height * (int)i), 
                                     box.w - (buffer * 2), 
                                     button_height };
            button_boxes[i].render( renderer, &button_rect, (selected_index == (int)i) );
        }
    }

    void Container::renderTextWithButtons( SDL_Renderer *renderer )
    {
        if (orientation == ContainerOrientation::HORIZONTAL)
        {
            int split_location = box.x + (int)((float)box.w * divider_ratio);
            int split_location_min = split_location - buffer / 2;
            int split_location_max = split_location + buffer / 2;
            int button_width = split_location_min - (box.x + buffer) ;
            int button_height = ((box.y + box.h - buffer) - (box.y + buffer)) / button_boxes.size() ;
            int text_width = (box.x + box.w - buffer) - split_location_max;
            int text_height = (box.y + box.h - buffer) - (box.y + buffer);

            for (unsigned int i = 0; i < button_boxes.size(); i++)
            {
                SDL_Rect button_rect = { box.x + buffer, 
                                         box.y + buffer + (button_height * (int)i), 
                                         button_width, 
                                         button_height  };
                button_boxes[i].render( renderer, &button_rect, (selected_index == (int)i) );
            }
            for (unsigned int i = 0; i < text_boxes.size(); i++)
            {
                SDL_Rect text_rect = { split_location_max, 
                                       box.y + buffer,
                                       text_width, 
                                       text_height  };
                text_boxes[i].render( renderer, &text_rect );
            }
        }
        else if (orientation == ContainerOrientation::VERTICAL)
        {
            int split_location = box.y + (int)((float)box.h * divider_ratio);
            int split_location_min = split_location - buffer / 2;
            int split_location_max = split_location + buffer / 2;
            int button_width = ((box.x + box.w - buffer) - (box.x + buffer)) / button_boxes.size() ;
            int button_height = (box.y + box.h - buffer) - (split_location_max + buffer) ;
            int text_width = (box.x + box.w - buffer) - (box.x + buffer);
            int text_height = split_location_min - (box.y + buffer) ;

            for (unsigned int i = 0; i < button_boxes.size(); i++)
            {
                SDL_Rect button_rect = { box.x + buffer + (button_width * (int)i), 
                                         box.y + box.h - buffer - button_height,
                                         button_width, 
                                         button_height  };
                button_boxes[i].render( renderer, &button_rect, (selected_index == (int)i) );
            }
            for (unsigned int i = 0; i < text_boxes.size(); i++)
            {
                SDL_Rect text_rect = { box.x + buffer, 
                                       box.y + buffer,
                                       text_width, 
                                       text_height  };
                text_boxes[i].render( renderer, &text_rect );
            }
            
        }
    }

    void Container::renderText( SDL_Renderer *renderer )
    {
        SDL_Rect text_rect = { box.x + buffer,
                               box.y + buffer,
                               box.w - (buffer * 2), 
                               box.h - (buffer * 2)  };
        text_boxes[text_index].render( renderer, &text_rect);
    }

    void Container::update()
    {
        // If following a character
        if ( character != nullptr )
        {
            setEmittedPosition( character->getCenterX(), character->getCenterY() );
        }
    }
};
