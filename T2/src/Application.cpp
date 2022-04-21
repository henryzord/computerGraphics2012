/**
Henry Cagnini
201010352
*/

#include "Application.h"

Application::Application(void) : Kernel() {
   setWindowSize(s_defaultWindowWidth, s_defaultWindowHeight);
   lockWindowSize(false);
   setFramesPerSecond(60);

   setWindowTitle("Gorillaz");

}

Application::~Application(void) {
}

void Application::init(void) {

   _mainPanel = new scv::Panel(scv::Point(0, 0), scv::Point(s_defaultWindowWidth, s_defaultWindowHeight));

   addComponent(_mainPanel);

   int endCanvas = s_defaultWindowHeight-45;
   GameCanvas *canvasScreen = new GameCanvas(scv::Point(5,5), scv::Point(s_defaultWindowWidth-5, endCanvas));
   addComponent(canvasScreen);

   MainFrame *internalFrameMain = new MainFrame(200, 80, "Menu Principal", canvasScreen);
   internalFrameMain->setRelativePosition(scv::Point(s_defaultWindowWidth/2,s_defaultWindowHeight/2));
   addComponent(internalFrameMain);

   scv::InternalFrame *internalFrameHelp = new scv::InternalFrame(300, 400, "Ajuda");
   internalFrameMain->setRelativePosition(scv::Point(s_defaultWindowWidth/2 + 200,s_defaultWindowHeight/2));
   addComponent(internalFrameHelp);
      scv::TextBox *textBoxHelp = new scv::TextBox(scv::Point(0,0), scv::Point(300, 400), HelpReader::read("help.txt"));
      textBoxHelp->setEditable(false);
      textBoxHelp->setParent(internalFrameHelp->getPanel());
   
      InternalFrameButton *buttonHelp = new InternalFrameButton(scv::Point(2,53), scv::Point(198, 77), "Ajuda", internalFrameHelp);
      buttonHelp->setParent(internalFrameMain->getPanel());

      DifficultyButton *buttonChange = new DifficultyButton(scv::Point(2,27), scv::Point(198, 51), "Facil", canvasScreen);
      buttonChange->setParent(internalFrameMain->getPanel());

      ResetButton *buttonReset = new ResetButton(scv::Point(2,1), scv::Point(198, 25), "Reiniciar Fase", canvasScreen);
      buttonReset->setParent(internalFrameMain->getPanel());

   MainButton *buttonMain = new MainButton(scv::Point(5,endCanvas+5), scv::Point(105, endCanvas+35), "Menu Principal", internalFrameMain, canvasScreen);
   addComponent(buttonMain);

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
