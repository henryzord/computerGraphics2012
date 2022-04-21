/**
Henry Cagnini
201010352
*/

#include "Widget.h"

//CanvasSweep
CanvasSweep::CanvasSweep(scv::Point p1, scv::Point p2) : scv::Canvas(p1, p2) {
   displaying = false;
   projectionMode = Camera::perspective;
   representation = CanvasSweep::dots;
   steps = valid_divisors[0];

   setDrawVector();
   object = new SweepObject(toDraw, steps, Camera::defaultDistance);
   camera = new Camera(this->object, Camera::perspective, scv::Point(getWidth()/2, getHeight()/2));

   render_call = &CanvasSweep::renderDraw;

   toShow = camera->getToShow();
}

Camera *CanvasSweep::getCamera(void) {
   return camera;
}

void CanvasSweep::setDrawVector(void) {
   toDraw.clear();
   int thirdPart = getHeight()/3;
   toDraw.push_back(scv::Point(getWidth()/2, getHeight()-thirdPart -1));
   toDraw.push_back(scv::Point(getWidth()/2, thirdPart));
}

void CanvasSweep::drawObject(void) {
   //empurra os pontos desenhados no canvas para a
   //origem do canvas, para facilitar posterior manipulação
   std::vector<scv::Point> centralized;
   scv::Point axis_center(getWidth()/2, getHeight()/2);
   for(int n = 0; n < toDraw.size(); n++) {
      centralized.push_back(toDraw.at(n) - axis_center);
   }
   //inicia um objeto com os pontos centralizados, o número
   //de paradas que a volta vai dar, e a distância do centro
   //de projeção
   *object = SweepObject(centralized, steps, Camera::defaultDistance);
   camera->displayObject();
}

void CanvasSweep::changeRepresentation(int id) {
   if(displaying) {
      if(id == CanvasSweep::dots) {
         render_call = &CanvasSweep::renderDots;  
      } else {
         render_call = &CanvasSweep::renderLines;
      }
   } else {
      render_call = &CanvasSweep::renderDraw;
   }
   this->representation = id;
}

void CanvasSweep::changeSteps(int steps) {
   this->steps = steps;
   if(displaying) {
      int rotateX, rotateY, rotateZ;
      rotateX = object->getAngleX() - SweepObject::initialX;
      rotateY = object->getAngleY() - SweepObject::initialY;
      rotateZ = object->getAngleZ() - SweepObject::initialZ;
      drawObject();
      camera->onPositionChanged(rotateX, rotateY, rotateZ);
   }   
}

void CanvasSweep::changeDisplay(bool display) {
   if(displaying != display) {
      if(display) { //draw -> display
         drawObject();
         if(representation == CanvasSweep::dots) {
            render_call = &CanvasSweep::renderDots;
         } else {
            render_call = &CanvasSweep::renderLines;
         }
      } else { //display -> draw
         setDrawVector();      
         render_call = &CanvasSweep::renderDraw;
      }
      displaying = display;
   }
}

void CanvasSweep::renderDots() {
   int size = toShow->size();
   for(int n = 0; n < size; n++) {
      circle(toShow->at(n).x, toShow->at(n).y, 1, 100);
   }
}

void CanvasSweep::renderLines() {
   int steps = object->getSteps(), prev = steps-1, size = toShow->size();
   //desenha os anéis
   for(int n = 0; n < size; n++) {
      line(toShow->at(prev).x, toShow->at(prev).y, toShow->at(n).x, toShow->at(n).y);
      prev = n + (((n+1) % steps == 0)*steps);
   }   
   //desenha as colunas
   prev = 0;
   for(int n = steps; n < size; n++) {
      line(toShow->at(prev).x, toShow->at(prev).y, toShow->at(n).x, toShow->at(n).y);
      prev++;
   } 
}

void CanvasSweep::renderDraw() {
   int size = toDraw.size();
   scv::Point *previous = &toDraw.at(0), *current;
   for(int n = 0; n < size; n++) {
      current = &toDraw.at(n);
      circleFill(current->x, current->y, 1, 100);
      line(previous->x, previous->y, current->x, current->y);
      previous = current;
   }
}

void CanvasSweep::render(void) {
   color(0.f, 0.f, 0.f);
   (this->*render_call)();
}

void CanvasSweep::update(void) {

}

void CanvasSweep::onMouseClick(const scv::MouseEvent &evt) {
   scv::Point position = evt.getPosition();
   //se está na hora de desenhar e o ponto não ultrapassa a metade da tela.
   //isso é feito porque um sólido de rotação desconsideraria qualquer ponto
   //colocado além do seu eixo de rotação.
   if((!displaying) && (position.x < getWidth()/2)) {
      toDraw.push_back(position);
   }
}

void CanvasSweep::onKeyPressed(const scv::KeyEvent &evt) {
   if(!evt.special && displaying) {
      int rotateX = 0, rotateY = 0;
      switch(evt.keycode) {
      case(CanvasSweep::w_key):
         rotateX = -min_degree;
         break;
      case(CanvasSweep::s_key):
         rotateX = min_degree;
         break;
      case(CanvasSweep::a_key): 
         rotateY = -min_degree;
         break;
      case(CanvasSweep::d_key): 
         rotateY = min_degree;
         break;
      }
      if(rotateY != 0 || rotateX != 0) {
         camera->onPositionChanged(rotateX, rotateY, 0);
      }
   }
}

CanvasSweep::~CanvasSweep(void) {
   delete object;
   delete camera;
}

//BoxProjection
BoxProjection::BoxProjection(scv::Point p1, scv::Point p2, Camera *camera) : scv::ComboBox(p1, p2.x) {
   this->camera = camera;

   addItem(std::string("Perspective"));
   addItem(std::string("Orthographic"));
   this->setIndex(Camera::perspective);
}

void BoxProjection::onSelectionChanged(std::string address, int id) {
   camera->setProjection(id);
}

//BoxRepresentation

BoxRepresentation::BoxRepresentation(scv::Point p1, scv::Point p2, CanvasSweep *canvasSweep) : scv::ComboBox(p1, p2.x) {
   this->canvasSweep = canvasSweep;

   addItem(std::string("Dots"));
   addItem(std::string("Lines"));
   this->setIndex(CanvasSweep::dots);
}

void BoxRepresentation::onSelectionChanged(std::string address, int id) {
   canvasSweep->changeRepresentation(id);
}

//ToggleRotate
ToggleRotate::ToggleRotate(scv::Point p1, scv::Point p2, bool state, const std::string str, CanvasSweep *canvasSweep) : scv::ToggleButton(p1, p2, state, str) {
   this->canvasSweep = canvasSweep;
}

void ToggleRotate::onValueChange(void) {
   canvasSweep->changeDisplay(this->getState());
}

//SliderSteps
SliderSteps::SliderSteps(scv::Point &p, int width, CanvasSweep *canvasSweep) : scv::Slider(p, width, 0.f, 20.f, 0.f, 1.f) {
   this->canvasSweep = canvasSweep;
   divisor = valid_divisors[(int)getValue()];
}

int SliderSteps::getDivisor(void) {
   return valid_divisors[(int)getValue()];
}

void SliderSteps::onValueChange(void) {
   canvasSweep->changeSteps(getDivisor());
}

//Help e etc
//TextHelp
TextHelp::TextHelp(scv::Point p1, scv::Point p2, std::string str, char *path) : scv::TextBox(p1, p2, str) {
   std::ifstream help;
   help.open(path);
   if(help.fail()) {
      setString(std::string("Erro lendo ajuda. O arquivo help.txt esta na pasta do executavel?"));
   } else {
      int length;
      char *buffer;
      help.seekg(0, std::ios::end);
      length = (int)help.tellg();
      help.seekg(0, std::ios::beg);
      buffer = new char [length];
      help.read(buffer,length);
      help.close();
      setString(std::string(buffer));
   }
}

//FrameHelp
FrameHelp::FrameHelp(int width, int height, std::string title, TextHelp *textHelp) : scv::InternalFrame(width, height, title) {
   this->textHelp = textHelp;
   setVisible(false);
}

void FrameHelp::onSizeChange(void) {
   scv::Point size = this->getSize();
   textHelp->setSize(size.x, size.y);
}

//ButtonHelp
ButtonHelp::ButtonHelp(scv::Point p1, scv::Point p2, std::string str, FrameHelp *frameHelp) : scv::Button(p1, p2, str) {
   this->frameHelp = frameHelp;
}
void ButtonHelp::onMouseClick(const scv::MouseEvent &evt) {
   frameHelp->setVisible(true);
}
