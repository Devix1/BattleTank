cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# Название проекта
set(PROJECT_NAME BattleTank)
project(${PROJECT_NAME})

# Стандарты C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Главный исполняемый файл и исходники
add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/Renderer/ShaderProgram.cpp
    src/Renderer/ShaderProgram.h
)

# Настройки сборки зависимостей GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Подключение GLFW и GLAD
add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

# Установка директории для вывода исполняемых файлов
set_target_properties(${PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/
)

# Копирование директории ресурсов после сборки
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    COMMENT "Copying resources directory to output folder"
)
