# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(RGB_LED_Matrix C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(RGB_LED_Matrix
    RGB_LED_Matrix.c
    include/keypad.c
    include/matriz_led_control.c
)

# Set the program name and version
pico_set_program_name(RGB_LED_Matrix "RGB_LED_Matrix")
pico_set_program_version(RGB_LED_Matrix "0.1")

# Enable UART/USB output as required
pico_enable_stdio_uart(RGB_LED_Matrix 0)
pico_enable_stdio_usb(RGB_LED_Matrix 1)

pico_generate_pio_header(RGB_LED_Matrix ${CMAKE_CURRENT_LIST_DIR}/pio_matrix.pio)

# Add the standard library to the build
target_link_libraries(RGB_LED_Matrix 
        pico_stdlib
        hardware_pwm
        hardware_pio
        hardware_adc
        pico_bootrom
        )

# Add the "include" directory to the include path
target_include_directories(RGB_LED_Matrix PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# Add the standard include files to the build
target_include_directories(RGB_LED_Matrix PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_BINARY_DIR}  # Adiciona o diretório "build"
)

# Add extra outputs for the project
pico_add_extra_outputs(RGB_LED_Matrix)
