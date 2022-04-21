#include "stdafx.h"
#include "Canvas.h"

#include "Kernel.h"

#include <cstring>

namespace scv {

	

#define PI_2 6.28318530717958
Canvas::Canvas(const scv::Point &p1, const scv::Point &p2) : Component(p1, p2) 
{
	setType(Component::CANVAS);
}

void Canvas::display()
{
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();

   update();

   if (_isVisible == false) return;

   //@afrasson
   //Point currPosition = getRelativePosition();
   Point currPosition = getAbsolutePosition();
   //std::cout << "Canvas::getRelativePosition()(" << currPosition.x << ", " << currPosition.y << ")" << std::endl;
   //@afrasson

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, getWidth(), getHeight(), 0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glViewport(currPosition.x, kernel->getHeight() - (getHeight() + currPosition.y), getWidth(), getHeight());

   scissor->pushScissor(getScissor());
   glPushAttrib(GL_ALL_ATTRIB_BITS);

   glClearColor(1.f, 1.f, 1.f, 1.f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //removido - Pozzer
   //para permitir desenhar linhas e outros objetos sem textura. 
   //o unico elemento que usa textura eh a classe Image, que agora habilita a textura a cada render()
   //e retorna ao estado inicial apos a execucao. glPushAttrib ()
   glDisable(GL_TEXTURE_2D);

   render();

   glPopAttrib();

   scissor->popScissor();

   glDisable(GL_DEPTH_TEST);
   glDisable(GL_LIGHTING);

   if (glUseProgram) glUseProgram(0);

   kernel->applyDefaultTransformMatrix();
}

void Canvas::pointf(float x, float y)
{
   glBegin(GL_POINTS);
      glVertex2f(x, y);
   glEnd();
}
void Canvas::pointd(double x, double y)
{
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();
}
void Canvas::point(const scv::Point &p)
{
	glBegin(GL_POINTS);
	glVertex2i(p.x, p.y);
	glEnd();
}

void Canvas::linef(float x1, float y1, float x2, float y2)
{
   glBegin(GL_LINES);
      glVertex2f(x1, y1);
      glVertex2f(x2, y2);
   glEnd();
}
void Canvas::lined(double x1, double y1, double x2, double y2)
{
	glBegin(GL_LINES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glEnd();
}
void Canvas::line(const scv::Point &p0, const scv::Point &p1)
{
	glBegin(GL_LINES);
	glVertex2i(p0.x, p0.y);
	glVertex2i(p1.x, p1.y);
	glEnd();
}


void Canvas::rectf(float x1, float y1, float x2, float y2)
{
   glBegin(GL_LINE_LOOP);
      glVertex2f(x1, y1);
      glVertex2f(x1, y2);
      glVertex2f(x2, y2);
      glVertex2f(x2, y1);
   glEnd();
}
void Canvas::rectd(double x1, double y1, double x2, double y2)
{
	glBegin(GL_LINE_LOOP);
	glVertex2d(x1, y1);
	glVertex2d(x1, y2);
	glVertex2d(x2, y2);
	glVertex2d(x2, y1);
	glEnd();
}
void Canvas::rect(const scv::Point &p0, const scv::Point &p1)
{
	glBegin(GL_LINE_LOOP);
	glVertex2i(p0.x, p0.y);
	glVertex2i(p0.x, p1.y);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p1.x, p0.y);
	glEnd();
}

void Canvas::rectFillf(float x1, float y1, float x2, float y2)
{
   glBegin(GL_QUADS);
      glVertex2f(x1, y1);
      glVertex2f(x1, y2);
      glVertex2f(x2, y2);
      glVertex2f(x2, y1);
   glEnd();
}
void Canvas::rectFilld(double x1, double y1, double x2, double y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1, y1);
	glVertex2d(x1, y2);
	glVertex2d(x2, y2);
	glVertex2d(x2, y1);
	glEnd();
}
void Canvas::rectFill(const scv::Point &p0, const scv::Point &p1)
{
	glBegin(GL_QUADS);
	glVertex2i(p0.x, p0.y);
	glVertex2i(p0.x, p1.y);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p1.x, p0.y);
	glEnd();
}

void Canvas::polygon(float vx[], float vy[], int elems)
{
   int cont;
   glBegin(GL_LINE_LOOP);
      for(cont=0; cont<elems; cont++)
      {
         glVertex2d(vx[cont], vy[cont]);
      }
   glEnd();

}

void Canvas::polygonFill(float vx[], float vy[], int elems)
{
   int cont;
   glBegin(GL_POLYGON);
      for(cont=0; cont<elems; cont++)
      {
         glVertex2d(vx[cont], vy[cont]);
      }
   glEnd();

}

/*void Canvas::text(int x, int y, const char *t)
{
    int tam = strlen(t);
    int c;

    for(c=0; c<tam; c++)
    {
      glRasterPos2i(x + c*10, y);
      //glutBitmapCharacter(GLUT_BITMAP_8_BY_13, t[c]);
    }
}*/

void Canvas::clear(float r, float g, float b)
{
   glClearColor( r, g, b, 1 );
   //@afrasson
   glClear(GL_COLOR_BUFFER_BIT);
   //@afrasson
}

void Canvas::circlef(float x, float y, float radius, int div)
{
	float ang, x1, y1;
	float inc = PI_2 / div;
   glBegin(GL_LINE_LOOP);
      for(ang=0; ang<6.27; ang+=inc) 
      {
		  x1 = (cos(ang)*radius);
		  y1 = (sin(ang)*radius);
         glVertex2f(x1+x, y1+y);
      }
   glEnd();
}
void Canvas::circled(double x, double y, double radius, int div)
{
	double ang, x1, y1;
	double inc = PI_2 / div;
	glBegin(GL_LINE_LOOP);
	for (ang = 0; ang<6.27; ang += inc)
	{
		x1 = (cos(ang)*radius);
		y1 = (sin(ang)*radius);
		glVertex2d(x1 + x, y1 + y);
	}
	glEnd();
}
void Canvas::circle(const scv::Point &p, double radius, int div)
{
	double ang, x1, y1;
	double inc = PI_2 / div;
	glBegin(GL_LINE_LOOP);
	for (ang = 0; ang<6.27; ang += inc)
	{
		x1 = (cos(ang)*radius);
		y1 = (sin(ang)*radius);
		glVertex2d(x1 + p.x, y1 + p.y);
	}
	glEnd();
}

void Canvas::circleFillf(float x, float y, float radius, int div)
{
	float ang, x1, y1;
	float inc = PI_2 / div;
   glBegin(GL_POLYGON);
      for(ang=0; ang<6.27; ang+=inc)
      {
		  x1 = (cos(ang)*radius);
		  y1 = (sin(ang)*radius);
         glVertex2f(x1+x, y1+y);
      }
   glEnd();
}
void Canvas::circleFilld(double x, double y, double radius, int div)
{
	double ang, x1, y1;
	double inc = PI_2 / div;
	glBegin(GL_POLYGON);
	for (ang = 0; ang<6.27; ang += inc)
	{
		x1 = (cos(ang)*radius);
		y1 = (sin(ang)*radius);
		glVertex2d(x1 + x, y1 + y);
	}
	glEnd();
}
void Canvas::circleFill(const scv::Point &p, double radius, int div)
{
	double ang, x1, y1;
	double inc = PI_2 / div;
	glBegin(GL_POLYGON);
	for (ang = 0; ang<6.27; ang += inc)
	{
		x1 = (cos(ang)*radius);
		y1 = (sin(ang)*radius);
		glVertex2d(x1 + p.x, y1 + p.y);
	}
	glEnd();
}

void Canvas::color(float r, float g, float b)
{
   glColor3d(r, g, b  );
}

} // namespace scv
