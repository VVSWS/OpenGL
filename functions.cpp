#include <functions.h>

float rotationOffset = 0.0f;
bool isRotating = true;
float stopTime = 0.0f;
float scaleFactor = 1.0f;

void createSphere(float radius, int sectors, int stacks, std::vector<float>& vertices, std::vector<unsigned int>& indices)
{
    const float PI = 3.1415926f;
    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / radius;
    float s, t;

    float sectorStep = 2 * PI / sectors;
    float stackStep = PI / stacks;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stacks; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (int j = 0; j <= sectors; ++j)
        {
            sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            s = (float)j / sectors;
            t = (float)i / stacks;
            vertices.push_back(s);
            vertices.push_back(t);
        }
    }

    for (int i = 0; i < stacks; ++i)
    {
        int k1 = i * (sectors + 1);
        int k2 = k1 + sectors + 1;

        for (int j = 0; j < sectors; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stacks - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    scaleFactor += yoffset * 0.1f; // Adjust sensitivity
    scaleFactor = glm::clamp(scaleFactor, 0.5f, 2.0f); // Prevent extreme scaling
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if (isRotating)
        {
            stopTime = glfwGetTime(); // Store when stopped
        }
        else
        {
            rotationOffset += glfwGetTime() - stopTime; // Preserve rotation timing
        }
        isRotating = !isRotating;
    }
}