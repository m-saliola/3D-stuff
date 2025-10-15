cmake_minimum_required(VERSION 3.10)
project(main)

file(GLOB SRC_FILES
"${CMAKE_SOURCE_DIR}/src/*.cpp"
"${CMAKE_SOURCE_DIR}/src/*.c"
"${CMAKE_SOURCE_DIR}/src/vendor/**/*.cpp"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

link_directories(${CMAKE_SOURCE_DIR}/lib)

find_library(GLFW_LIB NAMES glfw3 libglfw3 PATHS "${CMAKE_SOURCE_DIR}/lib" NO_DEFAULT_PATH)

target_include_directories(${PROJECT_NAME} PRIVATE include)

if (WIN32)
    if (GLFW_LIB)
        target_link_libraries(${PROJECT_NAME}
            ${GLFW_LIB}
            opengl32
            gdi32
        )
    else()
        target_link_libraries(${PROJECT_NAME}
            glfw3
            opengl32
            gdi32
        )
    endif()

    target_link_options(${PROJECT_NAME} PRIVATE
        -static-libstdc++
        -static-libgcc
    )
elseif (APPLE)
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_LIBRARIES})
else()
    find_package(OpenGL REQUIRED)
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME}
        glfw
        ${OPENGL_LIBRARIES}
        ${X11_LIBRARIES}
        pthread
        dl
    )
endif()
