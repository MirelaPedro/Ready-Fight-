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

vector <Galo> createTime(string nomeTime){
    vector <Galo> time;
    string arq = path + nomeTime + ".txt";
    ifstream fp;
    fp.open(arq);

    if(fp.is_open() == false) {
        cout << "Erro, o arquivo não abriu." << endl;
        return time;
    }

    string line;

    // ou por um for?
    while(getline(fp, line)){
        Galo novo(line, rand()%100+1, rand()%15+1, rand()%20+1);
        time.push_back(novo);
    }

    /*
    for(size_t i=1; i < arq.size(); i++){
        getline(fp, arq[i]);
    }

    for(size_t i = 0; players.size(); i++){
        cout << "PLAYER: " << players.at(i).m_name << " - Life: " <<   players.at(i).GetName() << " - Attack: " <<   players.at(i).GetAttack() << " - Defense: " <<   players.at(i).GetDefense() << endl; 
    }
    */

    fp.close();
    return time;
}

/*
sitema de luta:
- enquanto os dois jogadores estiverem vivos, eles se atacam
retorno: 
1 - para o jogador 1 ganhou 
2 - para o jogador 2 ganhou
*/
int luta(Galo player1, Galo player2, vector <Armamento> armas){
    Armamento arma1 = atribuirArma(armas);
    Armamento arma2 = atribuirArma(armas);

    while(player1.GetLife() > 0 && player2.GetLife() > 0){
        // ataque do player1 no player2
        bool sucess = player1.Attack(player2, arma1);
        if(sucess == true){
            cout << player1.GetName() << " atacou " << player2.GetName() << endl;
            cout << player2.GetName() << " perdeu " << (player1.GetAttack() - player2.GetDefense()) << " de vida!" << endl;
            cout << player2.GetName() << " agora tem " << player2.GetLife() << " de vida!" << endl;
        }
        else{
            cout << player1.GetName() << " não conseguiu atacar " << player2.GetName() << endl;
        }

        if(player2.GetLife() <= 0){
            cout << player2.GetName() << " morreu!" << endl;
            return 1;
        }

        // ataque do player2 no player1
        sucess = player2.Attack(player1, arma2);
        if(sucess == true){
            cout << player2.GetName() << " atacou " << player1.GetName() << endl;
            cout << player1.GetName() << " perdeu " << (player2.GetAttack() - player1.GetDefense()) << " de vida!" << endl;
            cout << player1.GetName() << " agora tem " << player1.GetLife() << " de vida!" << endl;
        }
        else{
            cout << player2.GetName() << " não conseguiu atacar " << player1.GetName() << endl;
        }

        if(player1.GetLife() <= 0){
            cout << player1.GetName() << " morreu!" << endl;
            return 2;
        }
    }
}

vector <Armamento> createArmamento(string nome){
    vector <Armamento> armas;
    string arq = path + nome + ".txt";

    ifstream fp;
    fp.open(arq);

    if(fp.is_open() == false) {
        cout << "Erro, o arquivo não abriu." << endl;
        return armas;
    }

    string line;

    // ou por um for?
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

Armamento atribuirArma(vector <Armamento> armas){
    if(rand()%100 < 70){
        int index = rand()%armas.size();
        return armas.at(index);
    }
    else{
        return Armamento();
    }    
}

int main()
{
    srand(time(0));
    string nomeTime1, nomeTime2;
    vector <Galo> time1, time2;
    vector <Armamento> armas;

    armas = createArmamento("armas");

    cout << "Digite o nome do time 1: ";
    getline(cin, nomeTime1);
    cout << "Digite o nome do time 2: ";
    getline(cin, nomeTime2);

    // LENDO O ARQUIVO DE NOMES e criando os times
    time1 = createTime(nomeTime1);
    time2 = createTime(nomeTime2);    
    

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
    }

    // rever retorno ao usuario
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


/*

TAREFAS 
CRIAR SISTEMA DE PRECISAO DE ATAQUE E DEFESA (ASSIM GALOS FRACOS PODEM GANHAR TB)
- criar arquivos txt (nomes e armamento)
- classes com atributos e protótipos de função - player(galo), armas
- funções (aplicações) das classes
- funções de luta - ok
- main -- okk
- pegar uma arma ou escudo antes da partida -- ok
- menu e respostas ao usuário - ok
- tratamento de erro e testes
- poderes diferenciados (bicada fatal) 
- ataques críticos aleatórios - maldição do galo -- ok
- chance da arma se quebrar no fim de cada rodada

- gravar o vídeo (e editar)
*/

// pra compilar g++ **.cpp -o rinha