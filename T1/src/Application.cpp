/**
Autor: Henry Cagnini
Matrícula: 201010352
*/

#include "Application.h"
#include "FileInterpreter.h"

Application::Application(void) : Kernel() {
   setWindowSize(default_width, default_height);
   lockWindowSize(false);
   setFramesPerSecond(60);

   setWindowTitle("Cosin Transformation");
}

Application::~Application(void) {
}

void Application::init(void) {
   _mainPanel = new scv::Panel(scv::Point(0, 0), scv::Point(default_width, default_height));
   addComponent(_mainPanel);

   FileInterpreter fi;
   std::vector<SampleCollection> *col = fi.readFile("in.txt");;

   //panels
   scv::Panel *panelFather = new scv::Panel(scv::Point(0,0), scv::Point(default_width, default_width));
   addComponent(panelFather);
   scv::Panel *panelOriginal = new scv::Panel(scv::Point(0,0), scv::Point(default_width/3, default_height));
   panelOriginal->setParent(panelFather);
   scv::Panel *panelIDCT = new scv::Panel(scv::Point(default_width-(default_width/3),0), scv::Point(default_width, default_height));
   panelIDCT->setParent(panelFather);
   //labels
   scv::Label *label50448698 = new scv::Label(scv::Point((default_width/6),(default_height/2)-5), scv::Point((default_width/6)+76, (default_height/2)+8), "Original");
   label50448698->setParent(panelOriginal);
   scv::Label *label50448704 = new scv::Label(scv::Point(default_width/2,(default_height/2) - 5), scv::Point((default_width/2) + 76, (default_height/2) + 11), "DCT"); 
   label50448704->setParent(panelFather);
   scv::Label *label50448706 = new scv::Label(scv::Point((default_width/6),(default_height/2)-5), scv::Point((default_width/6)+76, (default_height/2)+8), "IDCT");
   label50448706->setParent(panelIDCT);
   scv::Label *label50448700 = new scv::Label(scv::Point((default_width/3) + 10,20), scv::Point((default_width/3) + 86, 33), "Opcoes");
   label50448700->setParent(panelFather);
   scv::Label *label50448701 = new scv::Label(scv::Point((default_width/3) + 10,40), scv::Point((default_width/3) + 86, 53), "Conjunto de Amostras");
   label50448701->setParent(panelFather);
   scv::Label *label50448703 = new scv::Label(scv::Point((default_width/3)+10,60), scv::Point((default_width/3) + 86, 73), "Compressao");
   label50448703->setParent(panelFather);

   //textfields
   scv::TextField *compressionStatus = new scv::TextField(scv::Point((default_width/3) + 191,63), 100, "Sem Compressao");
   compressionStatus->setParent(panelFather);
   //textboxes
   scv::TextBox *signal1 = new scv::TextBox(scv::Point(0,(default_height-(default_height/2))+13), scv::Point((default_width/3),default_height),"Signal1");
   signal1->setParent(panelOriginal);
   scv::TextBox *signal2 = new scv::TextBox(scv::Point((default_width/3)-12,(default_height-(default_height/2)))+13, scv::Point(default_width-(default_width/3),default_height),"Signal2");
   signal2->setParent(panelFather);
   scv::TextBox *signal3 = new scv::TextBox(scv::Point(0,(default_height-(default_height/2))+13), scv::Point((default_width/3),default_height),"Signal3");
   signal3->setParent(panelIDCT);


   //GraphicCanvas
   GraphicCanvas *canvasOriginal = new GraphicCanvas(scv::Point(0,0), scv::Point(default_width/3, (default_height/2)-13));
   canvasOriginal->setParent(panelOriginal);
   GraphicCanvas *canvasIDCT = new GraphicCanvas(scv::Point(0,0), scv::Point(default_width/3, (default_height/2)-13));
   canvasIDCT->setParent(panelIDCT);


   //compressor
   Compressor *cmp = new Compressor(canvasOriginal, canvasIDCT, signal1, signal2, signal3, col);

   //compressionSlider
   CompressionSlider *sliderCompression = new CompressionSlider(scv::Point((default_width/3) + 81,63), compressionStatus, cmp); 
   sliderCompression->setParent(panelFather);

   //ComboCollection
   ComboCollection *comboBoxCollection = new ComboCollection(scv::Point((default_width/3) + 126,38), 100, cmp, sliderCompression);
   comboBoxCollection->setParent(panelFather);

   //objetos referentes ao botão de ajuda e afins
   scv::InternalFrame *internalFrameHelp = new scv::InternalFrame(240, 240, "Help");
   internalFrameHelp->setRelativePosition(scv::Point(0,0));
   addComponent(internalFrameHelp);
   scv::TextBox *textHelp = new scv::TextBox(scv::Point(0,0), scv::Point(240, 240), HelpReader::read("help.txt")); 
   textHelp->setEditable(false);
   textHelp->setParent(internalFrameHelp->getPanel());
   internalFrameHelp->setVisible(false);
   HelpButton *helpButton = new HelpButton(scv::Point((default_width-(default_width/3))-50,0), "Help", internalFrameHelp);
   helpButton->setParent(panelFather);
}

void Application::onMouseClick(const scv::MouseEvent &evt) {
}
void Application::onMouseHold(const scv::MouseEvent &evt) {
}
void Application::onMouseOver(const scv::MouseEvent &evt) {
}
void Application::onMouseUp(const scv::MouseEvent &evt) {
}
void Application::onMouseWheel(const scv::MouseEvent &evt) {
}

void Application::onKeyPressed(const scv::KeyEvent &evt) {
}
void Application::onKeyUp(const scv::KeyEvent &evt) {
}

void Application::onSizeChange(void) {
   _mainPanel->setSize(getWidth(), getHeight());
}
void Application::onPositionChange(void) {
}
