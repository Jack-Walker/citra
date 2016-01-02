#pragma once

using namespace std;

#include <iostream>
#include <string>
#include <vector>

namespace Cheats
{
    enum CheatType
    {
        CHEAT_TYPE_8,
        CHEAT_TYPE_16,
        CHEAT_TYPE_32
    };

    struct CheatItem
    {
        char cheatName[64];
        int32_t cheatAddress;
        int32_t cheatValue;
        CheatType cheatType;
    };

    class CheatManager
    {
    public:
        CheatManager();
        ~CheatManager();
        void AddCheat(std::string name, int32_t address, int32_t value, CheatType type);
        void Update();
        vector<CheatItem*>* GetCheatItems();

    private:
        int numCheats;
        vector<CheatItem*> cheatItems;
    };

    extern CheatManager* cheatManager;
    extern bool isInitialized;

    void Init();
}