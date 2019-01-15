#include "Engine.h"
#include "ResourceManager.hpp"

const GLint WIDTH = 1366, HEIGHT = 768;

sf::Time Engine::deltaTime;
sf::Time Engine::timeSinceStart;

void Engine::loadDefaultShaders()
{
	ResourceManager::getInstance()->loadShader("Shaders/basic.vert", "Shaders/basic.frag", "defaultShader");
	ResourceManager::getInstance()->loadShader("Shaders/TexturedMeshUnlit.vert", "Shaders/TexturedMeshUnlit.frag", "texturedMeshUnlit");
	ResourceManager::getInstance()->loadShader("Shaders/TexturedMesh.vert", "Shaders/TexturedMesh.frag", "texturedMeshShader");
}

void Engine::start() {
    // engine specific initializations
    if(!setupSFML()) {
        isEngineRunning = false;
    }
    if(!init()) {
        isEngineRunning = false;
    }

	glEnable(GL_DEPTH_TEST);

    sf::Clock clock;
    while (isEngineRunning) {
        sf::Event windowEvent;

        while ( window->pollEvent( windowEvent ) )
        {
            switch ( windowEvent.type )
            {
                case sf::Event::Closed:
                    isEngineRunning = false;
                    break;
            }
        }
        deltaTime = clock.restart();
        timeSinceStart += deltaTime;
        update();

        glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        render();

        window->display( );
    }

    // perform shutdown steps
    window->close();
}

bool Engine::setupSFML() {

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    settings.attributeFlags = sf::ContextSettings::Core;

    window = new sf::Window( sf::VideoMode( WIDTH, HEIGHT, 32 ), "OpenGL SFML", sf::Style::Titlebar | sf::Style::Close, settings );

    glewExperimental = GL_TRUE;

    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    // Load Default Shaders

	loadDefaultShaders();

  return true;
}
