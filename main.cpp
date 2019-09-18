#include<GL/gl.h>
#include<GL/glut.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>

int i,q;
int score = 0;


bool collide = false;
char buffer[10];

int paddleX = 100, paddleY = 50;
int stoneX[3], stoneY[3];
int ballX[4], ballY[4];
int divx = 250, divy = 4, movd;


void drawText(char ch[],int xpos, int ypos)//draw score/message on screen
{
    int numofchar = strlen(ch);
    glLoadIdentity ();
    glRasterPos2f( xpos, ypos);
    for (i = 0; i < numofchar; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[i]);
    }
}


void drawTextNum(char ch[],int numtext,int xpos, int ypos)//counting the score
{
    int len;
    int k;
    k = 0;
    len = numtext - strlen (ch);
    glLoadIdentity ();
    glRasterPos2f( xpos, ypos);
    for (i = 0; i <=numtext - 1; i++)
    {
        if ( i < len )
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'0');
        else
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);
            k++;
        }

    }
}

// Okay
void stonePos()
{
    glClearColor(0,0,1,0);
    for(i = 0; i < 3; i++)
    {
        if(rand() % 3 == 0)
        {
            stoneX[i] = 100;
        }
        else if(rand() % 2 == 0)
        {
            stoneX[i] = 200;
        }
        else if(rand() % 5 == 0)
        {
            stoneX[i] = 300;
        }
        else
        {
            stoneX[i] = 400;
        }
        stoneY[i] = 1000 - i * 200;
    }
}

void ballPos()
{
    glClearColor(0,0,1,0);
    for(i = 0; i < 4; i++)
    {
        if(rand() % 2 == 0)
        {
            ballX[i] = 200;
        }
        else
        {
            ballX[i] = 300;
        }
        ballY[i] = 1000 - i * 200;
    }
}

// Okay
void drawSpace()
{
    glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex2f(50, 500);
        glVertex2f(50, 0);
        glVertex2f(450, 0);
        glVertex2f(450, 500);
    glEnd();
}

// Okay
void drawPaddle()
{
    glPointSize(10.0);

    glBegin(GL_QUADS);
        glColor3f(0.1,0.5,0.4);
        glVertex2f(paddleX - 35, paddleY + 20);
        glVertex2f(paddleX - 35, paddleY - 20);
        glVertex2f(paddleX + 35, paddleY - 20);
        glVertex2f(paddleX + 35, paddleY + 20);
    glEnd();

}
// Draw Stone
void drawStone()
{

    for(i = 0; i < 3; i++)
    {
        // Stone
        glBegin(GL_QUADS);
            glColor3f(1,0,0);
            glVertex2f(stoneX[i] -5, stoneY[i] +5);
            glVertex2f(stoneX[i] -5, stoneY[i] -10);
            glVertex2f(stoneX[i] +5, stoneY[i] -10);
            glVertex2f(stoneX[i] +5, stoneY[i] +5);
        glEnd();

        stoneY[i] = stoneY[i] - 5;

        if(stoneY[i] > paddleY - 5 - 5 && stoneY[i] < paddleY + 10 + 10 && stoneX[i] == paddleX)
        {
            collide = true;
        }

        if(stoneY[i] < -25)
        {
            if(rand() % 2 == 0)
            {
                stoneX[i] = 200;
            }
            else
            {
                stoneX[i] = 300;
            }
            stoneY[i] = 800;
        }
    }
}

// Do The Ball thing
void drawBall()
{

    for(i = 0; i < 4; i++)
    {
        // ball
        glBegin(GL_QUADS);
            glColor3f(0,1,0);
            glVertex2f(ballX[i] -5, ballY[i] +5);
            glVertex2f(ballX[i] -5, ballY[i] -10);
            glVertex2f(ballX[i] +5, ballY[i] -10);
            glVertex2f(ballX[i] +5, ballY[i] +5);
        glEnd();

        ballY[i] = ballY[i] - 5;

        if(ballY[i] > paddleY - 5 - 5 && ballY[i] < paddleY + 10 + 10 && ballX[i] == paddleX)
        {
            score = score+10;
            ballY[i] = -10;
        }

        if(ballY[i] < -25)
        {
            if(rand() % 2 == 0)
            {
                ballX[i] = 200;
            }
            else
            {
                ballX[i] = 300;
            }
            ballY[i] = 800;
        }
    }
}

// Okay
void Specialkey(int key, int x, int y)
{
    switch(key){
    case GLUT_KEY_LEFT:
        if(paddleX == 400){
            paddleX = 300;
            break;
        }
        else if(paddleX == 300){
            paddleX = 200;
            break;
        }
        else if(paddleX == 200){
            paddleX = 100;
            break;
        }
    case GLUT_KEY_RIGHT:
        if(paddleX == 100){
            paddleX = 200;
            break;
        }
        else if(paddleX == 200){
            paddleX = 300;
            break;
        }
        else if(paddleX == 300){
            paddleX = 400;
            break;
        }
    case GLUT_KEY_HOME:
        collide = false;
        score = 0;
        if(paddleX == 200)
        {
            paddleX = 300;
        }
        else if(paddleX == 300)
        {
            paddleX = 200;
        }
        break;
    }

    glutPostRedisplay();
}

// Ok
void init()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}


void display()
{
    if(collide != true)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        drawSpace();
        drawPaddle();
        drawStone();
        drawBall();
        movd = movd - 16;
        if(movd < - 60)
        {
            movd = 0;
        }

        score = score + 1;

        glColor3f(1,1,1);
        drawText("Score:", 360,455);
        itoa (score, buffer, 10);
        drawTextNum(buffer, 6, 420,455);

        glutSwapBuffers();
        for(q = 0; q<= 10000000; q++)
        {
            ;
        }
    }
    else
    {
        glColor3f(1,1,1);
        drawText("Game Over, Click Home to Restart", 200,250);
        glutSwapBuffers();
    }
}

// Okay
int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,500);
    glutCreateWindow("Humanoids");
    stonePos();
    ballPos();
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(Specialkey);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
