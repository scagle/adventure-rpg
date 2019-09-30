#include "container.hpp"
#include "enums/direction.hpp"

namespace game
{
    Container::Container() : background(CONTAINER_BACKGROUND_COLOR), foreground(CONTAINER_FOREGROUND_COLOR)
    {
        this->box = {0, 0, 250, 250};
    }

    Container::Container(std::vector< TextBox > tbs, std::vector< ButtonBox > bbs)
        : text_boxes(tbs), button_boxes(bbs), background(CONTAINER_BACKGROUND_COLOR), foreground(CONTAINER_FOREGROUND_COLOR)
    {
        this->box = {0, 0, 250, 250};
    }
    Container::Container(std::vector< TextBox > tbs, std::vector< ButtonBox > bbs, ContainerOrientation orientation)
        : text_boxes(tbs), button_boxes(bbs), background(CONTAINER_BACKGROUND_COLOR), foreground(CONTAINER_FOREGROUND_COLOR)
    {
        this->box = {0, 0, 250, 250};
        this->orientation = orientation;
    }

    void Container::render( SDL_Renderer *renderer )
    {
        // Draw Container background
        SDL_SetRenderDrawColor( renderer, background.r, background.g, background.b, background.a );
        SDL_RenderFillRect( renderer, &box ); 

        // Draw Text Boxes / Button Boxes
        const int buffer = 2; // buffer of pixels around edges
        if (text_boxes.size() == 0 && button_boxes.size() == 0)
        {
            printf("*** WARNING: Trying to render an empty Container\n");
            return;
        }
        else if (text_boxes.size() == 0 && button_boxes.size() > 0)  // If just buttons (menu)
        {
            int button_height = (box.h - (buffer * 2)) / button_boxes.size() ;
            for (unsigned int i = 0; i < button_boxes.size(); i++)
            {
                SDL_Rect button_rect = { box.x + buffer, 
                                         box.y + buffer + (button_height * (int)i), 
                                         box.w - (buffer * 2), 
                                         box.h - (buffer * 2) };
                button_boxes[i].render( renderer, &button_rect, (selected_index == (int)i) );
            }
        }
        else if ((unsigned int)text_index == text_boxes.size() - 1)  // If at last text box, display buttons
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
        else  // Just display text_box
        {
            printf("display\n");
            SDL_Rect text_rect = { box.x + buffer,
                                   box.y + buffer,
                                   box.w - (buffer * 2), 
                                   box.h - (buffer * 2)  };
            text_boxes[text_index].render( renderer, &text_rect);
        }
    }

    void Container::moveCursor(Direction dir)
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

    std::string Container::select()
    {
        return button_boxes[selected_index].getAction();
    }

    void Container::update()
    {

    }
};
