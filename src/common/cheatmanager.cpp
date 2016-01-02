#include "cheatmanager.h"
#include "core\memory.h"

namespace Cheats
{
    CheatManager* cheatManager;
    bool isInitialized;

    void Init()
    {
        if (!isInitialized)
        {
            cheatManager = new CheatManager();
            isInitialized = true;
        }
    }

    CheatManager::CheatManager()
    {
        cheatItems = vector<CheatItem*>();
    }

    CheatManager::~CheatManager()
    {
        cheatItems.clear();
    }

    void CheatManager::AddCheat(std::string name, int32_t address, int32_t value, CheatType type)
    {
        CheatItem* item = (CheatItem*)malloc(sizeof(CheatItem));
        strcpy((char*)&item->cheatName, name.c_str());
        item->cheatAddress = address;

        if (type == CHEAT_TYPE_8)
            item->cheatValue = value % 255;
        else if (type == CHEAT_TYPE_16)
            item->cheatValue = value % 65535;
        else
            item->cheatValue = value;

        item->cheatType = type;

        cheatItems.push_back(item);
    }

    vector<CheatItem*>* CheatManager::GetCheatItems()
    {
        return &cheatItems;
    }

    void CheatManager::Update()
    {
        for (int i = 0; i < cheatItems.size(); i++)
        {
            CheatItem* item = cheatItems[i];

            if (item->cheatAddress != NULL)
            {
                switch (item->cheatType)
                {
                case CHEAT_TYPE_8:
                    Memory::Write8(item->cheatAddress, item->cheatValue);
                    break;
                case CHEAT_TYPE_16:
                    Memory::Write16(item->cheatAddress, item->cheatValue);
                    break;
                case CHEAT_TYPE_32:
                    Memory::Write32(item->cheatAddress, item->cheatValue);
                    break;
                }
            }
        }
    }
}