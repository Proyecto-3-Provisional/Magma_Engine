cmake_minimum_required(VERSION 3.0)
project(lua)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib) # Se establece la carpeta donde se generarán los archivos de la biblioteca

# Agrega todos los archivos de código fuente Lua necesarios
file(GLOB LUA_SRC src/*.c)

# Agrega la biblioteca Lua
add_library(lua STATIC ${LUA_SRC})

# Configura la biblioteca Lua
target_include_directories(lua PUBLIC include)
target_compile_definitions(lua PUBLIC LUA_COMPAT_5_2)
