# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/pi/pico/pico-sdk")

# Pull in Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(screen_sku_mar2406 C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

set(PICO_CXX_ENABLE_RTTI 1)

# Initialise the Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(screen_sku_mar2406 main.c lcd.c graphism.c constants.c)

pico_set_program_name(screen_sku_mar2406 "screen_sku_mar2406")
pico_set_program_version(screen_sku_mar2406 "0.1")

pico_enable_stdio_uart(screen_sku_mar2406 0)
pico_enable_stdio_usb(screen_sku_mar2406 1)

# Add the standard library to the build
target_link_libraries(screen_sku_mar2406 pico_stdlib)

# Add any user requested libraries
target_link_libraries(screen_sku_mar2406
        hardware_spi
        hardware_i2c
        hardware_dma
        hardware_pio
        )

pico_add_extra_outputs(screen_sku_mar2406)

