/*
 * *******************************************************************
 * This file is part of the Paper Blossoms application
 * (https://github.com/dashnine/PaperBlossoms).
 * Copyright (c) 2019 Kyle Hankins (dashnine)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * The Legend of the Five Rings Roleplaying Game is the creation
 * and property of Fantasy Flight Games.
 * *******************************************************************
 */

#include "newcharwizardpage4.h"
#include "ui_newcharwizardpage4.h"
#include "QMessageBox"

NewCharWizardPage4::NewCharWizardPage4(DataAccessLayer *dal, QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::NewCharWizardPage4)
{
    ui->setupUi(this);
    this->dal = dal;
    this->setTitle("Part 4: Strengths and Weaknesses");

    ui->nc4_q9_desc_label->setVisible(false);
    ui->nc4_q10_desc_label->setVisible(false);
    ui->nc4_q11_desc_label->setVisible(false);
    ui->nc4_q12_desc_label->setVisible(false);
    ui->nc4_q13_desc_label->setVisible(false);

    ui->nc4_q13_adv_comboBox->setVisible(false);
    ui->nc4_q13_disaadv_comboBox->setVisible(false);
    ui->nc4_q13_skill_comboBox->setVisible(false);

    registerField("q13DisadvChecked", ui->nc4_q13_disadv_radioButton);
    registerField("q13AdvChecked", ui->nc4_q13_adv_radioButton);
    registerField("q13skill", ui->nc4_q13_skill_comboBox, "currentText");
    registerField("q13Advantage",ui->nc4_q13_adv_comboBox, "currentText");
    registerField("q13Disadvantage",ui->nc4_q13_disaadv_comboBox, "currentText");


    registerField("distinction",    ui->nc4_q9_advdisadv_comboBox,  "currentText");
    registerField("adversity",      ui->nc4_q10_advdisadv_comboBox, "currentText");
    registerField("passion",        ui->nc4_q11_advdisadv_comboBox, "currentText");
    registerField("anxiety",        ui->nc4_q12_advdisadv_comboBox, "currentText");


    registerField("q9Text", ui->nc4_q9_lineEdit);
    registerField("q10Text", ui->nc4_q10_lineEdit);
    registerField("q11Text", ui->nc4_q11_lineEdit);
    registerField("q12Text", ui->nc4_q12_lineEdit);
    registerField("q13Text", ui->nc4_q13_lineEdit);

}

NewCharWizardPage4::~NewCharWizardPage4()
{
    delete ui;
}

bool NewCharWizardPage4::validatePage(){

    if(!ui->nc4_q13_adv_radioButton->isChecked() && !ui->nc4_q13_disadv_radioButton->isChecked()){
        QMessageBox msg;
        msg.setText("Error: choose an option for Question 13.");
        msg.exec();
        return false;
    }
    return true;
}

void NewCharWizardPage4::initializePage(){
    ui->nc4_q9_advdisadv_comboBox->clear();
    ui->nc4_q10_advdisadv_comboBox->clear();
    ui->nc4_q11_advdisadv_comboBox->clear();
    ui->nc4_q12_advdisadv_comboBox->clear();
    ui->nc4_q13_adv_comboBox->clear();
    ui->nc4_q13_disaadv_comboBox->clear();
    ui->nc4_q13_skill_comboBox->clear();
    ui->nc4_q9_advdisadv_comboBox->addItems(dal->qsl_getadvdisadv("Distinctions"));
    ui->nc4_q10_advdisadv_comboBox->addItems(dal->qsl_getadvdisadv("Adversities"));
    ui->nc4_q11_advdisadv_comboBox->addItems(dal->qsl_getadvdisadv("Passions"));
    ui->nc4_q12_advdisadv_comboBox->addItems(dal->qsl_getadvdisadv("Anxieties"));
    ui->nc4_q13_adv_comboBox->addItems(dal->qsl_getadv());
    ui->nc4_q13_disaadv_comboBox->addItems(dal->qsl_getdisadv());
    ui->nc4_q13_skill_comboBox->addItems(dal->qsl_getskills());
}

void NewCharWizardPage4::on_nc4_q13_adv_radioButton_toggled(bool checked)
{
    ui->nc4_q13_adv_comboBox->setVisible(checked);
    ui->nc4_q13_disaadv_comboBox->setVisible(!checked);
    ui->nc4_q13_skill_comboBox->setVisible(!checked);
}

void NewCharWizardPage4::on_nc4_q13_disadv_radioButton_toggled(bool checked)
{
    ui->nc4_q13_adv_comboBox->setVisible(!checked);
    ui->nc4_q13_disaadv_comboBox->setVisible(checked);
    ui->nc4_q13_skill_comboBox->setVisible(checked);
}
