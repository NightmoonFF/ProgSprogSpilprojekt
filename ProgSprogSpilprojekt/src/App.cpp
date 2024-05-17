#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


/* Personal Notes:

        Create a buffer with param of how many (one),
        and we put in an unsigned integers address as the pointer
        Gives back an ID (the address pointer? not sure)

        Selecting in GL is called binding.
        Since this is a buffer of memory, we use an array buffer
        It takes in the ID of the buffer we just generated, that we want to select
        Usually you have to specify the size of the buffer.

        Using unsigned int is very important

        For glBufferData:
        Specify target of the buffer: an array
        Specify name of the buffer object
        Specify the size in bytes of buffer objects new data store. (We have 6 positions in float, so size will be the bytes of 6 floats)
        Specify a pointer to data that will be copied into the data store for init
        Specify usage, where we in this case just want the object drawn

        Primary purpose of vertexShader is to tell openGL to tell where you want that vertex to be in your screenspace.
        It runs for each vertex, in this case 3 times.

        The fagment shader or pixel shader, is what then rasterizes (fills in) the triangle of the pixels in the window or screenspace.
        Primary purpose of this type of shader, is to decide what each individual pixel should be (and at what time?)
        this fragment shader can be potentially called potentially millions of times, so as little calculation as possible should happen in the vertex shader, which can then
        be passed to the fragment

        glDrawArrays: non indexBuffer
        glDrawElements: indexBuffer
        BindBuffer is what makes GL know what is the buffer that needs to be drawn here (it is a State machine)
        GLCallwrapper is error handling, it allows debugging OpenGL where it would otherwise be very difficult.
        Ideally all gl-functions should be wrapped
        */

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Syncrhronizes without v-sync?
    glfwSwapInterval(1);


    if (glewInit() != GLEW_OK)
        std::cout << "Error?" << std::endl;

    std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;

    {
        // An array of the positions we want to use for the triangle
        float positions[] = {
            -0.5f, -0.5f, // 0
             0.5f, -0.5f, // 1
             0.5f,  0.5f, // 2
            -0.5f,  0.5f  // 3
        };

        // Index buffer - render a square without providing duplicate vertice positions
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);


        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;

        /* Game-Loop happens here: */
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();
        
            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f); // modify the uniform at "location"
        
            renderer.Draw(va, ib, shader);
            

            // Rainbow Flash
            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;
       

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }

    glfwTerminate();
    return 0;
}