
set(SOURCES 
	src/main.cpp
	src/shader.cpp)

set(HEADERS 
	src/shader.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

set(DEPENDENCY_DIR ${CMAKE_SOURCE_DIR}/deps)
set(glad ${DEPENDENCY_DIR}/glad)
set(glfw ${DEPENDENCY_DIR}/glfw)
set(glm ${DEPENDENCY_DIR}/glm)
set(stb ${DEPENDENCY_DIR}/stb)
set(imgui ${DEPENDENCY_DIR}/imgui)

set(DEPENDENCY_INCLUDES 
	${glad}/include
	${glfw}/include
	${glm}
	${stb}
	${imgui})

set(DEPENDENCY_LIBRARIES
	glad
	glfw
	imgui)

target_include_directories(${PROJECT_NAME} PRIVATE ${DEPENDENCY_INCLUDES})
target_link_libraries(${PROJECT_NAME} ${DEPENDENCY_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PRIVATE STB_IMAGE_IMPLEMENTATION)