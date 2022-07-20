# Jogo Campo Minado

# Funcionalidades do jogo: [FEITO]

A ação de revelar uma célula pode ser definida conforme as regras abaixo:
1. Uma mina é revelada: nesse caso, jogo encerra com a derrota do usuário;
2. Um número é revelado: o valor indica a quantidade de minas adjacentes considerando as 8 células ao redor de uma posição (vertical, horizontal e
diagonais);
3. Uma posição vazia é revelada: nesse caso, o jogo aplica a ação revelar sobre todas as células adjacentes a essa posição, visto que ela não possui minas
adjacentes.

# A interface do jogo [FEITO]

A interface do jogo deve apresentar as seguintes ações para o usuário:
1. Ação de revelar uma célula;
2. Ação de verificar o tempo decorrido desde a primeira ação de revelar;
3. Ação de solicitar ajuda ao jogo - uma função que receba o estado atual do jogo (sem as informações das minas) e retorna uma posição que possui baixa chances de ser uma mina.

# Modo de jogo autônomo [FEITO]

O programa ainda deve ter um modo de jogo autônomo, isto é, um modo em que jogo executa sozinho suas ações revelando as posições do campo até o fim do
jogo. Esse modo deve usar uma função que receba o estado atual do jogo (sem as informações da mina) e retorna uma posição que possui baixa chances de ser uma
mina. Assim, ao selecionar essa opção, o jogo deve escolher uma posição e revelá-la iterativamente até que o final, ou seja, vitória ou derrota. 

# Técnicas de programação [FEITO]

Quanto à aplicação das técnicas de programação, vocês devem empregar ao menos 5 dos tópicos abaixo de modo adequado ao problema:

- Estruturas, enumerações e typedef;
- Alocação dinâmica de memória;
- Passagem por referência;
- Recursão;
- Manipulação de arquivos;
- Modularização do código;

# Observações