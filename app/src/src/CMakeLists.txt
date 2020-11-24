project(comm_parser)
set(CMAKE_CXX_STANDARD 14)

file(GLOB SRCS
        *.c*
        ../crc/*.c*
        )
add_library(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC .. .)
