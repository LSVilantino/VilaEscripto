# VilaEscripto — público
<img src="https://user-images.githubusercontent.com/118770355/232245381-213897db-1ce7-4705-8b57-bba86627b3d5.png"/> 

###### Este documento ou quaisquer citados nele, pertencentes ao grupo Vilantino, são de acesso públicos e não devem ser re-publicados com quaisquer modificações. 

#

# LSVE

VilaEscripto (LSVE) foi uma idéia, inicialmente, de conseguir construir programas de sem depender de algum Ambiente Integrado (AI/IDE), ou a repetição da digitação de linhas de commando, ou o uso de escriptos, também para resolução de repositórios; 
o LSVE pretende eliminar o uso destas coisas todas e organizar melhor o arquivo-raíz de projectos de programação, juntamente a seus receituários e inter-dependências. 

O LSVE foi desenhado para que, em tempo-de-corrida, 
uma linha de commando fosse corrida diretamente nos internos do programa, sem que o desenvolvedor precise elaborá-la, somente a indicar quais são os caminhos dos projectos, ficheiros, receituário, dependências, sinais e compiladores que devem ser usados na construcção, tudo através da leitura e armazenamento dessas informações em ficheiros de textos simples. 

### Qual o propósito, por quê não só usar uma AI, ou um CLI?

Isso é feito para que seja facilitada a manutenção dos commandos de construcção ou de corrida dos projectos, principalmente os projectos inter-dependentes, os AIs têm uma definição para cada que se usa, cada AI é dedicada a um conjunto restricto de linguagens, então geralmente utiliza-se muitas, usam definições diferentes para a construcção. 

Os escriptos são muito longos e muitas vezes repetem-se. Ao invés de se abrir e procurar em vários escriptos, ou ter de configurar os projectos todos no AI para padronizá-los, alteram-se somente os ficheiros de texto, entregues ao LSVE.

Actualmente, da maneira que se desenrolou, o LSVE é mais abrangente. Antes, que servia para este único propósito, faz mais vis ao nome, podendo compôr e desempenhar múltiplos tipos de commandos gerais, definidos a gosto do utilizador.

Mais detalhes técnicos, sigas o documento: doc/funcionamento.

&nbsp;

###### Todas as imagens neste documento foram feitas e pertencem ao grupo Vilantino, não devem ser utilizadas ou re-publicadas, com ou sem alterações.
