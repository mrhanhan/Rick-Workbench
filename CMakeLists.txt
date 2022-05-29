cmake_minimum_required(VERSION 3.21)
project(Workbench)

set(CMAKE_CXX_STANDARD 20)

set(GLFW_HOME G:/Lib/GLFW/glfw-3.3.7.bin.WIN64)

include_directories(${GLFW_HOME}/include ${PROJECT_SOURCE_DIR}/thirdPart )

link_directories(G:/Lib/GLFW/glfw-3.3.7.bin.WIN64/lib-static-ucrt)
link_libraries(glfw3dll.lib)

# 源代码
#aux_source_directory(src SOURCE_FILES)
aux_source_directory(src/utils SOURCE_FILES)
aux_source_directory(src/game SOURCE_FILES)
aux_source_directory(src/render SOURCE_FILES)
aux_source_directory(src/gl SOURCE_FILES)
# Glad
aux_source_directory(thirdPart/glad GLAD_SOURCE_FILES)
# Glm
#add_subdirectory(thirdPart/glm)
#add_library(glm::glm ALIAS glm)

message("${GLAD_SOURCE_FILES}")
message("${SOURCE_FILES}")
add_executable(Workbench src/main.cpp ${SOURCE_FILES} ${GLAD_SOURCE_FILES})
add_executable(Test src/test.cpp ${SOURCE_FILES} ${GLAD_SOURCE_FILES})
