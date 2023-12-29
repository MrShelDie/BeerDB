#include "mainwindow.h"

#include "./ui_mainwindow.h"

#include <sstream>
#include <streambuf>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setFixedSize(
      this->geometry().width(),
      this->geometry().height());

  ui->plainTextEdit
      ->setStyleSheet(
          "background-image:url(\"/home/gannemar/BeerDB/BeerDB/img/lager-beer.png\"); background-position: center;");

  ui->textBrowser
      ->setStyleSheet(
          "background-image:url(\"/home/gannemar/BeerDB/BeerDB/img/el.png\"); background-position: center; opacity: 127;");

}

MainWindow& MainWindow::getMainWindow() {
  static MainWindow w;
  return w;
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_runButton_clicked() {
  ui->textBrowser->clear();

  // Redirect cout.
  std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
  std::ostringstream strCout;
  std::cout.rdbuf(strCout.rdbuf());

  std::string sql = ui->plainTextEdit->toPlainText().toStdString();
  trim(sql);
  itp.ExecSQL(sql);

  // Restore old cout.
  std::cout.rdbuf(oldCoutStreamBuf);

  ui->textBrowser->append(strCout.str().c_str());
}

std::string& MainWindow::trim(std::string& s) {
  if (s.empty()) {
    return s;
  }
  s.erase(0, s.find_first_not_of(" "));
  s.erase(s.find_last_not_of(" ") + 1);
  return s;
}
