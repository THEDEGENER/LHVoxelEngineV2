cmake_minimum_required(VERSION 3.20)
project(LHCraftApp)

add_executable(LHCraftApp
    src/App.cpp
)

target_link_libraries(LHCraftApp PRIVATE
    Core
)



