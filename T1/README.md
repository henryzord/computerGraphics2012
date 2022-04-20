Existem dois canvas nesta aplicacao: o canvas do sinal original (esquerda) 
e o canvas da IDCT (direita). 

Os graficos das funcoes correspondem aos sinais exibidos abaixo deles.

O eixo x sera exibido em preto, quando ele estiver dentro do Canvas (se o grafico não
chegar perto de nenhum `y = 0`, entao ele nao sera mostrado).
A função sempre sera exibida em vermelho.

Para comprimir uma coleção de dados, use o slider e desloque-o para a direita. 
O metodo de compressão e por truncamento. Ele trunca metade do vetor de DCTs, 
e calcula a IDCT em cima desse novo vetor DCT.
O TextField ao lado do Slider dirá se esta comprimido ou não.
Para trocar a coleção, utilize o ComboBox em cima do Slider.