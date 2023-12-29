#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "interpreter.h"

#include <QMainWindow>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  static MainWindow& getMainWindow();
  ~MainWindow();

 private slots:
  void on_runButton_clicked();

 private:
  MainWindow(QWidget *parent = nullptr);
  std::string& trim(std::string &s);

  static MainWindow* mw;
  Ui::MainWindow *ui;
  Interpreter itp;
};
#endif  // MAINWINDOW_H
