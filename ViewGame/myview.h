#ifndef MYVIEW_H
#define MYVIEW_H

#define _H_G 3
#define W 3


#include <QtWidgets>

class ButtonReClick;
struct XY;

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
    ButtonReClick *p_brc;

    QLabel *p_textInfo;
private:
    qint16 currentHight = _H_G;
    qint16 currentWight = W;
    char **p_arr;
public:
    MyView(QWidget *pwgt = Q_NULLPTR) ;

public:
    bool setCellField(char v, qint16 x, qint16 y);
    void setField(QVector<QVector<qint16>> v);
    void resize(qint16 sizeX,qint16 sizeY);
    void redraw();
private:
    QPushButton *createButton(const QString& str, qint16 x, qint16 y);
//public slots:
//    void slotFoo();
};
struct My_XY{
    qint16 x;
    qint16 y;
};

class ButtonReClick : public QObject
{
    Q_OBJECT
private:
    qint16 x;
    qint16 y;
public:
    ButtonReClick(qint16, qint16);

signals:
    void butClick(My_XY);
public slots:
    void slotClick();
    void slotClick(My_XY);

};

#endif // MYVIEW_H
