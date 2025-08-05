cmake_minimum_required(VERSION 3.31)
project(BudgetBlocks)

set(CMAKE_CXX_STANDARD 20)

# ========== Backend Sources ==========
set(BACKEND_SOURCES
        backend/World.cpp
        backend/World.h
        backend/Block.cpp
        backend/Block.h
        backend/Chunk.cpp
        backend/Chunk.h
        backend/Player.cpp
        backend/Player.h
        backend/CameraView.cpp
        backend/CameraView.h
        backend/WorldView.cpp
        backend/WorldView.h
        backend/stb_perlin.cpp
)

# ========== Frontend Sources ==========
set(FRONTEND_SOURCES
        frontend/Game.cpp
        frontend/Camera.cpp
        frontend/stb.cpp
        frontend/glad.c
        frontend/Shader.cpp
        frontend/Shader.h
        frontend/EBO.cpp
        frontend/EBO.h
        frontend/VBO.cpp
        frontend/VBO.h
        frontend/VAO.cpp
        frontend/VAO.h
        frontend/Texture.cpp
        frontend/Texture.h
)

# ========== Entry Point ==========
set(MAIN_SOURCE
        main.cpp
        utils.h
)

# ========== Build GameLogic Library ==========
add_library(GameLogic STATIC
        ${BACKEND_SOURCES}
        ${MAIN_SOURCE}
)

target_include_directories(GameLogic
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/include
)

# ========== Find SFML ==========
find_package(SFML 2 REQUIRED COMPONENTS system window graphics)

# ========== Build Executable ==========
add_executable(ScuffedCraft ${FRONTEND_SOURCES})

target_include_directories(ScuffedCraft
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/include
        /usr/include/GLFW
        /usr/include/glm
)

target_link_libraries(ScuffedCraft
        glfw
        ${OPENGL_LIBRARIES}
        dl
        GameLogic
)

# ========== Install Rules ==========
install(TARGETS ScuffedCraft RUNTIME DESTINATION bin)
install(TARGETS GameLogic ARCHIVE DESTINATION lib)
