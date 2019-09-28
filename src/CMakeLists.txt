# SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2TTF_INCLUDE_DIRS})

set(GAME_SOURCES 
    character.cpp
    character.hpp
    dialog.cpp
    dialog.hpp
    environment.cpp
    environment.hpp
    event.cpp
    event.hpp
    gamedata.cpp
    gamedata.hpp
    globals.hpp
    keyboard_handler.cpp
    keyboard_handler.hpp
    main.cpp
    menu.cpp
    menu_handler.cpp
    menu_handler.hpp
    menu.hpp
    option.cpp
    option.hpp
    sdl_utils.cpp
    sdl_utils.hpp
    solid.cpp
    solid.hpp
    world.cpp
    world.hpp
)

add_subdirectory(enums)
add_executable(game ${GAME_SOURCES} ${ENUM_SOURCES})

target_link_libraries(game SDL2 SDL2_ttf)

message("Copying binary to <project>/build")
add_custom_command(TARGET game
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:game> "${CMAKE_SOURCE_DIR}/build/"
)
