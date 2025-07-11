#include <iostream>
#include "jogo.h"
#include "regras.h"
#include "cadastro.h"

using namespace std;

void exibir_menu(int& escolha);

int main(){
    int escolha;
    do{
     exibir_menu(escolha);
     switch (escolha){
     case 1:
      jogar();break;
     case 2:
     exibir_regras(); break;
     case 3:
      //mostrar_ranking(); break;
     case 4:
      adicionar_pergunta();
      system("pause");
      break;
     case 5:
      cout << "\nSaindo do programa...\n";
      return 0;
     }
     system("cls");
    }while (true);

    return 0;
}

void exibir_menu(int& escolha){
    do{
        cout << "+=====================================+\n";
        cout << "|         QUIZ INTERATIVO C++         |\n";
        cout << "+-------------------------------------+\n";
        cout << "|  1 - Jogar                          |\n";
        cout << "|  2 - Ver Regras                     |\n";
        cout << "|  3 - Visualizar Ranking             |\n";
        cout << "|  4 - Adicionar Pergunta             |\n";
        cout << "|  5 - Sair                           |\n";
        cout << "+-------------------------------------+\n";
        cout << "Digite sua opcao: ";
        cin >> escolha;
    if(escolha < 1 || escolha > 5){
        cout << "\nopcao invalida,Pressione Enter para tentar novamente. ";
        cin.ignore();
        cin.get();
    }
  }while(escolha < 1 || escolha > 5);
}

