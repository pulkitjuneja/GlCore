#include "Engine.h"
#include "ResourceManager.hpp"

sf::Time Engine::deltaTime;
sf::Time Engine::timeSinceStart;


void Engine::loadDefaultShaders()
{
	ResourceManager::getInstance()->loadShader("Shaders/basic.vert", "Shaders/basic.frag", "defaultShader");
	ResourceManager::getInstance()->loadShader("Shaders/TexturedMeshUnlit.vert", "Shaders/TexturedMeshUnlit.frag", "texturedMeshUnlit");
	ResourceManager::getInstance()->loadShader("Shaders/TexturedMesh.vert", "Shaders/TexturedMesh.frag", "texturedMeshShader");
	ResourceManager::getInstance()->loadShader("Shaders/DepthMap.vert", "Shaders/DepthMap.frag", "depthMap");
	ResourceManager::getInstance()->loadShader("Shaders/DefferedGeometryPass.vert", "Shaders/DefferedGeometryPass.frag", "defferedGeometryPass");
	ResourceManager::getInstance()->loadShader("Shaders/DefferedDirectionalLight.vert", "Shaders/DefferedDirectionalLight.frag", "defferedDirectionalLightPass");
	ResourceManager::getInstance()->loadShader("Shaders/DefferedPointLight.vert", "Shaders/DefferedPointLight.frag", "defferedPointLightPass");
	ResourceManager::getInstance()->loadShader("Shaders/DefferedDirectionalLight.vert", "Shaders/HDRToneMapping.frag", "basicToneMapping");
}

void Engine::start() {

    // engine specific initializations
    if(!setupSFML()) {
        isEngineRunning = false;
    }

	//renderer = new Renderer();
	defferedRenderer = new DefferedRenderer();

    if(!init()) {
        isEngineRunning = false;
    }

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glEnable(GL_DEBUG_OUTPUT);
	//glDebugMessageCallback(MessageCallback, 0);

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

		defferedRenderer->render();

        window->display( );
    }

    // todo: perform shutdown steps
    window->close();
}

bool Engine::setupSFML() {

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    settings.attributeFlags = sf::ContextSettings::Core;

    window = new sf::Window( sf::VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 64 ), "OpenGL SFML", sf::Style::Titlebar | sf::Style::Close, settings );
	window->setVerticalSyncEnabled(false);
    glewExperimental = GL_TRUE;

    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
    }

	std::string versionString = std::string((const char*)glGetString(GL_VERSION));
	cout << versionString.c_str();

    // Load Default Shaders

	loadDefaultShaders();

  return true;
}
