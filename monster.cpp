#include <iostream>
#include <ctime>
#include <string>

using namespace std;

const int armors = 4;
const int weapons = 4;

void pause(string text = "") {
    cout << "\n" << text << "\n";
    fflush(stdin);
    cin.get();
    system("clear");
}

void clean() {
    system("clear");
}

bool writeCode(string saver, int count, string text) {
    string code, write_code;
    for (int i = 0; i < count; i++) {
        code += saver[rand() % (saver.length() - 1)];
    }
    cout << text << code << "): ";
    cin >> write_code;
    if (write_code == code) {
        return true;
    }
    else {
        return false;
    }
}

int getId(string names[], string text, int items) {
    int item_id;
    cout << text;
    for (int i = 0; i < items; i++) {
        cout << i + 1 << ". " << names[i] << endl;
    }
    cin >> item_id;

    return item_id;
} 

class Weapon {
    private:
        string name;
        int damage;
    public:
        Weapon(string name = "") {
            this->name = name;
            if (name == "Ніж") {
                damage = 15;
            }
            else if (name == "Мачете") {
                damage = 20;
            }
            else if (name == "Катана") {
                damage = 25;
            }
            else if (name == "Джавелін") {
                damage = 100000;
            }
            else {
                damage = 5;
            }
        }

        int getDamage() {
            return damage;
        }

        string getName() {
            return name;
        }
};

class Armor {
    private:
        string name;
        int defence;
    public:
        Armor(string name = "") {
            this->name = name;
            if (name == "Кольчуга") {
                defence = 20;
            }
            else if (name == "Золота броня") {
                defence = 15;
            }
            else if (name == "Алмазка") {
                defence = 30;
            }
            else if (name == "Незерітка") {
                defence = 40;
            }
            else {
                defence = 0;
            }
        }

        int getDefence() {
            return defence;
        }

        string getName() {
            return name;
        }

        int setAttack(int attack) {
            if (defence <= 0) {
                defence = 0;
                cout << "\nУ вас залишилося " << defence << " очків броні";
                return defence - attack;
            }
            else {
                defence -= attack;

                if (defence <= 0) {
                    cout << "\nУ вас залишилося " << 0 << " очків броні";
                    return defence;
                }
                else {
                    cout << "\nУ вас залишилося " << defence << " очків броні";
                    return 0;
                }
            }
        }
};

class Npc {
    protected:
        int lvl;
        int hp;
    public:
        int getHp() {
            return hp;
        }

        int getLvl() {
            return lvl;
        }
};

class Player : public Npc {
    private:
        int max_hp;
        Armor* armor = new Armor();
        Weapon* weapon = new Weapon();
    public:
        Player(int lvl, string armor_names[], string weapon_names[]) {
            hp = 75 + (25 * lvl);
            max_hp = hp;
            this->lvl = lvl;

            armor = generateArmor(armor_names);
            weapon = generateWeapon(weapon_names);
        }

        Armor* generateArmor(string armor_names[]) {
            Armor* armor = new Armor(armor_names[getId(armor_names, "Ти можеш вибрати собі зброю, введи номер зброї: \n", armors) - 1]);

            return armor;
        }

        int getDamage(string text) {
            cout << text << weapon->getDamage() << " ХП!";
            return weapon->getDamage();
        }

        Weapon* generateWeapon(string weapon_names[]) {
            clean();

            Weapon* weapon = new Weapon(weapon_names[getId(weapon_names, "Ти можеш вибрати собі вбрання, введи номер вбрання: \n", weapons) - 1]);

            return weapon;
        }

        int getWeaponDamage() {
            return weapon->getDamage();
        }

        string getWeaponName() {
            return weapon->getName();
        }

        int getArmorDefence() {
            return armor->getDefence();
        }

        string getArmorName() {
            return armor->getName();
        }

        bool setAttack(int attack) {
            hp += armor->setAttack(attack);
            if (hp == 0 || hp < 0) {
                cout << "\nВи загинули :C \nГру завершено";
                return true;
            }
            else {
                cout << " та " << hp << " ХП";
                return false;
            }
        }

        int getMaxHp() {
            return max_hp;
        }

        void setHeal() {
            hp += 15;
            if (hp >= max_hp) {
                hp = max_hp;
            }
        }
};

class Monster : public Npc {
    private: 
        int attack;
    public:
        Monster(int lvl) {
            hp = 90 + (10 * lvl);
            attack = 5 + (5 * lvl);
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

        int getAttack(string text) {
            cout << text << attack << " ХП!";
            return attack;
        }
};

class Engine {
    private:
        string saver = "1234567890abcdefgABCDEFG";
        string armor_names[armors] = {"Кольчуга", "Золота броня", "Алмазка", "Незерітка"};
        string weapon_names[weapons] = {"Ніж", "Мачете", "Катана", "Джавелін"};
    public:
        Engine() {

        }

        Player* generatePlayer(int lvl = 1) {
            Player* player = new Player(lvl, armor_names, weapon_names);

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
            return writeCode(saver, 4, "\nВведіть код щоб захиститись від атаки(");
        }

        bool healPlayer() {
            return writeCode(saver, 6, "\nВведіть код щоб полікуватися(");
        }

        bool oneRound(Player* player, Monster* monster) {
            bool isDie = false;

            paintArena();
            pause("На вас атакує монстр! ");
            
            paintArena(1);
            if (savePlayer() == true) {
                cout << "Ви захистились від атаки";
            }
            else {
                isDie = player->setAttack(monster->getAttack("Неправильно\nВам було нанесено "));
            }

            if (isDie) {
                return true;
            }

            pause();
            paintArena();

            pause("Тепер ви нападаєте на монтра ");
            paintArena(0, 1);
            isDie = monster->setDamage(player->getDamage("\nМонстру було нанесено "));
            
            if (isDie) {
                return true;
            }

            if (player->getHp() == player->getMaxHp()) {
                pause();
            }
            else if (healPlayer()) {
                player->setHeal();
                cout << "\nВи полікувались, вам додалось 15 ХП. Тепер ваше ХП - " << player->getHp() << endl;
                pause();
            }
            else {
                cout << "\nВи не полікувались";
                pause();
            }

            return false;
        }
};

int main() {
    srand(time(NULL));

    Engine* engine = new Engine();
    Player* player = engine->generatePlayer();
    Monster* monster = engine->generateMonster();

    bool theEnd = false;

    clean();

    cout << "Згенеровано плеєра(позначка %). Його ХП - " << player->getHp() << ". У нього є броня - " << player->getArmorName() << " яка дає " << player->getArmorDefence() << " очок захисту і зброя - "<< player->getWeaponName() <<" яка наносить " << player->getWeaponDamage() << " урону. А також монстра(позначка $) " << monster->getLvl() << " рівню. Його ХП - " << monster->getHp() << endl;

    pause("Для того щоб гра працювала нажимайте Enter: ");

    while(theEnd == false) {
        theEnd = engine->oneRound(player, monster);
    }

    engine->~Engine();

    pause("Для виходу нажміть Enter: ");

    return 0;
}