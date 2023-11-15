# Analisador Léxico

### Configurando ambiente
O trabalho utiliza C++ e a ferramenta FLex, para configurar o ambiente, basta:
* Configurar o ambiente para compilar / executar C++ (cpp) - parte-se do principio que o usuário já tenha confiugrado
* Adicionar a pasta bin do Flex na variável de usuario Path, possibilitando executar comandos flex por linha de comando

------

### Execução
Para execução, são necessários três passos:
* Gerar arquivo cpp a partir do main.lex (sim, -ooutput.cpp está certo, não é permitido espaço entre os dois): flex -ooutput.cpp main.lex 
* Compilar o arquivo cpp gerado no passo anterior: g++ -o output output.cpp -w
* Executar aquivo cpp com a entrada, como o arquivo de teste da pasta test: output test/sample-input.txt

A parte de build está abstraída no comando build.sh, sendo necessário somente executar o último passo.