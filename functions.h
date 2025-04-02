#pragma once
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

//Global variables for mouse control
extern float rotationOffset;
extern bool isRotating;
extern float stopTime;
extern float scaleFactor;

//Creating a sphere
void createSphere(float radius, int sectors, int stacks, std::vector<float>& vertices, std::vector<unsigned int>& indices);

//Callbacks for scrolling
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

//Callbacks for clicking
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);