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
#include <ctime>
#include <cstdlib>
#include "galo.hpp"

using namespace std;

const string path = "./times/";

vector <Galo> createTime(string nomeTime);
int luta(Galo &player1, Galo &player2, vector <Armamento> &armas);
bool maldicaoDoGalo(vector <Galo> *timeAtacante, vector <Galo> *timeAtacado,  int index);
bool galoJudas(vector <Galo> *timeAnterior, vector <Galo> *timeNovo,  int index);
bool galoCovarde(vector <Galo> *timeAnterior,  int index);
vector <Armamento> createArmamento(string nome);
bool atribuirArma(vector <Armamento> &armas, Galo &player);
bool quebrou(Galo &player, vector <Armamento> &armas);
bool inVector(vector <int> vec, int value);


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
    cout << endl;

    // LENDO O ARQUIVO DE NOMES
    time1 = createTime(nomeTime1);
    time2 = createTime(nomeTime2);
    armas = createArmamento("armas");

    // LUTANDO
    while(time1.size() > 0 && time2.size() > 0){
        int player1 = rand()%time1.size();
        int player2 = rand()%time2.size();

       // funções especiais de fuga e traicao
        if (galoJudas(&time1, &time2, player1)) {
            cout << "O galo traiu o time!!" << endl; 
            continue;
        }
        if (galoCovarde(&time1, player1)) {
            cout << "O galo fugiu da luta!!" << endl; 
            continue;
        }
        if (galoJudas(&time2, &time1, player2)) {
            cout << "O galo traiu o time!!" << endl;
            continue;
        }
        if (galoCovarde(&time2, player2)) {
            cout << "O galo fugiu da luta!!" << endl;
            continue;
        }

        int result = luta(time1.at(player1), time2.at(player2), armas);

        if(result == 1){
            maldicaoDoGalo(&time2, &time1, player2);
            time2.erase(time2.begin() + player2);
        } else {
            maldicaoDoGalo(&time1, &time2, player1);
            time1.erase(time1.begin() + player1);
        }
    }

    cout << "LUTA FINALIZADA" << endl;

    // RESULTADO FINAL  
    if(time1.size() >= 1){
        cout << "TIME VENCEDOR: " << nomeTime1<< endl;
        for(int i = 0; i < time1.size(); i++){
            cout << " - " << time1.at(i).GetName() << endl;
        }
    } 
    else if(time2.size() >= 1) {
        cout << "TIME VENCEDOR: " << nomeTime2  << endl;
        for(int i = 0; i < time2.size(); i++){
            cout << " - " << time2.at(i).GetName() << endl;
        }
    }
    else {
        cout << "Não houveram vencedores!" << endl;
    }

    return 0;
}

// ------------------ FUNÇÕES DE GALOS ------------------
// Leitura do arquivo de nomes
vector <Galo> createTime(string nomeTime){
    vector <Galo> time;
    string arq = path + nomeTime + ".txt"; // caminho do arquivo no projeto
    string line, tipo;

    // abrindo o arquivo
    ifstream fp;
    fp.open(arq);

    if(fp.is_open() == false) {
        cout << "Erro, o arquivo não abriu." << endl;
        return time;
    }

    // o professor anderson nos ensinou a fazer assim
    // lendo o arquivo
    while(!fp.eof()){
        getline(fp, tipo);
        getline(fp, line);
        Galo novo(line, tipo, rand()%100+1, rand()%15+1, rand()%20+1);
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
o segundo jogador tem um adicional de 2 no ataque por começar depois
*/
int luta(Galo &player1, Galo &player2, vector <Armamento> &armas){
    // atribuição de armas aos galos
    bool arma1 = atribuirArma(armas, player1);
    bool arma2 = atribuirArma(armas, player2);

    while(player1.GetLife() > 0 && player2.GetLife() > 0){

        // ataque do player1 no player2
        bool sucess = player1.Attack(player2, 0);
        if(sucess == true){
            cout << player1.GetName() << " atacou " << player2.GetName() << endl;

            if(player2.GetLife() > 0) {
                cout << player2.GetName() << " agora tem " << player2.GetLife() << " de vida!" << endl << endl;
            }
        }
        else{
            cout << player1.GetName() << " não conseguiu atacar " << player2.GetName() << endl << endl;
        }

        // verificando se o player2 morreu
        if(player2.GetLife() <= 0){
            cout << player2.GetName() << " morreu!" << endl << endl;
            quebrou(player1, armas);
            quebrou(player2, armas);
            return 1;
        }

        // ataque do player2 no player1
        sucess = player2.Attack(player1, 2); // esse 2 é um adicional de ataque que o player2 tem por ser o segundo a atacar
        if(sucess == true){
            cout << player2.GetName() << " atacou " << player1.GetName() << endl;

            if(player1.GetLife() > 0) {
                cout << player1.GetName() << " agora tem " << player1.GetLife() << " de vida!" << endl << endl;
            }
        }
        else{
            cout << player2.GetName() << " não conseguiu atacar " << player1.GetName() << endl << endl;
        }

        // verificando se o player1 morreu
        if(player1.GetLife() <= 0){
            cout << player1.GetName() << " morreu!" << endl << endl;
            quebrou(player1, armas);
            quebrou(player2, armas);
            return 2;
        }
    }
}

bool maldicaoDoGalo(vector <Galo> *timeAtacante, vector <Galo> *timeAtacado,  int index) {
    int numAtacados = rand()%timeAtacado->size(), indexVitima;
    vector <int> atacados; 

    // verificando se o galo que vai atacar ainda está vivo pois a maldição só é ativada se o galo tiver morrido
    if(timeAtacante->at(index).GetLife() > 0) {
        return false;
    }

    else {
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
            cout << timeAtacante->at(index).GetName() << " lançou a Maldição do Galo!" << endl;
            return true;
        }
        else{
            return false;
        }
    }
}

bool galoJudas(vector <Galo> *timeAnterior, vector <Galo> *timeNovo,  int index){
    if(timeAnterior->at(index).GaloJudas()){
        timeNovo->push_back(timeAnterior->at(index));
        timeAnterior->erase(timeAnterior->begin() + index);
        return true;
    }

    return false;
}

bool galoCovarde(vector <Galo> *timeAnterior,  int index){
    if(timeAnterior->at(index).FugaDasGalinhas()){
        timeAnterior->erase(timeAnterior->begin() + index);
        return true;
    }

    return false;
}

// ----------- FUNÇÕES DE ARMAMENTO ----------------
// lendo o arquivo de armas
vector <Armamento> createArmamento(string nome){
    vector <Armamento> armas;
    string arq = nome + ".txt";
    string line, type;

    // abrindo o arquivo
    ifstream fp;
    fp.open(arq);

    if(fp.is_open() == false) {
        cout << "Erro, o arquivo não abriu." << endl;
        return armas;
    }

    // lendo o arquivo
    /*
    tipo do arma
    nome da arma
    tipo da arma
    nome da arma..
    */

    
    while(!fp.eof()){
        getline(fp, type);
        getline(fp, line);
        Armamento novo(line, type, rand()%20+1);
        armas.push_back(novo);
    }

    fp.close();
    return armas;
}

// atribuição
bool atribuirArma(vector <Armamento> &armas, Galo &player){
        if(armas.size() == 0){
        return false;
    }

    else if(rand()%100 < 70){
        int index = rand()%armas.size();
        player.SetArma(armas.at(index));
        return true;
    }

    else{
        return false;
    }    
}

// se quebrou ou nao
bool quebrou(Galo &player, vector <Armamento> &armas){
    if(player.GetArma().BreakWeapon()){
        //verificar se o galo tem uma arma para ser quebrada
        if (player.GetArma().GetName() != "Sem arma") {
            cout << "A arma " << player.GetArma().GetName() << " quebrou!" << endl << endl;

            // percorrendo o vetor de armas para remover a arma quebrada pelo nome
            for(size_t i = 0; i < armas.size(); i++){
                if(armas.at(i).GetName() == player.GetArma().GetName()){ // as armas não possuem nomes repitidos;
                    armas.erase(armas.begin() + i);
                    player.SetArma(Armamento());
                    return true;
                }
            }
        }
    }

    return false;
}

//-----------FUNÇÕES EXTRAS DE AUXILIO-----------
bool inVector(vector <int> vec, int value){
    for(size_t i = 0; i < vec.size(); i++){
        if(vec.at(i) == value){
            return true;
        }
    }
    return false;
}

/*
TAREFAS 
- implementa o "herói" (ler o aquivo corretamente) - (a madição do galo)
- gravar o vídeo (e editar)

LINAHS QUE EU MUDEI PRA CONCERTAR DEPOIS:

Main:
- 191
- 273 (comentei)


Galo:
- 131
- 147
- 162


*/

// pra compilar g++ **.cpp -o rinha