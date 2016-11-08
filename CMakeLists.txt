cmake_minimum_required(VERSION 3.5.1)
project(Skilled_Eagle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (DEFINED ENV{PROJECT_ROOT})
    set (PROJECT_ROOT "$ENV{PROJECT_ROOT}" CACHE PATH "project root" FORCE)
endif()

add_custom_target(BMPTK_clean_${PROJECT_NAME}
        bmptk-make clean -C "${CMAKE_CURRENT_SOURCE_DIR}/Source"
        DEPENDS
        COMMENT "Cleaning ${PROJECT_NAME}")

add_custom_target(BMPTK_build_${PROJECT_NAME}
        bmptk-make build -C "${CMAKE_CURRENT_SOURCE_DIR}/Source"
        DEPENDS
        COMMENT "Building ${PROJECT_NAME}")

add_custom_target(BMPTK_clean_build_${PROJECT_NAME}
        bmptk-make clean build -C "${CMAKE_CURRENT_SOURCE_DIR}/Source"
        DEPENDS
        COMMENT "Building ${PROJECT_NAME}")

add_custom_target(BMPTK_upload_${PROJECT_NAME}
        bmptk-make run -C "${CMAKE_CURRENT_SOURCE_DIR}/Source"
        DEPENDS
        COMMENT "Uploading ${PROJECT_NAME}")

add_custom_target(BMPTK_clean_upload_${PROJECT_NAME}
        bmptk-make clean run -C "${CMAKE_CURRENT_SOURCE_DIR}/Source"
        DEPENDS
        COMMENT "Uploading ${PROJECT_NAME}")


set(SOURCE_FILES
        Source/Makefile
        Source/hwlib.hpp

        Source/main.cpp

        Source/Weapons.hpp

        Source/IRReceiver.cpp Source/IRReceiver.hpp
        Source/IRSender.cpp Source/IRSender.hpp
        Source/DisplayController.cpp Source/DisplayController.hpp
        Source/KeyPadController.cpp Source/KeyPadController.hpp
        
        Source/InitController.cpp Source/InitController.hpp
        Source/RegisterController.cpp Source/RegisterController.hpp
        Source/GameController.cpp Source/GameController.hpp
        Source/GameTimeController.cpp Source/GameTimeController.hpp
        Source/Gamemodes.hpp Source/SpeakerController.cpp Source/SpeakerController.hpp)
add_executable(Skilled_Eagle ${SOURCE_FILES})
