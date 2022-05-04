#include <iostream>
#include <ctime>

using namespace std;

void pause(string text = "") {
    cout << "\n" << text << "\n";
    fflush(stdin);
    cin.get();
    system("clear");
}

class Npc {
    protected:
        int lvl;
        int hp;
        int attack;
    public:
        int getHp() {
            return hp;
        }

        int getLvl() {
            return lvl;
        }

        int getAttack(string text) {
            cout << text << attack << " ХП!";
            return attack;
        }
};

class Player : public Npc {
    public:
        Player(int lvl) {
            hp = 75 + (25 * lvl);
            attack = 15 + (5 * lvl);
            this->lvl = lvl;
        }

        bool setDamage(int damage) {
            hp -= damage;
            if (hp == 0 || hp < 0) {
                cout << "\nВи загинули :C \nГру завершено";
                return true;
            }
            else {
                cout << "\nУ вас залишилося " << hp << " ХП";
                return false;
            }
        }
};

class Monster : public Npc {
    public:
        Monster(int lvl) {
            hp = 90 + (10 * lvl);
            attack = 15 + (5 * lvl);
            this->lvl = lvl;
        }

        bool setDamage(int damage) {
            hp -= damage;
            if (this->hp == 0 || this->hp < 0) {
                cout << "\nМонстр загинув! \nГру завершено";
                return true;
            }
            else {
                cout << "\nУ монстра залишилося " << this->hp << " ХП";
                return false;
            }
        }
};

class Engine {
    private:
        string saver = "1234567890abcdefgABCDEFG";
    public:
        Player* generatePlayer(int lvl = 1) {
            Player* player = new Player(lvl);

            return player;
        }

        Monster* generateMonster(int lvl = rand() % 10 + 1) {
            Monster* monster = new Monster(lvl);

            return monster;
        }

        void paintArena(int m = 0, int p = 0) {
            for (int i = 0; i < 9; i++) {
                cout << "#";
            }

            cout << endl;

            for (int i = 0; i < 7; i++) {
                cout << "#";
                for (int j = 0; j < 7; j++) {
                    if (i == 2 + m && j == 3) {
                        cout << "$";
                    }
                    else if (i == 4 - p && j == 3) {
                        cout << "%";
                    }
                    else {
                        cout << " ";
                    }
                }
                cout << "#" << endl;
            }

            for (int i = 0; i < 9; i++) {
                cout << "#";
            }
        }

        bool savePlayer() {
            string code, write_code;
            for (int i = 0; i < 4; i++) {
                code += saver[rand() % (saver.length() - 1)];
            }
            cout << "\nВведіть код щоб захиститись від атаки(" << code << "): ";
            cin >> write_code;
            if (write_code == code) {
                return true;
            }
            else {
                return false;
            }
        }

        bool oneRound(Player* player, Monster* monster) {
            bool isDie = false;

            paintArena();
            pause("На вас атакує монстр! ");
            
            paintArena(1);
            if (savePlayer() == true) {
                cout << "\nВи захистились від атаки";
            }
            else {
                isDie = player->setDamage(monster->getAttack("\nНеправильно\nВам було нанесено "));
            }

            if (isDie) {
                return true;
            }

            pause();
            paintArena();

            pause("Тепер ви нападаєте на монтра ");
            paintArena(0, 1);
            isDie = monster->setDamage(player->getAttack("\nМонстру було нанесено "));
            
            if (isDie) {
                return true;
            }

            pause();

            return false;
        }
};

int main() {
    srand(time(NULL));

    Engine* engine = new Engine();
    Player* player = engine->generatePlayer();
    Monster* monster = engine->generateMonster();

    bool theEnd = false;

    cout << "Згенеровано плеєра(позначка %). Його ХП - " << player->getHp() << ". А також монстра(позначка $) " << monster->getLvl() << " рівню. Його ХП - " << monster->getHp() << endl;

    pause("Для того щоб гра працювала нажимайте Enter: ");

    while(theEnd == false) {
        theEnd = engine->oneRound(player, monster);
    }

    pause("Для виходу нажміть Enter: ");
}