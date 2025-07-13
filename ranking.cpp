#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "ranking.h"

using namespace std;

struct jogador{
    string nome;
    int pontuacao;
};

void salvar_ranking(string nome,int pontuacao){
    ifstream arquivo_ler("ranking.csv");

    string linha;
    int quant = 0;
    while (getline(arquivo_ler, linha)) {
        quant++;
    }

    arquivo_ler.clear();
    arquivo_ler.seekg(0);
    jogador* jogadores = new jogador[quant + 1]; 
    int i = 0;
    bool existe = false;

    while (getline(arquivo_ler, linha)) {
        stringstream ss(linha);
        getline(ss, jogadores[i].nome, ';');
        ss >> jogadores[i].pontuacao;

        if (jogadores[i].nome == nome) {
            jogadores[i].pontuacao += pontuacao;
            existe = true;
        }
        i++;
    }
    arquivo_ler.close();

    if (!existe) {
        jogadores[i].nome = nome;
        jogadores[i].pontuacao = pontuacao;
        i++;
    }

    ofstream arquivo("ranking.csv");
    if(!arquivo.is_open()){
        cout << "erro ao abrir o arquivo de ranking.";
        return;
    }
    for (int j = 0; j < i; j++) {
        arquivo << jogadores[j].nome << ";" << jogadores[j].pontuacao << "\n";
    }
    arquivo.close();
    delete[] jogadores;
    return;
}


void mostrar_ranking(){
    ifstream arquivo("ranking.csv");

    string linha;
    int quant = 0;
    while(getline(arquivo,linha)){
        quant ++;
    }
    if (quant == 0) {
    cout << "\nRanking vazio.Pressione enter para voltar ao menu . .\n";
    cin.ignore();
    cin.get();
    return;
    }
    jogador* jogadores = new jogador[quant];
    arquivo.clear();
    arquivo.seekg(0);
    int i = 0;
    while(getline(arquivo,linha)){
        stringstream ss (linha);
        getline(ss,jogadores[i].nome,';');
        ss >> jogadores[i].pontuacao;
        i++;
    }
    arquivo.close();

    cout << "\n===== RANKING =====\n";
    for(int i=0;i<quant;i++){
        cout << "Nome :" << jogadores[i].nome << "\nPontuacao:" << jogadores[i].pontuacao << "\n-------------------\n";
    }

    delete[] jogadores;
    cout << "\nPressione enter para voltar ao menu . . ";
    cin.ignore();
    cin.get();

}