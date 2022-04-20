/**
Autor: Henry Cagnini
Matr�cula: 201010352
*/

/**
Cont�m todos os objetos gr�ficos que ser�o exibidos na SCV, e mais 
3 n�o gr�ficos: dois de suporte � outras classes gr�ficas e um que 
abstrai uma camada de controle entre as classes gr�ficas.
*/
#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <SCV/SCV.h>

const static int default_width = 1024; //pode ser mudado depois
const static int default_height = 600; //mas n�o garanto nada.

#ifndef __HELP__READER__H__
#define __HELP__READER__H__

/**
L� o arquivo de ajuda help.txt (definido no Application.cpp), que ser� exibido no InternalFrame de ajuda
posteriormente. NOTA: Este arquivo deve estar na mesma pasta do execut�vel!
*/
class HelpReader {
public:
   /**
   Retorna o conte�do lido no arquivo de ajuda definido em path.
   path - o caminho do arquivo de ajuda. Deve conter a termina��o .txt.
   */
   static std::string read(char *path);
};

#endif //__HELP__READER__H__

#ifndef __HELP__BUTTON__H__
#define __HELP__BUTTON__H__

/**
Respons�vel por abrir o InternalFrame de ajuda.
*/
class HelpButton : public scv::Button {
private:
   scv::InternalFrame *intfram;
public:
   HelpButton(scv::Point p1, std::string t, scv::InternalFrame* intfram);
   void onMouseClick(const scv::MouseEvent &evt);
};

#endif //__HELP__BUTTON__H__

#ifndef __CONVERSOR__H__
#define __CONVERSOR__H__

/**
Classe usada para facilitar a convers�o de n�meros
inteiros ou flutuantes em strings.
*/

class Conversor {
public:
   /**
   Converte um double em string.
   val - o valor a ser convertido em string.
   */
   static std::string *doubleToString(double val);
   /**
   Converte um int em string.
   val - o valor a ser convertido em string.
   */
   static std::string *intToString(int val);
};

#endif //__CONVERSOR__H__

#ifndef __GRAPHIC__CANVAS__H__
#define __GRAPHIC__CANVAS__H__

/**
Canvas que desenhar� o gr�fico dos valores que forem passados
para ele, atrav�s do m�todo changeContent.
*/

class GraphicCanvas : public scv::Canvas {
private:
   scv::Color4f bg_color;
   double *value, biggest, smallest, interval;
   int length, yline;

public:
   GraphicCanvas(const scv::Point& p1, const scv::Point& p2);
   /**
   Troca o vetor de valores para serem desenhados na tela.
   � nessa fun��o que � realizada uma discretiza��o para a tela
   do universo real de dados.
   value - o vetor de valores
   length - o tamanho do vetor
   */
   void changeContent(double *value, int length);
   /**
   Desenhar� na tela o gr�fico dos valores value.
   O eixo x ser� length, e o y ser� value[n].
   */
   void GraphicCanvas::render(void);
};

#endif //__GRAPHIC__CANVAS__H

#ifndef __COMPRESSOR__H__
#define __COMPRESSOR__H__

/**
Classe respons�vel por "comprimir" (na verdade apenas chama a classe
CosinTransformer) a DCT e a IDCT. Tamb�m � uma classe de controle, pois
faz a conex�o entre classes atrav�s de seus m�todos.
*/

#include <iomanip>

#include "SampleCollection.h"

const static float not_compressed = -9999;
const static int max_collections = 10;

class Compressor {

private:
   bool isCompressed;
   int curCol;
   GraphicCanvas *g1, *g2;
   scv::TextBox *t1, *t2, *t3;
   std::vector<SampleCollection> *col;

public:
   /**
   Recebe dois GraphicCanvas (um para o sinal original (g1), outro para a IDCT (g2))
   Tr�s TextBoxes (um para o sinal original (t1), um para a DCT (t2), outro para a IDCT (t3)
   E um vetor de SampleCollections (col)
   */
   Compressor(GraphicCanvas *g1, GraphicCanvas *g2, scv::TextBox *t1, scv::TextBox *t2, scv::TextBox *t3, std::vector<SampleCollection> *col);
   /**
   Comprime a cole��o que est� atualmente sendo setada pelo Compressor.
   Por defini��es da SampleCollection, ela s� ser� comprimida de fato se ainda n�o tiver sido.
   */
   void compressCollection();
   /**
   Muda a cole��o a ser setada no vector<SampleCollection.
   index - o �ndice da nova cole��o.
   */
   void changeCollection(int index);
   /**
   Muda se os GraphicCanvas e os TextBoxes devem exibir a vers�o comprimida
   ou normal dos sinais.
   state - true para comprimir, false para descomprimir. 
   */
   void changeCompressionState(bool state);
   /**
   Diz o n�mero de cole��es que existem no vector<SampleCollection>.
   */
   int getAmountCollections();
   /**
   Mostra os dados na tela.
   */
   void display(void);
};

#endif //__COMPRESSOR__H__

#ifndef __COMPRESSION__SLIDER__H__
#define __COMPRESSION__SLIDER__H__

/**
Slider que definir� o status de compress�o da cole��o sendo atualmente mostrada.
*/

class CompressionSlider : public scv::Slider {
private:
   scv::TextField *st;
   Compressor *cmp;

public:
   /**
   Recebe um textfield para dizer se est� comprimido ou n�o, e um compressor, para
   mudar o status dele de comprimido.
   */
   CompressionSlider(scv::Point p1, scv::TextField *st, Compressor *cmp);
   void onValueChange(void);
};

#endif //__COMPRESSION__SLIDER__H__

#ifndef __COMBO__COLLECTION__H__
#define __COMBO_COLLECTION__H__

/**
Combobox que seleciona a cole��o a ser mostrada na tela.
*/

class ComboCollection : public scv::ComboBox {
private:
   Compressor *cmp;
   CompressionSlider *cp;

public:
   /**
   Recebe o compressor, para mudar a cole��o a ser mostrada na tela, 
   e um CompressionSlider, apenas por uma quest�o de est�tica, para trocar para
   "Sem compress�o" automaticamente quando troca uma cole��o.
   */
   ComboCollection(scv::Point p1, int width, Compressor *cmp, CompressionSlider *cp);
   void onSelectionChanged(std::string address, int id);
};

#endif //__COMBO__COLLECTION__H__

#endif //__WIDGET_H__
