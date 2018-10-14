cmake_minimum_required(VERSION 3.10)
project(GlCore)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
#find_package(GLEW REQUIRED)

add_library(GlCore
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
        src/Engine.cpp 
	    src/Engine.h
        src/Particle.cpp
        src/Particle.h
		src/Renderable.h
		src/MeshRenderer.h
		src/MeshRenderer.cpp
        src/ParticleManager.cpp
        src/ParticleManager.h
		src/Entity.h src/Entity.cpp
		src/Camera.h src/Camera.cpp
		src/EntityManager.h src/EntityManager.cpp src/Component.h
        src/ParticleUpdater.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ext/glm)

target_link_libraries(GlCore 
	${OPENGL_LIBRARIES}
	sfml-graphics.lib
	sfml-window.lib
	sfml-system.lib
	glew32.lib)

if(APPLE)
    target_include_directories(GlCore PUBLIC
            /usr/local/include)
    target_link_libraries(GlCore
            /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.0.dylib
            /usr/local/Cellar/sfml/2.4.2_1/lib/libsfml-window.2.4.2.dylib
            /usr/local/Cellar/sfml/2.4.2_1/lib/libsfml-system.2.4.2.dylib ${OPENGL_LIBRARIES})
endif()
