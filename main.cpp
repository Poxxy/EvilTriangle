/* Intended for educational purposes. Read the docs for more help: http://docs.gl/
   Remember: OpenGL is like a state machine!
*/

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

    /* Creates a buffer, useful for things which are static (such as background). */
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), tri_positions, GL_STATIC_DRAW); // 6 float values from 3 vertices (each with 2 coordinates)

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
