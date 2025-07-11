#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "cadastro.h"

using namespace std;

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
