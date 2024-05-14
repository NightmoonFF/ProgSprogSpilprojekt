#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) { //if the line has found shader
            
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //TODO: Error handling

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

// Provides OpenGL with our actual shader source-code, for it to compile it, link them together to one shader program, and return a unique identifier
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // delete intermediate shaders no longer used
    glDeleteShader(vs); 
    glDeleteShader(fs);

    return program;
}


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

    if (glewInit() != GLEW_OK)
        std::cout << "Error?" << std::endl;

    std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;




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

#pragma region Array Buffer

    /*
        Create a buffer with param of how many (one),
        and we put in an unsigned integers address as the pointer
        Gives back an ID (the address pointer? not sure)

        Selecting in GL is called binding.
        Since this is a buffer of memory, we use an array buffer
        It takes in the ID of the buffer we just generated, that we want to select
        Usually you have to specify the size of the buffer.

        For glBufferData:
        Specify target of the buffer: an array
        Specify name of the buffer object
        Specify the size in bytes of buffer objects new data store. (We have 6 positions in float, so size will be the bytes of 6 floats)
        Specify a pointer to data that will be copied into the data store for init
        Specify usage, where we in this case just want the object drawn
    */
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

#pragma endregion


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // Index Buffer Object
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * 2 * sizeof(unsigned int), indices, GL_STATIC_DRAW);



    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    /* 
    Primary purpose of vertexShader is to tell openGL to tell where you want that vertex to be in your screenspace. 
    It runs for each vertex, in this case 3 times.

    The fagment shader or pixel shader, is what then rasterizes (fills in) the triangle of the pixels in the window or screenspace.
    Primary purpose of this type of shader, is to decide what each individual pixel should be (and at what time?)
    this fragment shader can be potentially called potentially millions of times, so as little calculation as possible should happen in the vertex shader, which can then
    be passed to the fragment shader 
    */


    /* Loop until the user closes the window */
    /* Can be thought of as the Game-Loop */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* 
           Use if you dont have indexBuffer. Otherwise you'd use glDrawElements
           BindBuffer is what makes GL know that THAT is the buffer which needs to be drawn here (State machine)
        */
        //glDrawArrays(GL_TRIANGLES, 0, 3);


        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}