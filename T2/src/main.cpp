/**
Henry Cagnini
201010352
*/

#include <SCV/SCV.h>
#include "Application.h"

int main(int argc, char* argv[]) {
   
   Application *kernel = new Application();
   scv::Kernel::setInstance(kernel);

   kernel->init();
   kernel->run();

   system("pause");
   return 0;
}
