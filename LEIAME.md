# EP01 - Introdução à Computação Ciêntéfica

## Descrição

Este trabalho inclui a implementação de 4 algoritmos clássicos para a resolução de sistemas lineares na forma Ax = b. O objetivo é comparar o tempo de execução de cada um dos métodos, bem como os FLOPs utilizados. Para tal, o programa principal foi instrumentado com a biblioteca LIKWID. 

## Métodos Implementados

1. **Eliminação de Gauss**: A implementação deste algoritmo clássico inclui pivoteamento parcial, e retro-substituição. O algoritmo também confere o pivot e as linhas para identificar sistemas com infinitas, ou nenhuma, solução.

3. **Método de Gauss-Seidel**: Esta implementação é limitada a 50 iterações. O critério de convergêngia é o da norma máxima da diferença entre os vetores solução da iteração atual para a última; se a diferença for menor que 1e-4, o algoritmo se encerra. 

2. **Eliminação de Gauss para Matrizes Tridiagonais**: Uma variação do método de eliminação de Gauss otimizada para matrizes garantidamente 3-diagonais. O algoritmo divide a matriz em 3 vetores para cada diagonal, e opera sobre eles para melhorar o tempo de execução. 

4. **Método de Gauss-Seidel para Matrizes Tridiagonais**: Uma variação do método de Gauss-Seidel otimizada para matrizes garantidamente 3-diagonais. O algoritmo divide a matriz em 3 vetores para cada diagonal, e opera sobre eles para melhorar o tempo de execução. Esta implementação também é limitadas a 50 iterações, com um critério de convergência norma máxima da diferença menor que 1e-4.


## Uso

Para compilar, faça:
~~~
make purge
make
~~~

Para utilizar o programa, faça:
~~~
./perfSL < sl.dat
~~~

Onde sl.dat é um arquivo contendo, na primeira linha, a dimensão do sistema, seguida pela matriz aumentada, onde seus coeficientes são separados por um único espaço. Ex:
~~~
3
1 1 10 12
10 1 1 12
1 10 1 12
~~~

Para executar com instrumentação por LIKWID, utilize o script shell fornecido, da seguinte forma:
~~~
./perfSL.sh <sl.dat>
~~~
Esta execução irá gerar um arquivo FLOPS_DP.log, o qual contém toda a saída do LIKWID para a métrica FLOPS_DP, além de imprimir ao console somente a métrica MFLOP/s. O script pode ser alterado para gerar logs de outras métricas adicionais.

## Funcionalidades e Limitações

- O programa deve obrigatóriamente ser compilado e executado em uma máquina física rodando Linux. a biblioteca LIKWID deve estra devidamente instalada e acessível ao programa.
- A entrada deve ser bem formada, seguindo exatamente a forma indicada. O programa não tem tratamento de erro em caso de entradas mal formadas, e irá apresentar comportamento de execução indesejado. 
- O programa não possuí tratamento de caso para matrizes não 3-diagonais. No caso dessas matrizes, os métodos específicos irão executar sobre elas de qualquer maneira, produzindo resultados incorretos, que devem ser ignorados.
- No caso dos métodos iterativos de Seidel, também não há testes que parem a execução para uma matriz divergente. O programa vai executar ao máximo 50 iteraçãoes, e retornará a solução até este ponto. O programa tende a apresentar números de grande magnitude, ou '-nan', para matrizes divergentes, que também devem ser ignorados.
- O programa não possuí um tratamento extensivo para sistemas sem solução única. O programa testa para linhas do tipo 0 = b, ou para pivots nulos, no caso de sistemas com infinitas ou nenhuma solução, mas não possuí outros tratamentos mais robustos para classificar a natureza do sistema linear.

