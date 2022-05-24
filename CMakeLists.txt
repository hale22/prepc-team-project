Cmake_minimum_required(VERSION 3.10)
project(database)

set(CMAKE_CXX_STANDARD 17)

include_directories(managers /project/include)

find_package(sqlite3 3.38.3 REQUIRED)

option(USE_STATIC "Use static library" ON)
message(STATUS "Compile with static library? ${USE_STATIC}")

add_library( db-raw
    OBJECT
    database.hpp
    database.cpp
)

target_compile_options(db-raw
    PRIVATE
            -Wall -Wextra -Werror
)

if(USE_STATIC)
    add_library(db
     STATIC
        $<TARGET_OBJECTS:db-raw>
    )
    target_link_libraries(db ${sqlite3_LIBRARIES})

else()
    add_library(db
        SHARED
         $<TARGET_OBJECTS:db-raw>
    )
    target_link_libraries(db ${sqlite3_LIBRARIES})
#add_executable(database database.cpp)
endif()
