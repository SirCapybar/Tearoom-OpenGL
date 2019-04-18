#ifndef GLOBAL_H
#define GLOBAL_H

#define GLM_ENABLE_EXPERIMENTAL

#include "imgui.h"
#include "imgui_impl_glfw.h"         // Visual Studio says it's redundant, but IT IS NOT.
#include <glm/gtx/rotate_vector.hpp> // same applies to this one
#include "imgui_impl_opengl3.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <vector>
#include <string>

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include <functional>

struct Texture {
	GLuint id{};
	std::string path;
};

static const glm::ivec2 ENVMAP_SIZE(2048.0f, 2048.0f);

static const char *BTN_SHORT_IDLE = "res/ui/ButtonIdle.png", *BTN_SHORT_CLICKED = "res/ui/ButtonClicked.png", *BTN_SHORT_HOVER = "res/ui/ButtonHover.png",
*BTN_LONG_IDLE = "res/ui/ButtonLongIdle.png", *BTN_LONG_CLICKED = "res/ui/ButtonLongClicked.png", *BTN_LONG_HOVER = "res/ui/ButtonLongHover.png",
*BTN_TICK_IDLE = "res/ui/ButtonTickIdle.png", *BTN_TICK_CLICKED = "res/ui/ButtonTickClicked.png", *BTN_TICK_HOVER = "res/ui/ButtonTickHover.png";

static const float BASE_LONG_BTN_WIDTH = 0.3f, BASE_LONG_BTN_HEIGHT = 0.1f, BASE_BTN_SIZE = 0.1f;

struct DirLight {
	DirLight() : ambient(glm::vec4(0.0f)), diffuse(glm::vec4(0.0f)), specular(glm::vec4(0.0f)), model(glm::mat4(1.0f)), enabled(true) {}
	glm::mat4 lightSpace;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::mat4 model;
	glm::vec3 padding;
	bool enabled;
};

struct PointLight {
	PointLight() : constant(100.0f), linear(100.0f), quadratic(100.0f), near_plane(0.01f), far_plane(10.0f),
	ambient(glm::vec4(0.0f)), diffuse(glm::vec4(0.0f)), specular(glm::vec4(0.0f)), model(glm::mat4(1.0f)), enabled(true) {}
	float constant;
	float linear;
	float quadratic;
	float near_plane;
	glm::vec2 padding;
	float far_plane;
	bool enabled;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::mat4 model;
};

struct SpotLight {
	SpotLight() : ambient(glm::vec4(0.0f)), diffuse(glm::vec4(0.0f)), specular(glm::vec4(0.0f)), model(glm::mat4(1.0f)), constant(100.0f), linear(100.0f), quadratic(100.0f),
	cutOff(M_PI/12.0f), outerCutOff(M_PI/4.0f), enabled(true) {}
	glm::mat4 lightSpace;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::mat4 model;
	float constant;
	float linear;
	float quadratic;
	float cutOff;
	glm::vec2 padding;
	float outerCutOff;
	bool enabled;
};

struct LightShadowData {
	GLuint fbo = 0;
	GLuint rbo = 0;
	GLuint texture = 0;
	GLsizei width = 0;
	GLsizei height = 0;
};

class Global {
public:
	static glm::vec4 planeEquationOfPoints(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	static float distanceBetweenParallelPlanes(glm::vec4 plane1, glm::vec4 plane2);
	static glm::vec3* createHorizontalTransformArray(const int width, const int length, const glm::vec2 min, const glm::vec2 max, const float yPosition = 0.0f);
	static void drawToCubemap(GLuint cubemap, glm::vec3 position, GLuint fbo, GLuint rb, const std::function<void(glm::mat4, glm::mat4)> renderCallback, GLuint framebuffer);
	static double remap(const double value, const double sourceMin, const double sourceMax, double targetMin, double targetMax, const bool revertTarget = false, const bool snapIfInvalid = true);
	static float remap(const float value, const float sourceMin, const float sourceMax, float targetMin, float targetMax, const bool revertTarget, const bool snapIfInvalid);
	static int remap(const int value, const int sourceMin, const int sourceMax, const int targetMin, const int targetMax, const bool revertTarget = false, const bool snapIfInvalid = true);
};

#endif
