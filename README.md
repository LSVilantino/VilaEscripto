# VilaEscripto — público
<img src="https://user-images.githubusercontent.com/118770355/232245381-213897db-1ce7-4705-8b57-bba86627b3d5.png"/> 

###### Este documento ou quaisquer citados nele, pertencentes ao grupo Vilantino, são de acesso públicos, mas não devem ser re-publicados com quaisquer modificações. 

#

# LSVE

VilaEscripto (LSVE) é a idéia de conseguir construir programas de qualquer linguagem suportada sem que se dependa de algum Ambiente Integrado (AI), ou a repetição da digitação de linhas de commando, ou o uso de escriptos, também para resolução de repositórios; o LSVE pretende eliminar o uso destas coisas todas e organizar melhor o arquivo-raíz de projectos de programação, juntamente a seus receituários e inter-dependências. 

Em suma, o propósito do LSVE é construir, em tempo-de-corrida, uma linha de commando que é corrida diretamente nos internos do programa, sem que o desenvolvedor precise elaborá-la ou corrê-la, somente a indicar quais são os caminhos dos projectos, ficheiros, receituário, dependências, sinais e compiladores que devem ser usados na construcção, tudo através da leitura e armazenamento dessas informações em ficheiros de textos simples. Isso é feito para que seja facilitada a manutenção dos commandos de construcção ou de corrida dos projectos, os AIs têm uma definição para cada que se usa, cada linguagem usa uma AI diferente, logo, usam definições diferentes para se construir os projectos, os escriptos são muito longos e muitas vezes repetem muitas linhas de definição. Ao invés de se abrir e procurar em vários escriptos, ou ter de configurar os projectos todos no AI para cada um dos projectos, em um arquivo desestruturado, alteram-se somente os ficheiros de texto que o LSVE procura.

Com o ficheiro "ficheiros.txt", que é procurado pelo programa quando o corres, põe-se ao programa os outros ficheiros indicadores: de caminho, construcção, ligação, repositório, etc.

Em 'ficheiros.txt':
compilação > ..\..\lsve\compilação.txt
caminho > ..\..\lsve\caminho.txt

Dado o nome do projecto, por exemplo, 'vilaescripto', e os ficheiros indicativos, procura-se qual o dado referente a ele. 

No ficheiro indicador do compilador:

projecto1 > gcc
projecto2 > g++
vilaescripto > cl
projecto4 > javac
projecto5 > clang

No ficheiro indicador do caminho:

projecto1 > ..\..\projectos\projecto1
projecto2 > ..\..\projectos\projecto2
vilaescripto > ..\..\projectos\vilaescripto
projecto4 > ..\..\projectos\projecto4
projecto5 > ..\..\projectos\projecto5

Deste modo, pode-se construir e formatar uma linha de commando com estes e o restante das informações, sem têr de re-construir o LSVE, e sem grande complexidade de manutenção, com fácil escalabilidade.

#

&nbsp;

###### Todas as imagens neste documento foram feitas e pertencem ao grupo Vilantino, não devem ser utilizadas ou re-publicadas, com ou sem alterações.
