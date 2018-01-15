/* 
 * File:   Interpretador.cpp
 * Author: ubuntu
 * 
 * Created on 2 de Outubro de 2009, 20:21
 */

#include "Interpretador.h"
#include <strstream>

//! Construtor.
/*!
 *  O Consturou cria a pilha e a fila
*/
Interpretador::Interpretador() {
    sizePilha = 20;
    pilha = new string[20];
    topoPilha = 0;
    sizeFila = 20;
    inicioFila = -1;
    finalFila = -1;
    fila = new string[20];
    AIL = new NoLDE;
    AIL->ante = AIL->prox = AIL;
    lengthLista = 0;
    conteudo = "";
    operando = true;
}

//! stringToFloat.
/*!
 *  O método transforma recebe um varável string a qual transforma para float.
    \param a é uma strig.
    \return floar.
*/
float Interpretador::stringToFloat(string s) {
    return atof(s.c_str());
}

//! operacao.
/*!
 *  O método recebe uma caractere, o qual será interpretado como uma função aritimética,
 * além de dois número. Esses dois valores sofrerão a operação interpretada.
 * Por exemplo: Caso o método receba '+', 2, 3 ele efetuará e retonará a operação 2 + 2.
    \param ch é um char.
    \param a é um float.
    \param b é um float.
    \return floar.
*/
float Interpretador::operacao(char ch, float a, float b) {
    switch (ch){
        case '+': return a + b; break;
        case '-': return a - b; break;
        case '*': return a * b; break;
        case '/': return a / b; break;
    }
}

// função enqueue da fila
//! enqueue.
/*!
 * O metodo enqueue é responsavel por inserir um elemento no final da fila "fila".
    \param x é uma string. Nele está o valor que será inserido no final da fila "fila".
    \return bool.
*/
bool Interpretador::enqueue(string x) {
    int mod = ((finalFila+1) % sizeFila);
    if (mod != inicioFila)
    {
        finalFila = mod;
        fila[finalFila] = x;
        if (inicioFila == -1)
        {
            inicioFila = 0;
        };
        return true;
    }
    else
    {
        return false;
    }
}


//! dequeue.
/*!
 * O metodo dequeue é responsavel por retirar o primeiro elemento da fila "fila".
    \param x é uma string*. Ele receberá o valor do primeiro elemento da fila "fila".
    \return bool.
*/
bool Interpretador::dequeue(string& x) {
    if (inicioFila != -1)
    {
        x = fila[inicioFila];
        if (inicioFila == finalFila)
        {
            inicioFila = -1;
            finalFila = -1;
        }
        else
        {
            inicioFila = ((inicioFila+1) % sizeFila);
        };
        return true;
    }
    else
    {
        return false;
    };
}


//! front.
/*!
 * O metodo front é responsavel por revelar o primeiro elemento da fila "fila".
    \param x é uma string*. Ele receberá o valor do primeiro elemento da fila "fila".
    \return bool.
*/
bool Interpretador::front(string& x) {
    if (inicioFila != -1)
    {
        x = fila[inicioFila];
        return true;
    }
    else
    {
        return false;
    }
}


//! ehOperando.
/*!
 * O metodo ehOperando é responsavel por distinguir se o caractere(dado no parametro
 * de entrada da funcao) é um operando ou um operador. O método retorna true se a entrada é um operando ou false se é um operador.
    \param s é um string*. 
    \return bool.
*/
bool Interpretador::ehOperando(string s) {
    char y = s[0];
    bool z;
    if (((y >= 48) && (y <= 57)) || ((y >= 97) && (y <= 122))) {
        z = true;
    } else {
        z = false;
    };
    return z;
}

// retorna true se o operador for um dos 4 operadores basicos

bool Interpretador::ehOperadorValido(string s) {
    char y = s[0];
    bool z;
    if ((y == 42 || y == 43) || (y == 47 || y == 45)) {
        z = true;
    } else {
        z = false;
    };
    return z;
}

//! top.
/*!
 * O metodo top é responsavel por revelar o elemento do topo da pilha "pilha".
    \param s é uma string*. Ele receberá o valor do topo da pilha "pilha".
    \return bool.
*/
bool Interpretador::top(string& s) {
    if (topoPilha > 0)
    {
        s = pilha[topoPilha-1];
        return true;
    }
    else
    {
        return false;
    }
}


//! prcd.
/*!
 * O metodo verifica a precedencia entre dois operadores.
    \param s é uma string. Ele representará um dos operadores a serem comparados.
    \param r é uma string. Ele representará um dos operadores a serem comparados.
    \return bool.
*/
bool Interpretador::prcd(string s, string r) {
    if ((s == "*") || (s == "/")) {
        return true;
    } else {
        if ((r == "+") || (r == "-")) {
            return true;
        } else {
            return false;
        }
    }
}



//! infixoParaPosfixo.
/*!
 * O metodo pega uma string, representando a equação matemática na notação parametrizada, e a tranforma
 * para a notação polonesa inversa, colocando-a numa fila.
    \param s é uma string. Ele representará a equção matemática na notação parametrizada.
    \return void.
*/
void Interpretador::infixoParaPosfixo(string s) {
    string symb, topSymb, aux;
    aux = "";
    bool precd;
    while (s != "") {
        symb = s[0];
        s.erase(0, 1);
        if (ehOperando(symb)) {
            topSymb = s[0];
            while (ehOperando(topSymb)) {
                s.erase(0, 1);
                symb = symb + topSymb;
                topSymb = s[0];
            }
            enqueue(symb);
        } else {
            if (ehOperadorValido(symb)) {
                precd = true;
                while ((aux != "") && precd) {
                    topSymb = aux[0];
                    if (precd = prcd(topSymb, symb)) {
                        aux.erase(0, 1);
                        enqueue(topSymb);
                    }
                };
                aux = symb + aux;
            } else {
                cout << "Operador invalido " << symb << ".\n";
                s = "";
                aux = "";
                }
            }
    };
    while (aux != "") {
        topSymb = aux[0];
        aux.erase(0, 1);
        enqueue(topSymb);
    }
}


//! push.
/*!
 * O metodo push é responsavel por inserir um elemento na pilha "pilha".
    \param s é uma string. Nele está o valor que será inserido ns pilha "pilha".
    \return bool.
*/

bool Interpretador::push(string s) {
    if (topoPilha < sizePilha)
    {
        pilha[topoPilha] = s;
        topoPilha = topoPilha + 1;
        return true;
    }
    else
    {
        return false;
    }
}

//! pop.
/*!
 * O metodo pop é responsavel por retirar o elemento do topo da pilha "pilha".
    \param s é uma string*. Ele receberá o valor do elemento do topo da pilha "pilha".
    \return bool.
*/
bool Interpretador::pop(string& s) {
    if (topoPilha > 0)
    {
        topoPilha = topoPilha - 1;
        s = pilha[topoPilha];
        return true;
    }
    else
    {
        return 0;
    }
}


//! removerEspacos.
/*!
 * O metodo removerEspacos é responsavel por remover os espaçoes entre os termos da equação.
 * Ex: "a = 10" => "a=10".
    \param s é uma string*. Ele representa a equação matemática na forma parametrizada.
    \return void.
*/
void Interpretador::removerEspacos(string& s) {
    int y;
    y = s.find(" ");
    while (y != -1){
        s.erase(y,1);
        y = s.find(" ");      
    }
}


//! atribuicao.
/*!
 * O metodo atribuicao é responsavel por verifica se tem '=' na string. Caso tenha é atribuição de valor.
    \param s é uma string. Ele representa a equação matemática na forma parametrizada.
    \return bool.
*/
bool Interpretador::atribuicao(string s) {
    int y;
    y = s.find("=");
    if (y == -1){
        return false;
    }else{
        return true;
    }
}


//! buscaLista.
/*!
 * O metodo buscaLista é responsável por buscar um elemento na LDE.
    \param a é uma Chave. Ele representa a chave do nó a ser buscado.
    \return NoLDE*.
*/
NoLDE* Interpretador::buscaLista(Chave a) {
    NoLDE *ultimo = AIL->ante;
    NoLDE *procurado = NULL;
    NoLDE *pont = NULL;
    (AIL->var).nomeVariavel = a + ".";
    if (a <= (ultimo->var).nomeVariavel) {
        pont = AIL->prox;
        while ((pont->var).nomeVariavel < a){
            pont = pont->prox;
        }
        procurado = pont;
    }
    else{
        procurado = AIL;
    }
    return procurado;
}



//! operarPosfixa.
/*!
 * O metodo operarPosfixa retorna o resultado de uma expressao armazenada na fila na forma posfixa.
    \return string.
*/
string Interpretador::operarPosfixa() {
    string symb, op1, op2;
    NoLDE* pont = NULL;
    char ch;
    float result, a, b;
    while (finalFila != -1) {
        dequeue(symb);
        if (ehOperando(symb)) {
            push(symb);
        } else {
            pop(op2);
            pop(op1);
            ch = op1[0];
            if ((ch >= 97) && (ch <= 122)) {
                pont = buscaLista(op1);
                a = (pont->var).valorVariavel;
            } else {
                a = stringToFloat(op1);
            };
            ch = op2[0];
            if ((ch >= 97) && (ch <= 122)) {
                pont = buscaLista(op2);
                b = (pont->var).valorVariavel;
            } else {
                b = stringToFloat(op2);
            };
            ch = symb[0];
            result = operacao(ch, a, b);
            stringstream x;
            x << result;
            symb = x.str();
            push(symb);
        }
    };
    pop(symb);
    return symb;
}


//! insereLista.
/*!
 * O metodo insereLista insere elementos na LDE.
    \param reg é uma RegistroVariaveis. É um elemento da lista a ser inserido.
    \return void.
*/
void Interpretador::insereLista(RegistroVariaveis reg) {
    NoLDE* pt = NULL;
    NoLDE* anterior = NULL;
    NoLDE *pont = NULL;
    pont = buscaLista(reg.nomeVariavel);
    if ((pont == AIL) || ((pont->var).nomeVariavel != reg.nomeVariavel))
    {
        anterior = pont->ante;
        pt = new NoLDE;
        pt->var = reg;
        pt->ante = anterior;
        pt->prox = pont;
        anterior->prox = pt;
        pont->ante = pt;
        lengthLista = lengthLista +1;
    }
    else
    {
        (pont->var).valorVariavel = reg.valorVariavel;
    }
}


//! listar.
/*!
 * O metodo listar imprime a LDE.
    \return void.
*/
void Interpretador::listar() {
    NoLDE *ptr = AIL->prox;
    if (lengthLista == 0) {
        cout << "Lista Vazia.\n\n";
    } else {
        cout << "Lista:\n";
    for (int i = 0; i < lengthLista; i++) {
        cout << "Nome da Variavel = " << (ptr->var).nomeVariavel <<
                "; Valor da Variavel = " << (ptr->var).valorVariavel << "\n";
        ptr = ptr->prox;
    };
    cout << "\n";
    }
}



//! imprimeVariavel.
/*!
 * O método imprimeVariavel é usado quando o usuário apenas dar uma letra na expressao matemática. Dessa forma
 * o método irá receber essa letra e a imprime junto com um possivél valor já associado a ela, na lista.
    \param s é uma Chave.
    \return void.
*/
void Interpretador::imprimeVariavel(Chave s) {
    NoLDE* pont = NULL;
    pont = buscaLista(s);
    if ((pont == AIL) || ((pont->var).nomeVariavel != s)) {
        cout << "Elemento nao esta na lista.\n\n";
    } else {
        cout << s << " = " << (pont->var).valorVariavel << "\n\n";
    }
}


//! comandoPosfixa.
/*!
 * O método comandoPosfixa é uma operação basica do programa para a forma posfixa, ou seja, nele é incluído
 * todos os métodos necessários pra executar o programa fazendo operações em equançoes na forma polonesa.
    \param s é uma string.
    \return void.
*/
void Interpretador::comandoPosfixa(string s) {
    string variavel;
    float valor;
    RegistroVariaveis reg;
    removerEspacos(s);
    if (atribuicao(s)) {
        variavel = s[0];
        s.erase(0, 2);
        infixoParaPosfixo(s);
        s = operarPosfixa();
        valor = stringToFloat(s);
        reg.nomeVariavel = variavel;
        reg.valorVariavel = valor;
        insereLista(reg);
    } else {
        imprimeVariavel(s);
    }
}


//! caractereInvalido.
/*!
 * O método caractereInvalido retorna true se há algum caractere inválido na expressao, false caso contrario
    \param s é uma string.
    \return bool.
*/
bool Interpretador::caractereInvalido(string s) {
    string temp = s;
    while (temp != "") {
        char c = temp[0];
        if (((c >= 97) && (c <= 122)) || ((c >= 48) && (c <= 57))) {
            return false;
        } else {
            if (((c == 42) || (c == 43)) || ((c == 45) || (c == 47))) {
                return false;
            } else {
                return true;
            }
        };
        temp.erase(0, 1);
    }
}


//! operandoAnterior.
/*!
 * O método operandoAnterior verifica o numero anterior a um operador (numa equação na forma infixa).
    \param s é uma string. Representa a equção matemática.
    \param x é um inteiro. Representa a posição de um operador que já foi achado.
    \tam1 é um inteiro*. Representa a quantidade de algarismos no número que vem antes do operador.
    \return string.
*/
string Interpretador::operandoAnterior(string s, int x, int& tam1) {
    int y = x - 1;
    string r;
    char c = s[y];
    if ((c >= 48) && (c <= 57)) {
        while ((c >= 48) && (c <= 57)) {
            y = y - 1;
            c = s[y];
        };
        y = y + 1;
    };
    tam1 = x - y;
    r = s.substr(y, tam1);
    return r;
}


//! operandoPosterior.
/*!
 * O método operandoPosterior verifica o numero posterior a um operador (numa equação na forma infixa).
    \param s é uma string. Representa a equção matemática.
    \param x é um inteiro. Representa a posição de um operador que já foi achado.
    \tam2 é um inteiro*. Representa a quantidade de algarismos no número que vem depois do operador.
    \return string.
*/
string Interpretador::operandoPosterior(string s, int x, int& tam2) {
    int y = x + 1;
    string r;
    char c = s[y];
    if ((c >= 48) && (c <= 57)) {
        while (c >= 48 && c <= 57) {
            y = y + 1;
            c = s[y];
        };
        y = y - 1;
    }
    tam2 = y - x;
    r = s.substr(x+1, tam2);
    return r;
}



//! operacaoIntermediaria.
/*!
 * O método operacaoIntermediaria da início a operação matemática que deve ser realizada a cada
 * instância da expressão(para forma infixa).
    \param s é uma string. Representa a equção matemática.
    \param x é um inteiro. Representa a posição de um operador na string.
    \return string.
*/
string Interpretador::operacaoIntermediaria(string s, int x) {
    NoLDE* pont = NULL;
    char c, ch;
    string s1, s2, result;
    float a, b, r;
    c = s[x];
    int tam1, tam2;
    s1 = operandoAnterior(s, x, tam1);
    s2 = operandoPosterior(s, x, tam2);
    ch = s1[0];
    if ((ch >= 97) && (ch <= 122)) {
        pont = buscaLista(s1);
        a = (pont->var).valorVariavel;
    } else {
        a = stringToFloat(s1);
    };
    ch = s2[0];
    if ((ch >= 97) && (ch <= 122)) {
        pont = buscaLista(s2);
        b = (pont->var).valorVariavel;
    } else {
        b = stringToFloat(s2);
    };
    r = operacao(c, a, b);
    stringstream y;
    y << r;
    result = y.str();
    int tam = tam1 + tam2 + 1;
    s.replace(x-tam1, tam, result);
    return s;
}


//! excessaoNegativo.
/*!
 * O método excessaoNegativo verifica se o sinal "-" e um operador ou uma representação para um número negativo.
    \param s é uma string. Representa a equção matemática.
    \param x é um inteiro. Representa a posição do sinal "-".
    \return string.
*/
string Interpretador::excessaoNegativo(string s, int x) {
    NoLDE* pont = NULL;
    char c, ch;
    string s1, s2, result;
    float a, b, r;
    c = s[x];
    int tam1, tam2;
    s1 = "0";
    tam1 = 0;
    s2 = operandoPosterior(s, x, tam2);
    ch = s1[0];
    if ((ch >= 97) && (ch <= 122)) {
        pont = buscaLista(s1);
        a = (pont->var).valorVariavel;
    } else {
        a = stringToFloat(s1);
    };
    ch = s2[0];
    if ((ch >= 97) && (ch <= 122)) {
        pont = buscaLista(s2);
        b = (pont->var).valorVariavel;
    } else {
        b = stringToFloat(s2);
    };
    r = operacao(c, a, b);
    stringstream y;
    y << r;
    result = y.str();
    int tam = tam1 + tam2 + 1;
    s.replace(x, tam, result);
    return s;
}



//! operarInfixa.
/*!
 * O método operarInfixa retorna o resultado de uma expressão matemática na forma infixa. Ou seja, ela retorna o resultado final da equação.
    \param s é uma string. Representa a equção matemática.
    \return string. Rpresenta o resutado da equação matemática.
*/
string Interpretador::operarInfixa(string s) {
    char c, ch;
    NoLDE* pont;
    int x;
    string s1, s2, result;
    float a, b, r;
            x = s.find("*");
            while (x != -1) {
                s = operacaoIntermediaria(s, x);
                x = s.find("*");
            };
            x = s.find("/");
            while (x != -1) {
                s = operacaoIntermediaria(s, x);
                x = s.find("/");
            };
            x = s.find("+");
            while (x != -1) {
                s = operacaoIntermediaria(s, x);
                x = s.find("+");
            };
            x = s.find("-");
            while (x != -1) {
                if (x == 0) {
                    s = excessaoNegativo(s, x);
                    x = -1;
                } else {
                    s = operacaoIntermediaria(s, x);
                    x = s.find("-");
                }
            };
            return s;
}


//! comandoInfixa.
/*!
 * comandoInfixa e o méotodo principal para se realizar operações em equações infixas.
  \param s é uma string. Representa a equação matemática na forma infixa.
  \return void.
*/
void Interpretador::comandoInfixa(string s) {
    string variavel;
    float valor;
    RegistroVariaveis reg;
    removerEspacos(s);
    if (atribuicao(s)) {
        variavel = s[0];
        s.erase(0, 2);
        if (caractereInvalido(s)) {
            cout << "Existe operador invalido";
        } else {
            valor = stringToFloat(operarInfixa(s));
            reg.nomeVariavel = variavel;
            reg.valorVariavel = valor;
            insereLista(reg);
        }
    } else {
        imprimeVariavel(s);
    }
}

//! Destrutor.
/*!
 * No Destrutor, usamos as funções "delete" para desalocoar o espaco de memoria ocupado pela pilha, fila e AIL.
*/
Interpretador::~Interpretador() {
    delete [] pilha;
    delete [] fila;
    delete AIL;
}