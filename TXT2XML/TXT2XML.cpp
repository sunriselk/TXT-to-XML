#include "TXT2XML.h"
#include <qfiledialog.h>
#include "tinyxml2.h"
#include <string>
#include <sstream>
#include <fstream>

TXT2XML::TXT2XML(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QObject::connect(ui.BTN_TXTDIR, &QPushButton::clicked, this, &TXT2XML::OnSelecttxtDir);
    QObject::connect(ui.BTN_XMLDIR, &QPushButton::clicked, this, &TXT2XML::OnSelectxmlDir);
    QObject::connect(ui.BTN_START, &QPushButton::clicked, this, &TXT2XML::OnStartTransformation);
}

void TXT2XML::OnSelecttxtDir()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setViewMode(QFileDialog::Detail);

    //QString filter = "*.txt";
    //fileDialog.setNameFilter(filter);

    if (fileDialog.exec())
    {
        m_strtxtDir = fileDialog.selectedFiles()[0];
        ui.LINEEDIT_TXTDIR->setText(m_strtxtDir);
    }
}

void TXT2XML::OnSelectxmlDir()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setViewMode(QFileDialog::Detail);

    QString filter = "*.xml";
    fileDialog.setNameFilter(filter);

    if (fileDialog.exec())
    {
        m_strxmlDir = fileDialog.selectedFiles()[0];
        ui.LINEEDIT_XMLDIR->setText(m_strxmlDir);
    }
}

void TXT2XML::OnStartTransformation()
{
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLNode;

    XMLDocument* doc = new XMLDocument();
    XMLNode* camera_param = doc->InsertEndChild(doc->NewElement("camera_param"));
    XMLNode* intrinsic_param = camera_param->InsertFirstChild(doc->NewElement("intrinsic_param"));
    XMLNode* extrinsic_param = camera_param->InsertEndChild(doc->NewElement("extrinsic_param"));
    
    for (int i = 0; i < 11; i++)
    {
        std::stringstream sstream;
        std::string strCameraName;
        sstream << "camera" << i + 1;
        sstream >> strCameraName;
        XMLNode* camerai = intrinsic_param->InsertEndChild(doc->NewElement(strCameraName.c_str()));

        sstream.clear();
        sstream.str("");
        std::string strFileName;
        sstream << "Camera";
        if (i < 9)
            sstream << 0 << i + 1 << ".txt";
        else
            sstream << i + 1 << ".txt";
        sstream >> strFileName;

        std::ifstream fin;
        fin.open((m_strtxtDir + "/" + strFileName.c_str()).toStdString().c_str());
        if (fin.is_open())
        {
            double dRes = 0;
            fin >> dRes;
            camerai->ToElement()->SetAttribute("fu", dRes);
            fin >> dRes;
            camerai->ToElement()->SetAttribute("fv", dRes);
            fin >> dRes;
            camerai->ToElement()->SetAttribute("u0", dRes);
            fin >> dRes;
            camerai->ToElement()->SetAttribute("v0", dRes);

            fin >> dRes;
            camerai->ToElement()->SetAttribute("k1", dRes);
            fin >> dRes;
            camerai->ToElement()->SetAttribute("k2", dRes);
            fin >> dRes;
            camerai->ToElement()->SetAttribute("k3", dRes);
            fin >> dRes;
            camerai->ToElement()->SetAttribute("p1", dRes);
            fin >> dRes;
            camerai->ToElement()->SetAttribute("p2", dRes);
        }
        fin.close();
    }
    doc->SaveFile(m_strxmlDir.toStdString().c_str());
}
