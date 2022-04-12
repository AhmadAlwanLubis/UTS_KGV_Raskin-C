#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

#include "util.h"

float color1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float color2[] = { 1.0f, 0.0f, 0.0f, 1.0f };
float color3[] = { 1.0f, 1.0f, 0.0f, 1.0f };
float color4[] = { 1.0f, 0.0f, 1.0f, 0.0f };
float color5[] = { 1.0f, 0.1f, 1.0f, 0.0f };
float color6[] = { 1.0f, 0.0f, 1.1f, 0.0f };
float color7[] = { 1.0f, 0.0f, 1.0f, 0.0f };
float color8[] = { 1.0f, 1.1f, 1.0f, 0.0f };
float xp, yp, r = 1, n = 8, x, y;
float a = 0.5f;

unsigned int program;
GLint color1Loc, color2Loc, color3Loc, color4Loc, color5Loc, color6Loc, color7Loc, color8Loc;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_E && action == GLFW_PRESS){
        for (int i = 0; i < 4; i++) {
            color1[i] = (rand() * 1.0f) / RAND_MAX;
            color2[i] = (rand() * 1.0f) / RAND_MAX;
            color3[i] = (rand() * 1.0f) / RAND_MAX;
            color4[i] = (rand() * 1.0f) / RAND_MAX;
            color5[i] = (rand() * 1.0f) / RAND_MAX;
            color6[i] = (rand() * 1.0f) / RAND_MAX;
            color7[i] = (rand() * 1.0f) / RAND_MAX;
            color8[i] = (rand() * 1.0f) / RAND_MAX;
        }
        std::cout << color1[1], color1[2], color1[3], color1[4] ;
        std::cout << color2 [1], color2[2], color2[3], color2[4] ;
        std::cout << color3 [1], color3[2], color3[3], color3[4] ;
        std::cout << color4[1], color4[2], color4[3], color4[4] ;
        std::cout << color5[1], color5[2], color5[3], color5[4] ;
        std::cout << color6[1], color6[2], color6[3], color6[4] ;
        std::cout << color7[1], color7[2], color7[3], color7[4] ;
        std::cout << color8[1], color8[2], color8[3], color8[4] ;

        glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);
        glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);
        glUniform4f(color3Loc, color3[0], color3[1], color3[2], color3[3]);
        glUniform4f(color4Loc, color4[0], color4[1], color4[2], color4[3]);
        glUniform4f(color5Loc, color5[0], color5[1], color5[2], color5[3]);
        glUniform4f(color6Loc, color6[0], color6[1], color6[2], color6[3]);
        glUniform4f(color7Loc, color7[0], color7[1], color7[2], color7[3]);
        glUniform4f(color8Loc, color8[0], color8[1], color8[2], color8[3]);
    }
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Raskin-C", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyCallback);

    GLenum err = glewInit();

    float vertices[18] = {

    };
    int u = 0;
    a = (2 * 3.14) / n;
    for (int i = 0; i < n; i++) {
        x = xp + r * cos(i * a);
        y = yp + r * sin(i * a);
        vertices[u] = x;
        std::cout << vertices[u];
        u = u + 1;
        vertices[u] = y;
        std::cout << vertices[u];
        u = u + 1;
    }
   

    unsigned int indexArr[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 7,
        0, 7, 8,
        0, 8, 1
    };

    unsigned int vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 24,indexArr, GL_STATIC_DRAW);

    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");

    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexChar, NULL);
    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);


    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glUseProgram(program);

    color1Loc = glGetUniformLocation(program, "color1");
    glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);

    color2Loc = glGetUniformLocation(program, "color2");
    glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);
    
    color3Loc = glGetUniformLocation(program, "color3");
    glUniform4f(color3Loc, color3[0], color3[1], color3[2], color3[3]);
    
    color4Loc = glGetUniformLocation(program, "color4");
    glUniform4f(color4Loc, color4[0], color4[1], color4[2], color4[3]);

    color5Loc = glGetUniformLocation(program, "color5");
    glUniform4f(color5Loc, color5[0], color5[1], color5[2], color5[3]);

    color6Loc = glGetUniformLocation(program, "color6");
    glUniform4f(color6Loc, color6[0], color6[1], color6[2], color6[3]);

    color7Loc = glGetUniformLocation(program, "color7");
    glUniform4f(color7Loc, color7[1], color7[1], color7[2], color7[3]);

    color8Loc = glGetUniformLocation(program, "color8");
    glUniform4f(color8Loc, color2[1], color8[1], color8[2], color8[3]);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}