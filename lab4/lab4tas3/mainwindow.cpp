#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#define maxl 10005
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
QString ans;
struct BigInt{
    int a[maxl], len;
    int& operator[](int x){
        return a[x];
    }
    void add(int x){ a[len=x]=1; }
    void div(){
        int re=0;
        for(int i=len;i>=0;i--)
            re=re*10+a[i],a[i]=re/2,re%=2;
        while(len&&!a[len])
            len--;
    }
    void print(){
        for(int i=len;i>=0;i--)
            ans += std::to_string(a[i]).c_str();
    }
}org;
int n;
vector < BigInt > q, zero, one;
bool isone(BigInt tmp, int pos){
    while(pos--){
        tmp.div();
    }
    return tmp[0] & 1;
}
void solve(){
    q.clear();
    q.push_back(org);
    for(int pos = 0; ; pos++){
        zero.clear(),one.clear();
        for(int i = 0;i < (int)q.size(); i++)
            if(!isone(q[i], pos)){
                BigInt tmp = q[i];
                zero.push_back(tmp);
                tmp.add(pos);
                one.push_back(tmp);
                if(!(--n)){
                    tmp.print();
                    return;
                }
            }
        q.clear();
        for(int i = 0; i < (int)zero.size(); i++){
            q.push_back(zero[i]);
        }
        for(int i = 0; i < (int)one.size(); i++){
            q.push_back(one[i]);
        }
    }
}
void MainWindow::on_pushButton_clicked()
{
    n = ui->textEdit->toPlainText().toInt();
    if (n > 10000 || n < 1){
        return;
    }
    solve();
    ui->textEdit_2->setText(ans);
    ans = "";
}

