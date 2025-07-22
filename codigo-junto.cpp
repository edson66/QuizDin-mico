#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <cstdlib>
#include <ctime>

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

struct jogador{
    string nome;
    int pontuacao;
};

void adicionar_pergunta();
void exibir_menu(int& escolha);
void jogar();
void exibir_regras();
void mostrar_ranking();
void salvar_ranking(string nome,int pontuacao);
void salvar_no_arquivo(string nome_arquivo,Pergunta p);

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
      mostrar_ranking(); break;
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