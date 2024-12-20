#ifndef SETLOBBBYIDWIDGET_H
#define SETLOBBBYIDWIDGET_H

#include <QWidget>

struct SetLobbyIdHandler {
    std::function<void(int)> onClickJoin;
    std::function<void()> onClickCancel;
};

namespace Ui {
class SetLobbyIdWidget;
}

class SetLobbyIdWidget: public QWidget {
    Q_OBJECT

private:
    Ui::SetLobbyIdWidget* ui;         // cppcheck-suppress unusedStructMember
    const SetLobbyIdHandler handler;  // cppcheck-suppress unusedStructMember

public:
    explicit SetLobbyIdWidget(const SetLobbyIdHandler& handler, QWidget* parent = nullptr);

    ~SetLobbyIdWidget();

private:
    void onClickJoin();

    void onClickCancel();
};

#endif
