cmake_minimum_required( VERSION 3.8 )

enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

project( playx )

add_executable( binary ./src/main.cpp )

include_directories( ./include ./src ./libs/hana/include )

add_subdirectory( ./libs/hana )
target_link_libraries( binary hana )

