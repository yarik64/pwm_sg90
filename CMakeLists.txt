cmake_minimum_required(VERSION 3.13...3.27)


set(PICO_SDK_PATH
	$ENV{HOME}/projects/MCU/RPico/pico-sdk
)

set(CMAKE_MODULE_PATH
		${CMAKE_MODULE_PATH}
		${PICO_SDK_PATH}
)

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pwm_sg90)

pico_sdk_init()

add_executable(${PROJECT_NAME}
        src/${PROJECT_NAME}.c
        )


add_subdirectory(thrid_party/pico-servo)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/thrid_party/pico-servo/include)
target_link_directories(   ${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/thrid_party/pico-servo/include)


# pull in common dependencies and additional pwm hardware support
target_link_libraries(${PROJECT_NAME}
	pico_stdlib 
	hardware_pwm
	pico-servo
)


# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})

