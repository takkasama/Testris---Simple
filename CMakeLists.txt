cmake_minimum_required(VERSION 3.16)

project(Tetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar archivos CPP
file(GLOB SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/source/*.cpp"
)

# Agregar main.cpp
list(APPEND SOURCES
    "${PROJECT_SOURCE_DIR}/main.cpp"
)

# Mostrar archivos encontrados
message(STATUS "Archivos encontrados: ${SOURCES}")

# Crear ejecutable Windows
add_executable(Tetris WIN32 ${SOURCES})

# Encabezados
target_include_directories(Tetris PRIVATE
    "${PROJECT_SOURCE_DIR}/header"
    "${PROJECT_SOURCE_DIR}/raylib/include"
)

# Bibliotecas Windows
target_link_libraries(Tetris PRIVATE
    "${PROJECT_SOURCE_DIR}/raylib/lib/libraylib.a"
    opengl32
    gdi32
    winmm
)

# Runtime GCC estático
target_link_options(Tetris PRIVATE
    -static
    -static-libgcc
    -static-libstdc++
)

# Copiar recursos
add_custom_command(TARGET Tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:Tetris>/resources"
)