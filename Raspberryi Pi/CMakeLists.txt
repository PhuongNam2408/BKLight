cmake_minimum_required(VERSION 3.18.4)
set(CMAKE_C_COMPILER /usr/bin/aarch64-linux-gnu-gcc)
project(BKLight C)
INCLUDE_DIRECTORIES(
    .
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}
    )
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable(BKLight main.c mqtt.c lora.c uart.c aes.c)
target_link_libraries(BKLight paho-mqtt3as)

# Locate libraries and headers
find_package(WiringPi REQUIRED)
find_package(Threads REQUIRED) 

# Include headers
include_directories(${WIRINGPI_INCLUDE_DIRS}) 

# Link against libraries
target_link_libraries(BKLight ${WIRINGPI_LIBRARIES}) 
target_link_libraries(BKLight ${CMAKE_THREAD_LIBS_INIT})
