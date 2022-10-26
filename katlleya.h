#ifndef KATLLEYA_H
#define KATLLEYA_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QClipboard>
#include <QMimeData>
#include <QFont>
#include <QCloseEvent>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class Katlleya; }
QT_END_NAMESPACE

class Katlleya : public QMainWindow
{
    Q_OBJECT

protected:
   void closeEvent(QCloseEvent *event) override;

public:
    Katlleya(QWidget *parent = nullptr);
    ~Katlleya();

private slots:
    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionBold_triggered(bool checked);

    void on_actionItalic_triggered(bool checked);

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_textEdit_textChanged();

    void on_actionAbout_triggered();

private:
    Ui::Katlleya *ui;
    QString currentFile;
    bool documentWasEdited {false};
};
#endif // KATLLEYA_H
