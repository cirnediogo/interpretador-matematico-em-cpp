/* 
 * File:   main.cpp
 * Author: ubuntu
 *
 * Created on 2 de Outubro de 2009, 19:17
 */

#include "Interpretador.h"

/*
 * 
 */

/**
 * A funcao main, a primeira funcao a ser chamada,
 * instancia o objeto programa da classe Interpretador.
 * Na main foi mostrado o seguinte exemplo, para testar o programa:
 * foram atribídos os valores a = 100, para b = 30, para c = -50,
 * d = 2. Em seguida, é pedido para se revelar o valor de b (no caso, 30).
 * Em seguida, atribui-se um novo valor para c atraves de uma equação dada.
 * Posteriormente, de similiar forma, cria-se uma variável z atravé de uma equação dada.
 * Logo após, atribui-se um novo valor para a.
 * Finalizando, mostramos o valor das variáves de a, c e z.
   \return int
 */
int main(int argc, char** argv) {

    Interpretador programa;
    programa.comandoPosfixa("a = 100");
    programa.comandoPosfixa("b=30");
    programa.comandoPosfixa("c=-50");
    programa.comandoPosfixa("d=2");
    programa.comandoPosfixa("b");
    programa.comandoPosfixa("c = b*d + a/25");
    programa.comandoPosfixa("z = b + a*d/2");
    programa.comandoPosfixa("a=c*b-d");
    programa.comandoPosfixa("a");
    programa.comandoPosfixa("c");
    programa.comandoPosfixa("z");
    programa.listar();
//    programa.comandoInfixa("a = 100");
//    programa.comandoInfixa("b=30");
//    programa.comandoInfixa("c=-50");
//    programa.comandoInfixa("d=2");
//    programa.listar();
//    programa.comandoInfixa("b");
//    programa.comandoInfixa("c = b*d + a/25");
//    programa.comandoInfixa("z = b + a*d/2");
//    programa.comandoInfixa("c");
//    programa.comandoInfixa("z");
//    programa.listar();

    return (EXIT_SUCCESS);
}

