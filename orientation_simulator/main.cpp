#include <windows.h>
#include <GL\glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<bits/stdc++.h>
#include "SerialPort.h"

using namespace std;



/*Portname must contain these backslashes, and remember to
replace the following com port*/
char *port_name = "\\\\.\\COM4";

SerialPort arduino(port_name);

//String for incoming data
char incomingData[MAX_DATA_LENGTH];

int x_angle, z_angle;

 GLfloat xRotated, yRotated, zRotated;
void init(void)
{
glClearColor(0,0,0,0);

}

void DrawCube(void)
{

     glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
        glTranslatef(0.0,0.0,-10.5);
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);
  glBegin(GL_QUADS);        // Draw The Cube Using quads
    glColor3f(0.0f,1.0f,0.0f);    // Color Blue
    glVertex3f( 2.0f, 0.2f,-2.0f);    // Top Right Of The Quad (Top)
    glVertex3f(-2.0f, 0.2f,-2.0f);    // Top Left Of The Quad (Top)
    glVertex3f(-2.0f, 0.2f, 2.0f);    // Bottom Left Of The Quad (Top)
    glVertex3f( 2.0f, 0.2f, 2.0f);    // Bottom Right Of The Quad (Top)
    glColor3f(1.0f,0.5f,0.0f);    // Color Orange
    glVertex3f( 2.0f,-0.2f, 2.0f);    // Top Right Of The Quad (Bottom)
    glVertex3f(-2.0f,-0.2f, 2.0f);    // Top Left Of The Quad (Bottom)
    glVertex3f(-2.0f,-0.2f,-2.0f);    // Bottom Left Of The Quad (Bottom)
    glVertex3f( 2.0f,-0.2f,-2.0f);    // Bottom Right Of The Quad (Bottom)
    glColor3f(1.0f,0.0f,0.0f);    // Color Red
    glVertex3f( 2.0f, 0.2f, 2.0f);    // Top Right Of The Quad (Front)
    glVertex3f(-2.0f, 0.2f, 2.0f);    // Top Left Of The Quad (Front)
    glVertex3f(-2.0f,-0.2f, 2.0f);    // Bottom Left Of The Quad (Front)
    glVertex3f( 2.0f,-0.2f, 2.0f);    // Bottom Right Of The Quad (Front)
    glColor3f(0.0f,1.0f,0.0f);    // Color Green
    glVertex3f( 2.0f,-0.2f,-2.0f);    // Top Right Of The Quad (Back)
    glVertex3f(-2.0f,-0.2f,-2.0f);    // Top Left Of The Quad (Back)
    glVertex3f(-2.0f, 0.2f,-2.0f);    // Bottom Left Of The Quad (Back)
    glVertex3f( 2.0f, 0.2f,-2.0f);    // Bottom Right Of The Quad (Back)
    glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    glVertex3f(-2.0f, 0.2f, 2.0f);    // Top Right Of The Quad (Left)
    glVertex3f(-2.0f, 0.2f,-2.0f);    // Top Left Of The Quad (Left)
    glVertex3f(-2.0f,-0.2f,-2.0f);    // Bottom Left Of The Quad (Left)
    glVertex3f(-2.0f,-0.2f, 2.0f);    // Bottom Right Of The Quad (Left)
    glColor3f(1.0f,0.0f,1.0f);    // Color Violet
    glVertex3f( 2.0f, 0.2f,-2.0f);    // Top Right Of The Quad (Right)
    glVertex3f( 2.0f, 0.2f, 2.0f);    // Top Left Of The Quad (Right)
    glVertex3f( 2.0f,-0.2f, 2.0f);    // Bottom Left Of The Quad (Right)
    glVertex3f( 2.0f,-0.2f,-2.0f);    // Bottom Right Of The Quad (Right)
  glEnd();            // End Drawing The Cube
glFlush();
}


void animation(void)
{

    //Check if data has been read or not
    int read_result = arduino.readSerialPort(incomingData, MAX_DATA_LENGTH);

        stringstream iss(incomingData);

    iss >> x_angle;
    iss >> z_angle;
    cout<<"x_angle = "<<x_angle-188<<endl<<"z_angle = "<<z_angle-192<<endl; //printing the angles made with axes
     //zRotated = 0.9*zRotated+0.1*(188-x_angle); // adding low pass filter
     //xRotated = 0.9*xRotated+0.1*(192-z_angle); // adding low pass filter
     zRotated += 0.9;
     xRotated += 0.9;
Sleep(20);



 DrawCube();
}


void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0



    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}



int main(int argc, char** argv){

glutInit(&argc, argv);
//we initizlilze the glut. functions
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowPosition(100, 100);
glutCreateWindow(argv[0]);


  if (arduino.isConnected()) cout << "Connection Established" << endl;
  else cout << "ERROR, check port name";

    init();
glutDisplayFunc(DrawCube);
glutReshapeFunc(reshape);
//Set the function for the animation.
glutIdleFunc(animation);
glutMainLoop();


return 0;
}                 /* glut_h */
