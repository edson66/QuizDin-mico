#ifndef CADASTRO_H
#define CADASTRO_H
#include <string>
#include "pergunta.h"

using namespace std;

void adicionar_pergunta();
void salvar_no_arquivo(string nome_arquivo,Pergunta p);

#endif