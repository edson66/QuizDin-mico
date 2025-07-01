#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

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

void adicionar_pergunta();
void exibir_menu(int& escolha);
//void jogar();
//void exibir_regras();
//void mostrar_ranking();
void salvar_no_arquivo(string nome_arquivo,Pergunta p);

int main(){
    int escolha;
    do{
     exibir_menu(escolha);
     switch (escolha){
     case 1:
      //jogar();break;
     case 2:
      //exibir_regras(); break;
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

void adicionar_pergunta(){
    Pergunta p;

    cout << "\nDigite o tema da pergunta(portugues,matematica,esportes,historia,computacao ou ciencia): ";
    cin >> p.tema;
    if(p.tema != "portugues" && p.tema != "matematica" && p.tema != "esportes"
         && p.tema != "historia" && p.tema != "computacao" && p.tema != "ciencia"){
            cout << "\nTema Invalido\n";
            return;
         }
    cout << "\nDigite a pergunta que deseja: ";
    cin.ignore();
    getline(cin,p.pergunta);
    cout << "\nDigite a primeira opcao de resposta da pergunta: ";
    getline(cin,p.opcaoA);
    cout << "\nDigite a segunda opcao de resposta da pergunta: ";
    getline(cin,p.opcaoB);
    cout << "\nDigite a terceira opcao de resposta da pergunta: ";
    getline(cin,p.opcaoC);
    cout << "\nDigite a resposta correta com (A,B ou C): ";
    cin >> p.resposta_correta;
    p.resposta_correta = tolower(p.resposta_correta);
    if (p.resposta_correta != 'a' && p.resposta_correta != 'b' && p.resposta_correta != 'c') {
      cout << "\nResposta correta inválida. Use apenas A, B ou C.\n";
      return;
    }
    cout << "\nDigite a dificuldade da pergunta: ";
    cin >> p.dificuldade;
    if (p.dificuldade == "Facil" || p.dificuldade == "facil"){
        p.pontuacao = 50;
    }
    else if (p.dificuldade == "Medio" || p.dificuldade == "medio"){
        p.pontuacao = 75;
    }
    else if (p.dificuldade == "Dificil" || p.dificuldade == "dificil"){
        p.pontuacao = 100;
    }
    else{
        cout << "\nDificuldade invalida. Use: facil, medio ou dificil.\n";
        return;
    }  
    
    if (p.tema == "portugues"){
        salvar_no_arquivo("portugues.csv",p);
    }
    else if (p.tema == "matematica"){
        salvar_no_arquivo("matematica.csv",p);
    }
    else if (p.tema == "esportes"){
        salvar_no_arquivo("esportes.csv",p);
    } 
    else if (p.tema == "historia"){
        salvar_no_arquivo("historia.csv",p);
    } 
    else if (p.tema == "computacao"){
        salvar_no_arquivo("computacao.csv",p);
    } 
    else if (p.tema == "ciencia"){
        salvar_no_arquivo("ciencia.csv",p);
    }
}    
void salvar_no_arquivo(string nome_arquivo,Pergunta p){
    ofstream arquivo(nome_arquivo,ios::app);
    if(!arquivo.is_open()){
        cout << "\nErro ao abrir arquivo de " << nome_arquivo;
        return;
    }
        
    arquivo << p.tema << ";" << p.dificuldade << ";" << p.pergunta << ";"
    << p.opcaoA << ";" << p.opcaoB << ";" << p.opcaoC << ";" << p.resposta_correta
    << ";" << p.pontuacao << "\n";
    arquivo.close();
    system("cls");
    cout << "\nPergunta salva com sucesso em " << nome_arquivo << "\n";
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