// 190001016
// Garvit Galgat
// header file with helper functions

#include <math.h>

/**
 * @brief initialize window with given parameters
 *
 * @param X width of window to create
 * @param Y height of window to create
 * @param windowTitle title for the window
 */
void initializeWindow(int X, int Y, char* windowTitle) {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(X, Y);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(windowTitle);
    gluOrtho2D(0, X, 0, Y);
}

/**
 * @brief draws a circle with given center and radius
 *
 * @param centerX X coordinate of center
 * @param centerY Y coordinate of center
 * @param radius radius of the given circle
 * @param fill fill color inside the created circle / if true circle will have a black border
 */
void drawCircle(GLfloat centerX, GLfloat centerY, GLfloat radius, bool fill = false) {
    if (fill)
        glBegin(GL_POLYGON);
    else
        glBegin(GL_LINE_LOOP);

    GLfloat angle, x, y;
    for (angle = 0.0f; angle <= (2.0f * M_PI); angle += 0.01f) {
        x = radius * sin(angle) + centerX;
        y = radius * cos(angle) + centerY;
        glVertex2f(x, y);
    }
    glEnd();

    // circle border
    if (fill) {
        glColor3f(0, 0, 0);
        drawCircle(centerX, centerY, radius, false);
    }
}

/**
 * @brief draws and equilateral triangle
 *
 * @param startX X coordinate for the bottom left coordinate of the circle
 * @param startY Y coordinate for the bottom left coordinate of the circle
 * @param sideLength length of side of the triangle
 * @param fill fill color inside the created triangle / if true triangle will have a black border
 */
void drawEquilateralTriangle(GLfloat startX, GLfloat startY, GLfloat sideLength, bool fill = false) {
    if (fill)
        glBegin(GL_POLYGON);
    else
        glBegin(GL_LINE_LOOP);

    glVertex2f(startX, startY);
    glVertex2f(startX + sideLength * cos(M_PI / 3), startY + sideLength * sin(M_PI / 6));
    glVertex2f(startX + sideLength, startY);

    glEnd();

    // draw triangle border
    if (fill) {
        glColor3f(0, 0, 0);
        drawEquilateralTriangle(startX, startY, sideLength, false);
    }
}

/**
 * @brief draws a rectangle with given width and height
 *
 * @param startX X coordinate for the bottom left coordinate of the rectangle
 * @param startY Y coordinate for the bottom left coordinate of the rectangle
 * @param width width of the rectangle to create
 * @param height height of the rectangle to create
 * @param fill fill color inside the created rectangle / if true rectangle will have a black border
 */
void drawRectangle(GLfloat startX, GLfloat startY, GLfloat width, GLfloat height, bool fill = false) {
    if (fill)
        glBegin(GL_POLYGON);
    else
        glBegin(GL_LINE_LOOP);

    glVertex2f(startX, startY);
    glVertex2f(startX + width, startY);
    glVertex2f(startX + width, startY + height);
    glVertex2f(startX, startY + height);
    glEnd();

    // draw rectangle border
    if (fill) {
        glColor3f(0, 0, 0);
        drawRectangle(startX, startY, width, height, false);
    }
}

/**
 * @brief draw a line using starting and ending coordinates
 *
 * @param startX X coordinate of starting point
 * @param startY Y coordinate of starting point
 * @param endX X coordinate of ending point
 * @param endY Y coordinate of ending point
 */
void drawLine(GLfloat startX, GLfloat startY, GLfloat endX, GLfloat endY) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(startX, startY);
    glVertex2f(endX, endY);
    glEnd();
}

/**
 * @brief draw a line using starting coordiate and slope
 *
 * @param startX X coordinate of starting point
 * @param startY Y coordinate of starting point
 * @param length length of the line to create
 * @param theta slope of line
 */
void drawLineUsingSlope(GLfloat startX, GLfloat startY, GLfloat length, GLfloat theta) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(startX, startY);
    glVertex2f(startX + length * cos(theta), startY + length * sin(theta));
    glEnd();
}