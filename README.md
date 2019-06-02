# Implementação do Problema da Vila dos Anões
Projeto implementado a partir de problema proposto para a disciplina de Programação Concorrente, ministrada pelo professor Eduardo Alchieri,
do Departamento de Ciência da Computação da Universidade de Brasília.

O projeto foi desenvolvido por:
- Eduardo de Azevedo dos Santos, Matrícula 14/0136967

## Problema Proposto

**Problema da Vila dos Anões**

Um pequeno vilarejo de anões nas montanhas vive majoritariamente
da renda consequente da mineração. Os anões passam o dia minerando
até cansar. Quando todos cansam, o dia de trabalho acaba.

Cada anão entra a mina com uma sacola que comporta 20 pedras. Há
apenas 3 túneis apertados e, como os anões, mesmo pequenos, são
parrudos, apenas um cabe por vez em cada túnel. Os outros anões
esperam na entrada da mina até um túnel liberar. Neste momento,
o anão que saiu vai até a vila entregar os minérios. Se estiver
cansado, ele fica na vila. Senão, ele volta para a mina. Os anões
cansam após carregarem, em média, 3 sacos de volta para a vila.

Após todos cansarem, o dia finaliza, com o expediente se repetindo
novamente no dia seguinte, com todos os anões descansados.

## Como compilar o programa

### Linux

- Clone o repositório do projeto
- Vá até a pasta do projeto
- Execute o comando `make` via terminal
- Vá até a pasta build e execute o programa através do comando `./ANAO X`, aonde X é a quantidade de anões(threads) que o programa irá executar.

### Windows
- Clone o repositório do projeto
- Vá até a pasta do projeto
- Garanta que tenha o MINGW instalado na sua máquina.
- Execute o comando `mingw32-make` via linha de comando.
- Vá até a pasta build e execute o programa através do comando `ANAO.exe X`, aonde X é a quantidade de anões(threads) que o programa irá executar.
