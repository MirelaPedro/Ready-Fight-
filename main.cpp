// pegar uma lista dos names dos jogadores de um arquivo txt externo

#include "player.hpp"
#include <vector>
#include <fstream>

int main()
{
    srand(time(0));
    vector <string> names;

    // LENDO O ARQUIVO DE NOMES
    ofstream fp;
    fp.open("names.txt");

    if(fp.is_open() == false) {
        cout << "Erro, o arquivo não abriu." << endl;
        return false;
    }

    for(size_t i=0; i < names.size(); i++){
        getline(fp, names[i]);
    }

    fp.close();

    // CRIANDO OS PLAYERS
    vector <Player> players;

    for(size_t i = 0; names.size(); i++){
        Player novo(names.at(i), rand()%50+1, rand()%5+1, rand()%20+1);
        players.push_back(novo);
    }
    
    for(size_t i = 0; players.size(); i++){
        cout << "PLAYER: " << players.at(i).m_name << " - Life: " <<   players.at(i).GetName() << " - Attack: " <<   players.at(i).GetAttack() << " - Defense: " <<   players.at(i).GetDefense() << endl; 
    }

    // LUTANDO
    while(players.size() > 1){
        int player0 = rand()%players.size();
        int player1 = rand()%players.size();

        bool sucess = players.at(player0).Attack(players.at(player1));

        if(players.at(player1) <= 0){
            cout << players.at(player1).GetName() << " morreu! " << endl;
            players.erase(player1);
        }
    }

    if(players.size() == 1){
        cout << "O vencedor foi: " << players.at(player1).GetName() << endl;
    } else {cout << "Ocorreu um erro!" << endl;}

    return 0;
}


// pra compilar g++ **.cpp -o rinha