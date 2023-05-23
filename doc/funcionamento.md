# VilaEscripto — público
<img src="https://user-images.githubusercontent.com/118770355/232245381-213897db-1ce7-4705-8b57-bba86627b3d5.png"/> 

###### Este documento ou quaisquer citados nele, pertencentes ao grupo Vilantino, são de acesso público e não devem ser re-publicados com quaisquer modificações. 

# Funcionamento do LSVE

O LSVE trabalha inteiramente com definição e arranjo de valôres. O utilizador é que o responsável por alimentar o LSVE com o que precisa usado para formar as linhas de commando através de um ficheiro indicado. 

Há modos diferentes de se introduzir valôres ao LSVE via ficheiro de texto, mas todos funcionam através do método de passe/clave e valôr, separados por um sinal.
	
	passe (separador/sinal) valôr

Eis como se parecem em uma aplicação mais fidedigna:

	1. Plataforma > Windows
	2. Projecto > VilaEscripto
	3. Caminho do Projecto > ..\..\VilaEscripto\
	4. Ficheiros do projecto >> ..\..\VilaEscripto\
	5. Compilador do projecto >>> ..\..\Compiladores.txt

Neste exemplo, valôres de tipos e formas diferentes são determinados por seus separadores. 

Nas segunda e terceira linhas, temos '>' (um sinal maior), indica que o valôr daquela clave é literalmente o que foi digitado a seguir e não deve ser tratado.

Na quarta, '>>' (dois sinais maiores), aponta que os valôres estão contidos em uma outra localização, seja um ficheiro ou um directório. 
Caso um ficheiro, todas os valôres contidas nele são armazenadas. Se for um directório, todos o nome de todos os ficheiros e pastas são inclusos.

	Por fazer — permitir adquirir um valôr de forma automática, por exemplo: Compilador do projecto >Compilador para $(Plataforma)> ..\..\Compilador.txt. 
	
	Aqui, entre os dois sinais maiores, usa-se uma clave que será procurada dentro do valôr de maneira automática, sem interação com o utilizador.
	No caso de 'Compilador do projecto' (quinta linha), seria atribuído o valôr do passe 'Compilador para $(Plataforma)' (sendo Windows o valôr de $(Plataforma), encontrado em '..\..\Compilador.txt'. Supondo que dentro deste ficheiro exista um passe 'Compilador para Windows' de valôr 'cl', seria repassado ao passe 'Compilador do projecto', requisitante do valôr.

	Pode-se também usar como valôr da clave outros ficheiros com outros tipos de separadores, mas não seria recomendável usar >> como procura à clave, e dentro usar >>>, já que acionaria uma selecção, envolvendo a acção do utilizador.



Na quinta linha, o separador '>>>' (dois sinais maiores) diz que há uma selecção adiante, comportamento semelhante ao separador anterior, mas
ao invés de simplesmente armazenar os valôres encontrados, permite-se a escolha de alguma delas, a seleccionada é armazenada.
	
#

Posteriormente, selecciona-se os 'modelos' para definir como as variáveis são ordenadas.

	rmdir $(Caminho do Projecto) 
Elimina o arquivo do projecto (Não faça isso, não me resposabilizo por qualquer arquivo perdido).
	
	echo $(Ficheiros do Projecto)|rm
Elimina todos os ficheiros do projecto no PShell (Não faça isso, não me resposabilizo por quaisquer ficheiros perdidos).

Deste modo, pode-se construir e formatar uma linha de commando com estes e o restante das informações, sem têr de re-construir o LSVE, e sem grande complexidade de manutenção, com fácil incremento.

#

&nbsp;

###### Todas as imagens neste documento foram feitas e pertencem ao grupo Vilantino, não devem ser utilizadas ou re-publicadas, com ou sem alterações.
