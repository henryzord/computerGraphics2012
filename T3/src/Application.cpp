/**
Henry Cagnini
201010352
*/

#include "Application.h"

Application::Application(void) : Kernel() {
   setWindowSize(s_defaultWindowWidth, s_defaultWindowHeight);
   lockWindowSize(true);
   setFramesPerSecond(60);

   setWindowTitle("Sweep Glass Shop");
}

Application::~Application(void) {
}

void Application::init(void) {
   _mainPanel = new scv::Panel(scv::Point(0, 0), scv::Point(s_defaultWindowWidth, s_defaultWindowHeight));

   addComponent(_mainPanel);

   CanvasSweep *canvasSweep = new CanvasSweep(scv::Point(5,30), scv::Point(s_defaultWindowWidth-5, s_defaultWindowHeight-5));

   SliderSteps *sliderSteps = new SliderSteps(scv::Point(210,7), 100, canvasSweep);

   addComponent(sliderSteps);
   addComponent(canvasSweep);

   BoxProjection *boxProjection = new BoxProjection(scv::Point(5,5), scv::Point(100, 25), canvasSweep->getCamera());
   addComponent(boxProjection);

   BoxRepresentation *boxRepresentation = new BoxRepresentation(scv::Point(107,5), scv::Point(100, 25), canvasSweep);
   addComponent(boxRepresentation);

   ToggleRotate *toggleRotate = new ToggleRotate(scv::Point(315,3), scv::Point(368, 27), 0, "Rotate", canvasSweep);
   addComponent(toggleRotate);

   //Help e etc
   TextHelp *textHelp = new TextHelp(scv::Point(0,0), scv::Point(200,200), "TextHelp", "help.txt");
   FrameHelp *frameHelp = new FrameHelp(200,200, "Help", textHelp);
   ButtonHelp *buttonHelp = new ButtonHelp(scv::Point(370,3), scv::Point(423, 27), "Help", frameHelp);

   frameHelp->setRelativePosition(scv::Point(0,0));

   textHelp->setParent(frameHelp->getPanel());
   addComponent(buttonHelp);
   addComponent(frameHelp);
}

void Application::onSizeChange(void) {
   _mainPanel->setSize(getWidth(), getHeight());
}

