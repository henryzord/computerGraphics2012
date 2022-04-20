/**
Autor: Henry Cagnini
Matrícula: 201010352
*/

#include <SCV/SCV.h>
#include "Application.h"

int main(int argc, char* argv[]) {
   try {
      Application *kernel = new Application();
      scv::Kernel::setInstance(kernel);

      kernel->init();

      kernel->run();
   } catch(exception &e) {
      std::cout << "Erro: " << e.what() << std::endl;
   }
   return 0;
}
