cmake_minimum_required(VERSION 3.6)
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


set(SOURCE_FILES Source/main.cpp)
add_executable(Skilled_Eagle ${SOURCE_FILES})
