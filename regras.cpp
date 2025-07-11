#include "regras.h"
#include <iostream>

using namespace std;

void exibir_regras(){
    system("cls");
    cout << "+==================== REGRAS DO QUIZ ====================+\n";
    cout << "|                                                        |\n";
    cout << "| 1. O jogo eh composto por rodadas de 3 perguntas.      |\n";
    cout << "| 2. Voce escolhe a dificuldade: facil, medio ou dificil.|\n";
    cout << "| 3. A dificuldade afeta a pontuacao:                    |\n";
    cout << "|     - Facil   => 50 pontos                             |\n";
    cout << "|     - Medio   => 75 pontos                             |\n";
    cout << "|     - Dificil => 100 pontos                            |\n";
    cout << "| 4. eh necessario que haja ao menos 3 perguntas da      |\n";
    cout << "|    dificuldade escolhida para jogar.                   |\n";
    cout << "| 5. Voce tambem escolhe o tema das perguntas.           |\n";
    cout << "|    Temas disponiveis:                                  |\n";
    cout << "|    - portugues, matematica, esportes, historia,        |\n";
    cout << "|      computacao e ciencia.                             |\n";
    cout << "| 6. As respostas devem ser informadas com A, B ou C.    |\n";
    cout << "| 7. Ao final, sua pontuacao sera exibida.               |\n";
    cout << "|                                                        |\n";
    cout << "+=======================================================+\n";
    cout << "\nPressione Enter para voltar ao menu...";
    cin.ignore();
    cin.get();
}