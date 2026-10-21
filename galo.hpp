#include <iostream>

using namespace std;

//ataques com pontuações diferentes: bicada, arranhão, asada, rabada

class Galo {
    private: 
        string m_name;
        float m_life, m_attack, m_defense;
        /*Heroi, Traidor ou Covarde*/
        string m_tipe;
    
    public:         
        Galo(string name, float life, float attack, float defense) {
            m_name = name;
            m_life = life;
            m_attack = attack;
            m_defense = defense;
        }

        string GetName() {
            return m_name;
        }

        float GetLife() {
            return m_life;
        }

        float GetAttack() {
            return m_attack;
        }

        float GetDefense() {
            return m_defense;
        }

        void SetLife(float newLife) {
            m_life = newLife;
        }

        bool Attack(Galo &opponent, Armamento &arma) {
            //booster do ataque

            //premissa 1: verificar se o ataque do jogador é maior que a defesa do oponente
            if (m_attack > opponent.m_defense) {

                //premissa 2: subtrair o dano (ataque - defesa) da vida do oponente
                float damage = m_attack - opponent.m_defense;
                opponent.SetLife(opponent.GetLife() - damage);
                if(MaldicaodoGalo(opponent)) { //verifica se o ataque crítico foi ativado
                return false;
                }
                else {
                    return true;
                }
                
            }
            else {
                return false;
            }
        }

        /*Ataque crítico reservado apenas para Heróis*/
        bool MaldicaodoGalo(Galo &opponent) {
            if(m_tipe == "Heroi") {
                srand(time(0));
                int chance = rand() % 20;
                if(chance > 20) { 
                    return true;
                }
                else {
                    return false;
                }
            }

            else {
                return false;
            }
        }

};

class Armamento {
    private:
        string m_name;
        /*Ataque ou defesa*/
        string m_tipe; 
        float m_power;

    public: 
        string GetName();
        string GetTipe();
        float GetPower();

        Armamento() {
            m_name = "Sem arma";
            m_tipe = "Na fé e na coragem";
            m_power = 0;
        }

        Armamento(string name, string tipe, float power) {
            m_name = name;
            m_tipe = tipe;
            m_power = power;
        }

        void SetName(string newName) {
            m_name = newName;
        }

        void SetTipe(string newTipe) {
            m_tipe = newTipe;
        }

        void SetPower(float newPower){
            m_power = newPower;
        }

        /*Existe 40% de chance da arma quebrar após cada uso*/
        bool BreakWeapon() {
            srand(time(0));
            int chance = rand() % 40;
            if(chance > 40) {
                return true;
            }
            else {
                return false;
            }
        }

};
