#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "pergunta.h"
#include "jogo.h"
#include "ranking.h"

using namespace std;

void jogar(){
    srand(time(0));
    string temas,tema1,tema2,dificuldade,nome;
    system("cls");
    cout << "\nDigite a dificuldade que deseja(facil,medio ou dificil): ";
    cin >> dificuldade;
    if (dificuldade != "facil" && dificuldade != "medio" && dificuldade != "dificil"){
         cout << "\nDificuldade invalida. Use: facil, medio ou dificil.\n";
         return;
    }
    cout << "\nEscolha um ou dois destes temas de perguntas --> (portugues,matematica,";
    cout << "\nesportes,historia,computacao ou ciencia) os separando entre espacos: ";
    cin.ignore();
    getline(cin,temas);
    stringstream ss(temas);
    ss >> tema1 >> tema2;

    ifstream arquivo1(tema1 + ".csv");
    ifstream arquivo2;
    if (!tema2.empty()){
        arquivo2.open(tema2 + ".csv");
    }
    if (!arquivo1.is_open() || (!tema2.empty() && !arquivo2.is_open())){
        cout << "\nNao foi possivel abrir um dos arquivos.\n";
        return;
    }
    int quantidade = 0;
    string linha;
    while(getline(arquivo1,linha)){
        if (linha.find(";" + dificuldade + ";") != string::npos){
            quantidade++;
        }
    }
    if(!tema2.empty()) {  
        while(getline(arquivo2,linha)){
            if (linha.find(";" + dificuldade + ";") != string::npos){
                quantidade++;
            }
        }
    }
    if(quantidade == 0){
        cout<< "\nNao ha perguntas com essa(s) dificuldade(s)";
        return;
    }
    if (quantidade > 0 && quantidade < 3) {
        cout << "\nErro: eh necessario ter pelo menos 3 perguntas com essa dificuldade.\n";
        return;
    }
    Pergunta* perguntas = new Pergunta[quantidade];
    arquivo1.clear();
    arquivo1.seekg(0);
    arquivo2.clear();
    arquivo2.seekg(0);
    int j = 0;
    while(getline(arquivo1,linha)){
        if (linha.find(";" + dificuldade + ";") != string::npos){
            stringstream ss(linha);
            getline(ss,perguntas[j].tema,';');
            getline(ss,perguntas[j].dificuldade,';');
            getline(ss,perguntas[j].pergunta,';');
            getline(ss,perguntas[j].opcaoA,';');
            getline(ss,perguntas[j].opcaoB,';');
            getline(ss,perguntas[j].opcaoC,';');
            ss >> perguntas[j].resposta_correta;
            ss.ignore();
            ss >> perguntas[j].pontuacao;
            j++;
        }
    }
    if(!tema2.empty()){
        while(getline(arquivo2,linha)){
            if (linha.find(";" + dificuldade + ";") != string::npos){
                stringstream ss(linha);
                getline(ss,perguntas[j].tema,';');
                getline(ss,perguntas[j].dificuldade,';');
                getline(ss,perguntas[j].pergunta,';');
                getline(ss,perguntas[j].opcaoA,';');
                getline(ss,perguntas[j].opcaoB,';');
                getline(ss,perguntas[j].opcaoC,';');
                ss >> perguntas[j].resposta_correta;
                ss.ignore();
                ss >> perguntas[j].pontuacao;
                j++;
            }
        }        
    }
    arquivo1.close();
    arquivo2.close();
    int pontuacao = 0;
    char resposta;
    system("cls");
    int indices[3];
    int sorteados = 0;

    while (sorteados < 3) {
    int aleatorio = rand() % quantidade;
    bool repetido = false;
    for (int j = 0; j < sorteados; j++) {
        if (indices[j] == aleatorio) {
            repetido = true;
            break;
        }
    }

    if (!repetido) {
        indices[sorteados] = aleatorio;
        sorteados++;
    }
}
    cout << "Rodada de 3 perguntas . . .\n";
    for(int i=0;i<3;i++){
        int rand=indices[i];
        cout << "Pergunta " << i+1 <<": "<<perguntas[rand].pergunta << "\n";
        cout << "A- " << perguntas[rand].opcaoA << "\n";
        cout << "B- " << perguntas[rand].opcaoB << "\n";
        cout << "C- " << perguntas[rand].opcaoC << "\n";
        cout << "Digite sua resposta: ";
        cin >> resposta;
        resposta = tolower(resposta);
        if(resposta == perguntas[rand].resposta_correta){
            cout << "\nResposta Correta!! + "<< perguntas[rand].pontuacao << "pontos\n";
            pontuacao += perguntas[rand].pontuacao;
            cout << "pressione enter para continuar";
            cin.ignore();
            cin.get();
            system("cls");
        } 
        else{
            cout << "\nNao foi dessa vez, Resposta correta : Letra " << perguntas[rand].resposta_correta << "\n";
            cout << "-" << perguntas[rand].pontuacao << "pontos\n";
            pontuacao -= perguntas[rand].pontuacao;
            cout << "pressione enter para continuar";
            cin.ignore();
            cin.get();
            system("cls");
            
        }
    }
    cout << "\nPontuacao total : " << pontuacao;
    cout << "\nDigite seu nome para salvar no ranking: ";
    getline(cin,nome);
    salvar_ranking(nome,pontuacao);
    system("cls");
 
    delete[] perguntas;
}