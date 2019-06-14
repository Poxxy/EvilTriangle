#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <GL/gl.h>

//Compile with:
// g++ appleGL.cpp -lglfw -lopengl32

void famebuffer_size_callback(GLFWwindow *window, int width, int height);
int createWindow();
void processInput(GLFWwindow *window);

//Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n" //C code!!! :)
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, .5, .2f, 1f);\n"
    "}\n\0";

void processInput(GLFWwindow *window) {
    //Input control
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) /*Check to see if escape key was pressed, close the window if so. */{
        glfwSetWindowShouldClose(window, true);
    } else if (glfwGetKey(window,GLFW_KEY_V) == GLFW_PRESS) { /*V button used as output to console for testing. */
        std::cout << "V key pressed.\n";
    } 

}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    //Use this function to resize window (and start from bottom left still).
    glViewport(0,0,width,height);
}

int createWindow() {
    // Create window: width, height, title, ignore, ignore.
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"OpenGL Is Fun", NULL, NULL);
    if (window == NULL) {
        //Something went wrong.
        std::cout << "Failed to create GLFW window.\n";
        glfwTerminate();
        return -1;
    }
    //Focus onto this window.
    glfwMakeContextCurrent(window);
    //Tell OpenGL size and coordinates of window (start bottom left).
    glViewport(0,0,800,600);
    //If user resizes window, viewport will be fixed by registering the window change.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Keep drawing until user tells program to stop.
    while(!glfwWindowShouldClose(window)) /* Check if window was asked to close. */ {
        //Choose color to be used for clearing of screen.
        glClearColor(.2f, .3f, .3f, 1.0f);
        //Clear the screen with select color.
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window); /*Possible input: esc (quit), v (print to console) */


        //Change color buffer (used for drawing)
        glfwSwapBuffers(window);
        //Check for any events being triggered (keyboard/mouse)
        glfwPollEvents();
    }
    //Cleanup resources used by GLFW
    glfwTerminate();
    return 0;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    float triangle[] = {
        -.5f, .5f, .0f,
        .5f, -.5f, .0f,
        .0f, .5f, .0f
    };

    unsigned int VBO; /*Vertex Buffer Object */
    glGenBuffers(1, &VBO); //Buffer type
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Buffer type for vertex objects are GL_ARRAY_BUFFER
    //Type of data to buffer, size of data (bytes), data to buffer, and how to manage the data (for graphics driver)
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW); /*Position of triangle won't change, so GL_STATIC_DRAW is appropriate */

    createWindow();
    

    std::cout << "Run successful!\n";
    return 0;
}