# GlCore
A minimal base framework for OpenGl based projects written in C++

## Features
* Cross-platform
* Wrapper classes for common OpenGL objects (Textures, Shaders, Mesh)
* Mesh loading (TBD)
* Texture loading
* Particle Manager
* Camera class

## What it looks like
Initializing an OpenGL application is as easy as including GlCore in your project and inheriting from the Engine class

```
class ParticleWorld : public Engine {

    std::vector<ParticleManager* > managers;
	Camera* camera;

public:

    virtual bool init ();
    virtual void update();
    virtual void render();
};
```

For a sample application you can have alook at the particle demo I created using the library [here](https://github.com/pulkitjuneja/OpenGL-Particles)

 ![image](https://pulkitjuneja.github.io/portfolio/particles.gif)

## Dependencies
* [SFML](https://github.com/SFML/SFML) 
* [glm](https://github.com/g-truc/glm) 
* [stb](https://github.com/nothings/stb) 


