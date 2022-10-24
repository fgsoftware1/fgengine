#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../engine/include/GLShader.hpp"

float angle = 0.0;
const int triangle = 1;

void drawCube(float size)
{
    glBegin(GL_QUADS);
        //front face
        glColor3f(1.0,0.0,0.0);
        glVertex3f(size/2,size/2,size/2);
        glVertex3f(-size/2,size/2,size/2);
        glVertex3f(-size/2,-size/2,size/2);
        glVertex3f(size/2,-size/2,size/2);
        //left face
        glColor3f(0.0,1.0,0.0);
        glVertex3f(-size/2,size/2,size/2);
        glVertex3f(-size/2,-size/2,size/2);
        glVertex3f(-size/2,-size/2,-size/2);
        glVertex3f(-size/2,size/2,-size/2);
        //back face
        glColor3f(0.0,0.0,1.0);
        glVertex3f(size/2,size/2,-size/2);
        glVertex3f(-size/2,size/2,-size/2);
        glVertex3f(-size/2,-size/2,-size/2);
        glVertex3f(size/2,-size/2,-size/2);
        //right face
        glColor3f(1.0,1.0,0.0);
        glVertex3f(size/2,size/2,size/2);
        glVertex3f(size/2,-size/2,size/2);
        glVertex3f(size/2,-size/2,-size/2);
        glVertex3f(size/2,size/2,-size/2);
        //top face
        glColor3f(1.0,0.0,1.0);
        glVertex3f(size/2,size/2,size/2);
        glVertex3f(-size/2,size/2,size/2);
        glVertex3f(-size/2,size/2,-size/2);
        glVertex3f(size/2,size/2,-size/2);
        // bottom face
        glColor3f(0.0,1.0,1.0);
        glVertex3f(size/2,-size/2,size/2);
        glVertex3f(-size/2,-size/2,size/2);
        glVertex3f(-size/2,-size/2,-size/2);
        glVertex3f(size/2,-size/2,-size/2);
    glEnd();
}

void init()
{
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-5.0);
    glRotatef(angle,1.0,1.0,1.0);
    drawCube(1.0);
}

int window()
{
    if(!glfwInit())
    {
        return -1;
    }

    auto gameWindow = glfwCreateWindow(1366, 768, "fgeditor", NULL, NULL);
    if(!gameWindow)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(gameWindow);

    while(!glfwWindowShouldClose(gameWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        display();
        glfwSwapBuffers(gameWindow);
    }

    glfwTerminate();
    return 0;
}

int main(int argc, char *argv[])
{
    GLuint program = LoadShader("../assets/shaders/shader.vert", "../assets/shaders/shader.frag");

    window();
    glUseProgram(program);

    return 0;
}
