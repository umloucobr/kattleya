#include "katelleya.h"
#include "./ui_katelleya.h"

Katelleya::Katelleya(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Katelleya)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
}

Katelleya::~Katelleya()
{
    delete ui;
}

void Katelleya::on_actionNew_triggered()
{
    QMessageBox messageBox;
    messageBox.setIcon(QMessageBox::Warning);
    messageBox.setText("This will erase all your unsaved changes");
    messageBox.setInformativeText("Are you sure you want to do this?");
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::No);
    currentFile.clear();
    int result = messageBox.exec();
    switch (result){
        case QMessageBox::Yes:
            ui->textEdit->setText(QString());
        case QMessageBox::No:
            break;
        default:
            break;
    }
}


void Katelleya::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void Katelleya::on_actionSave_triggered()
{
    QString fileName;
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        if (fileName.isEmpty())
            return;
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void Katelleya::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void Katelleya::on_actionExit_triggered()
{
    QMessageBox messageBox;
    messageBox.setIcon(QMessageBox::Warning);
    messageBox.setText("Are you sure you want to quit?");
    messageBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Save | QMessageBox::Discard);
    messageBox.setDefaultButton(QMessageBox::Cancel);
    currentFile.clear();
    int result = messageBox.exec();
    switch (result){
        case QMessageBox::Save:
            Katelleya::on_actionSave_triggered();
        case QMessageBox::Discard:
            QApplication::quit();
        case QMessageBox::Cancel:
            return;
            break;
        default:
            break;
    }
}


void Katelleya::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void Katelleya::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void Katelleya::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void Katelleya::on_actionBold_triggered(bool checked)
{
    if(checked){
        ui->textEdit->setFontWeight(QFont::Bold);
    }
    else {
        ui->textEdit->setFontWeight(QFont::Normal);
    }
}


void Katelleya::on_actionItalic_triggered(bool checked)
{
    if(checked){
        ui->textEdit->setFontItalic(true);
    }
    else {
        ui->textEdit->setFontItalic(false);
    }
}

