#include <iostream>
#include <cmath>
#include <vector>
#include <GL/freeglut.h>
#include "../mygllib/gl2d.h"


float cx = 200.0f;
float cy = 198.0f;
float rx = 50.0f;
float ry = 50.0f;
float dt = 0.1f;

struct point
{
    float x;
    float y;
};


void regular_polygon(float x, float y, float r, int num_points)
{
    glBegin(GL_LINE_LOOP);
    // glColor3f(color_r, color_g, color_b);
    for(float i = 0; i < 360; i += 360/num_points)
    {
        float rad = i * 0.01745;
        glVertex2f(r*cos(rad)+x, r*sin(rad)+y);
    }
    glEnd();
}

void circle(float x, float y, float r, int num_points=-1)
{
    
    if(num_points == -1)
        regular_polygon(x, y, r, 30);
    else 
        regular_polygon(x, y, r, num_points);
}

void arc(float x, float y, float r, int num_points, float line_width,
         float start_angle = 0.0f,
         float end_angle = 2 * 3.14159)
{
    glBegin(GL_LINE_STRIP);
    glLineWidth(line_width);
    glVertex2f(r*cos(start_angle)+x, r*sin(start_angle)+y);
 
    for(float i = start_angle; i <= end_angle; i += end_angle/num_points)
    {
        glVertex2f(r*cos(i)+x, r*sin(i)+y);
    }    
    glEnd();
}

void filled_arc(float x, float y, float r, int num_points,
                   float start_angle = 0.0f,
                   float end_angle = 2 * 3.14159)
{
    glBegin(GL_POLYGON);

    glVertex2f(r*cos(start_angle)+x, r*sin(start_angle)+y);
    for(float i = start_angle; i <= end_angle+(end_angle/num_points); i += end_angle/num_points)
    {
        glVertex2f(r*cos(i)+x, r*sin(i)+y);
    }    
    glEnd();
}

void Ellipse(float cx, float cy, float rx, float ry, int num_segments) 
{ 
    float theta = 2 * 3.1415926 / float(num_segments); 
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = 1;//we start at angle = 0 
    float y = 0; 

    glBegin(GL_LINE_LOOP); 
    for(int i = 0; i < num_segments; i++) 
    { 
        //apply radius and offset
        glVertex2f(x * rx + cx, y * ry + cy);//output vertex 

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    } 
    glEnd(); 
}

void Filled_Ellipse(float cx, float cy, float rx, float ry, int num_segments) 
{ 
    float theta = 2 * 3.1415926 / float(num_segments); 
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = 1;//we start at angle = 0 
    float y = 0; 

    glBegin(GL_POLYGON); 
    for(int i = 0; i < num_segments; i++) 
    { 
        //apply radius and offset
        glVertex2f(x * rx + cx, y * ry + cy);//output vertex 

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    } 
    glEnd(); 
}

void triangle(point p1, point p2, point p3)
{
    glBegin(GL_TRIANGLES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p3.x, p3.y);

    glEnd();
}

void star(float x, float y, float r, int num_points = 5)
{
    glBegin(GL_LINE_LOOP);
    float rad = 0;
    glVertex2f(r*cos(rad)+x, r*sin(rad)+y);
    for(int i = 0; i < num_points-1; ++i)
    {
        //360 degree is 6.282 rad
         rad += (4 *3.14159 )/(num_points);
         glVertex2f(r*cos(rad)+x, r*sin(rad)+y);
    }

    glEnd();
}

void fixedstar(float x, float y, float r, int num_points = 5)
{
    glBegin(GL_LINE_LOOP);
    float rad = 3.14159/2;
    glVertex2f(r*cos(rad)+x, r*sin(rad)+y);
    for(int i = 0; i < num_points-1; ++i)
    {
        //360 degree is 6.282 rad
         rad += (4 *3.14159 )/(num_points);
         glVertex2f(r*cos(rad)+x, r*sin(rad)+y);
    }

    glEnd();
}

void draw_red_bird(float x, float y, float r, int eye, int mouth)
{
    // glBegin();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    //main body
    glColor3f(0, 0, 0);
    Filled_Ellipse(200, 200, 100, 100, 50);
    glColor3f(1, 0, 0);
    Filled_Ellipse(200, 200, 98, 98, 50);
    
    //belly
    glColor3f(0, 0, 0); 
    Filled_Ellipse(200, 126, 65, 24, 50);
    glColor3f(0.94, 0.90, 0.55);
    Filled_Ellipse(200, 126, 63, 22, 50);
    
    //eyes
    glColor3f(0, 0, 0);
    Filled_Ellipse(200, 210, 20, 20, 30);
    Filled_Ellipse(240, 210, 20, 20, 30);
    glColor3f(1, 1, 1);
    Filled_Ellipse(200, 210, 18, 18, 30);
    Filled_Ellipse(240, 210, 18, 18, 30);
    glColor3f(0, 0, 0);
    Filled_Ellipse(208, 210, 5, 5, 30);
    Filled_Ellipse(232, 210, 5, 5, 30);
    
    //beak
    glColor3f(0, 0, 0);
    triangle({200, 180}, {220, 200}, {260, 170});
    triangle({200, 180}, {220, 160}, {260, 170});
    glColor3f(1, 0.55, 0);
    triangle({203, 181}, {220, 197}, {254, 172.2});
    
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        cy += dt;
        std::cout << '(' << cx << ", " << cy << ')' << " rx: " << rx << " ry: " << ry << std::endl;
        break;
    case 's':
        cy -= dt;
        std::cout << '(' << cx << ", " << cy << ')' << " rx: " << rx << " ry: " << ry << std::endl; 
        break;
    case 'a':
        cx -= dt;
        std::cout << '(' << cx << ", " << cy << ')' << " rx: " << rx << " ry: " << ry << std::endl;
        break;
    case 'd':
        cx += dt;
        std::cout << '(' << cx << ", " << cy << ')' << " rx: " << rx << " ry: " << ry << std::endl;
        break;
    
    case 'q':
        rx -= dt;
        std::cout << '(' << cx << ", " << cy << ')' << " rx: " << rx << " ry: " << ry << std::endl;
        break;

    case 'e':
        rx += dt;
        std::cout << '(' << cx << ", " << cy << ')' << " rx: " << rx << " ry: " << ry << std::endl;
        break;

    case 'o':
        ry -= dt;
        std::cout << '(' << x << ", " << y << ')' << " rx: " << rx << " ry: " << ry << std::endl;
        break;
    case 'p':
        ry += dt;
        std::cout << '(' << x << ", " << y << ')' << " rx: " << rx << " ry: " << ry << std::endl;
        break;
    case '+':
        dt += 0.1;
        std::cout << dt << std::endl;
        break;
    case '-':
        if(dt != 0.1)
            dt -= 0.1;
        std::cout << dt << std::endl;
        break;  
    }
    glutPostRedisplay();
}

int main()
{
    mygllib::init2d(900, 900);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
