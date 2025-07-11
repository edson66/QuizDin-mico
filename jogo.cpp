#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "pergunta.h"
#include "jogo.h"

using namespace std;

void jogar(){
    srand(time(0));
    string tema,dificuldade;
    system("cls");
    cout << "\nDigite a dificuldade que deseja(facil,medio ou dificil): ";
    cin >> dificuldade;
    if (dificuldade != "facil" && dificuldade != "medio" && dificuldade != "dificil"){
         cout << "\nDificuldade invalida. Use: facil, medio ou dificil.\n";
         return;
    }
    cout << "\nEscolha um ou mais destes temas de perguntas --> (portugues,matematica,";
    cout << "\nesportes,historia,computacao ou ciencia) os separando entre espacos: ";
    cin.ignore();
    getline(cin,tema);

    ifstream arquivo(tema + ".csv");
    if (!arquivo.is_open()){
        cout << "\nNao foi possivel abrir o arquivo" << tema << ".csv,tente novamente";
        return;
    }
    int quantidade = 0;
    string linha;
    while(getline(arquivo,linha)){
        if (linha.find(";" + dificuldade + ";") != string::npos){
            quantidade++;
        }
    }
    if(quantidade == 0){
        cout<< "\nNao ha perguntas com essa dificuldade";
        return;
    }
    if (quantidade > 0 && quantidade < 3) {
        cout << "\nErro: eh necessario ter pelo menos 3 perguntas com essa dificuldade.\n";
        return;
    }
    Pergunta* perguntas = new Pergunta[quantidade];
    arquivo.clear();
    arquivo.seekg(0);
    int j = 0;
    while(getline(arquivo,linha)){
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
    arquivo.close();
    int pontuacao = 0;
    char resposta;
    system("cls");
    //inicio
    int indices[3];
    int sorteados = 0;

    while (sorteados < 3) {
    int aleatorio = rand() % quantidade;

    // verificar se já foi sorteado
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
//fim da intrusão
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
        if(resposta == perguntas[i].resposta_correta){
            cout << "\nResposta Correta!! + "<< perguntas[i].pontuacao << "pontos\n";
            pontuacao += perguntas[i].pontuacao;
            cout << "pressione enter para continuar";
            cin.ignore();
            cin.get();
            system("cls");
        } 
        else{
            cout << "\nNao foi dessa vez, Resposta correta : Letra " << perguntas[i].resposta_correta << "\n";
            cout << "pressione enter para continuar";
            cin.ignore();
            cin.get();
            system("cls");
            
        }
    }
    cout << "\nPontuacao total : " << pontuacao;
    cout << "\npressione enter para continuar";
    cin.ignore();
    system("cls");
 
    delete[] perguntas;
}