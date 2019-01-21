#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_hexLineEdit_textEdited();

	void on_floatLineEdit_textEdited();

	void on_bigEndian_toggled();

private:
	Ui::MainWindow *ui = nullptr;
};

#endif // MAINWINDOW_H
