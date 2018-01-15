/* 
 * File:   RegistroPessoa.h
 * Author: ubuntu
 *
 * Created on 2 de Outubro de 2009, 13:59
 */

#ifndef _REGISTROVARIAVEIS_H
#define	_REGISTROVARIAVEIS_H
#include "Chave.h"
#include <iostream>
using namespace std;

//! RegistroVariaveis .
/*!
 *  O tipo estrutura RegistroVariaveis tem como campos nomeVariavel (do tipo Chave),
 * float (do tipo valorVariavel).
*/
typedef struct RegistroVariaveis {
    Chave nomeVariavel;
    float valorVariavel;
};

#endif	/* _REGISTROPESSOA_H */

