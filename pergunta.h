#ifndef PERGUNTA_H
#define PERGUNTA_H
#include <string>

using namespace std;

struct Pergunta {
string tema;
string dificuldade;
string pergunta;
string opcaoA;
string opcaoB;
string opcaoC;
char resposta_correta;
int pontuacao;
};


#endif