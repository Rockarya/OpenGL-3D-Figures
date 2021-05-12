#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, int shaderProgram);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "uniform mat4 transform;\n"
    "uniform mat4 view;\n"
    "void main()\n"
    "{\n"
        "gl_Position = transform  * view * vec4(aPos, 1.0f);\n"
    "   ourColor = aColor;\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0f);\n"
    "}\n\0";

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  0.5f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
const float cameraSpeed = 0.05f; // adjust accordingly
glm::mat4 view = glm::mat4(1.0f);


int NUM = 0,num_of_vertices,x_count=0,y_count=0,z_count=0,x_ang=0,y_ang=0,z_ang=0;

 // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[][10000] = {
    {
        // HEXAGONAL DIPYRAMID
        // positions                     // colors
        // UPPER PART
        -0.1732f, 0.0f, 0.10f,       1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.20f,           0.0f, 1.0f, 0.0f,
        0.0f, 0.40f, 0.0f,           0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.20f,           1.0f, 0.0f, 0.0f,        
        0.1732f, 0.0f, 0.10f,        0.0f, 1.0f, 0.0f,
        0.0f, 0.4f, 0.0f,            0.0f, 0.0f, 1.0f,
        0.1732f, 0.0f, 0.10f,        1.0f, 0.0f, 0.0f,
        0.1732f, 0.0f, -0.10f,       0.0f, 1.0f, 0.0f,
        0.0f, 0.40f, 0.0f,           0.0f, 0.0f, 1.0f,
        0.1732f, 0.0f, -0.10f,       1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, -0.20f,          0.0f, 1.0f, 0.0f,
        0.0f, 0.40f, 0.0f,           0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, -0.20f,          1.0f, 0.0f, 0.0f,
        -0.1732f, 0.0f, -0.10f,      0.0f, 1.0f, 0.0f,
        0.0f, 0.40f, 0.0f,           0.0f, 0.0f, 1.0f,
        -0.1732f, 0.0f, -0.10f,      1.0f, 0.0f, 0.0f,
        -0.1732f, 0.0f, 0.10f,       0.0f, 1.0f, 0.0f,
        0.0f, 0.40f, 0.0f,           0.0f, 0.0f, 1.0f,

        // LOWER PART
        -0.1732f, 0.0f, 0.10f,       1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.20f,           0.0f, 1.0f, 0.0f,
        0.0f, -0.40f, 0.0f,          0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.20f,           1.0f, 0.0f, 0.0f,
        0.1732f, 0.0f, 0.10f,        0.0f, 1.0f, 0.0f,
        0.0f, -0.40f, 0.0f,          0.0f, 0.0f, 1.0f,
        0.1732f, 0.0f, 0.10f,        1.0f, 0.0f, 0.0f,
        0.1732f, 0.0f, -0.10f,       0.0f, 1.0f, 0.0f,
        0.0f, -0.40f, 0.0f,          0.0f, 0.0f, 1.0f,
        0.1732f, 0.0f, -0.10f,       1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, -0.20f,          0.0f, 1.0f, 0.0f,
        0.0f, -0.40f, 0.0f,          0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, -0.20f,          1.0f, 0.0f, 0.0f,
        -0.1732f, 0.0f, -0.10f,      0.0f, 1.0f, 0.0f,
        0.0f, -0.40f, 0.0f,          0.0f, 0.0f, 1.0f,
        -0.1732f, 0.0f, -0.10f,      1.0f, 0.0f, 0.0f,
        -0.1732f, 0.0f, 0.10f,       0.0f, 1.0f, 0.0f,
        0.0f, -0.40f, 0.0f,          0.0f, 0.0f, 1.0f       
    },
    {
        // ELONGATED SQUARE DIPYRAMID
        // UPPER PART
        -0.10f, 0.10f, 0.10f,           1.0f, 0.0f, 0.0f,
        0.10f, 0.10f, 0.10f,            0.0f, 1.0f, 0.0f,
        0.0f, 0.30f, 0.0f,              0.0f, 0.0f, 1.0f,
        0.10f, 0.10f, 0.10f,            1.0f, 0.0f, 0.0f,
        0.10f, 0.10f, -0.10f,           0.0f, 1.0f, 0.0f,
        0.0f, 0.30f, 0.0f,              0.0f, 0.0f, 1.0f,
        0.10f, 0.10f, -0.10f,           1.0f, 0.0f, 0.0f,
        -0.10f, 0.10f, -0.10f,          0.0f, 1.0f, 0.0f,
        0.0f, 0.30f, 0.0f,              0.0f, 0.0f, 1.0f,
        -0.10f, 0.10f, -0.10f,          1.0f, 0.0f, 0.0f,
        -0.10f, 0.10f, 0.10f,           0.0f, 1.0f, 0.0f,
        0.0f, 0.30f, 0.0f,              0.0f, 0.0f, 1.0f,

        // MIDDLE PART
        -0.10f, 0.10f, 0.10f,           1.0f, 0.0f, 0.0f,
        -0.10f, -0.10f, 0.10f,          0.0f, 1.0f, 0.0f,
        0.10f, -0.10f, 0.10f,           0.0f, 0.0f, 1.0f,
        -0.10f, 0.10f, 0.10f,           1.0f, 0.0f, 0.0f,
        0.10f, 0.10f, 0.10f,            0.0f, 1.0f, 0.0f,
        0.10f, -0.10f, 0.10f,           0.0f, 0.0f, 1.0f,
        0.10f, -0.10f, -0.10f,          1.0f, 0.0f, 0.0f,
        0.10f, 0.10f, 0.10f,            0.0f, 1.0f, 0.0f,
        0.10f, -0.10f, 0.10f,           0.0f, 0.0f, 1.0f,
        0.10f, -0.10f, -0.10f,          1.0f, 0.0f, 0.0f,
        0.10f, 0.10f, 0.10f,            0.0f, 1.0f, 0.0f,
        0.10f, 0.10f, -0.10f,           0.0f, 0.0f, 1.0f,
        0.10f, -0.10f, -0.10f,          1.0f, 0.0f, 0.0f,
        -0.10f, -0.10f, -0.10f,         0.0f, 1.0f, 0.0f,
        0.10f, 0.10f, -0.10f,           0.0f, 0.0f, 1.0f,
        -0.10f, 0.10f, -0.10f,          1.0f, 0.0f, 0.0f,
        -0.10f, -0.10f, -0.10f,         0.0f, 1.0f, 0.0f,
        0.10f, 0.10f, -0.10f,           0.0f, 0.0f, 1.0f,
        -0.10f, 0.10f, -0.10f,          1.0f, 0.0f, 0.0f,
        -0.10f, -0.10f, -0.10f,         0.0f, 1.0f, 0.0f,
        -0.10f, -0.10f, 0.10f,          0.0f, 0.0f, 1.0f,
        -0.10f, 0.10f, -0.10f,          1.0f, 0.0f, 0.0f,
        -0.10f, 0.10f, 0.10f,           0.0f, 1.0f, 0.0f,
        -0.10f, -0.10f, 0.10f,          0.0f, 0.0f, 1.0f,

        // LOWER PART
        -0.10f, -0.10f, 0.10f,          1.0f, 0.0f, 0.0f,
        0.10f, -0.10f, 0.10f,           0.0f, 1.0f, 0.0f,
        0.0f, -0.30f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.10f, -0.10f, 0.10f,           1.0f, 0.0f, 0.0f,
        0.10f, -0.10f, -0.10f,          0.0f, 1.0f, 0.0f,
        0.0f, -0.30f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.10f, -0.10f, -0.10f,          1.0f, 0.0f, 0.0f,
        -0.10f, -0.10f, -0.10f,         0.0f, 1.0f, 0.0f,
        0.0f, -0.30f, 0.0f,             0.0f, 0.0f, 1.0f,
        -0.10f, -0.10f, -0.10f,         1.0f, 0.0f, 0.0f,
        -0.10f, -0.10f, 0.10f,          0.0f, 1.0f, 0.0f,
        0.0f, -0.30f, 0.0f,             0.0f, 0.0f, 1.0f
    },
    {
         // DECAGONAL PRISM
        // TOP VIEW TRIANGLES
        -0.0618f, 0.0f, 0.1902f,          1.0f, 0.0f, 0.0f,
        0.0618f, 0.0f, 0.1902f,           0.0f, 1.0f, 0.0f,
        0.0f, 0.40f, 0.0f,               0.0f, 0.0f, 1.0f,
        0.1618f, 0.0f, 0.11756f,          1.0f, 0.0f, 0.0f,
        0.0618f, 0.0f, 0.1902f,           0.0f, 1.0f, 0.0f,
        0.0f, 0.40f, 0.0f,               0.0f, 0.0f, 1.0f,
        0.1618f, 0.0f, 0.11756f,          1.0f, 0.0f, 0.0f,
        0.20f, 0.0f, 0.0f,               0.0f, 1.0f, 0.0f,
        0.0f, 0.40f, 0.0f,               0.0f, 0.0f, 1.0f,
        0.1618f, 0.0f, -0.11756f,         1.0f, 0.0f, 0.0f,
        0.20f, 0.0f, 0.0f,               0.0f, 1.0f, 0.0f,
        0.0f, 0.40f, 0.0f,               0.0f, 0.0f, 1.0f,
        0.1618f, 0.0f, -0.11756f,         1.0f, 0.0f, 0.0f,
        0.0618f, 0.0f, -0.1902f,          0.0f, 1.0f, 0.0f,
        0.0f, 0.40f, 0.0f,               0.0f, 0.0f, 1.0f,
        -0.0618f, 0.0f, -0.1902f,         1.0f, 0.0f, 0.0f,
        0.0618f, 0.0f, -0.1902f,          0.0f, 1.0f, 0.0f,
        0.0f, 0.40f, 0.0f,               0.0f, 0.0f, 1.0f,
        -0.0618f, 0.0f, -0.1902f,         1.0f, 0.0f, 0.0f,
        -0.1618f, 0.0f, -0.11756f,        0.0f, 1.0f, 0.0f,
        0.0f, 0.40f, 0.0f,               0.0f, 0.0f, 1.0f,
        -0.20f, 0.0f, 0.0f,              1.0f, 0.0f, 0.0f,
        -0.1618f, 0.0f, -0.11756f,        0.0f, 1.0f, 0.0f,
        0.0f, 0.40f, 0.0f,               0.0f, 0.0f, 1.0f,
        -0.20f, 0.0f, 0.0f,              1.0f, 0.0f, 0.0f,
        -0.1618f, 0.0f, 0.11756f,         0.0f, 1.0f, 0.0f,
        0.0f, 0.40f, 0.0f,               0.0f, 0.0f, 1.0f,
        -0.0618f, 0.0f, 0.1902f,          1.0f, 0.0f, 0.0f,
        -0.1618f, 0.0f, 0.11756f,         0.0f, 1.0f, 0.0f,
        0.0f, 0.40f, 0.0f,               0.0f, 0.0f, 1.0f,

        // BOTTOM VIEW TRIANGLES
        -0.0618f, 0.0f, 0.1902f,          1.0f, 0.0f, 0.0f,
        0.0618f, 0.0f, 0.1902f,           0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,               0.0f, 0.0f, 1.0f,
        0.1618f, 0.0f, 0.11756f,          1.0f, 0.0f, 0.0f,
        0.0618f, 0.0f, 0.1902f,           0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,               0.0f, 0.0f, 1.0f,
        0.1618f, 0.0f, 0.11756f,          1.0f, 0.0f, 0.0f,
        0.20f, 0.0f, 0.0f,               0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,               0.0f, 0.0f, 1.0f,
        0.1618f, 0.0f, -0.11756f,         1.0f, 0.0f, 0.0f,
        0.20f, 0.0f, 0.0f,               0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,               0.0f, 0.0f, 1.0f,
        0.1618f, 0.0f, -0.11756f,         1.0f, 0.0f, 0.0f,
        0.0618f, 0.0f, -0.1902f,          0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,               0.0f, 0.0f, 1.0f,
        -0.0618f, 0.0f, -0.1902f,         1.0f, 0.0f, 0.0f,
        0.0618f, 0.0f, -0.1902f,          0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,               0.0f, 0.0f, 1.0f,
        -0.0618f, 0.0f, -0.1902f,         1.0f, 0.0f, 0.0f,
        -0.1618f, 0.0f, -0.11756f,        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,               0.0f, 0.0f, 1.0f,
        -0.20f, 0.0f, 0.0f,              1.0f, 0.0f, 0.0f,
        -0.1618f, 0.0f, -0.11756f,        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,               0.0f, 0.0f, 1.0f,
        -0.20f, 0.0f, 0.0f,              1.0f, 0.0f, 0.0f,
        -0.1618f, 0.0f, 0.11756f,         0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,               0.0f, 0.0f, 1.0f,
        -0.0618f, 0.0f, 0.1902f,          1.0f, 0.0f, 0.0f,
        -0.1618f, .0f, 0.11756f,          0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,               0.0f, 0.0f, 1.0f
    }
};

int main(int argc, char ** argv)
{
    if(argc == 1)
    {
        std::cout<<"Please enter a valid whole number after the executable\n";
        return 0;
    }
    else
    {
        std::cout<<"\nUse these keys:-\nW: move in +y\nA:move in -x\nS: move in -y\nD: move in +x\nQ:move in -z\nE: move in +z\nX: spin object abt x-axis\nI: move camera towards object\nK: move camera away from object\nJ: move camera to left\nL: move camera to right\nR: rotate camera about the object\nESC: to exit\n";
        // This will be used to get which figure the user want to see.
        NUM = atoi(argv[1])%3;
        if(NUM == 0)
        {
            // HEXAGONAL DIPYRAMID
            num_of_vertices = 3*6*2;
        }
        else if(NUM == 1)
        {
            // ELONGATED SQUARE DIPYRAMID
            num_of_vertices = 3*(4 + 4*2 +4);
        }
        else
        {
            // DECAGONAL PYRAMID
            num_of_vertices = 3*10*2;
        }
    }
    // glfw: initialize and configure
    // how to handle the windows n all are done with this
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers connect to opengl implementaion from driver
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

   
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // first parameter is for number of buffer objects to create
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[NUM]), vertices[NUM], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window,shaderProgram);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);


        // render the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, num_of_vertices);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, int shaderProgram)
{
    glm::mat4 trans = glm::mat4(1.0f);
    int is_rotation = 0;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    // ROTATION ABT X-AXIS
    else if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        x_ang=(x_ang + 1)%120;
    }
    // Camera Movement
    else if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    else if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * cameraFront;
    }
    else if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    // CAMERA ROTATON
    else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        is_rotation = 1;
    }
    // TRANSLATION
    else
    { 
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            y_count++;
        }
        else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            y_count--;
        }
        else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            x_count--;
        }
        else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            x_count++;
        }
        else if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            z_count--;
        }
        else if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            z_count++;
        }
    }
    trans = glm::translate(trans, glm::vec3(0.0f + x_count*0.025f, 0.0f + y_count*0.025f, 0.0f + z_count*0.010f));
    trans = glm::rotate(trans, glm::radians(x_ang*3.0f), glm::vec3(1.0, 0.0, 0.0)); 
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    if(is_rotation == 1)
    {
        const float radius = 0.5f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.5f, 0.0));  
    }
    else
    {
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}