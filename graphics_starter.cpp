// The code in this file is based on code provided by Lisa Dion
// in a 3D graphics tutorial.

#include "graphics.h"
#include "cube.h"
#include <cmath>
#include "numberCubePolyhedron.h"
#include <iostream>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;

GLdouble width, height;
int wd;
glm::vec3 cameraLocation;
glm::vec3 cameraPosition;
glm::vec3 up;
glm::vec3 target;
glm::vec3 mostRecentClick; // debug
NumberCubePolyhedron ncp;
NumberCubeRow c;

// Mouse variables
int prevMouseX, prevMouseY;  // need prev locations for click/drag
boolean leftDown, rightDown; // which button is held down

// Prompts the user to enter a filename. If the filename is not
// valid or does not end with .txt, then "triangles.txt" is returned.
std::string getFilename();

// Given a string that consists of positive integers separated by commas, this
// parses it into a vector of ints.
std::vector<int> stringToVector(std::string line);

std::vector<vector<vector<int>>> readFromFile(std::string filename);

glm::vec3 convertPointToRay(int x, int y);

void init()
{
    width = 1000;
    height = 600;
    cameraLocation = {400,300,600};
    up = {0,1,0};
    target = {0,0,0};
    mostRecentClick = {0,0,0};
    /*glm::mat4 View = glm::lookAt(
            glm::vec3(2,3,6), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );*/
    glm::mat4 ViewMatrix = glm::translate( glm::vec3(-cameraLocation.x, -cameraLocation.y ,-cameraLocation.z));
    cameraPosition = glm::inverse(ViewMatrix) * glm::vec4{0, 0, 0, 1};
    //cameraPosition = {200, 300, 600};
    cout << cameraPosition.x << endl;
    cout << cameraPosition.y << endl;
    cout << cameraPosition.z << endl;
    prevMouseX = 0;
    prevMouseY = 0;
    leftDown = false;
    rightDown = false;
    std::string filename = getFilename();
    std::vector<vector<vector<int>>> data = readFromFile(filename);
    point p = {0,0,0};
    c = NumberCubeRow({0,0,0},{1,0,1,.5},{1,0,0,.5},p, 50, {1,1,1,1},{.4,.6,1,1},{1,.4,.6,1},{10,11});
    ncp = NumberCubePolyhedron({0,0,0}, {0,.2,.8,.5},
            {1, 0, 0, .5}, 50, {1,1,1,1},
            {0.4,0.6,1,1}, {1, 0.4, 0.6, 1}, data);
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
    //glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluLookAt(cameraLocation.x, cameraLocation.y, cameraLocation.z,  // eye position
              target.x, target.y, target.z,  // center position (not gaze direction)
              up.x, up.y, up.z); // up vector


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
    //glOrtho(-width/2, width/2, -height/2, height/2, -width, width);
    //glFrustum(	 -200,200,-200,200,100,500);
    gluPerspective(45, width/height, 50, 2000);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear the color buffer with current clearing color
    
    glEnable(GL_DEPTH);
    glPolygonMode(GL_FRONT, GL_FILL);

    /*glDisable(GL_CULL_FACE);
    glBegin(GL_QUADS);
    glColor4f(.5,.2,.7,1);
    glVertex3f(cameraPosition.x + 5, cameraPosition.y + 5, cameraPosition.z);
    glVertex3f(cameraPosition.x + 5, cameraPosition.y - 5, cameraPosition.z);
    glVertex3f(cameraPosition.x - 5, cameraPosition.y - 5, cameraPosition.z);
    glVertex3f(cameraPosition.x - 5, cameraPosition.y + 5, cameraPosition.z);
    glEnd();
    glColor4f(0,1,0,.4);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(cameraPosition.x + 5, cameraPosition.y + 5, cameraPosition.z);
    glVertex3f(cameraPosition.x + mostRecentClick.x*1000, cameraPosition.y + mostRecentClick.y*1000,
            cameraPosition.z + mostRecentClick.z*1000);
    glVertex3f(cameraPosition.x + 5, cameraPosition.y - 5, cameraPosition.z);
    glVertex3f(cameraPosition.x + mostRecentClick.x*1000, cameraPosition.y + mostRecentClick.y*1000,
               cameraPosition.z + mostRecentClick.z*1000);
    glVertex3f(cameraPosition.x - 5, cameraPosition.y - 5, cameraPosition.z);
    glVertex3f(cameraPosition.x + mostRecentClick.x*1000, cameraPosition.y + mostRecentClick.y*1000,
               cameraPosition.z + mostRecentClick.z*1000);
    glVertex3f(cameraPosition.x - 5, cameraPosition.y + 5, cameraPosition.z);
    glVertex3f(cameraPosition.x + mostRecentClick.x*1000, cameraPosition.y + mostRecentClick.y*1000,
               cameraPosition.z + mostRecentClick.z*1000);
    glEnd();*/
    
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

    // If it's the left mouse button
    if(leftDown)
    {
        // Left/Right means rotate around y-axis
        double theta_y = PI/100 * cos(theta);
        // Up/Down means rotate around x-axis
        double theta_x = PI/100 * sin(theta);
        ncp.rotate(theta_x, -theta_y, 0);
    }
    if(rightDown)
    {
        double theta_y = PI/100 * cos(theta)*0;
        double theta_z = PI/100 * sin(theta);
        if(prevMouseX < width/2)
        {
            ncp.rotate(0, -theta_y, (x/abs(x))*theta_z);
        }
        else
        {
            ncp.rotate(0, -theta_y, -(x/abs(x))*theta_z);
        }
    }


    prevMouseX = x;
    prevMouseY = y;
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_UP)
        {
            leftDown = false;
            glm::vec3 ray = convertPointToRay(x,y);
            mostRecentClick = ray;
            /*std::cout << "x: " << x << std::endl;
            std::cout << "y: " << y << std::endl;
            std::cout << ray.x << std::endl;
            std::cout << ray.y << std::endl;
            std::cout << ray.z << std::endl;*/
            /*cout << mostRecentClick.x*10000 << endl;
            cout << mostRecentClick.y*10000 << endl;
            cout << mostRecentClick.z*10000 << endl;
            cout << cameraPosition.x << endl;
            cout << cameraPosition.y << endl;
            cout << cameraPosition.z << endl;*/
            ncp.getNumberCubeFromClick(ray, cameraPosition);
        }
        else
        {
            leftDown = true;
        }
    }
    if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_UP)
        {
            rightDown = false;
        }
        else
        {
            rightDown = true;
        }
    }
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
    glutInitWindowPosition(200, 75); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Integer Sequence Polyhedron" /* title */ );
    
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

glm::vec3 convertPointToRay(int x, int y)
{
    /*glm::vec3 normalizedDeviceCoordinates = glm::vec3(2.0*x / width - 1, 1 - 2.0*y/height, 1);
    glm::vec4 homogeneousClipCoordinates = {normalizedDeviceCoordinates.x, normalizedDeviceCoordinates.y, -1, 1};
    glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(45.0f),
                                                  (float) width / (float)height, 100.0f, 1000.0f);
    //glm::mat4 ProjectionMatrix = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f);
    glm::vec4 eyeCoordinates = glm::inverse(ProjectionMatrix) * homogeneousClipCoordinates;
    eyeCoordinates = glm::vec4(eyeCoordinates.x, eyeCoordinates.y, -1.0, 0.0);
    glm::mat4 ViewMatrix = glm::translate( glm::vec3(-cameraLocation.x, -cameraLocation.y ,-cameraLocation.z));
    glm::vec3 worldCoordinates = glm::inverse(ViewMatrix) * eyeCoordinates;
    worldCoordinates = glm::normalize(worldCoordinates);
    return worldCoordinates;*/

    // Code from https://www.bfilipek.com/2012/06/select-mouse-opengl.html
    GLdouble m_start[3];
    GLdouble m_end[3];
    double matModelView[16], matProjection[16];
    int viewport[4];
    glGetDoublev( GL_MODELVIEW_MATRIX, matModelView );
    glGetDoublev( GL_PROJECTION_MATRIX, matProjection );
    glGetIntegerv( GL_VIEWPORT, viewport );
    double winX = (double)x;
    double winY = viewport[3] - (double)y;
    gluUnProject(winX, winY, 0.0, matModelView, matProjection,
                 viewport, &m_start[0], &m_start[1], &m_start[2]);
    gluUnProject(winX, winY, 1.0, matModelView, matProjection,
                 viewport, &m_end[0], &m_end[1], &m_end[2]);
    return glm::normalize(glm::vec3{m_end[0] - m_start[0], m_end[1] - m_start[1], m_end[2] - m_start[2]});
}