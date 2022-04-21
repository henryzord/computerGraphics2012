# Instruções

Existem dois canvas nesta aplicação: o canvas do sinal original (esquerda) e o canvas da IDCT (direita). 
Os gráficos das funções correspondem aos sinais exibidos abaixo deles.
O eixo x será exibido em preto, quando ele estiver dentro do Canvas (se o gráfico não
chegar perto de nenhum y = 0, então ele não será mostrado).
A função sempre será exibida em vermelho.

Para comprimir uma coleção de dados, use o slider e desloque-o para a direita. 
O método de compressão é por truncamento. Ele trunca metade do vetor de DCTs, 
e calcula a IDCT em cima desse novo vetor DCT.
O TextField ao lado do Slider dirá se está comprimido ou não.
Para trocar a coleção, utilize o ComboBox em cima do Slider.