# VilaEscripto — público
<img src="https://user-images.githubusercontent.com/118770355/232245381-213897db-1ce7-4705-8b57-bba86627b3d5.png"/> 

###### Este documento ou quaisquer citados nele, pertencentes ao grupo Vilantino, são de acesso públicos e não devem ser re-publicados com quaisquer modificações. 

###### O conteúdo deste documento, actualmente, é demonstrativo, está incompleto e suas informações estão em trabalho ou são planos futuros.

# Desbraga do LSVE
###### Braga: muro das antigas fortificações; Desbragar: eliminar impedimento.

As desbragas servem do LSVE funcionam através de mensagens na consola. Para saber como um valôr foi adereçado à clave, pode-se verificá-las com o uso de sinais.

Alguns pontos do LSVE têm seus comportamentos alterados quando recebem um sinal, para que tenham suas informações avaliadas. 
Como amóstra, ao lêr um ficheiro pode ser que hajam problemas que não estão ao controle teu, mas que podem ser contornados sem que precise de uma actualização, se o problema for percebido.

Outra é quando se corre algum commando, se não quiseres simplesmente corrê-lo sem validar se está totalmente correcto, durante experimentações ou desenvolvimento, podes recorrêr aos sinais também.

# Como funciona

O LSVE pede como primeiro argumento o ficheiro indicativo, usado para definir as claves e valôres para a função principal do LSVE. 
Como *segundo*, um outro ficheiro que contém os sinais, que deve seguir estrictamente a esta documentação.

##### Por pré-definição, as claves deste ficheiro são seleccionáveis à partida do LSVE.

	Desbragar ficheiro indicativo > desbraga-ficheiro-i (mostra o quê se leu do ficheiro)
	Desbragar valôres das claves > desbraga-clave-e-valôr (mostra as claves e seu valôres)
	Desbragar contenção > desbraga-contenção (mostra o processo para validar se, como amóstra, "ABCD" é contido em "ABCDEF" ― sim, "ABCDEF" contém "ABCD". Usado para comparar nome das claves.)
	Desbragar comparação rígida > desbraga-comparação-rígida (mostra o processo para avaliar se, por exemplo, "ABCD" se compara com "ABCDEF" ― não, são diferentes, a considerar o inteiro: "ABCDEF" não é "ABCD". Usado para comparar nome das claves.)
	Desbragar reposição de variáveis > desbraga-repôr-variável (mostra as claves que foram repostas nos valôres, e por quais valôres foram repostas)

##### Não deve portar separadôres de corrida, pode ser que resulta em comportamento indefinido. Supostamente, seria somente corrido.

#

&nbsp;

###### Todas as imagens neste documento foram feitas e pertencem ao grupo Vilantino, não devem ser utilizadas ou re-publicadas, com ou sem alterações.