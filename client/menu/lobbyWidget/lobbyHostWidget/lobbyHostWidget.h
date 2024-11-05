#ifndef LOBBYHOSTWIDGET_H
#define LOBBYHOSTWIDGET_H

#include <QWidget>

#include "../playerWidget/playerWidget.h"

struct LobbyHostHandler {
    std::function<void()> onClickStart;
    std::function<void()> onClickCancel;
};

namespace Ui {
class LobbyHostWidget;
}

class LobbyHostWidget: public QWidget {
    Q_OBJECT

private:
    Ui::LobbyHostWidget* ui;         // cppcheck-suppress unusedStructMember
    const LobbyHostHandler handler;  // cppcheck-suppress unusedStructMember

    int numberOfPlayers = 0;

public:
    explicit LobbyHostWidget(const LobbyHostHandler& handler, QWidget* parent = nullptr);

    void updateIdDisplayedInLobby(int id);

    void addPlayerToLobby();

    void removePlayerFromLobby();

    ~LobbyHostWidget();

private:
    void onClickStart();

    void onClickCancel();
};

#endif
