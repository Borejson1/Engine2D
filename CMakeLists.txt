cmake_minimum_required(VERSION 3.20)
project("EngineMaster2D" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/SFML/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include"
)

link_directories("${CMAKE_CURRENT_SOURCE_DIR}/Include/SFML/lib")

# Automatyczne pobranie wszystkich plików z Include i Source
file(GLOB SOURCES 
    "Source/*.cpp"
    "Include/*.h"
)

add_executable(EngineMaster2D ${SOURCES})

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