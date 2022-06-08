
#ifndef MONO_VIO_MAINWINDOWUI_H
#define MONO_VIO_MAINWINDOWUI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowUI; }
QT_END_NAMESPACE

class MainWindowUI : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindowUI(QWidget *parent = nullptr);

    ~MainWindowUI() override;

private:
    Ui::MainWindowUI *ui;
};


#endif //MONO_VIO_MAINWINDOWUI_H
