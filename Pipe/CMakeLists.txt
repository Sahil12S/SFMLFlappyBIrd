cmake_minimum_required(VERSION 3.13)
project(SFMLGameEngine)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_COMPILER  /usr/bin/g++)
set(CMAKE_C_COMPILER /usr/bin/gcc)

set(SOURCE_FILES main.cpp State.h StateMachine.cpp StateMachine.h AssetManager.cpp AssetManager.h InputManager.cpp InputManager.h Game.cpp Game.h DEFINITIONS.h SplashState.cpp SplashState.h MainMenuState.cpp MainMenuState.h GameState.cpp GameState.h GameOverState.cpp GameOverState.h Pipe.cpp Pipe.h Land.cpp Land.h)

add_executable(SFMLGameEngine ${SOURCE_FILES})

set(EXECUTABLE_NAME ${PROJECT_NAME})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()