#ifndef MYCLIENTTTT_H
#define MYCLIENTTTT_H
#include<QtWidgets>


class MyClientTTT : public QWidget
{
private:
    QLabel *p_netInfo;
    QLineEdit *p_ipInput;
    QPushButton *p_butConnect;
    QLabel *p_connectInfo;
    QLabel *p_gameInfo;
    QWidget *p_gameWidget[][];
    QGridLayout *p_gridGame;
public:
    MyClientTTT();
};

#endif // MYCLIENTTTT_H
