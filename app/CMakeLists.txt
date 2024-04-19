cmake_minimum_required(VERSION 3.16..3.24)
project(App	    
    VERSION 1.0.0
    DESCRIPTION "Application"
    LANGUAGES CXX
    )

add_executable(App 
    src/app.cpp
    )

find_package(Core REQUIRED)
find_package(Visualizer REQUIRED)

target_link_libraries(
    App 
        PUBLIC 
            Core::Core
            Visualizer::Visualizer
        PRIVATE
            sfml-system
            sfml-network 
            sfml-graphics 
            sfml-window)
