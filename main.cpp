/*
JOGO RINHA DE GALO
Equipe: 
26102209 - Mirela Pedro
26104469 - Amanda Leal
*/
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "galo.hpp"

using namespace std;

const string path = "/times/";


int main()
{
    srand(time(0));
    string nomeTime1, nomeTime2;
    vector <Galo> time1, time2;
    vector <Armamento> armas;

    // Recebendo nomes dos times
    cout << "Digite o nome do time 1: ";
    getline(cin, nomeTime1);
    cout << "Digite o nome do time 2: ";
    getline(cin, nomeTime2);

    // LENDO O ARQUIVO DE NOMES
    time1 = createTime(nomeTime1);
    time2 = createTime(nomeTime2);
    armas = createArmamento("armas");

    // LUTANDO
    while(time1.size() > 0 && time2.size() > 0){
        int player0 = rand()%time1.size();
        int player1 = rand()%time2.size();

        int result = luta(time1.at(player0), time2.at(player1), armas);

        if(result == 1){
            time2.erase(time2.begin() + player1);
        } else {
            time1.erase(time1.begin() + player0);
        }

        maldicaoDoGalo(&time1, &time2, player0);
        maldicaoDoGalo(&time2, &time1, player1);
    }

    // RESULTADO FINAL  
    if(time1.size() >= 1){
        cout << "VENCEDOR: " << nomeTime1<< endl;
        for(int i = 0; i < time1.size(); i++){
            cout << " - " << time1.at(i).GetName() << endl;
        }
    } else {
        cout << "VENCEDOR: " << nomeTime2  << endl;
        for(int i = 0; i < time2.size(); i++){
            cout << " - " << time2.at(i).GetName() << endl;
        }
    }

    return 0;
}

// ------------------ FUNÇÕES DE GALOS ------------------
// Leitura do arquivo de nomes
vector <Galo> createTime(string nomeTime){
    vector <Galo> time;
    string arq = path + nomeTime + ".txt", line; // caminho do arquivo no projeto

    // abrindo o arquivo
    ifstream fp;
    fp.open(arq);

    if(fp.is_open() == false) {
        cout << "Erro, o arquivo não abriu." << endl;
        return time;
    }

    // o professor anderson nos ensinou a fazer assim
    // lendo o arquivo
    while(getline(fp, line)){
        Galo novo(line, rand()%100+1, rand()%15+1, rand()%20+1);
        time.push_back(novo);
    }

    fp.close();
    return time;
}

/*
sitema de LUTA:
- enquanto os dois jogadores estiverem vivos, eles se atacam
retorno: 
1 - para o jogador 1 ganhou 
2 - para o jogador 2 ganhou
*/
int luta(Galo player1, Galo player2, vector <Armamento> armas){
    // atribuição de armas aos galos
    Armamento arma1 = atribuirArma(armas);
    Armamento arma2 = atribuirArma(armas);

    while(player1.GetLife() > 0 && player2.GetLife() > 0){
        // ataque do player1 no player2
        bool sucess = player1.Attack(player2, arma1, 0);
        if(sucess == true){
            cout << player1.GetName() << " atacou " << player2.GetName() << endl;
            cout << player2.GetName() << " perdeu " << (player1.GetAttack() - player2.GetDefense()) << " de vida!" << endl;
            cout << player2.GetName() << " agora tem " << player2.GetLife() << " de vida!" << endl;
        }
        else{
            cout << player1.GetName() << " não conseguiu atacar " << player2.GetName() << endl;
        }

        // verificando se o player2 morreu
        if(player2.GetLife() <= 0){
            cout << player2.GetName() << " morreu!" << endl;
            quebrou(arma2, armas);
            quebrou(arma1, armas);
            return 1;
        }

        // ataque do player2 no player1
        sucess = player2.Attack(player1, arma2, 2); // esse 5 é um adicional de ataque que o player2 tem por ser o segundo a atacar
        if(sucess == true){
            cout << player2.GetName() << " atacou " << player1.GetName() << endl;
            cout << player1.GetName() << " perdeu " << (player2.GetAttack() - player1.GetDefense()) << " de vida!" << endl;
            cout << player1.GetName() << " agora tem " << player1.GetLife() << " de vida!" << endl;
        }
        else{
            cout << player2.GetName() << " não conseguiu atacar " << player1.GetName() << endl;
        }

        // verificando se o player1 morreu
        if(player1.GetLife() <= 0){
            cout << player1.GetName() << " morreu!" << endl;
            quebrou(arma2, armas);
            quebrou(arma1, armas);
            return 2;
        }
    }
}

bool maldicaoDoGalo(vector <Galo> *timeAtacante, vector <Galo> *timeAtacado,  int index) {

    // verificando se o galo que vai atacar ainda está vivo
    // a maldição só é ativada se o galo tiver morrido
    if(timeAtacante->at(index).GetLife() > 0) {
        return false;
    }

    int numAtacados = rand()%timeAtacado->size(), indexVitima;
    vector <int> atacados; 

    // contém uma mini verificação para não repetir o mesmo galo
    for(int i = 0; i < numAtacados; i++) 
    {
        do {
            indexVitima = rand()%timeAtacado->size();
        } while(inVector(atacados, indexVitima));
        
        atacados.push_back(indexVitima);
    }

    // ataque da maldição do galo
    bool maldicao = timeAtacante->at(index).MaldicaoDoGalo(timeAtacado, atacados);
    if(maldicao){
        cout << timeAtacante->at(index).GetName() << " ativou a maldição do galo!" << endl;
        return true;
    }
    else{
        return false;
    }
}

// ----------- FUNÇÕES DE ARMAMENTO ----------------
// lendo o arquivo de armas
vector <Armamento> createArmamento(string nome){
    vector <Armamento> armas;
    string arq = nome + ".txt", line;

    // abrindo o arquivo
    ifstream fp;
    fp.open(arq);

    if(fp.is_open() == false) {
        cout << "Erro, o arquivo não abriu." << endl;
        return armas;
    }

    // lendo o arquivo
    while(getline(fp, line)){
        Armamento arma;
        arma.SetName(line);
        getline(fp, line);
        arma.SetTipe(line);
        getline(fp, line);
        arma.SetPower(stof(line)); // arrumar isso depois
        armas.push_back(arma);
    }

    fp.close();
    return armas;
}

// atribuição
Armamento atribuirArma(vector <Armamento> armas){
    if(armas.size() == 0){
        return Armamento();
    }

    if(rand()%100 < 70){
        int index = rand()%armas.size();
        return armas.at(index);
    }
    else{
        return Armamento();
    }    
}

// se quebrou ou nao
bool quebrou(Armamento &arma, vector <Armamento> armas){
    if(arma.BreakWeapon()){
        cout << "A arma " << arma.GetName() << " quebrou!" << endl;

        // percorrendo o vetor de armas para remover a arma quebrada pelo nome
        for(size_t i = 0; i < armas.size(); i++){
            if(armas.at(i).GetName() == arma.GetName()){ // as armas não possuem nomes repitidos;
                armas.erase(armas.begin() + i);
                return true;
            }
        }
    }
    else{
        return false;
    }
}

// FUNÇÕES EXTRAS DE AUXILIO
bool inVector(vector <int> vec, int value){
    for(int i = 0; i < vec.size(); i++){
        if(vec.at(i) == value){
            return true;
        }
    }
    return false;
}

/*

TAREFAS 
CRIAR SISTEMA DE PRECISAO DE ATAQUE E DEFESA (ASSIM GALOS FRACOS PODEM GANHAR TB)
- criar arquivos txt (nomes e armamento) - okk
- classes com atributos e protótipos de função - player(galo), armas
- funções (aplicações) das classes
- funções de luta - ok
- main -- okk
- pegar uma arma ou escudo antes da partida -- ok
- menu e respostas ao usuário - ok
- tratamento de erro e testes
- poderes diferenciados (bicada fatal) -- okk
- ataques críticos aleatórios - maldição do galo -- ok
- MUDAR TUDO PARA PONTERIRO 

- chance da arma se quebrar no fim de cada rodada -- okk 
- escrever todas as mecanicas do jogo no readme
- criar precisão de defesa
- traidor e covarde
- bet com moedinhas mágicas 
- colocar contagem de quantos galos ainda estão vivos no momento do jogo
- colocar um aviso no inicio do jogo: " Este jogo é apenas para fins de entretenimento, não é recomendado apostar dinheiro real. E nem apoia maus tratos a animais, o jogo é apenas uma simulação de rinha de galos MÁGICA, não é real. Jogue com moderação."


// não precisa po r enquanto
- precisão de ataque e defesa (quanto mais forte o galo, mais chance de acertar o ataque)
- 
- gravar o vídeo (e editar)
*/

// pra compilar g++ **.cpp -o rinha