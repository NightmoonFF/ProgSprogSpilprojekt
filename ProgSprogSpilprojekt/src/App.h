#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Snake.h"
#include "Sphere.h"
#include "Renderer.h"
#include "Shader.h"
#include "Mat4.h"

Vec3 sphericalToCartesian(float radius, float latitude, float longitude);

class App {
public:
    App();
    ~App();

    void Run();

private:

    GLFWwindow* window;
    Renderer renderer;
    Sphere sphere;
    Snake snake;
    Shader shader;
    Mat4 proj, view, model, mvp;

    float lastTime, currentTime;
    void ProcessInput();
    void Update();
    void Render();
};
