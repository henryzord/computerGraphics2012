/**
Autor: Henry Cagnini
Matrícula: 201010352
*/

#include "Widget.h"

std::string* Conversor::doubleToString(double val) {
   std::ostringstream out;
   out << std::fixed << val;
   std::string *str = new std::string(out.str());
   return str;
}

std::string* Conversor::intToString(int val) {
   std::ostringstream out;
   out << val;
   std::string *str = new std::string(out.str());
   return str;
}

HelpButton::HelpButton(scv::Point p1, std::string t, scv::InternalFrame* intfram) : scv::Button(p1, scv::Point(p1.x + 50,p1.y + 20), t) {
   this->intfram = intfram;
   scv::Kernel::getInstance()->addComponent(this);
}

void HelpButton::onMouseClick(const scv::MouseEvent &evt) {
   intfram->setVisible(true);
}

GraphicCanvas::GraphicCanvas(const scv::Point& p1, const scv::Point& p2) : scv::Canvas(p1, p2) {
   bg_color = scv::Color4f(1.f, 1.f, 1.f);
}

void GraphicCanvas::changeContent(double *value, int length) {
   this->value = value;
   this->length = length;

   biggest = -99999.f;
   smallest = 99999.f;

   for(int n = 0; n < length; n++) {
      if(value[n] > biggest) {
         biggest = value[n];
      }
      if(value[n] < smallest) {
         smallest = value[n];
      }
   }
   interval = biggest - smallest;
   yline = this-> getHeight() - (int)(((this->getHeight())*(interval))/(biggest + interval));
}

void GraphicCanvas::render(void) {
   clear(bg_color[0], bg_color[1], bg_color[2]);
   color(0,0,0);

   line(0, yline, this->getWidth(), yline);
   text(5, yline, "x");

   color(1,0,0);
   int actx, acty, prevx, prevy;
   for(int n = 0; n < length; n++) {
      actx = (n * this->getWidth())/length;
      acty = this->getHeight() - (int)(((float)(this->getHeight())*(value[n] + interval))/(biggest+interval));
      if(n > 0) {
         line(actx, acty, prevx, prevy);
      }
      prevx = actx;
      prevy = acty;
   }
}

Compressor::Compressor(GraphicCanvas *g1, GraphicCanvas *g2, scv::TextBox *t1, scv::TextBox *t2, scv::TextBox *t3, std::vector<SampleCollection> *col) {
   this->g1 = g1;
   this->g2 = g2;
   this->t1 = t1;
   this->t2 = t2;
   this->t3 = t3;
   this->col = col;

   this->t1->setEditable(false);
   this->t2->setEditable(false);
   this->t3->setEditable(false);

   isCompressed = false;
   curCol = 0;
}

void Compressor::compressCollection() {
   col->at(curCol).compressCollection();
}

void Compressor::changeCollection(int index) {
   curCol = index;
   isCompressed = false;
   display();
}

void Compressor::changeCompressionState(bool state) {
   isCompressed = state;
   display();
}

int Compressor::getAmountCollections() {
   return col->size();
}

void Compressor::display(void) {
   std::string st1(""), st2(""), st3(""), left_bracket("["), right_bracket("]");
   g1->changeContent(col->at(curCol).smps, col->at(curCol).nsmps);
   g1->render();
   if(isCompressed) {
      if(!col->at(curCol).hasCDCT) {
         compressCollection();
      }
      g2->changeContent(col->at(curCol).cidcts, col->at(curCol).nsmps);

      for(int n = 0; n < col->at(curCol).nsmps; n++) {
         left_bracket += *(Conversor::doubleToString(col->at(curCol).getSample(n)));
         left_bracket += right_bracket;
         st1 += left_bracket;
         left_bracket = "[";

         left_bracket += *(Conversor::doubleToString(col->at(curCol).getCDCT(n)));
         left_bracket += right_bracket;
         st2 += left_bracket;
         left_bracket = "[";

         left_bracket += *(Conversor::doubleToString(col->at(curCol).getCIDCT(n)));
         left_bracket += right_bracket;
         st3 += left_bracket;
         left_bracket = "[";
      }
   } else {
      g2->changeContent(col->at(curCol).idcts, col->at(curCol).nsmps);

      for(int n = 0; n < col->at(curCol).nsmps; n++) {
         left_bracket += *(Conversor::doubleToString(col->at(curCol).getSample(n)));
         left_bracket += right_bracket;
         st1 += left_bracket;
         left_bracket = "[";

         left_bracket += *(Conversor::doubleToString(col->at(curCol).getDCT(n)));
         left_bracket += right_bracket;
         st2 += left_bracket;
         left_bracket = "[";

         left_bracket += *(Conversor::doubleToString(col->at(curCol).getIDCT(n)));
         left_bracket += right_bracket;
         st3 += left_bracket;
         left_bracket = "[";
      }
   }
   t1->setString(st1);
   t2->setString(st2);
   t3->setString(st3);

   t1->display();
   t2->display();
   t3->display();
   g1->render();
   g2->render();
}

CompressionSlider::CompressionSlider(scv::Point p1, scv::TextField *st, Compressor *cmp) : scv::Slider(p1, 100, 0.f, 1.f, 0.f, 1) {
   this->st = st;
   this->cmp = cmp;

   this->st->setEditable(false);

   onValueChange();
}
void CompressionSlider::onValueChange(void) {
   if(this->getValue() > 0) { 
      cmp->changeCompressionState(true);
      st->setString("Com compressao");
   } else { 
      cmp->changeCompressionState(false);
      st->setString("Sem compressao");
   }
}

ComboCollection::ComboCollection(scv::Point p1, int width, Compressor *cmp, CompressionSlider *cp) : scv::ComboBox(p1, width) {
   this->cmp = cmp;
   this->cp = cp;
   std::vector<std::string> names;
   string colecao("Colecao ");
   for(int n = 0; n < cmp->getAmountCollections(); n++) {
      colecao += *(Conversor::intToString(n));
      names.push_back(colecao);
      colecao = "Colecao ";
   }
   setItems(names);
   setIndex(0);
   cmp->changeCollection(0);
}
void ComboCollection::onSelectionChanged(std::string address, int id) {
   cmp->changeCollection(id);
   cp->setValue(cp->getMinValue());
   cp->onValueChange();
}

std::string HelpReader::read(char *path) {
   std::ifstream help;
   help.open(path);
   if(help.fail()) {
      return *(new std::string("Erro lendo ajuda."));
   } else {
      int length;
      char *buffer;
      help.seekg(0, ios::end);
      length = (int)help.tellg();
      help.seekg(0, ios::beg);
      buffer = new char [length+1];
      help.read(buffer,length);
      string *helpstr = new string(buffer);
      help.close();
      return *helpstr;
   }
}