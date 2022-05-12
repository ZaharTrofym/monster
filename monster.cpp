#include <iostream>
#include <ctime>
#include <string>
#include <fstream>

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
        string name = "";
        int damage = 0;
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
                this->name = "Кулаки";
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
        string name = "";
        int defence = 0;
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
        int lvl = 0;
        int hp = 0;
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
        int maxHp = 0;
        Armor* armor = NULL;
        Weapon* weapon = NULL;
    public:
        Player() {
            lvl = 1;
            hp = 75 + (25 * lvl);
            maxHp = hp;
            armor = new Armor();
            weapon = new Weapon();
        }

        Player(int lvl, Armor* armor, Weapon* weapon) {
            hp = 75 + (25 * lvl);
            maxHp = hp;
            this->lvl = lvl;
            this->armor = armor;
            this->weapon = weapon;
        }

        int getDamage(string text) {
            cout << text << weapon->getDamage() << " ХП!";

            return weapon->getDamage();
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
            return maxHp;
        }

        void setHeal() {
            hp += 15;

            if (hp >= maxHp) {
                hp = maxHp;
            }
        }
};

class Monster : public Npc {
    private: 
        int attack = 0;
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
        string armorNames[armors] = {"Кольчуга", "Золота броня", "Алмазка", "Незерітка"};
        string weaponNames[weapons] = {"Ніж", "Мачете", "Катана", "Джавелін"};
    public:
        Engine() {

        }

        Player* generatePlayer(int lvl = 1) {
            Player* player = new Player(lvl, generateArmor(), generateWeapon());

            return player;
        }

        Monster* generateMonster(int lvl = rand() % 10 + 1) {
            Monster* monster = new Monster(lvl);

            return monster;
        }

        Armor* generateArmor() {
            Armor* armor = new Armor(armorNames[getId(armorNames, "Ти можеш вибрати собі зброю, введи номер зброї: \n", armors) - 1]);

            return armor;
        }

        Weapon* generateWeapon() {
            clean();
            Weapon* weapon = new Weapon(weaponNames[getId(weaponNames, "Ти можеш вибрати собі вбрання, введи номер вбрання: \n", weapons) - 1]);

            return weapon;
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

bool save(Player* player) {
    ofstream outputFile;

    outputFile.open("database.txt");

    if (!outputFile.is_open()) {
        cout << "Error!";

        return false;
    }

    outputFile.write((char*)player, sizeof(Player));

    outputFile.close();

    return true;
}

Player* load() {
    ifstream inputFile;
    Player* obj = new Player();

    inputFile.open("database.txt");

    if (!inputFile.is_open()) {
        cout << "Error!";
    }

    inputFile.read((char*)obj, sizeof(Player));

    inputFile.close();

    return obj;

}

int getNum(string text) {
    int num;
    cout << text;
    cin >> num;

    return num;
}

int main() {
    srand(time(NULL));
    setlocale(0, "");
    int num = getNum("Ви хочете загрузити бійця з минулої гри?(Так - 1, Ні - 2): ");
    Engine* engine = new Engine();
    Player* player = new Player();

    if (num == 1) {
        player = load();
    }
    else {
        player = engine->generatePlayer();
    }

    Monster* monster = engine->generateMonster();

    bool theEnd = false;

    clean();

    cout << "Згенеровано плеєра(позначка %). Його ХП - " << player->getHp() << ". У нього є броня - " << player->getArmorName() << " яка дає " << player->getArmorDefence() << " очок захисту і зброя - "<< player->getWeaponName() <<" яка наносить " << player->getWeaponDamage() << " урону. А також монстра(позначка $) " << monster->getLvl() << " рівню. Його ХП - " << monster->getHp() << endl;

    pause("Для того щоб гра працювала нажимайте Enter: ");

    while(theEnd == false) {
        theEnd = engine->oneRound(player, monster);
    }

    engine->~Engine();
    
    pause();
    num = getNum("Ви хочете зберегти бійця для того щоб продовжити грати за нього?\nЯкщо так - 1, ні - 2: ");

    if (num == 1) {
        if(save(player) == true) {
            return 0;
        }
        else {
            pause();

            return 0;
        }
    }
    else {
        clean();
        cout << "кінець";

        return 0;
    }
}