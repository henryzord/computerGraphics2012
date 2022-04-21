/**
Henry Cagnini
201010352
*/

#include "Control.h"
#include "Backhoe.h"

Backhoe *backhoe;

void init(int *argc, char *argv[]) {
   
   glutInit(argc, argv);                                         
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowPosition(0, 0);
   glutInitWindowSize(1000, 500);
   glutCreateWindow("Construction Site");                     

   glutDisplayFunc(render);
   glutIdleFunc(render);
   glutMouseFunc(onMousePressed);
   glutMotionFunc(onMouseHold);
   glutPassiveMotionFunc(onMouseOver);
   glutKeyboardFunc(onKeyPressed);
   glutKeyboardUpFunc(onKeyUp);

   glEnable(GL_DEPTH_TEST);

   glMatrixMode(GL_PROJECTION);
   gluPerspective(45, 1.0, 10.0, 1000.0);
   glMatrixMode(GL_MODELVIEW);

   //cria a escavadeira e a empurra para trás, para 
   //bem da câmera não ficar localizada dentro dela.
   backhoe = new Backhoe();
   backhoe->translate(TriPoint(0, 0, -200));

   glutMainLoop();              
}

void render(void) {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
   backhoe->draw();

   glutSwapBuffers();
}

void onMousePressed(int button, int state, int x, int y) {
}

void onMouseHold(int x, int y) {
}

void onMouseOver(int x, int y) {
   backhoe->onMouseOver(x, y);
}

void onKeyPressed(unsigned char key, int x, int y) {
   backhoe->onKeyPressed(key);
}

void onKeyUp(unsigned char k, int x, int y) {
}