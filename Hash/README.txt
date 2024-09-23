Conclusão: O tamanho do número primo é inversamente proporcional à quantidade de colisões que irão ocorrer.
Por exemplo, quanto menor o número primo escolhido, menor a tabela de hash e, consequentemente,
ocorrerão mais colisões devido à baixa quantidade de posições, fazendo com que os elementos tendam a colidir muito mais.
Por outro lado, quanto maior o número primo escolhido, maior a tabela de hash e, assim, menor a quantidade de colisões,
pois haverá muitas posições e os elementos (neste caso as cidades) serão distribuídos mais uniformemente.

ENLAÇAMENTO DESLOCADO
O método funciona a partir da concatenação dos valores hash para diminuir a quantidade de colisões.

Por que usar? 
O enlaçamento deslocado diminui a quantidade de colisões na tabela hash.

Por que não usar?
As diferenças nos números de colisões não são tão significativas e para ser, precisamos aumentar muito o tamanho da tabela hash e consequentemente aumenta o numero de espaços vazios, "buracos".