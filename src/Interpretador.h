/* 
 * File:   Interpretador.h
 * Author: ubuntu
 *
 * Created on 2 de Outubro de 2009, 20:22
 */

#ifndef _INTERPRETADOR_H
#define	_INTERPRETADOR_H
#include "NoLDE.h"
#include <stdlib.h>
#include <sstream>
#include <string>
#include <string.h>
#include <strings.h>
#include <iostream>
using namespace std;

class Interpretador {
public:
    Interpretador();
    bool enqueue(string x);
    bool dequeue(string& x);
    bool front(string& x);
    NoLDE* buscaLista(Chave a);
    void listar();
    void imprimeVariavel(string s);
    void insereLista(RegistroVariaveis reg);
    bool push(string s);
    bool pop(string& s);
    bool top(string& s);
    void comandoPosfixa(string s);
    void comandoInfixa(string s);
    bool caractereInvalido(string s);
    string operacaoIntermediaria(string s, int x);
    string excessaoNegativo(string s, int x);
    string operandoAnterior(string s, int x, int& tam1);
    string operandoPosterior(string s, int x, int& tam2);
    string operarInfixa(string s);
    bool atribuicao(string s);
    void removerEspacos(string& s);
    bool prcd(string s, string r);
    bool ehOperadorValido(string s);
    bool ehOperando(string s);
    void infixoParaPosfixo(string s);
    float stringToFloat(string s);
    float operacao(char ch, float a, float b);
    string operarPosfixa();
    virtual ~Interpretador();
private:

    /**Na classe Interpretador.h é criado as variavéis topoPilha,
     * sizePilha, *pilha, sizeFila, inicioFila, finalFila, fila,
     * *AIL, lengthLista, operando, conteudo. Todas essas variáveis
     * são reconhecidas dentro dos métodos criados na classe Interpretador.h**/
    int topoPilha;
    int sizePilha;
    string *pilha;
    int sizeFila;
    int inicioFila;
    int finalFila;
    string* fila;
    NoLDE *AIL;
    int lengthLista;
    bool operando;
    string conteudo;

};

#endif	/* _INTERPRETADOR_H */

