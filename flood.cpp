#include <iostream>
#include <GL/glut.h>
using namespace std;

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // white background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
}

void flood_it(int x, int y, float* fillColor, float* bc) {
    float color[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);

    // Compare with boundary and fill color
    if ((color[0] != bc[0] || color[1] != bc[1] || color[2] != bc[2]) &&
        (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2])) {

        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        // Recursive 8-direction fill
        flood_it(x + 1, y, fillColor, bc);
        flood_it(x - 1, y, fillColor, bc);
        flood_it(x, y + 1, fillColor, bc);
        flood_it(x, y - 1, fillColor, bc);
        flood_it(x - 1, y - 1, fillColor, bc);
        flood_it(x - 1, y + 1, fillColor, bc);
        flood_it(x + 1, y - 1, fillColor, bc);
        flood_it(x + 1, y + 1, fillColor, bc);
    }
}

void mouse(int btn, int state, int x, int y) {
    y = 480 - y; // Flip y-axis
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float bCol[] = {1, 0, 0};     // Boundary color (red)
        float color[] = {0, 0, 1};    // Fill color (blue)
        flood_it(x, y, color, bCol);
    }
}

void world() {
    glLineWidth(3);
    glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw triangle boundary in red
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(150, 100);
    glVertex2i(300, 300);
    glVertex2i(450, 100);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Flood Fill Algorithm");
    glutDisplayFunc(world);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return 0;
}
