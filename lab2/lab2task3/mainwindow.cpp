#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mStack.h"
#include <iostream>
#include <string>
#include <QMessageBox>
using namespace std;
double a, b, c, d, e;
string pol;
bool delim (char c) {
    return c == ' ';
}

bool is_op (char c) {
    return c=='+' || c=='-' || c=='*' || c=='/';
}

int priority (char op) {
    return
        op == '+' || op == '-' ? 1 :
        op == '*' || op == '/' ? 2 :
        -1;
}

void process_op (mStack<double> & st, char op) {
    double r = st.top();  st.pop();
    double l = st.top();  st.pop();
    switch (op) {
        case '+':  st.push (l + r);  break;
        case '-':  st.push (l - r);  break;
        case '*':  st.push (l * r);  break;
        case '/':  st.push (l / r);  break;
    }
}
double get_variable_val(string s){
    if (s == "a"){
        return a;
    }
    if (s == "b"){
        return b;
    }
    if (s == "c"){
        return c;
    }
    if (s == "d"){
        return d;
    }
    if (s == "e"){
        return e;
    }
}
double calc (string & s) {
    mStack<double> st;
    mStack<char> op;
    for (size_t i=0; i<s.length(); ++i)
        if (!delim (s[i]))
            if (s[i] == '('){
                op.push ('(');
            }
            else if (s[i] == ')') {
                while (op.top() != '(')
                    process_op (st, op.top()),  op.pop();
                op.pop();
            }
            else if (is_op (s[i])) {
                char curop = s[i];
                while (!op.empty() && priority(op.top()) >= priority(s[i]))
                    process_op (st, op.top()),  op.pop();
                op.push (curop);
            }
            else {
                string operand;
                while (i < s.length() && isalnum (s[i]))
                    operand += s[i++];
                --i;
                if (isdigit (operand[0])){
                    st.push (atoi (operand.c_str()));
                }
                else{
                    st.push (get_variable_val (operand));
                }
            }
    while (!op.empty())
        process_op (st, op.top()),  op.pop();
    return st.top();
}
bool is_dNum(char c){
    if (c == '.' || c == '-'){
        return 1;
    }
    if (c < '0' || c > '9'){
        return 0;
    }
    return 1;
}
bool is_ur(string s){
    for (int i = 0; i < int(s.size()); i++){
        if (s[i] == 'a' || s[i] == 'b' || s[i] == 'c' || s[i] == 'd' || s[i] == 'e' || s[i] == '(' || s[i] == ')'
                || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'){
            continue;
        }
        return 0;
    }
    return 1;
}
bool is_dNum(string s){
    if (s.size() == 1 && s[0] == '.'){
        return 0;
    }
    for (int i = 0; i < int(s.size()); i++){
        if (!is_dNum(s[i])){
            return 0;
        }
    }
    int kol = 0;
    for (int i = 0; i < int(s.size()); i++){
        if (s[i] == '-'){
            if (i == 0){
                continue;
            }
            else{
                return 0;
            }
        }
        if (s[i] == '.'){
            kol++;
        }
    }
    if (kol > 1){
        return 0;
    }
    return 1;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    a = ui->textEdit_2->toPlainText().toDouble();
    b = ui->textEdit_7->toPlainText().toDouble();
    c = ui->textEdit_3->toPlainText().toDouble();
    d = ui->textEdit_4->toPlainText().toDouble();
    e = ui->textEdit_5->toPlainText().toDouble();
    string str = ui->textEdit->toPlainText().toStdString();
    string temp;
    mStack < string > st1;
    mStack < double > stA, stB, stC, stD, stE;
    for (int i = 0; i < int(str.size()); i++){
        if (str[i] == '\n'){
            if (!is_ur(temp)){
                QMessageBox::information(this, "info", "invalid input");
                return;
            }
            st1.push(temp);
            temp.clear();
            continue;
        }
        temp += str[i];
    }
    if (temp.size() != 0 && temp[0] != ' '){
        if (!is_ur(temp)){
            QMessageBox::information(this, "info", "invalid input");
            return;
        }
        st1.push(temp);
        temp.clear();
    }
    str = ui->textEdit_2->toPlainText().toStdString();
    for (int i = 0; i < int(str.size()); i++){
        if (str[i] == '\n'){
            if (!is_dNum(temp)){
                QMessageBox::information(this, "info", "invalid input");
                return;
            }
            stA.push(stod(temp));//temp to double
            temp.clear();
            continue;
        }
        temp += str[i];
    }
    if (temp.size() != 0 && temp[0] != ' '){
        if (!is_dNum(temp)){
            QMessageBox::information(this, "info", "invalid input");
            return;
        }
        stA.push(stod(temp));
        temp.clear();
    }
    str = ui->textEdit_7->toPlainText().toStdString();
    for (int i = 0; i < int(str.size()); i++){
        if (str[i] == '\n'){
            if (!is_dNum(temp)){
                QMessageBox::information(this, "info", "invalid input");
                return;
            }
            stB.push(stod(temp));//temp to double
            temp.clear();
            continue;
        }
        temp += str[i];
    }
    if (temp.size() != 0 && temp[0] != ' '){
        if (!is_dNum(temp)){
            QMessageBox::information(this, "info", "invalid input");
            return;
        }
        stB.push(stod(temp));
        temp.clear();
    }
    str = ui->textEdit_3->toPlainText().toStdString();
    for (int i = 0; i < int(str.size()); i++){
        if (str[i] == '\n'){
            if (!is_dNum(temp)){
                QMessageBox::information(this, "info", "invalid input");
                return;
            }
            stC.push(stod(temp));//temp to double
            temp.clear();
            continue;
        }
        temp += str[i];
    }
    if (temp.size() != 0 && temp[0] != ' '){
        if (!is_dNum(temp)){
            QMessageBox::information(this, "info", "invalid input");
            return;
        }
        stC.push(stod(temp));
        temp.clear();
    }
    str = ui->textEdit_4->toPlainText().toStdString();
    for (int i = 0; i < int(str.size()); i++){
        if (str[i] == '\n'){
            if (!is_dNum(temp)){
                QMessageBox::information(this, "info", "invalid input");
                return;
            }
            stD.push(stod(temp));//temp to double
            temp.clear();
            continue;
        }
        temp += str[i];
    }
    if (temp.size() != 0 && temp[0] != ' '){
        if (!is_dNum(temp)){
            QMessageBox::information(this, "info", "invalid input");
            return;
        }
        stD.push(stod(temp));
        temp.clear();
    }
    str = ui->textEdit_5->toPlainText().toStdString();
    for (int i = 0; i < int(str.size()); i++){
        if (str[i] == '\n'){
            if (!is_dNum(temp)){
                QMessageBox::information(this, "info", "invalid input");
                return;
            }
            stE.push(stod(temp));//temp to double
            temp.clear();
            continue;
        }
        temp += str[i];
    }
    if (temp.size() != 0 && temp[0] != ' '){
        if (!is_dNum(temp)){
            QMessageBox::information(this, "info", "invalid input");
            return;
        }
        stE.push(stod(temp));
        temp.clear();
    }
    if (stA.Size() != stB.Size() || stA.Size() != stC.Size() || stA.Size() != stD.Size() || stA.Size() != stE.Size()){
        QMessageBox::information(this, "info", "invalid input");
        return;
    }
    QString txt;
    while (!st1.empty()){
        string s = st1.top();
        st1.pop();
        a = stA.top();
        b = stB.top();
        c = stC.top();
        d = stD.top();
        e = stE.top();
        stA.pop();
        stB.pop();
        stC.pop();
        stD.pop();
        stE.pop();
        pol.clear();
        double result = calc(s);
        txt = QString::number(result) + '\n' + txt;
    }
    ui->textEdit_6->setText(txt);
}

