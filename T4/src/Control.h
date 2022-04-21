/**
Henry Cagnini
201010352
*/

/**
O header Control provê callbacks de comunicação com 
a Glut. A impossibilidade de setar ponteiros de um objeto
para funções da Glut exigiu uma modelagem procedural.
*/

#ifndef __CONTROL__H__
#define __CONTROL__H__

#include <windows.h>

#include <gl\glut.h>
#include <gl\glu.h>
#include <gl\gl.h>

/*
Definição das teclas
*/
const static int SPACE_KEY = 32;
const static int A_KEY = 97;
const static int B_KEY = 98;
const static int C_KEY = 99;
const static int D_KEY = 100;
const static int E_KEY = 101;
const static int F_KEY = 102;
const static int G_KEY = 103;
const static int H_KEY = 104;
const static int I_KEY = 105;
const static int J_KEY = 106;
const static int K_KEY = 107;
const static int L_KEY = 108;
const static int M_KEY = 109;
const static int N_KEY = 110;
const static int O_KEY = 111;
const static int P_KEY = 112;
const static int Q_KEY = 113;
const static int R_KEY = 114;
const static int S_KEY = 115;
const static int T_KEY = 116;
const static int U_KEY = 117;
const static int V_KEY = 118;
const static int W_KEY = 119;
const static int X_KEY = 120;
const static int Y_KEY = 121;
const static int Z_KEY = 122;


/**
Inicia a glut com os parâmetros passados para a função
main (que chama init).
*/
void init(int *argc, char *argv[]);
void render(void);

/**
Callbacks
*/
void onMousePressed(int button, int state, int x, int y);
void onMouseHold(int x, int y);
void onMouseOver(int x, int y);
void onKeyPressed(unsigned char key, int x, int y);
void onKeyUp(unsigned char k, int x, int y);

#endif //__CONTROL__H__