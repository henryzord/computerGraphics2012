/**
Henry Cagnini
201010352
*/

/**
*CanvasSweep:
Canvas onde s�o exibidos tanto os pontos a serem
desenhados quanto o s�lido de rota��o. Possui m�todos
que s�o chamados quando devem ser mudados seus dados de proje��o,
visualiza��o, rota��o, etc.

*BoxProjection: 
Muda a proje��o da Camera contida no CanvasSweep.

*BoxRepresentation: 
Muda a representa��o do s�lido contido no CanvasSweep.

*SliderSteps:
Muda quantos passos devem ser tomados para desenhar o s�lido
da CanvasSweep.

*ToggleRotate:
Rotaciona os pontos desenhados na fase de desenho do CanvasSweep,
gerando um SweepObject.

*TextHelp:
Cont�iner onde � colocado o texto de ajuda contido no arquivo help.txt.

*FrameHelp:
O InternalFrame onde ser� exibido TextHelp.

*ButtonHelp:
Mostra FrameHelp.

*/

#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <SCV/SCV.h>
#include "Camera.h"

/**
Utilizado pelo SliderSteps, mas como C++ n�o permite a
inicializa��o de tipos n�o-primitivos dentro de classes,
foram deslocados para fora da classe.
*/
const static int divisors_quantity = 21;
const static int valid_divisors[divisors_quantity] = {4, 5, 6, 8, 9, 10, 12, 15, 18, 20, 24, 30, 36, 40, 45, 60, 72, 90, 120, 180, 360};

class CanvasSweep : public scv::Canvas {
private:
   const static int min_degree = 2;

   const static int w_key = 119;
   const static int s_key = 115;
   const static int a_key = 97;
   const static int d_key = 100;

   Camera *camera;
   SweepObject *object;
   bool displaying;
   int projectionMode, representation, steps;
   std::vector<scv::Point> *toShow, toDraw;

   void (CanvasSweep::*render_call)(void);

   /**
   Renderiza o s�lido de rota��o com pontos.
   */
   inline void renderDots(void);
   /**
   Renderiza o s�lido de rota��o com linhas.
   */
   inline void renderLines(void);
   /**
   Renderiza a se��o transversal do s�lido de 
   rota��o, que posteriormente ser� rotacionada.
   */
   inline void renderDraw(void);

   /**
   Limpa o vetor de pontos de desenhos e posiciona
   o eixo principal no Canvas.
   */
   inline void setDrawVector(void);
   /**
   Rotaciona a se��o transversal do objeto, gerando
   um SweepObject.
   */
   inline void drawObject(void);

public:
   const static int dots = 0;
   const static int lines = 1;

   CanvasSweep(scv::Point p1, scv::Point p2);

   Camera *getCamera(void);
   void render(void);
   void update(void);

   /**
   Muda o display: de desenho para rota��o ou vice-versa.
   */
   inline void changeDisplay(bool display);
   /**
   Muda a representa��o: de pontos para linhas e vice-versa.
   */
   inline void changeRepresentation(int id);
   /**
   Muda a quantidade de passos que devem ser tomados para o s�lido
   ser desenhado.
   */
   inline void changeSteps(int steps);

   /**
   Chamado apenas quando est� na fase de desenho, para desenhar os pontos.
   */
   virtual void onMouseClick(const scv::MouseEvent &evt);
   /**
   Chamado apenas na fase de rota��o, para rotacionar o objeto.
   */
   virtual void onKeyPressed(const scv::KeyEvent &evt);

   ~CanvasSweep(void);
};

class BoxProjection : public scv::ComboBox {
private:
   Camera *camera;
public:
   BoxProjection(scv::Point p1, scv::Point p2, Camera *camera);
   virtual void BoxProjection::onSelectionChanged(std::string address, int id);
};

class BoxRepresentation : public scv::ComboBox {
private:
   CanvasSweep *canvasSweep;
public:
   BoxRepresentation(scv::Point p1, scv::Point p2, CanvasSweep *canvasSweep);
   virtual void onSelectionChanged(std::string address, int id);
};

class SliderSteps : public scv::Slider {
private:
   int divisor;
   CanvasSweep *canvasSweep;
public:
   SliderSteps(scv::Point &p, int width, CanvasSweep *canvasSweep);
   virtual void onValueChange(void);
   int getDivisor(void);
};

class ToggleRotate : public scv::ToggleButton {
private:
   CanvasSweep *canvasSweep;
public:
   ToggleRotate(scv::Point p1, scv::Point p2, bool state, std::string str, CanvasSweep *canvasSweep);
   virtual void onValueChange(void);
};

class TextHelp : public scv::TextBox {
public:
   TextHelp(scv::Point p1, scv::Point p2, std::string str, char *path);
};

class FrameHelp : public scv::InternalFrame {
private:
   TextHelp *textHelp;
public:
   FrameHelp(int width, int height, std::string title, TextHelp *textHelp);
   virtual void onSizeChange(void);
};

class ButtonHelp : public scv::Button {
private:
   FrameHelp *frameHelp;
public:
   ButtonHelp(scv::Point p1, scv::Point p2, std::string str, FrameHelp *FrameHelp);
   virtual void onMouseClick(const scv::MouseEvent &evt);
};

#endif //__WIDGET_H__