#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->hexLineEdit->setFocus();
}

MainWindow::~MainWindow()
{
	delete ui;
}

static quint32 toUint(const QByteArray &data, bool bigEndian)
{
	if (data.size() != 4)
		return 0;

	quint32 word = 0;

	if (bigEndian) {
		word = quint32((quint8(data.at(0)) << 24) |
					   (quint8(data.at(1)) << 16) |
					   (quint8(data.at(2)) <<  8) |
					   (quint8(data.at(3)) <<  0));
	} else {
		word = quint32((quint8(data.at(0)) <<  0) |
					   (quint8(data.at(1)) <<  8) |
					   (quint8(data.at(2)) << 16) |
					   (quint8(data.at(3)) << 24));

	}
	return word;
}

static float toFloat(const QString &data, bool bigEndian)
{
	const QByteArray ba = QByteArray::fromHex(data.toLatin1());
	quint32 word = toUint(ba, bigEndian);

	const float *f = reinterpret_cast<const float *>(&word);

	return *f;
}

static QString toHex(quint32 value, bool bigEndian)
{
	QByteArray ba;
	if (bigEndian) {
		ba.append(char(value >> 24));
		ba.append(char(value >> 16));
		ba.append(char(value >>  8));
		ba.append(char(value >>  0));
	} else {
		ba.append(char(value >>  0));
		ba.append(char(value >>  8));
		ba.append(char(value >> 16));
		ba.append(char(value >> 24));
	}
	return ba.toHex().toUpper();
}

static QString toHex(float value, bool bigEndian)
{
	const quint32 *i = reinterpret_cast<const quint32 *>(&value);

	return toHex(*i, bigEndian);
}

void MainWindow::on_hexLineEdit_textEdited()
{
	const bool bigEndian = ui->bigEndian->isChecked();

	float f = toFloat(ui->hexLineEdit->text(), bigEndian);
	ui->floatLineEdit->setText(QString::number(double(f)));
}

void MainWindow::on_floatLineEdit_textEdited()
{
	const bool bigEndian = ui->bigEndian->isChecked();
	const float f = ui->floatLineEdit->text().toFloat();

	ui->hexLineEdit->setText(toHex(f, bigEndian));
}

void MainWindow::on_bigEndian_toggled()
{
	on_floatLineEdit_textEdited();
}
