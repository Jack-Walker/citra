// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "ui_cheats_add.h"

class QDialog;
class QKeySequence;
class QSettings;
class QShortcut;

class GCheatsDialogAdd : public QDialog
{
    Q_OBJECT

public:
    GCheatsDialogAdd(QWidget* parent = nullptr);

private:
    Ui::CheatsAdd addCheatUI;

private slots:
    void OnAddCheatClick();
};
