#include <iostream>
#include <utility>
#include <array>

using namespace std;

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
        string GetTipe() {
            return m_tipe;
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

        bool Attack(Galo &opponent, Armamento &arma, int adicional) {
            /*Tipos de ataques diferentes com precisões de ataque diferentes*/
            array <pair<string, int>, 4> Ataques = {{
                {"Bicada", 70},
                {"Arranhão", 45},
                {"Batida de Asa", 30},
                {"Investida", 60}
            }};
            /*Ataques específicos para galos Heróis*/
            array <pair<string, int>, 4> AtaquesDiferenciados = {{
                {"Bicada Fatal", 100},
                {"Arranhão Profundo", 100},
                {"Batida de Asa Lendária", 100},
                {"Investida Suprema", 100}
            }};
            
            /*
            */

            //premissa 1: verificar se o galo é Herói ou não para decidir o tipo de ataque utilizado
            if (m_tipe == "Heroi") {
                srand(time(0));
                int ataque = rand() % 4;
                cout << "Ataque utilizado: " << AtaquesDiferenciados[ataque].first << endl << "Precisão do ataque: " << AtaquesDiferenciados[ataque].second << "%" << endl;
                
            }
            else {
                srand(time(0));
                int ataque = rand() % 4;
                cout << "Ataque utilizado: " << Ataques[ataque].first << endl << "Precisão do ataque: " << Ataques[ataque].second << "%" << endl;
            }

            //premissa 2: adicionar os booster de ataque ou defesa 

            //premissa 3: verificar se o ataque do galo é maior que a defesa do oponente
            if (m_attack > opponent.m_defense) {
                //premissa 4: subtrair o dano (ataque - defesa) da vida do oponente
                float damage = m_attack - opponent.m_defense;
                opponent.SetLife(opponent.GetLife() - damage);                
            }
            else {
                return false;
            }
        }

        /*Ataque crítico reservado apenas para Heróis*/
        bool MaldicaoDoGalo(vector <Galo> *timeAtacante,vector <int> Vitimas) {
            if(m_tipe == "Heroi") {
                srand(time(0));
                int chance = rand() % 60;
                if(chance > 60) { 
                        return true;
                }
                    else {
                        return false;
                    }
            }
        }
        
        /*Fuga do Covarde*/
        bool FugaDasGalinhas() {
            srand(time(0));
            int chance = rand() % 40;
            if(chance > 40) { 
                return true;
            }
            else {
                return false;
            }
        }

        /*Traição do galo Traidor*/
        bool GaloJudas() {
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

class Armamento {
    private:
        string m_name;
        /*Ataque ou defesa*/
        string m_tipe; 
        float m_power;

    public: 
        string GetName() {
            return m_name;
        }
        string GetTipe() {
            return m_tipe;
        }
        float GetPower() {
            return m_power;
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

        /*Existe 40% de chance da arma quebrar após cada uso*/
        bool BreakWeapon() {
            srand(time(0));
            int chance = rand() % 25;
            if(chance > 25) {
                return true;
            }
            else {
                return false;
            }
        }

};
