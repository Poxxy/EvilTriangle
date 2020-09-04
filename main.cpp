/* Intended for educational purposes. Read the docs for more help: http://docs.gl/
   Remember: OpenGL is like a state machine!
*/

#include <GL/glew.h>
//#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>

static int compileShader(const std::string& source, unsigned int type) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader." << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();

    unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs); //cleanup after linking
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    std::cout << "Program Start.\n";

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(400, 400, "Graphics Pad", NULL, NULL); // Width, Height, Title
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    /* glewInit() MUST be called after an OpenGL window context has been made. */
    if (glewInit() != GLEW_OK) {
        std::cout << "An Error Has Occured with glewInit()" << std::endl;
    } else {
        fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    }

    /* Triangle */
    float tri_positions[6] =
        {
        -.5f, -.5f,
        .0f, .5f,
        .5f, -.5f
        };

    /* Square */
    float square_positions[8] =
    {
        -.5f, -.5f,
        -.5f,.5f,
        .5f,.5f,
        .5f,-.5f
    };

    /* Creates a buffer, useful for things which are static (such as background). */
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), tri_positions, GL_STATIC_DRAW); // 6 float values from 3 vertices (each with 2 coordinates)

    /* stride is distance between vertecies in bytes. */
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, 2*sizeof(float), 0);
    glEnableVertexAttribArray(0);

    //Actual shader definition
    std::string vertexShader =
    "#version 330 core\n"
    "\n"
    "layout(location = 0) in vec4 position;\n"
    "\n"
    "void main()\n"
    "{\n"
    " gl_Position = position;\n"
    "}\n";

    std::string fragmentShader =
    "#version 330 core\n"
    "\n"
    "layout(location = 0) out vec4 color;\n"
    "\n"
    "void main()\n"
    "{\n"
    " color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

    unsigned int shader = createShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Calls upon buffer */
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
