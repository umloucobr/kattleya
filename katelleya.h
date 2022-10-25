#ifndef KATELLEYA_H
#define KATELLEYA_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QClipboard>
#include <QMimeData>
#include <QFont>

QT_BEGIN_NAMESPACE
namespace Ui { class Katelleya; }
QT_END_NAMESPACE

class Katelleya : public QMainWindow
{
    Q_OBJECT

public:
    Katelleya(QWidget *parent = nullptr);
    ~Katelleya();

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

private:
    Ui::Katelleya *ui;
    QString currentFile;
};
#endif // KATELLEYA_H
