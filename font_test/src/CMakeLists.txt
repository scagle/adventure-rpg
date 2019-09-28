# SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2TTF_INCLUDE_DIRS})

add_executable(font 
    main.cpp
)

target_link_libraries(font SDL2 SDL2_ttf)

message("Copying binary to <project>/build")
add_custom_command(TARGET font
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:font> "${CMAKE_SOURCE_DIR}/build/"
)
