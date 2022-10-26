#include "katlleya.h"
#include "./ui_katlleya.h"

Katlleya::Katlleya(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Katlleya)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
}

Katlleya::~Katlleya()
{
    delete ui;
}

//Tool bar actions.
void Katlleya::on_actionNew_triggered()
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


void Katlleya::on_actionOpen_triggered()
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


void Katlleya::on_actionSave_triggered()
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


void Katlleya::on_actionSave_as_triggered()
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


void Katlleya::on_actionExit_triggered()
{
    QApplication::quit();
}


void Katlleya::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void Katlleya::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void Katlleya::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void Katlleya::on_actionBold_triggered(bool checked)
{
    if(checked){
        ui->textEdit->setFontWeight(QFont::Bold);
    }
    else {
        ui->textEdit->setFontWeight(QFont::Normal);
    }
}


void Katlleya::on_actionItalic_triggered(bool checked)
{
    if(checked){
        ui->textEdit->setFontItalic(true);
    }
    else {
        ui->textEdit->setFontItalic(false);
    }
}


void Katlleya::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void Katlleya::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

//Ask if user want to save before quitting.
void Katlleya::closeEvent(QCloseEvent *event)
{
    if(documentWasEdited){
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setText("Are you sure you want to quit?");
        messageBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Save | QMessageBox::Discard);
        messageBox.setDefaultButton(QMessageBox::Cancel);
        int result = messageBox.exec();
        switch (result){
        case QMessageBox::Save:
            event->accept();
            Katlleya::on_actionSave_triggered();
            QApplication::quit();
        case QMessageBox::Discard:
            event->accept();
            QApplication::quit();
        case QMessageBox::Cancel:
            event->ignore();
        default:
            break;
        }
    }
    else {
        event->accept();
        QApplication::quit();
    }
}

void Katlleya::on_textEdit_textChanged()
{
    if(currentFile.isEmpty()){
        QString filename = {"*Katlleya"};
        setWindowTitle(filename);
    }
    else{
        QString filename = currentFile;
        filename.prepend("*");
        setWindowTitle(filename);
    }
    documentWasEdited = true;
}


void Katlleya::on_actionAbout_triggered()
{
    QMessageBox messageBox;
    messageBox.setIcon(QMessageBox::Information);
    messageBox.setText("Kattleya V1.0");
    messageBox.setStandardButtons(QMessageBox::Ok);
    messageBox.setDefaultButton(QMessageBox::Ok);
    messageBox.exec();
}

