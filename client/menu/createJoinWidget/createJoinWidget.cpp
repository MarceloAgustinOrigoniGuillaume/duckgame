#include "createJoinWidget.h"

#include "ui_createJoinWidget.h"

CreateJoinWidget::CreateJoinWidget(const CreateJoinHandler& handler, QWidget* parent):
        QWidget(parent), ui(new Ui::CreateJoinWidget), handler(handler) {
    ui->setupUi(this);

    QPixmap pixMapTitle;
    if (pixMapTitle.load("./res/ui/duckGameTitle.png")) {
        ui->Title->setPixmap(pixMapTitle.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Title->setAlignment(Qt::AlignCenter);
    }

    connect(ui->createGameButton, &QPushButton::clicked, this,
            &CreateJoinWidget::onClickCreateGame);
    connect(ui->joinGameButton, &QPushButton::clicked, this, &CreateJoinWidget::onClickJoinGame);
    connect(ui->quitButton, &QPushButton::clicked, this, &CreateJoinWidget::onClickQuit);
}

CreateJoinWidget::~CreateJoinWidget() { delete ui; }

void CreateJoinWidget::onClickCreateGame() {
    if (handler.onClickCreateGame)
        handler.onClickCreateGame();
}

void CreateJoinWidget::onClickJoinGame() {
    if (handler.onClickJoinGame)
        handler.onClickJoinGame();
}

void CreateJoinWidget::onClickQuit() {
    if (handler.onClickQuit)
        handler.onClickQuit();
}
