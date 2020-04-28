# integer-sequence-polyhedron
A C++ program using OpenGL/Glut to help me visualize and find 
patterns in sequences of 2D tables of integers.

### OpenGL Instructions
I use Windows. I don't know much about how to put the libraries
 in the correct directories, so I'll just tell you what I have.
 You can see in the CMakeLists file that things need
to be put in C:/Program Files/Common Files. In that folder, I have
a folder called freeglut which contains two folders, include and
lib. So you need to download those from somewhere. Also, put
freeglut.dll from the freeglut bin folder into your 
cmake-build-debug folder. Finally, this project also uses glm.
I might get rid of that, because I don't think I'm really using
any of its features. But I just put a folder called glm into the
same C:/Program Files/Common Files folder, and that works because
the CMakeLists already references that location.

### Text File Instructions
The program reads in data from text files. Your data needs to be
a sequence of 2D tables of non-negative integers. Each line of
the text file is a single row of a table. Each value is separated
by a comma. At the end of each table, put a blank line before
starting the next table. Here's an example:

1,2,3<br/>4,5,6

10,20,30,40<br/>50,60,70,80<br/>90,100,110,120

This would create two tables, where the front table is 2x3 and 
the back table is 3x4.

### Controls
The polyhedron can be moved using w and s for forwards and backwards,
a and d for left and right, and r and c for up and down. It can be
rotated around the different axes by holding 1,2, or 3. You can
also rotate by click-dragging. Left click rotates around the x and
y axes, and right click rotates around the z-axis (assuming the 
z-axis is coming out toward you). Pressing q resets the rotating
so it is facing you again.  There is a control pad in the bottom
left corner you can click which determine the alignment of the
tables and rows relative to each other. Clicking those buttons
just moves the cubes around. Finally, you can click on the cubes.
Click on a cube to highlight it, and click on a second cube to
highlight the line containing both cubes. Click anywhere to
unhighlight the line.

![](/screenshots/polyhedron1.png)
![](/screenshots/polyhedron2.png)
![](/screenshots/polyhedron3.png)
![](/screenshots/polyhedron4.png)
![](/screenshots/polyhedron5.png)
![](/screenshots/polyhedron6.png)
![](/screenshots/polyhedron7.png)
![](/screenshots/polyhedron8.png)
