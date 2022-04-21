/**
Henry Cagnini
201010352
*/

/**
Uma descri��o passo-a-passo do programa ser� mais sucinta que uma 
explana��o extensiva:

1. Posicione pontos no canvas na fase de desenho. Apenas pontos � esquerda
do eixo principal podem ser desenhados. Um s�lido de rota��o desconsideraria
qualquer ponto posicionado al�m do eixo.
2. Rotacione o objeto utilizando o bot�o rotate.
3. Troque a proje��o (perspectiva/ortogr�fica) usando o primeiro ComboBox.
4. Troque a visuliza��o (pontos/linhas) usando o segundo ComboBox.
5. O slider se refere a quantos passos deseja-se para desenhar o s�lido. A progress�o
ocorre em divisores de 360, come�ando por 4 (4, 5, 6, 8, 9, etc) e terminando em 360.
6. Volte ao modo de desenho desabilitando o bot�o Rotate.
7. As modifica��es impostas ao s�lido e ao plano de proje��o podem ser feitos em tempo 
de rota��o ou desenho.
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
