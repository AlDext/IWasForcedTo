#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

struct unit {
    double hp, spd, bav, av;
    std::string name;
    int element;
};
class combat {
public:
    std::vector<unit> team = {
        {100, 98, 0, 0, "c1", 1},
        {100, 121, 0, 0, "c2", 1},
        {100, 112, 0, 0, "c3", 1}
    };
    std::vector<unit> oppteam = {
        {100, 95, 0, 0, "v1", 2},
        {100, 100, 0, 0, "v2", 2},
        {100, 111, 0, 0, "v3", 2}
    };
    std::vector<unit> allunits;

    std::vector<unit> bufferunits;
    std::vector<unit> currentunits;

    double ta;
public:
    void bav(std::vector<unit>& team) {
        for (int i = 0; i < team.size(); i++) {
            team[i].bav = 10000/team[i].spd;
        }
    }
    void assign_bav_av(std::vector<unit>& team) {
        for (int i = 0; i < team.size(); i++) {
            team[i].av = team[i].bav;
        }
    }
    void sync_hp(std::vector<unit>& updated) {
        for (const auto& u : updated) {
            for (auto& t : team) {
                if (u.name == t.name) {
                    t.hp = u.hp;
                }
            }
            for (auto& o : oppteam) {
                if (u.name == o.name) {
                    o.hp = u.hp;
                }
            }
        }
    }

    /*void arrange(std::vector<unit> allies, std::vector<unit> enemies, std::vector<unit>& allunits) {
        for (int i = 0; i < allies.size(); i++) {
            allunits.push_back(allies.at(i));
        }
        for (int i =0;i<enemies.size();i++) {
            allunits.push_back(enemies.at(i));
        }
        std::sort(allunits.begin(), allunits.end(), [](const unit& a, const unit& b) {
    return b.av > a.av;
});
    }*/
    void arrange(const std::vector<unit>& allies,
             const std::vector<unit>& enemies,
             std::vector<unit>& out) {
        out.clear();
        out.reserve(allies.size() + enemies.size());
        out.insert(out.end(), allies.begin(), allies.end());
        out.insert(out.end(), enemies.begin(), enemies.end());
        std::sort(out.begin(), out.end(), [](const unit& a, const unit& b) {
            return b.av > a.av;
        });
    }

    void reassign_av(std::vector<unit> currentunits) {
        if (currentunits.empty()) return;
        for (int i = 0; i < team.size(); i++) {
            if (currentunits[0].name == team[i].name) {
                currentunits[0].av = team[i].bav;
            }
        }
        for (int i = 0; i < oppteam.size(); i++) {
            if (currentunits[0].name == oppteam[i].name) {
                currentunits[0].av = oppteam[i].bav;
            }
        }
    }
    bool battleover(std::vector<unit>& units) {
        int deadt =0;
        int t=0;

        int deado=0;
        int o=0;
        for (int i =0; i < units.size(); ++i) {
            if (units[i].element == team[0].element) {
                t++;
                if (units[i].hp <1) {
                    deadt++;
                }
            }
            else if (units[i].element == oppteam[0].element) {
                o++;
                if (units[i].hp <1) {
                    deado++;
                }
            }
        }
        if (deadt==t || deado==o) {
            return true;
        }
        else {
            return false;
        }
    }
    std::string subject(std::vector<unit>& units, std::string cmd) {
        for (int i = 0; i < units.size(); ++ i) {
            if (cmd.find(units[i].name) != std::string::npos) {
                return units[i].name;
            }
        }
        return "";
    }
    void action(std::vector<unit>& units, const std::string& subject, const std::string& cmd) {
        if (subject.empty()) {
            std::cerr << "Error: no subject found in command '" << cmd << "'\n";
            return;
        }

        int target = -1;
        for (int i = 0; i < units.size(); ++i) {
            if (subject == units[i].name) {
                target = i;
                break;
            }
        }

        if (target == -1) {
            std::cerr << "Error: subject '" << subject << "' not found in current units.\n";
            return;
        }

        // --- parsing logic continues safely here ---
        size_t dash = cmd.find('-');
        if (dash == std::string::npos) {
            std::cerr << "Invalid command format (missing '-')\n";
            return;
        }

        size_t space = cmd.find(' ', dash);
        if (space == std::string::npos) {
            std::cerr << "Invalid command format (missing value)\n";
            return;
        }

        std::string param = cmd.substr(dash + 1, space - dash - 1);
        std::string value_str = cmd.substr(space + 1);

        try {
            double value = std::stod(value_str);

            if (param == "d") { // damage
                units[target].hp -= value;
                if (units[target].hp < 0) units[target].hp = 0;
                std::cout << units[target].name << " took " << value
                          << " damage. New HP: " << units[target].hp << '\n';
            }
            else if (param == "h") { // heal
                units[target].hp += value;
                std::cout << units[target].name << " healed " << value
                          << " HP. New HP: " << units[target].hp << '\n';
            }
            else {
                std::cerr << "Unknown action parameter: " << param << '\n';
            }
        } catch (...) {
            std::cerr << "Invalid numeric value: " << value_str << '\n';
        }
    }

};
void combatflow();
int main() {
    combatflow();
    return 0;
}
void combatflow() {
    combat battle;

    battle.bav(battle.team);
    battle.bav(battle.oppteam);
    battle.assign_bav_av(battle.team);
    battle.assign_bav_av(battle.oppteam);

    // Initialize bufferunits with all units
    //battle.bufferunits = battle.team;
   // battle.arrange(battle.team, battle.oppteam, battle.bufferunits);
   // battle.bufferunits.insert(battle.bufferunits.end(), battle.oppteam.begin(), battle.oppteam.end());
    battle.arrange(battle.team, battle.oppteam, battle.bufferunits);
   /* for (int i = 0; i < battle.bufferunits.size(); ++i) {
        std::cout << battle.bufferunits[i].name << " " << battle.bufferunits[i].av << '\n';
    }*/
    do{ //jahfajvlbriu
        std::string smth = "clear";
        battle.currentunits.clear();
        battle.currentunits = battle.bufferunits;
        battle.bufferunits.clear();

        for (int i = 0; i < battle.currentunits.size(); ++i) {
            std::cout << battle.currentunits[i].name << " - (" << battle.currentunits[i].hp << ") (" << battle.currentunits[i].av << ") " << '\n';
        }

        battle.ta = battle.currentunits[0].av;

        for (int i = 0; i < battle.currentunits.size(); ++i) {
            battle.currentunits[i].av -= battle.ta;
        }

        battle.reassign_av(battle.currentunits);
        std::sort(battle.currentunits.begin(), battle.currentunits.end(), [](const unit& a, const unit& b) {
return b.av > a.av;
});
        //battle.bufferunits = battle.currentunits;
        do{
            smth.clear();
            std::cout << "\n> ";

            std::getline(std::cin, smth);
        }while (smth.empty()) ;
        std::string subject = battle.subject(battle.currentunits, smth);


    }while (!battle.battleover(battle.currentunits)) ;
}
