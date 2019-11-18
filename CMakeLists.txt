cmake_minimum_required(VERSION 3.10)
project(GlCore)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)

message ("Open gl libs" ${OPENGL_LIBRARIES})

link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/ext/assimp/lib
)

file(GLOB glcore_src
    "src/*.h"
    "src/*.cpp"
	"src/utils/*.h"
	"src/utils/*.cpp"
)

add_executable(GlCore ${glcore_src}
	TestWorld.cpp
	main.cpp
	src/Texture.cpp
)
  
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ext/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ext/assimp/include)

if(WIN32)
target_link_libraries(GlCore 
	${OPENGL_LIBRARIES}
	sfml-graphics.lib
	sfml-window.lib
	sfml-system.lib
	glew32.lib
	assimpd.lib
	)
endif()

if(APPLE)
    target_include_directories(GlCore PUBLIC
            /usr/local/include)
    target_link_libraries(GlCore
			libassimp.dylib
            /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.0.dylib
            /usr/local/Cellar/sfml/2.4.2_1/lib/libsfml-window.2.4.2.dylib
            /usr/local/Cellar/sfml/2.4.2_1/lib/libsfml-system.2.4.2.dylib ${OPENGL_LIBRARIES})
endif()
