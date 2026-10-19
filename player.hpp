#include <iostream>

using namespace std;

class Player {
    private: 
        string m_name;
        float m_life, m_attack, m_defense;
    
    public: 
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

        bool Attack(Player &opponent) {
            //premissa 1: verificar se o ataque do jogador é maior que a defesa do oponente
            if (m_attack > opponent.m_defense) {

                //premissa 2: subtrair o dano (ataque - defesa) da vida do oponente
                float damage = m_attack - opponent.m_defense;
                opponent.SetLife(opponent.GetLife() - damage);
                return true;
            }
            else {
                return false;
            }
        }

};