# SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2TTF_INCLUDE_DIRS})

# Threads
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

set(BASE_SOURCES 
# Non Dependants
    sdl_utils.cpp
    sdl_utils.hpp
    globals.hpp
    game_texture.cpp
    game_texture.hpp
# Priority 3
    event.cpp
    event.hpp
    text_box.cpp
    text_box.hpp
    button_box.cpp
    button_box.hpp
    solid.cpp
    solid.hpp
    dynamic_character.cpp
    dynamic_character.hpp
    main_character.cpp
    main_character.hpp
    character.cpp
    character.hpp
    container.cpp
    container.hpp
# Priority 2
    environment.cpp
    environment.hpp
# Priority 1
    keyboard_handler.cpp
    keyboard_handler.hpp
    dialog_handler.cpp
    dialog_handler.hpp
    menu_handler.cpp
    menu_handler.hpp
    travel_handler.cpp
    travel_handler.hpp
    container_handler.cpp
    container_handler.hpp
    world.cpp
    world.hpp
    ui_manager.cpp
    ui_manager.hpp
# Priority 0
    gamedata.cpp
    gamedata.hpp
    main.cpp
)

add_subdirectory(enums)
add_subdirectory(datatypes)
message(STATUS ${PONG_SOURCES})
add_executable(game ${BASE_SOURCES} ${ENUMS_SOURCES} ${DATATYPES_SOURCES})

target_link_libraries(game SDL2 SDL2_ttf)
target_link_libraries(game Threads::Threads)

message("Copying binary to <project>/build")
add_custom_command(TARGET game
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:game> "${CMAKE_SOURCE_DIR}/build/"
)
