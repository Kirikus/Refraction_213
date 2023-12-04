project(core VERSION 0.1 LANGUAGES CXX)

file(GLOB PROJECT_SOURCES "*.h" "*.cpp")

add_library(core STATIC ${PROJECT_SOURCES})
target_link_libraries(core PRIVATE Qt5::Core)
