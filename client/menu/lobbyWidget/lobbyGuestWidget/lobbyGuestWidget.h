#ifndef LOBBYGUESTWIDGET_H
#define LOBBYGUESTWIDGET_H

#include <QWidget>

#include "../playerWidget/playerWidget.h"

struct LobbyGuestHandler {
    std::function<void()> onClickCancel;
};

namespace Ui {
class LobbyGuestWidget;
}

class LobbyGuestWidget: public QWidget {
    Q_OBJECT

private:
    Ui::LobbyGuestWidget* ui;         // cppcheck-suppress unusedStructMember
    const LobbyGuestHandler handler;  // cppcheck-suppress unusedStructMember

    int numberOfPlayers = 0;

public:
    explicit LobbyGuestWidget(const LobbyGuestHandler& handler, QWidget* parent = nullptr);

    void updateIdDisplayedInLobby(int id);

    void addPlayerToLobby();

    void removePlayerFromLobby();

    ~LobbyGuestWidget();

private:
    void onClickCancel();
};

#endif
