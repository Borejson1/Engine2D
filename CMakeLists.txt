cmake_minimum_required(VERSION 3.20)
project("EngineMaster2D" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Include/SFML/include")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/Include/SFML/lib")

add_executable(EngineMaster2D 
    "Source/EngineMaster2D.cpp"
    "Source/EngineMaster2D.h"
)

target_link_libraries(EngineMaster2D PRIVATE 
    $<$<CONFIG:Debug>:sfml-graphics-d sfml-window-d sfml-system-d>
    $<$<NOT:$<CONFIG:Debug>>:sfml-graphics sfml-window sfml-system>
)

if(WIN32)
    add_custom_command(TARGET EngineMaster2D POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/SFML/bin"
        "$<TARGET_FILE_DIR:EngineMaster2D>"
    )
endif()