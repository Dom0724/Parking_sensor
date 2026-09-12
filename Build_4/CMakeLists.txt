# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.3.1)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.3.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Build_4 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Build_4 Build_4.c )

pico_set_program_name(Build_4 "Build_4")
pico_set_program_version(Build_4 "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Build_4 0)
pico_enable_stdio_usb(Build_4 0)

# Add the standard library to the build


# Include Pico SDK libraries and CYW43 driver
# Required for main file to access cyw43 headers and therefore control the onboard LED
target_link_libraries(Build_4
        pico_stdlib
        pico_cyw43_arch_none)

# Add the standard include files to the build
target_include_directories(Build_4 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(Build_4 
        
        )

pico_add_extra_outputs(Build_4)

