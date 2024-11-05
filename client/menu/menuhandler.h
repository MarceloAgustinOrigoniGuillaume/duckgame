#ifndef LOBBY_MENU_MANAGER_H
#define LOBBY_MENU_MANAGER_H

#include <string>

#include "client/core/lobby_client_sender.h"
#include "client/core/lobby_connector.h"
#include "client/core/lobby_listener.h"
#include "common/dtos.h"
#include "common/queue.h"

#include "menuAction.h"

class MenuHandler: public LobbyListener {
private:
    LobbyConnector& connector;  // cppcheck-suppress unusedStructMember
    LobbyClientSender* sender;  // cppcheck-suppress unusedStructMember

    Queue<MenuAction> queueToMenu = Queue<MenuAction>(20);  // cppcheck-suppress unusedStructMember

public:
    explicit MenuHandler(LobbyConnector& _connector);

    void onSetHostnamePort(const std::string& hostaname, const std::string& port);

    void onCreateSoloLobby();

    void onCreateDuoLobby();

    void onJoinSoloLobby(int lobbyId);

    void onJoinDuoLobby(int lobbyId);

    void onStartLobby(const std::string& map);

    void onCancelLobby();

    ~MenuHandler();

    // Acciones en el menu a partir de las notificaciones
    void setLobbyId(int lobbyId);
    void addSoloToLobby();
    void addDuoToLobby();
    void removePlayerFromLobby();

    // Para recibir notificaciones de la lobby... son directos.
    void startedLobby() override;
    void canceledLobby(const char* msg) override;
    void failedJoin(const char* msg) override;
    void failedCreate(const char* msg) override;


    // Notificacion inicial sobre si se pudo crear/unirse a una lobby.
    void createdLobbyDual(unsigned int id_lobby) override;
    void createdLobbySolo(unsigned int id_lobby) override;

    void joinedLobbyDual(const GameContext& context) override;
    void joinedLobbySolo(const GameContext& context) override;

    void playerJoinedLobby(int id) override;
    void playerLeftLobby(int id) override;

    // void notifyInfo(GameContext& context, const lobby_info& info) override;

private:
    bool tryPopActionToMenu(MenuAction& actionToMenu);
    friend class Menu;
};

#endif
