cmake_minimum_required(VERSION 3.8)
project(potom_pridumaem_game)

set(EXECUTABLE_NAME "potom_pridumaem_game")
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES Egor/main.cpp Egor/Entity.h Egor/Player.h Egor/SimpleBullet.h)
add_executable(potom_pridumaem_game ${SOURCE_FILES} )

set(SFML_DIR "C:/Users/knyaz/Documents/My progs/c++/potom_pridumaem_game/SFML/cmake/Modules")
set(SFML_ROOT "C:/Users/knyaz/Documents/My progs/c++/potom_pridumaem_game/SFML")
set(CMAKE_MODULE_PATH "C:/Users/knyaz/Documents/My progs/c++/potom_pridumaem_game/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()