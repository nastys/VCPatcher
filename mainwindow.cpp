/*
 * Copyright © 2015 nastys
 *
 * This file is part of VCPatcher.
 * VCPatcher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * VCPatcher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with VCPatcher.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QByteArray"
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_actionEnglish_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_romType_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        ui->start->setText("0x10064C");
        ui->end->setText("0x14065B");
        break;
    case 1:
        ui->start->setText("0x0FCB080");
        ui->end->setText("0x12CB07F");
        break;
    case 2:
        ui->start->setText("0x12CB07F");
        ui->end->setText("0x13CB07F");
    }
}

void MainWindow::on_Inject_clicked()
{
    QFile inemu(ui->PathE->text());
    inemu.open(QIODevice::ReadOnly);
    QFile newrom(ui->PathR->text());
    newrom.open(QIODevice::ReadOnly);
    QByteArray outemu = inemu.readAll();
    QByteArray newromarray = newrom.readAll();
    static int offsetA = ui->start->text().toInt();
    static int offsetB = ui->end->text().toInt();
    for(int i = 0; i < offsetB; i++)
        outemu[i+offsetA] = newromarray[i];
    QString saveas = QFileDialog::getSaveFileName(this);
    QFile outfile(saveas);
    if(saveas!="")
    {
        outfile.open(QIODevice::WriteOnly);
        outfile.write(outemu);
    }
    inemu.close();
    newrom.close();
    outfile.close();
}

void MainWindow::on_actionEnglish_triggered()
{
    ui->menuFile->setTitle("File");
    ui->menuEnglish->setTitle("Language");
    ui->actionOpen->setText("Open...");
    ui->actionOpen_ROM->setText("Open ROM...");
    ui->actionSave->setText("Inject...");
    ui->actionExit->setText("Exit");
    ui->label->setText("Emulator to patch:");
    ui->label_2->setText("New ROM to inject:");
    ui->BrowseE->setText("Browse...");
    ui->BrowseR->setText("Browse...");
    ui->Inject->setText("Inject");
}

void MainWindow::on_actionSpanish_triggered()
{
    ui->menuFile->setTitle("Archivo");
    ui->menuEnglish->setTitle("Idioma");
    ui->actionOpen->setText("Abrir...");
    ui->actionOpen_ROM->setText("Abrir ROM...");
    ui->actionSave->setText("Inyectar...");
    ui->actionExit->setText("Salir");
    ui->label->setText("Emulador para parchar:");
    ui->label_2->setText("Nueva ROM para inyectar:");
    ui->BrowseE->setText("Examinar...");
    ui->BrowseR->setText("Examinar...");
    ui->Inject->setText("Inyectar");
}

void MainWindow::on_actionItalian_triggered()
{
    ui->menuFile->setTitle("File");
    ui->menuEnglish->setTitle("Lingua");
    ui->actionOpen->setText("Apri...");
    ui->actionOpen_ROM->setText("Apri ROM...");
    ui->actionSave->setText("Inietta...");
    ui->actionExit->setText("Esci...");
    ui->label->setText("Emulatore da patchare:");
    ui->label_2->setText("Nuova ROM da iniettare:");
    ui->BrowseE->setText("Sfoglia...");
    ui->BrowseR->setText("Sfoglia...");
    ui->Inject->setText("Inietta");
}

void MainWindow::on_BrowseE_clicked()
{
    ui->PathE->setText(QFileDialog::getOpenFileName(this, "", "", "RPX (*.rpx)"));
}

void MainWindow::on_BrowseR_clicked()
{
    ui->PathR->setText(QFileDialog::getOpenFileName(this));
}

void MainWindow::on_actionOpen_triggered()
{
    on_BrowseE_clicked();
}

void MainWindow::on_actionOpen_ROM_triggered()
{
    on_BrowseR_clicked();
}

void MainWindow::on_actionSave_triggered()
{
    on_Inject_clicked();
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}
