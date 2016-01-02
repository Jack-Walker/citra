// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <map>

#include <QKeySequence>
#include <QSettings>
#include <QShortcut>

#include "citra_qt/cheats.h"
#include "citra_qt/cheats_add.h"
#include "common/cheatmanager.h"

GCheatsDialog::GCheatsDialog(QWidget* parent): QDialog(parent)
{
    cheatsUI.setupUi(this);

    connect(cheatsUI.addCheatButton, SIGNAL(released()), this, SLOT(OnAddCheatClick()));
    connect(cheatsUI.deleteCheatButton, SIGNAL(released()), this, SLOT(OnDeleteCheatClick()));

    // Initialize cheats, if they weren't initialized already.
    Cheats::Init();

    // Fill list with cheats.
    SetupItems();

    cheatsUI.treeWidget->resizeColumnToContents(0);
    cheatsUI.treeWidget->resizeColumnToContents(1);
    cheatsUI.treeWidget->resizeColumnToContents(2);
}

void GCheatsDialog::OnAddCheatClick()
{
    GCheatsDialogAdd dialog(this);
    dialog.exec();
}

void GCheatsDialog::OnDeleteCheatClick()
{
    int listPos = cheatsUI.treeWidget->pos().y();
    std::vector<Cheats::CheatItem*>* cheatItems = Cheats::cheatManager->GetCheatItems();
    if (listPos < cheatItems->size())
    {
        cheatItems->erase(cheatItems->begin() + listPos);
        SetupItems();
    }
}

void GCheatsDialog::SetupItems()
{
    cheatsUI.treeWidget->clear();

    for (int i = 0; i < Cheats::cheatManager->GetCheatItems()->size(); i++)
    {
        Cheats::CheatItem* cheatItem = Cheats::cheatManager->GetCheatItems()->at(i);

        std::string itemText;
        QTreeWidgetItem* toplevel_item = new QTreeWidgetItem(QStringList(""));

        char cheatAddrStr[64], cheatValStr[64];

        sprintf((char*)&cheatAddrStr, "%08x", cheatItem->cheatAddress);

        if (cheatItem->cheatType == Cheats::CHEAT_TYPE_8)
            sprintf((char*)&cheatValStr, "%02x", cheatItem->cheatValue);
        else if (cheatItem->cheatType == Cheats::CHEAT_TYPE_16)
            sprintf((char*)&cheatValStr, "%04x", cheatItem->cheatValue);
        else
            sprintf((char*)&cheatValStr, "%08x", cheatItem->cheatValue);

        toplevel_item->setText(0, cheatItem->cheatName);
        toplevel_item->setText(1, cheatAddrStr);
        toplevel_item->setText(2, cheatValStr);

        cheatsUI.treeWidget->addTopLevelItem(toplevel_item);
    }

    cheatsUI.treeWidget->resizeColumnToContents(0);
    cheatsUI.treeWidget->resizeColumnToContents(1);
    cheatsUI.treeWidget->resizeColumnToContents(2);
}