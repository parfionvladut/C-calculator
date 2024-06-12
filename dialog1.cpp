#include "dialog1.h"
#include "ui_dialog1.h"
#include "QRegularExpressionValidator"
#include <QRegularExpression>
#include <QDebug>
#include <vector>
#include <numeric>

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
std::vector<double>  memory;

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
    ui->display->setText(QString::number(calcVal));
    QPushButton*numButtons[10];
    for(int i= 0; i < 10; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i]= Dialog1::findChild<QPushButton *>(butName);
        connect(numButtons[i],SIGNAL(released()),this,
                                     SLOT(NumPressed()));
    }
    connect(ui->Adition,SIGNAL(released()),this,
                                 SLOT(MathButtonPressed()));
    connect(ui->Subtract,SIGNAL(released()),this,
                                 SLOT(MathButtonPressed()));
    connect(ui->Division,SIGNAL(released()),this,
                                 SLOT(MathButtonPressed()));
    connect(ui->Multiply,SIGNAL(released()),this,
                                 SLOT(MathButtonPressed()));
    connect(ui->Result,SIGNAL(released()),this,
                                 SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign,SIGNAL(released()),this,
                                 SLOT(ChangeNumberSign()));
    connect(ui->ChangeSign,SIGNAL(released()),this,
                                 SLOT(ClearButtonPressed()));
}

Dialog1::~Dialog1()
{
    delete ui;
}

void Dialog1::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butval = button->text();
    QString displayVal = ui->display->text();
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        ui->display->setText(butval);
    }else{
        QString newVal = displayVal + butval;
        double dblNewVal = newVal.toDouble();
        ui->display->setText(QString::number(dblNewVal,'g',16));
    }
}
void Dialog1::MathButtonPressed(){
     divTrigger = false;
     multTrigger = false;
     addTrigger = false;
     subTrigger = false;

    QString displayVal = ui->display->text();
    calcVal = displayVal.toDouble();

    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal,"/",Qt::CaseInsensitive)==0){
        divTrigger = true;
    }else if(QString::compare(butVal,"*",Qt::CaseInsensitive)==0){
        multTrigger= true;
    }else if(QString::compare(butVal,"+",Qt::CaseInsensitive)==0){
        addTrigger= true;
    }else {
        subTrigger= true;
    }

    ui->display->setText("");
}
void Dialog1::EqualButtonPressed(){

    double solution = 0.0;

    QString displayVal = ui->display->text();
    double dblDisplayVal = displayVal.toDouble();

    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        }else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        }else if(multTrigger){
            solution = calcVal * dblDisplayVal;
        }else{
            solution = calcVal / dblDisplayVal;
        }
    }
    ui->display->setText(QString::number(solution));
}
void Dialog1::ChangeNumberSign(){
    QString displayVal = ui->display->text();
    QRegularExpression reg(QRegularExpression::anchoredPattern("[-]?[0-9.]*"));
    QRegularExpressionMatch match = reg.match(displayVal);
    if(match.hasMatch()){
        double dblDisplayVal= displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->display->setText(QString::number(dblDisplayValSign));
    }
}

void Dialog1::on_MemAdd_pressed()
{
    memory.push_back(calcVal);
}
void Dialog1::on_MemClear_pressed()
{
    memory.push_back(-calcVal);
}

void Dialog1::on_MemGet_pressed()
{
    double solution = 0.0;
    solution = std::accumulate(memory.begin(), memory.end(),0);
    ui->display->setText(QString::number(solution));
}

void Dialog1::on_Clear_clicked()
{
    calcVal=0.0;
     ui->display->setText("0.0");
}






