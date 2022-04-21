/**
Henry Cagnini
201010352
*/

/**
Uma descrição passo-a-passo do programa será mais sucinta que uma 
explanação extensiva:

1. Posicione pontos no canvas na fase de desenho. Apenas pontos à esquerda
do eixo principal podem ser desenhados. Um sólido de rotação desconsideraria
qualquer ponto posicionado além do eixo.
2. Rotacione o objeto utilizando o botão rotate.
3. Troque a projeção (perspectiva/ortográfica) usando o primeiro ComboBox.
4. Troque a visulização (pontos/linhas) usando o segundo ComboBox.
5. O slider se refere a quantos passos deseja-se para desenhar o sólido. A progressão
ocorre em divisores de 360, começando por 4 (4, 5, 6, 8, 9, etc) e terminando em 360.
6. Volte ao modo de desenho desabilitando o botão Rotate.
7. As modificações impostas ao sólido e ao plano de projeção podem ser feitos em tempo 
de rotação ou desenho.
8. Rotacione o objeto utilizando W, S, A, D.
*/

#include <SCV/SCV.h>
#include "Application.h"

int main(int argc, char* argv[]) {
   Application *kernel = new Application();
   scv::Kernel::setInstance(kernel);

   kernel->init();

   kernel->run();
   return 0;
}
