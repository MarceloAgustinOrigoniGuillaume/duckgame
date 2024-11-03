#include <iostream>

#include "./testerclient.h"
#include "common/core/liberror.h"
#include "common/dtos.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "server/lobbycontainer.h"

using ::testing::InSequence;
using ::testing::ThrowsMessage;

class ServerIntegrationTest: public ::testing::Test {
protected:
    Socket sktserver;
    LobbyContainer lobbies;

    inline ServerIntegrationTest(): sktserver("2048"), lobbies() {}

    Socket openClient() { return Socket(NULL, "2048"); }

    virtual ~ServerIntegrationTest() {
        sktserver.shutdown(2);
        sktserver.close();
    }
};


TEST_F(ServerIntegrationTest, SimpleCreateLobby) {

    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbyDual();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";

    host.startMatch();

    // 2 is count of players.
    host.assertLobbyStarted(2);
}

/*
TEST_F(ServerIntegrationTest, SimpleCreateLobbySingle) {

    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbySingle();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";
    host.startMatch();

    // 1 is count of players. Should not start maybe?
    host.assertLobbyStarted(1);
}


TEST_F(ServerIntegrationTest, SimpleCreateLobbyAndJoin) {
    TesterClient host(openClient(), sktserver, lobbies);

    uint8_t id_lobby = host.createClientLobbySingle();
    ASSERT_EQ(id_lobby, 1) << "ID lobby received by client is 1, since its the first match";


    TesterClient joined1(openClient(), sktserver, lobbies);

    uint8_t first = 0;
    uint8_t second = joined1.assertJoinLobbyDual(id_lobby, 1, &first);

    host.assertLobbyJoinNotif(first);
    host.assertLobbyJoinNotif(second);

    host.startMatch();

    // 1 is count of players. Should not start maybe?
    host.assertLobbyStarted(3);
    joined1.assertLobbyStarted(3);
}

*/
