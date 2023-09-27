#include <iostream>
#include <cmath>
#include <vector>
#include <GL/freeglut.h>
#include "../mygllib/gl2d.h"


const float PI = 3.14159;

float cx = 200.0f;
float cy = 202.0f;
float rs = 0.0;
float re = 2 * PI;
float rx = 20.0f;
float ry = 100.0f;
float dt = 1.0f;
float da = PI / 180.0 / 2.0;

struct point
{
    float x;
    float y;
};

void print_grid()
{

    glColor3f(0, 0, 0);
    float dr = mygllib::WIN_W / 20;
    for(int i = 1; i <= 20; ++i)
    {
        glBegin(GL_LINES);
        glVertex2f(i * dr, 0);
        glVertex2f(i * dr, mygllib::WIN_H);
        glEnd();
    }
    for(int i = 1; i <= 20; ++i)
    {
        glBegin(GL_LINES);
        glVertex2f(0, i * dr);
        glVertex2f(mygllib::WIN_W , i * dr);
        glEnd();
    }
}

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

void filled_arc(float cx, float cy, float r, int num_points,
                   float start_angle = 0.0f,
                   float end_angle = 2 * 3.14159)
{
    float theta = end_angle / float(num_points-1);
    float c = cosf(theta);
    float t = tanf(theta); 

    float x = r * cosf(start_angle);//we start at angle = 0 
    float y = r * sinf(start_angle); 

    glBegin(GL_POLYGON); 
    for(int i = 0; i < num_points; i++) 
    { 
        //apply radius and offset
        glVertex2f(x + cx, y + cy);//output vertex 

        float tx = -y;
        float ty =  x;

        x += tx * t;
        y += ty * t;

        x *= c;
        y *= c;

    } 
    // glBegin(GL_POLYGON);
    // glVertex2f(r*cos(start_angle)+x, r*sin(start_angle)+y);
    // for(float i = start_angle; i <= end_angle+(end_angle/num_points); i += end_angle/num_points)
    // {
    //     glVertex2f(r*cos(i)+x, r*sin(i)+y);
    // }    
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

void draw_red_bird(float x = 200, float y = 200 , float r = 100, int eye = 0, int mouth = 0)
{

    //feathers
    glColor3f(0, 0, 0);
    triangle({x + (r * -1.1f), y + (r * 0.45f)}, 
             {x + (r * -1.2f), y + (r * 0.28f)}, 
             {x + (r * -0.55f), y + (r * 0.1f)});
    triangle({x + (r * -1.5f), y + (r * 0.32f)}, 
             {x + (r * -1.58f) , y}, 
             {x + (r * -0.5f) , y});
    triangle({x + (r * -1.3f), y + (r * -0.05f)}, 
             {x + (r * -1.25f), y + (r * -0.35f)}, 
             {x + (r * -0.72f), y + (r * -0.05f)});
    glEnd();

    //main body
    glColor3f(0, 0, 0); // black
    Filled_Ellipse(x, y, r, r, 50);
    glColor3f(0.8, 0, 0); // red
    Filled_Ellipse(x, y, r * 0.96, r * 0.96, 50);
    
    //belly
    glColor3f(0.94, 0.90, 0.55); // tan
    filled_arc(x, y + (r * -1.35f), r, 30, 0.7678, 1.6054);
    filled_arc(x, y + (r * 0.043f), r, 30, 3.9088, 1.6054);
    
    //eyes 0 aka open
    if(eye == 0)
    {
        glColor3f(0, 0, 0);// black
        Filled_Ellipse(x, y + (r * 0.1f), r * 0.2f, r * 0.2f, 30);
        Filled_Ellipse(x + (r * 0.4f), y + (r * 0.1f), r * 0.2f, r * 0.2f, 30);
    
        glColor3f(1, 1, 1); // white
        Filled_Ellipse(x, y + (r * 0.1f), r * 0.17f, r * 0.17f, 30);
        Filled_Ellipse(x + (r * 0.4f), y + (r * 0.1f), r * 0.17f, r * 0.17f, 30);
    
        glColor3f(0, 0, 0); // black
        Filled_Ellipse(x + (r * 0.08f), y + (r * 0.1f), r * 0.05f, r * 0.05f, 30);
        Filled_Ellipse(x + (r * 0.32f), y + (r * 0.1f), r * 0.05f, r * 0.05f, 30);
    }
    else
    {
        glColor3f(0, 0, 0);// black
        Filled_Ellipse(x, y + (r * 0.1f), r * 0.2f, r * 0.2f, 30);
        Filled_Ellipse(x + (r * 0.4f), y + (r * 0.1f), r * 0.2f, r * 0.2f, 30);

        // glColor3f(0, 0, 1);
        glColor3f(0.8f, 0, 0);// eye lids
        filled_arc(x, y + (r * 0.11f), (r * 0.17f),  30, 0.0f, PI);
        filled_arc(x, y + (r * 0.09f), (r * 0.17f), 30, PI, PI);
        filled_arc(x + (r * 0.4f), y + (r * 0.11f), (r * 0.17f),  30, 0.0f, PI);
        filled_arc(x + (r * 0.4f), y + (r * 0.09f), (r * 0.17f), 30, PI, PI);

    }

    //eye Brows
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(x + (r * -0.2f), y + (r * 0.46f)); 
    glVertex2f(x + (r * -0.4f), y + (r * 0.3f)); 
    glVertex2f(x + (r * 0.2f), y + (r * 0.2f));
    glVertex2f(x + (r * 0.2f), y + (r * 0.3f));
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(x + (r * 0.7f), y + (r * 0.46f));
    glVertex2f(x + (r * 0.8f), y + (r * 0.3f));
    glVertex2f(x + (r * 0.2f), y + (r * 0.2f));
    glVertex2f(x + (r * 0.2f), y + (r * 0.3f));
    glEnd();
    //beak 0 aka closed
    if(mouth == 0)
    {
        glColor3f(0, 0, 0); // Black
        triangle({x, y + (r * -0.2f)}, 
                 {x + (r * 0.2f), y}, 
                 {x + (r * 0.85f), y + (r * -0.32f)});
        
        triangle({x, y + (r * -0.2f)}, 
                 {x + (r * 0.2f), y + (r * -0.4f)}, 
                 {x + (r * 0.85f), y + (r * -0.32f)});
        
        glColor3f(1, 0.55, 0); // Orange
        triangle({x + (r * 0.05f), y + (r * -0.18f)}, 
                 {x + (r * 0.2f), y + (r * -0.03f)}, 
                 {x + (r * 0.765f), y  + (r * -0.3f)});
        
        triangle({x + (r * 0.06f), y + (r * -0.22f)}, 
                 {x + (r * 0.2f), y + (r * -0.35f)}, 
                 {x + (r * 0.72f), y + (r * -0.31f)});
    }
    else
    {
        glColor3f(0, 0, 0); // Black
        triangle({x, y + (r * -0.2f)}, 
                 {x + (r * 0.2f), y}, 
                 {x + (r * 0.85f), y + (r * -0.32f)});
        
        triangle({x, y + (r * -0.2f)},
                 {x + (r * 0.18f), y + (r * -0.44f)},
                 {x + (r * 0.75f), y + (r * -0.44f)});

        glColor3f(1, 0.55, 0); // Orange
        triangle({x + (r * 0.05f), y + (r * -0.18f)}, 
                 {x + (r * 0.2f), y + (r * -0.03f)}, 
                 {x + (r * 0.765f), y  + (r * -0.3f)});

        triangle({x + (r * 0.05f), y + (r * -0.24f)},
                 {x + (r * 0.18f), y + (r * -0.42f)},
                 {x + (r * 0.68f), y + (r * -0.43f)});
        
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    draw_red_bird(200, 200, 100, 0, 1);
    print_grid();

    glutSwapBuffers();
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
    case 'r':
        ry -= dt;
        std::cout << '(' << cx << ", " << cy << ')' << " rx: " << rx << " ry: " << ry << std::endl;
        break;
    case 't':
        ry += dt;
        std::cout << '(' << cx << ", " << cy << ')' << " rx: " << rx << " ry: " << ry << std::endl;
        break;
    case 'o':
        rs -= PI / 180.0 / 2.0;
        std::cout << '(' << cx << ", " << cy << ')' << " rs: " << rs << " re: " << re << std::endl;
        break;
    case 'p':
        rs += da;
        std::cout << '(' << cx << ", " << cy << ')' << " rs: " << rs << " re: " << re << std::endl;
        break;
    case 'u':
        re -= da;
        std::cout << '(' << cx << ", " << cy << ')' << " rs: " << rs << " re: " << re << std::endl;
        break;
    case 'i':
        re += da;
        std::cout << '(' << cx << ", " << cy << ')' << " rs: " << rs << " re: " << re << std::endl;
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
