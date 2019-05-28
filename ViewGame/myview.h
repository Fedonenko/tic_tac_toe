#ifndef MYVIEW_H
#define MYVIEW_H

#define _H_G 3
#define W 3


#include <QtWidgets>

class MyView : public QWidget
{
    Q_OBJECT
private:
    friend class ConnectClass;

    QLabel *p_serverConnection;
    QLineEdit *p_fieldServersIp;
    QPushButton *p_buttonConnect;

    QLabel *p_labelNamePlayers;
    QLineEdit *p_editNamePlayers;
    QPushButton *p_buttonNamePlayer;


    QComboBox *p_listPlayers;
    QLabel *p_gameState;

    QGridLayout *p_playingField;
    QPushButton *createButton(const QString& str);

    QLabel *p_textInfo;
public:
    MyView(QWidget *pwgt = Q_NULLPTR) ;
//public slots:
//    void slotFoo();
};

#endif // MYVIEW_H
