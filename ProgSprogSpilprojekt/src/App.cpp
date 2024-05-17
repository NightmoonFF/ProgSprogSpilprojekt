#include "App.h"
#include <iostream>
#include "Sphere.h"

App::App() {
    
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    window = glfwCreateWindow(640, 480, "SuperSnake", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    glfwSwapInterval(1);

    //proj = Mat4::perspective(45.0f * (3.14159265359f / 180.0f), 640.0f / 480.0f, 0.1f, 10.0f);
    //view = Mat4::translate(Vec3(0, 0, -3));
    //model = Mat4();
    //mvp = proj * view * model;

    //shader.Bind();
    //shader.SetUniformMat4f("u_MVP", mvp);

    printf("test");
}

App::~App() {
    glfwTerminate();
}

void App::Run() {


    Sphere sphere(1.0f, 30, 30);

    VertexArray va;
    VertexBuffer vb(sphere.vertices.data(), sphere.vertices.size() * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(3); // 3 for XYZ axis
    va.AddBuffer(vb, layout);

    IndexBuffer ib(sphere.indices.data(), sphere.indices.size());

    Shader shader("res/shaders/Sphere.shader");
    shader.Bind();
    shader.SetUniformMat4f("u_MVP", mvp);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    float rotationAngle = 0.0f;

    
    while (!glfwWindowShouldClose(window)) {
        
        renderer.Clear();
        
        shader.Bind();
        //shader.SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(va, ib, shader);
        
        rotationAngle += 0.01f;

        model = Mat4::rotateY(rotationAngle) * model; // Rotate around the y-axis
        mvp = proj * view * model;
        
        
        //currentTime = glfwGetTime();
        /*if (currentTime - lastTime >= 0.1) {
            snake.move();
            lastTime = currentTime;
        }*/
        


        ProcessInput();
        
        Update();
        
        //Render();

        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }

    printf("GL window terminated");
}

void App::ProcessInput() {
    //if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) snake.setDirection(Snake::UP);
    //if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) snake.setDirection(Snake::DOWN);
    //if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) snake.setDirection(Snake::LEFT);
    //if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) snake.setDirection(Snake::RIGHT);
}

void App::Update() {
    // Any game logic updates
}

void App::Render() {

    //renderer.Clear();






    /*shader.Bind();
    shader.SetUniformMat4f("u_MVP", mvp);*/
    
    //renderer.Draw(va, ib, shader);
    //renderer.Draw(sphere.va, sphere.ib, shader);

    //for (const Position& pos : snake.getBody()) {
    //    Vec3 cartesianPos = sphericalToCartesian(1.0f, pos.latitude, pos.longitude);
    //    model = Mat4::translate(cartesianPos);
    //    mvp = proj * view * model;
    //    shader.SetUniformMat4f("u_MVP", mvp);
    //}
}

Vec3 sphericalToCartesian(float radius, float latitude, float longitude) {
    float lat = latitude * (3.14159265359f / 180.0f);
    float lon = longitude * (3.14159265359f / 180.0f);
    float x = radius * cos(lat) * cos(lon);
    float y = radius * sin(lat);
    float z = radius * cos(lat) * sin(lon);
    return Vec3(x, y, z);
}
