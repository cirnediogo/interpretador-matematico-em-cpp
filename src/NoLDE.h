/* 
 * File:   NoLDE.h
 * Author: ubuntu
 *
 * Created on 28 de Setembro de 2009, 19:59
 */

#ifndef _NOLDE_H
#define	_NOLDE_H
#include "RegistroVariaveis.h"


//! NoLDE.
/*!
 *  O tipo estrutura NoLDE tem como campos var (do tipo RegistroVariaveis),
 * *prox (do tipo NolDE) e *ante (do tipo NolDE).
*/
typedef struct NoLDE {
    RegistroVariaveis var;
    NoLDE *prox;
    NoLDE *ante;
} NoLDE;

#endif	/* _NOLDE_H */

