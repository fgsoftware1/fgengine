#include "GL/glew.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include "../engine/include/GLShader.hpp"

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
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *screen;
    SDL_SetVideoMode(1366, 768, 8, SDL_SWSURFACE|SDL_OPENGL);

    bool running = true;
    const int FPS = 30;
    Uint32 start;
    SDL_Event event;

    init();
    while(running) {
        start = SDL_GetTicks();
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        display();
        SDL_GL_SwapBuffers();
        angle += 0.5;
        if(angle > 360)
            angle -= 360;
        if(1000/FPS > SDL_GetTicks()-start)
            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
    }
    SDL_Quit();
    return 0;
}

int main(int argc, char *argv[])
{
    //GLuint program = LoadShader("../assets/shaders/shader.vert", "../assets/shaders/shader.frag");

    window();
    //glUseProgram(program);

    return 0;
}
