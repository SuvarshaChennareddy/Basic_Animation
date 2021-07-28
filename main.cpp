#include <iostream>
#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include "SOIL.h"
using namespace std;
GLuint ID;
GLfloat angle = -5;
float x_position = -20.0f;
float height = 4.0f;
float velocity = 0.25f;
boolean rot = true;
int iw = 100;
int ih = 100;
float posy = 2; float nposy = -2;
float sizee = 0.1f;
GLuint t;
GLuint image;

GLuint loadTex(const char* texname){
    GLuint texture = SOIL_load_OGL_texture
                    (
                        texname,
                        SOIL_LOAD_AUTO,
                        SOIL_CREATE_NEW_ID,
                        SOIL_FLAG_INVERT_Y

                    );

    if( 0 == texture )
    {
        cout <<  SOIL_last_result() << endl;
    }

    //glBindTexture(GL_TEXTURE_2D, texture);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return texture;
}

void init(){
    glewInit();
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    /*image = SOIL_load_image("pheonix.png",&iw, &ih, NULL, SOIL_LOAD_RGBA);*/
    image = loadTex("pheonix.png");
}

void display(){

    //glColor4f(1.0f,0.0f,0.0f, 0.0f);
    //glLoadIdentity();
    glShadeModel(GL_FLAT);
    glClear(GL_COLOR_BUFFER_BIT);
    //glLoadIdentity();
    //glEnable(GL_VERTEX_ARRAY);

//glEnable(GL_DEPTH_TEST);
    glPushMatrix();
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(1.0f,0.0f,0.0f);
    glTranslatef(x_position, (posy-height/2), 0);
    glRotatef(angle,0,1,0);
    glScalef(sizee, sizee, sizee);
    glTranslatef(-x_position, -(nposy+height/2), 0);
    float data[][3] = {
    {x_position, posy, 0},{x_position+height, posy, 0},{x_position+height, nposy, 0}, {x_position, nposy, 0},
    {x_position, posy, 5},{x_position+height, posy, 5},{x_position+height, nposy, 5}, {x_position, nposy, 5},
    {x_position, posy, 10},{x_position+height, posy, 10},{x_position+height, nposy, 10}, {x_position, nposy, 10}};
    glGenBuffers(1,&ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glVertexPointer(3, GL_FLOAT, 3*sizeof(float), 0);
    glDrawArrays(GL_QUADS,0,12);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
    //glutSwapBuffers();
    glDeleteBuffers(1, &ID);
    //glEnable(GL_DEPTH_TEST);
/*
    glGenTextures(1, &t);
    glBindTexture(GL_TEXTURE_2D, t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
    if (image){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei) &iw, (GLsizei) &ih, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        cout << SOIL_last_result() << endl;
        int i = 9/0;
    }

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
*/

    //glClear(GL_COLOR_BUFFER_BIT);

   //glGenTextures(1, &image);
    // Front side brick wall
    //glShadeModel(GL_FLAT);
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        //glClear(GL_COLOR_BUFFER_BIT);
        //glColor4f(0.5f,0.5f,0.5f, 0.5f);

        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, image);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTranslatef(x_position, (10-height/2), 0);
        glRotatef(angle,0,0,10);
        glTranslatef(-x_position, -(5+height/2), 0);
        glBegin(GL_POLYGON);
            glTexCoord2f(0,0);  glVertex2f(x_position,5);
            glTexCoord2f(1,0);  glVertex2f(x_position+height,5);
            glTexCoord2f(1,1); glVertex2f(x_position+height,10);
            glTexCoord2f(0,1);  glVertex2f(x_position,10);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glutSwapBuffers();
    if (rot){
        angle +=5;
        rot = false;
    }
    glDeleteBuffers(1, &image);
    //glEnableClientState(GL_VERTEX_ARRAY);

}

void reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20, 20, -20, 20, -20, 20);
/*   glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();*/
}

void timer(int){

    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
    x_position += velocity;
    sizee +=0.05;
    if(sizee >= 3){
        sizee = 0.1f;
    }
    if((x_position < -20) || (x_position > 16)) velocity*=-1;

}

    void mySpecialFunc(int key, int x, int y){
    switch (key) {
    case GLUT_KEY_RIGHT:
        x_position+=1;

        break;
    case GLUT_KEY_LEFT:
        x_position-=1;

        break;
    case GLUT_KEY_UP:
        posy+=1;
        nposy+=1;

        break;
    case GLUT_KEY_DOWN:
        posy-=1;
        nposy-=1;

        break;
    case GLUT_KEY_PAGE_UP:
        rot = true;

        break;
    }
    glutPostRedisplay();
}
int main(int argc, char**argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(300,300);
    glutCreateWindow("Simple Application");

    //glEnable(GL_DEPTH_TEST);
    glutSpecialFunc(mySpecialFunc);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,timer,0);
    init();
    glutMainLoop();
    return 0;

}
/*
float xpos1 = -0.5f, xpos2 = -1.0f, xpos3  = -1.5f;
float ypos1 = 0.5f, ypos2 = 1.5f, ypos3 = 0.5f;
float midx = (xpos1 + xpos2 + xpos3)/3;
float midy = (ypos1 + ypos2 + ypos3)/3;
float interval = 1.0f / 10.0f;
float anglee = interval;
float* cord1;
float* cord2;
float* cord3;
float* nextPoint(float angle, float midX, float midY, float xx, float yy) {
    float x = xx;
    float y = yy;
    float xPos;
    float yPos;
    if (midX == NULL) midX = 0;
    if (midY == NULL) midY = 0;
	// rotate about (0,0)
    float cosa = cos(angle);
	float sina = sin(angle);
	if (midX == 0 && midY == 0) {
		xPos = x * cosa + y * sina;
		yPos = -x * sina + y * cosa;
	} else {
		xPos = midX + (x - midX) * cosa + (y - midY) * sina;
		yPos = midY - (x - midX) * sina + (y - midY) * cosa;
	}
	x = xPos;
	y = yPos;
	float* r = new float[2];
	r[0] = x;
	r[1] = y;
	return r;
}
*/


/*
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "SOIL.h"
#include <stdio.h>

float _angle = 0.0;
GLuint _textureBrick;

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void renderScene(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);

    // Front side brick wall
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureBrick);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(-50.0,2.0,0.1);  glVertex3f(-50,0,1);
            glTexCoord3f(50.0,2.0,0.1);  glVertex3f(50,0,1);
            glTexCoord3f(50.0,0.0,0.1);  glVertex3f(50,-1.5,1);
            glTexCoord3f(-50.0,0.0,0.1);  glVertex3f(-50,-1.5,1);
        glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void mySpecialFunc(int key, int x, int y){
    switch (key) {
    case GLUT_KEY_RIGHT:
        _angle += 1;
        if (_angle > 360) _angle = 0.0;
        break;
    case GLUT_KEY_LEFT:
        _angle -= 1;
        if (_angle > 360) _angle = 0.0;
        break;
    }
    glutPostRedisplay();
}

GLuint loadTex(const char* texname)
{
    GLuint texture = SOIL_load_OGL_texture
                    (
                        texname,
                        SOIL_LOAD_AUTO,
                        SOIL_CREATE_NEW_ID,
                        SOIL_FLAG_INVERT_Y

                    );

    if( 0 == texture )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }

    //glBindTexture(GL_TEXTURE_2D, texture);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return texture;
}

void Initialize() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

    //_textureFloor = loadTex("C:\\Users\\Mikle\\OneDrive\\Uni work\\Second Year\\Projects\\3D-House-using-OpenGL-and-C--master\\court.png");

    _textureBrick = loadTex("pheonix.png");
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(600,600);
    glutCreateWindow("Textured House");
    glEnable(GL_DEPTH_TEST);

    glutReshapeFunc(resize);
    glutSpecialFunc(mySpecialFunc);
    glutDisplayFunc(renderScene);
    Initialize();

    glutMainLoop();

    return 0;
}
*/
