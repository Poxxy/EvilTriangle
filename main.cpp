/* Intended for educational purposes. Read the docs for more help: http://docs.gl/
   Remember: OpenGL is like a state machine!
*/

#include <GL/glew.h>
#include <GL/glut.h>
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
    float tri_positions[] =
        {
        .0f, .0f,
        1.0f, .0f,
        1.0f, 1.0f,
        .0f, 1.0f
        };

    /* Index Buffer. Can be reduced to unsigned char or unsigned short if space is an issue. */
    unsigned int indices[] {
        0, 1, 2, //triangle 1
        3, 0, 2
    };

    /* Creates the main buffer, useful for things which are static (such as background). */
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), tri_positions, GL_STATIC_DRAW); // 8 float values from 4 vertices (each with 2 coordinates)

    /* stride is distance between vertecies in bytes. */
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, 2*sizeof(float), 0);
    glEnableVertexAttribArray(0);

    /* Creates the index buffer, useful for reducing amount of GPU calls */
    unsigned int index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * 2 * sizeof(unsigned int), indices, GL_STATIC_DRAW); // 6 unsigned ints from 2 triangles (each with 3 vertices)

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

        /* Calls upon buffer, glDrawArrays is used if no index buffer is in place. */
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
