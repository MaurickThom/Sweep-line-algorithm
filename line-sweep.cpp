#include <stdlib.h>
#include <iostream>
#include <gl/glut.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <math.h>
#include <complex>
using namespace std;


int height = 600, width = 600;

void paintPixel(double x, double y, int c)
{
  glPointSize(2);
  if (c == 0)
  {
    glColor3f(1, 1, 1);
  }
  else
  {
    if (c == 2)
    {
      glColor3f(0, 1, 0);
    }
    else
    {
      if (c == 3)
      {
        glColor3f(0, 1, 0);
      }
      else
      {
        if (c == 4)
        {
          glColor3f(0, .8, .5);
        }
      }
    }
  }
  glBegin(GL_POINTS);
  glVertex2f(x, y);
  glEnd();
  glFlush();
  glutSwapBuffers();
}

void paintLine(int x1, int y1, int x2, int y2)
{
  double dy = y2 - y1;
  double dx = x2 - x1;

  if (dx != 0)
  {
    float m = dy / dx;
    float b = y1 - (x1 * m);
    if (abs(dx) > abs(dy))
    {
      if (x1 > x2)
      {
        for (double x = x1; x >= x2; x--)
        {
          paintPixel(x, (m * x) + b, 2);
        }
      }
      else
      {
        if(x2>x1){
          for (double x = x1; x <= x2; x++)
          {
            paintPixel(x, (m * x) + b, 2);
          }
        }
      }
    }
    else if (abs(dy) > abs(dx))
    {
      if (y1 > y2)
      {
        for (double y = y1; y >= y2; y--)
        {
          paintPixel((y - b) / m, y, 3);
        }
      }
      else
      {
        if (y2 > y1)
        {
          for (double y = y1; y <= y2; y++)
          {
            paintPixel((y - b) / m, y, 3);
          }
        }
      }
    }
  }
  else
  {
    if (y1 > y2)
    {
      for (double y = y1; y >= y2; y--)
      {
        paintPixel(x1, y, 4);
      }
    }
    else if (y1 < y2)
    {
      for (double y = y1; y <= y2; y++)
      {
        paintPixel(x1, y, 4);
      }
    }
  }
}

int cx = 0, cy = 0, c2x = 0, c2y = 0, p = 0,X[10],Y[10],m=0,n=0,xmin,xmax,ymin,ymax;

void filling(int xs[],int ys[]){
  for (int i = 0; i < 10; i++)
  {
    if(xs[i]>xmax){
      xmax = xs[i];
    }

    if(xs[i]<=xmin && xs[i] != 0){
      xmin = xs[i];
    }
    if(ys[i] > ymax){
      ymax = ys[i];
    }
    if(ys[i]<=ymin && ys[i] !=0){
      ymin = ys[i];
    }
  }
  for(int x = xmin;x<=xmax;x++)
  {
    for(int y = ymin;y<=ymax;y++)
    {
      unsigned char pixel[4];
      glReadPixels(x,glutGet(GLUT_WINDOW_HEIGHT)-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,pixel);
      if((int)pixel[1]==255){
        if(p==0){
          c2x = x;c2y = y;
        }
        if(p!=0){
          cx = x;cy = y;
        }
        p++;
      }
      if(y==ymax){
        if(cx !=0){
          paintLine(c2x,c2y,cx,cy);
        }else{
          paintPixel(c2x,c2y,4);
        }
      }
    }
    cx = c2x = cy = c2y = p = 0;
  }

}

void mouse(int btn,int state,int x,int y){
  system("cls");
  if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    X[n] = x;
    Y[n] = y;
    if(m!=0){
      paintLine(X[n-1],Y[n-1],X[n],Y[n]);
    }
    n++;
    m++;
  }

  if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
    X[n] = x;Y[n] = y;
    paintLine(X[n-1],Y[n-1],X[n],Y[n]);
    paintLine(X[n],Y[n],X[0],Y[0]);
    xmin = X[0],xmax = X[0],ymin = Y[0], ymax = Y[0];
    filling(X,Y);

    for (int e = 0; e < 10; e++)
    {
      X[e] = 0;
      Y[e] = 0;
    }
    ymax = xmax = ymin = xmin = n = m = 0;
  }
}

void display(){
}

int main(int argc, char** argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(width,height);
  glutInitWindowPosition(10,10);
  glutCreateWindow("Rellenando");
  glutDisplayFunc(display);
  gluOrtho2D(0,width,height,0);
  glClearColor(0,0,0,0);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}

// g++ -m32 -Wall -o line-sweep.out line-sweep.cpp -L"C:\MinGW\lib" -lglu32 -lglut32 -lopengl32 -lstdc++
