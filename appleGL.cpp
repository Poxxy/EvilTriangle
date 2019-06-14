#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>

//Compile with:
// g++ appleGL.cpp -lglfw -lopengl32

void famebuffer_size_callback(GLFWwindow *window, int width, int height);
int createWindow();
void processInput(GLFWwindow *window);

//Window settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

    createWindow();
    

    std::cout << "Run successful!\n";
    return 0;
}