/*

SCV - Simple Components for Visual
Developed at Federal University of Santa Maria - UFSM
LaCA - Computer Applied Laboratory - Laborat�rio de Computa��o Aplicada
webpage: www.inf.ufsm.br/~pozzer/scv
email: pozzer@inf.ufsm.br
2007-2012 

*/

#include <SCV/SCV.h>

#include "Application.h"
#include "Properties.h"
#include <SCV/GapSpring.h>


#include "GroupPanelWrapper.h"
#include "SequentialGroupPanel.h"
#include "ParallelGroupPanel.h"

int main(int argc, char* argv[]) {
   Application *app = new Application();
   scv::Kernel::setInstance(app);   

   app->init();

   app->run();
   return 0;
}
