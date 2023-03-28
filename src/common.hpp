#define SDL_MAIN_HANDLED

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/gl.h>

typedef glm::mat4x4 Mat4;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;

#include "geometry.hpp"
#include "shaders.hpp"
#include "textures.hpp"
#include "mesh.hpp"
#include "renderer.hpp"
#include "camera.hpp"
#include "appwindow.hpp"
#include "debug.hpp"