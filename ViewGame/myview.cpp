

#include "myview.h"


MyView::MyView( QWidget *pwgt) : QWidget (pwgt)
{
    p_serverConnection = new QLabel("Связь с сервером не установлена");
    p_fieldServersIp = new QLineEdit("localhost");
    p_buttonConnect = new QPushButton("&connect");

    p_labelNamePlayers = new QLabel("Ваш nickname:");
    p_editNamePlayers = new QLineEdit;
    p_buttonNamePlayer = new QPushButton("&ok");

    p_listPlayers = new QComboBox;
    p_gameState = new QLabel("Никто не подключен");

    p_textInfo = new QLabel;

    //setup layout
    QVBoxLayout* p_VBox = new QVBoxLayout;

    p_VBox->addWidget(p_serverConnection);
    QHBoxLayout* p_HBox = new QHBoxLayout;
    p_HBox->addWidget(p_fieldServersIp);
    p_HBox->addWidget(p_buttonConnect);
    p_VBox->addLayout(p_HBox);

    p_VBox->addWidget(p_labelNamePlayers);
    QHBoxLayout* p_HBox2 = new QHBoxLayout;
    p_HBox2->addWidget(p_editNamePlayers);
    p_HBox2->addWidget(p_buttonNamePlayer);
    p_VBox->addLayout(p_HBox2);

    p_VBox->addWidget(p_listPlayers);
    p_VBox->addWidget(p_gameState);

    p_brc = new ButtonReClick(-1,-1);
    p_arr = new char*[currentHight];
    for(qint16 i = 0; i < currentHight; i++){
        p_arr[i] = new char[currentWight]{'_'};
    }

    p_playingField =new QGridLayout;
    for(qint16 i = 0; i < currentHight; i++){
        for(qint16 j = 0; j < currentWight; j++){
            //QPushButton *pcmd = new QPushButton("_");
            p_playingField->addWidget(createButton("_", i, j), i, j);
        }
    }

    //p_playingField->itemAtPosition(0,0)->widget();
    p_VBox->addLayout(p_playingField);

    p_VBox->addWidget(p_textInfo);

    setLayout(p_VBox);

}

QPushButton* MyView::createButton(const QString& str, qint16 x, qint16 y){
    QPushButton *pcmd = new QPushButton(str);
    ButtonReClick *pbrc = new ButtonReClick(x, y);
    connect(pcmd, SIGNAL(clicked()),
            pbrc, SLOT(slotClick()));

    connect(pbrc, SIGNAL(butClick(My_XY)),
            p_brc, SLOT(slotClick(My_XY)));

    pcmd->setMinimumSize(40,40);
    //connect(pcmd, SIGNAL(clicked()), SLOT(this_slot));
    return pcmd;
}
bool MyView::setCellField(char v, qint16 x, qint16 y){
    if(x <= currentHight and x > 0 and y <= currentWight and y > 0){
        p_arr[x][y] = v;
        //меняем символ на кнопке в поле gridlayout на переданный
        static_cast<QPushButton*>(p_playingField->itemAtPosition(x,y)->widget())->setText(QString(v));
        return true;
    }
    else{
        return false;
    }
}
void MyView::setField(QVector<QVector<qint16>> v){
    for(qint16 i = 0; i < currentHight; i++){
        for(qint16 j = 0; j < currentWight; j++){
            //qDebug() << "*********__setField__befor";
            try{
                p_arr[i][j] = (v[i][j] >= 0)? ((v[i][j] == 0)? '_' : 'O') :'X';
            }catch(QException ex){
                qDebug() << "_____ERROR_____" << ex.what() << " " << QString::number(i)
                         << " " << QString::number(j);
                break;
            }
        }
    }
    //qDebug() << "*********__setField__after";
    redraw();

}
void MyView::resize(qint16 sizeX, qint16 sizeY){

}
void MyView::redraw(){
    for(qint16 i = 0; i < currentHight; i++){
        for(qint16 j = 0; j < currentWight; j++){
            QPushButton *p;
            p = static_cast<QPushButton*>(p_playingField->itemAtPosition(i,j)->widget());
            p->setText( QString(p_arr[i][j]) );
        }
    }
}



ButtonReClick::ButtonReClick(qint16 x, qint16 y) :
    QObject (),
    x(x) , y(y)
{
}
void ButtonReClick::slotClick(){
    My_XY obj;
    obj.x = x;
    obj.y = y;
    emit butClick(obj);
}
void ButtonReClick::slotClick(My_XY inf){
    emit butClick(inf);
}
