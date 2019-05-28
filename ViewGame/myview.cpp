

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

    p_playingField =new QGridLayout;
    for(int i = 0; i < _H_G; i++){
        for(int j = 0; j < W; j++){
            p_playingField->addWidget(createButton("_"), i, j);
        }
    }

    //p_playingField->itemAtPosition(0,0)->widget();
    p_VBox->addLayout(p_playingField);

    p_VBox->addWidget(p_textInfo);

    setLayout(p_VBox);

}

QPushButton* MyView::createButton(const QString& str){
    QPushButton *pcmd = new QPushButton(str);
    pcmd->setMinimumSize(40,40);
    //connect(pcmd, SIGNAL(clicked()), SLOT(this_slot));
    return pcmd;
}
