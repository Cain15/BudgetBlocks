cmake_minimum_required(VERSION 3.31)
project(BudgetBlocks)

set(CMAKE_CXX_STANDARD 20)

# ========== Backend ==========
set(BACKEND_SOURCES
        backend/World.cpp
        backend/Block.cpp
        backend/Chunk.cpp
        backend/Player.cpp
        backend/CameraView.cpp
        backend/CameraView.h
)

# ========== Frontend ==========
set(FRONTEND_SOURCES
        frontend/stb.cpp
        frontend/glad.c
        frontend/Game.cpp
        frontend/Camera.cpp
)

# ========== Entry Point ==========
set(MAIN_SOURCE
        main.cpp
        utils.h
)

# ========== Group Sources ==========
set(LOGIC_SOURCES
        ${BACKEND_SOURCES}
        backend/WorldView.cpp
        backend/WorldView.h
)

set(UI_SOURCES
        ${FRONTEND_SOURCES}
        ${MAIN_SOURCE}
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

# ========== Build GameLogic Library ==========
add_library(GameLogic STATIC ${LOGIC_SOURCES})
target_include_directories(GameLogic PUBLIC src)

# ========== Find SFML ==========
find_package(SFML 2 REQUIRED COMPONENTS system window graphics)

# ========== Build Executable ==========
add_executable(ScuffedCraft ${UI_SOURCES})
target_include_directories(ScuffedCraft PRIVATE src)
target_include_directories(ScuffedCraft PRIVATE /usr/include/GLFW)
target_include_directories(ScuffedCraft PRIVATE /usr/include/glm)
target_include_directories(ScuffedCraft PRIVATE libraries/include)
target_link_libraries(ScuffedCraft glfw ${OPENGL_LIBRARIES} dl)


# ========== Install Rules ==========
install(TARGETS ScuffedCraft RUNTIME DESTINATION bin)
install(TARGETS GameLogic ARCHIVE DESTINATION lib)
target_link_libraries(ScuffedCraft GameLogic)


