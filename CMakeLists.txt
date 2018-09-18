cmake_minimum_required(VERSION 3.10)
project(GlTestBed)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
#find_package(GLEW REQUIRED)

message ('--------'  ${OPENGL_LIBRARIES})

add_Library(GlTestBed
        src/Globals.h
        src/Mesh.cpp
        src/Mesh.h
        src/ResourceManager.cpp
        src/ResourceManager.hpp
        src/Shader.cpp
        src/Shader.h
        src/stb_image.cpp
        src/stb_image.h
        src/Material.h
        src/Engine.cpp src/Engine.h
        src/Particle.cpp
        src/Particle.h
		src/Camera.h
		src/Camera.cpp
        src/ParticleManager.cpp
        src/ParticleManager.h
        src/ParticleUpdater.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ext/glm)
target_include_directories(GlTestBed PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ext/SFML-2.4.2/include)


target_link_libraries(GlTestBed 
	${OPENGL_LIBRARIES} 
	glew32.lib 
	${CMAKE_CURRENT_SOURCE_DIR}/ext/SFML-2.4.2/lib/sfml-graphics.lib
	${CMAKE_CURRENT_SOURCE_DIR}/ext/SFML-2.4.2/lib/sfml-window.lib
	${CMAKE_CURRENT_SOURCE_DIR}/ext/SFML-2.4.2/lib/sfml-system.lib)

if(APPLE)
    target_include_directories(GlTestBed PUBLIC
            /usr/local/include)
    target_link_libraries(GlTestBed
            /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.0.dylib
            /usr/local/Cellar/sfml/2.4.2_1/lib/libsfml-window.2.4.2.dylib
            /usr/local/Cellar/sfml/2.4.2_1/lib/libsfml-system.2.4.2.dylib ${OPENGL_LIBRARIES})
endif()
