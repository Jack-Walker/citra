// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "ui_cheats.h"

class QDialog;
class QKeySequence;
class QSettings;
class QShortcut;

class GCheatsDialog : public QDialog
{
    Q_OBJECT

public:
    GCheatsDialog(QWidget* parent = nullptr);
    void SetupItems();

private:
    Ui::CheatsDialog cheatsUI;

private slots:
    void OnAddCheatClick();
    void OnDeleteCheatClick();
};
