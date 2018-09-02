# Trabalho de estrutura de dados
## Universidade Federal De Santa Maria (https://www.ufsm.br/)

Trabalho para o curso de sistemas para internet da cadeira do segundo semestre (http://csi.ufsm.br/) 

### Considerações

Desenvolva um programa para gerenciar uma tabela hash com dados dos alunos da UFSM. Dos
alunos deve-se saber a matrícula, o nome, o sobrenome e o e-mail. Você deve criar uma tabela
hash através de um vetor de registros, a qual conterá em suas posições ocupadas os
elementos que coincidirem com o cálculo hash da matricula do aluno. Além das informações
do aluno, o registro deverá conter um ponteiro. Quando houver uma colisão de hash (a
posição do vetor já estiver ocupada), o elemento deve ser inserido na lista encadeada (através
do ponteiro), que conterá os elementos com colisão (imagem ilustrativa abaixo). O programa
deve permitir de forma dinâmica a inserção, visualização e retirada de alunos. As funções do
exercício devem ser definidas em uma biblioteca denominada alunos.h. Adicionalmente,
mantenha uma lista encadeada com as chaves utilizadas no vetor. Desta forma, percorrendo a
lista de chaves, é possível acessar todos os elementos salvos na tabela (lembre-se de percorrer
os elementos encadeados). Lembre-se também de remover elementos dessa lista quando eles
deixarem de existir na tabela.

### Requisitos

#### Inserção
* Caso haja uma colisão e a posição do vetor já estiver em uso, o novo elemento deve ser
encadeado, como o último elemento.

* Alunos não podem se repetir, deve-se verificar se a matricula é a mesma e, nesse caso,
substituir o aluno.

#### Remoção

* Remover alunos com base na sua matrícula. Caso exista mais de um aluno naquela
posição, manter a organização dos alunos remanescentes.

#### Visualização
* Exibir o aluno com base em sua matricula, bem como quantos passos foram necessários
para encontrá-lo. Ex: estava no vetor, um passo. Estava na lista encadeada, N passos + 1.

* Exibir todos os alunos armazenados, através da lista de chaves. Basta percorrer a lista e
utilizar a função de exibir alunos individualmente.



