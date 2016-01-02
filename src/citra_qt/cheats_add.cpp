// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <map>

#include <QKeySequence>
#include <QSettings>
#include <QShortcut>
#include <qerrormessage.h>

#include <Windows.h>

#include "citra_qt/cheats_add.h"
#include "common\cheatmanager.h"
#include "citra_qt/cheats.h"

GCheatsDialogAdd::GCheatsDialogAdd(QWidget* parent): QDialog(parent)
{
    addCheatUI.setupUi(this);
    connect(addCheatUI.addCheatButton, SIGNAL(released()), this, SLOT(OnAddCheatClick()));
}

void GCheatsDialogAdd::OnAddCheatClick()
{
    // Get cheat info
    string addressStr = addCheatUI.addressBox->text().toStdString();
    string valueStr = addCheatUI.valueBox->text().toStdString();
    Cheats::CheatType cheatType;

    // Add cheat
    if (addCheatUI.radioEightBit->isChecked())
        cheatType = Cheats::CHEAT_TYPE_8;
    else if (addCheatUI.radioSixteenBit->isChecked())
        cheatType = Cheats::CHEAT_TYPE_16;
    else
        cheatType = Cheats::CHEAT_TYPE_32;

    Cheats::cheatManager->AddCheat(addCheatUI.cheatNameBox->text().toStdString(), strtol(addressStr.c_str(), NULL, 16), strtol(valueStr.c_str(), NULL, 16), cheatType);

    // Close dialog
    close();

    // Refresh our list of cheats.
    GCheatsDialog* cheatsDiag = (GCheatsDialog*)parent();
    cheatsDiag->SetupItems();
}
