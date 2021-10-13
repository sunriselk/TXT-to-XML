#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TXT2XML.h"

class TXT2XML : public QMainWindow
{
    Q_OBJECT

public:
    TXT2XML(QWidget *parent = Q_NULLPTR);

private:
    Ui::TXT2XMLClass ui;
    QString m_strtxtDir;
    QString m_strxmlDir;


protected slots:
    void OnSelecttxtDir();
    void OnSelectxmlDir();
    void OnStartTransformation();
};
