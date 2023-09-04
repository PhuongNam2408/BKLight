cmake_minimum_required(VERSION 3.18.4)
project(BKLight C)
INCLUDE_DIRECTORIES(
    .
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}
    )
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable(BKLight main.c mqtt.c lora.c uart.c)
target_link_libraries(BKLight paho-mqtt3as)
