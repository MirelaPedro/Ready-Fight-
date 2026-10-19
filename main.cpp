// pegar uma lista dos nomes dos jogadores de um arquivo txt externo

#include "player.hpp"
#inclde <vector>

// prototypes - depois transferir para outro arquivo
vector <Player> readArq(string name);
void createPlayer();

int main()
{
    srand(time(0));
    //Player pl("Olaf", 50, 8, 3);

    vector <string> nomes = {"Olaf", "Rapunzel", "Damian"};
    vector <Player> players;

    for(size_t i = 0; nomes.size(); i++){
        Player novo(names.at(i), rand()%50+1, rand()%5+1, rand()%20+1);
        players.push_back(novo);
    }
    
    for(size_t i = 0; players.size(); i++){
        cout << "PLAYER: " << players.at(i).m_name << " - Life: " <<   players.at(i).GetName() << " - Attack: " <<   players.at(i).GetAttack() << " - Defense: " <<   players.at(i).GetDefense() << endl; 
    }
}


// pra compilar g++ **.cpp -o rinha