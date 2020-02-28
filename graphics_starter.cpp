// The code in this file is based on code provided by Lisa Dion
// in a 3D graphics tutorial.

#include "graphics.h"
#include "cube.h"
#include <cmath>
#include "digitalNumber.h"
#include "numberCube.h"
#include "numberCubeRow.h"
#include "numberCubeTable.h"
#include "numberCubePolyhedron.h"
#include <iostream>
#include <fstream>

using namespace std;

GLdouble width, height;
int wd;
NumberCubePolyhedron ncp;
int prevMouseX, prevMouseY;

// Prompts the user to enter a filename. If the filename is not
// valid or does not end with .txt, then "triangles.txt" is returned.
std::string getFilename();

// Given a string that consists of positive integers separated by commas, this
// parses it into a vector of ints.
std::vector<int> stringToVector(std::string line);

std::vector<vector<vector<int>>> readFromFile(std::string filename);

void init()
{
    width = 1000;
    height = 500;
    prevMouseX = 0;
    prevMouseY = 0;
    std::string filename = getFilename();
    std::vector<vector<vector<int>>> data = readFromFile(filename);
    ncp = NumberCubePolyhedron({0,0,0}, {0,.2,.8,.5}, {1,1,1,1}, 50, data, {0.4,0.6,1,1});
}

/* Initialize OpenGL Graphics */
void initGL()
{
    // Enable alpha transparency
    // Code from https://www.opengl.org/archives/resources/faq/technical/transparency.htm
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.0, 3.0, 6.0,  // eye position
              0.0, 0.0, 0.0,  // center position (not gaze direction)
              0.0, 1.0, 0.0); // up vector
}

void draw_axes()
{
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-width/2.0, 0.0, 0.0);
    glVertex3f(width/2.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, height/2.0, 0.0);
    glVertex3f(0.0, -height/2.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, width);
    glVertex3f(0.0, 0.0, -width);
    glEnd();
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display()
{

    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2, -width, width);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear the color buffer with current clearing color
    
    glEnable(GL_DEPTH);
    glPolygonMode(GL_FRONT, GL_FILL);
    
    /*
     * Draw here
     */
    draw_axes();

    glDisable(GL_CULL_FACE);
    //testNum.draw();

    glEnable(GL_CULL_FACE);
    //c.draw();
    //ncr.draw();
    ncp.draw();
    
    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27)
    {
        glutDestroyWindow(wd);
        exit(0);
    }

    switch(key)
    {
        // Rotating
        case '1': ncp.rotate(PI / 100.0, 0, 0);
            break;
        case '2': ncp.rotate(0, PI / 100.0, 0);
            break;
        case '3': ncp.rotate(0, 0, PI / 100.0);
            break;
        // Moving around
        case 'a': ncp.move(-5, 0, 0);
            break;
        case 'd': ncp.move(5, 0, 0);
            break;
        case 'w': ncp.move(0, 0, -5);
            break;
        case 's': ncp.move(0, 0, 5);
            break;
        case 'r': ncp.move(0, 5, 0);
            break;
        case 'c': ncp.move(0, -5, 0);
            break;
    }
    
    glutPostRedisplay();
}

void kbdS(int key, int x, int y)
{
    /*switch(key)
    {
        case GLUT_KEY_DOWN:
            
            break;
        case GLUT_KEY_LEFT:
            c.move(-5, 0, 0);
            break;
        case GLUT_KEY_RIGHT:
            c.move(5, 0, 0);
            break;
        case GLUT_KEY_UP:
            
            break;
    }*/
    
    glutPostRedisplay();
}

void cursor(int x, int y)
{
    
    glutPostRedisplay();
    prevMouseX = x;
    prevMouseY = y;
}

void clickDrag(int x, int y)
{
    int xDif = x - prevMouseX;
    int yDif = y - prevMouseY;
    double theta = atan2(yDif,xDif);
    // Left/Right means rotate around y-axis
    double theta_y = PI/100 * cos(theta);
    // Up/Down means rotate around x-axis
    double theta_x = PI/100 * sin(theta);
    ncp.rotate(theta_x, -theta_y, 0);

    prevMouseX = x;
    prevMouseY = y;
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y)
{
    
    glutPostRedisplay();
}

void timer(int dummy)
{

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{
    
    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(200, 150); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("3D Graphics!" /* title */ );
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // clicking and dragging
    glutMotionFunc(clickDrag);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, timer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}

std::string getFilename()
{
    std::string input;
    std::cout << "Enter the name of the text file containing the data." << std::endl;
    std::cout << "If you do not enter a valid filename, the default will be triangles.txt." << std::endl;
    std::cout << "See the ReadMe for details on how to format the text files." << std::endl;
    std::cout << "Filename: ";
    getline(std::cin, input);
    std::ifstream fIn;
    fIn.open(input);
    if(!fIn || input.substr(input.size() - 4) != ".txt")
    {
        input = "triangles.txt";
    }
    fIn.close();
    return input;
}

std::vector<int> stringToVector(std::string line)
{
    std::vector<int> output;
    std::string curInt;
    for(char c : line)
    {
        // If we are at the end of the current number
        if(c == ',')
        {
            if(!curInt.empty())
            {
                output.push_back(std::stoi(curInt));
                curInt = "";
            }
        }
        // Otherwise, add the digit to the number
        else if(c != ' ')
        {
            curInt += c;
        }
    }
    if(!curInt.empty())
    {
        output.push_back(std::stoi(curInt));
    }
    return output;
}

std::vector<vector<vector<int>>> readFromFile(std::string filename)
{
    std::vector<vector<vector<int>>> polyhedronVector;
    std::vector<vector<int>> currentTable;
    std::string currentLine;

    std::ifstream fIn;
    fIn.open(filename);
    while(fIn)
    {
        getline(fIn, currentLine);

        // If the line is blank, we have reached the end of this table
        if(currentLine.empty())
        {
            if(!currentTable.empty())
            {
                polyhedronVector.push_back(currentTable);
                currentTable = std::vector<vector<int>>();
            }
        }
        else if(fIn)
        {
            currentTable.push_back(stringToVector(currentLine));
        }
    }
    fIn.close();

    // The last table might not be ended with a blank line, because we
    // reached the end of the file
    if(!currentTable.empty())
    {
        polyhedronVector.push_back(currentTable);
    }
    return polyhedronVector;
}