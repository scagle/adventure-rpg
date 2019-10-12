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
    button_box.cpp
    button_box.hpp
    character.cpp
    character.hpp
    container.cpp
    container_handler.cpp
    container_handler.hpp
    container.hpp
    dialog.cpp
    dialog_handler.cpp
    dialog_handler.hpp
    dialog.hpp
    enums/direction.hpp
    enums/event_type.hpp
    enums/ui.hpp
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
    text_box.cpp
    text_box.hpp
    travel_handler.cpp
    travel_handler.hpp
    ui_manager.cpp
    ui_manager.hpp
    world.cpp
    world.hpp
)

add_subdirectory(enums)
add_subdirectory(datatypes)
add_executable(game ${BASE_SOURCES} ${ENUMS_SOURCES} ${DATATYPES_SOURCES})

target_link_libraries(game SDL2 SDL2_ttf)
target_link_libraries(game Threads::Threads)

message("Copying binary to <project>/build")
add_custom_command(TARGET game
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:game> "${CMAKE_SOURCE_DIR}/build/"
)
