#include <iostream>

#include "common/clientprotocol.h"
#include "common/core/liberror.h"
#include "common/serverprotocol.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "common/core/simplemessenger.h"
#include "tests/core/testermatchdto.h"

using ::testing::InSequence;
using ::testing::ThrowsMessage;

TEST(TestProtocolMocked, SendReceiveStateNoPlayer) {

    SimpleMessenger msgbase(20, true);

    MatchDto state;

    // Los protocols se encargan. De liberar el shared socket.
    ServerProtocol server(msgbase);
    ClientProtocol client(msgbase);

    server.sendstate(state);

    MatchDto state_recv;
    MatchStatsInfo stats_recv;

    // Assert que se mando/se esta jugando.
    ASSERT_TRUE(client.recvstate(stats_recv, state_recv));

    TesterMatchDTO tester(state);
    tester.assertEquals(state);
}


TEST(TestProtocolMocked, SendReceiveState1PlayerMoveLeft) {

    SimpleMessenger msgbase(20, true);

    MatchDto state;
    PlayerDTO player1(3, true, 10, 5,
                      TypeMoveAction::MOVE_LEFT);  // id, is alive, x , y, move_action
    state.players.push_back(player1);


    // Los protocols se encargan. De liberar el shared socket.
    ServerProtocol server(msgbase);
    ClientProtocol client(msgbase);

    server.sendstate(state);


    MatchDto state_recv;
    MatchStatsInfo stats_recv;

    // Assert que se mando/se esta jugando.
    ASSERT_TRUE(client.recvstate(stats_recv, state_recv));


    TesterMatchDTO tester(state_recv);
    tester.assertEquals(state);
}


TEST(TestProtocolMocked, SendReceiveState2PlayerMoveLeftAndAirLeft) {

    SimpleMessenger msgbase(20, true);

    MatchDto state;

    //                      id,alive, x , y, move_action
    state.players.emplace_back(3, true, 10, 5, TypeMoveAction::MOVE_LEFT);
    state.players.emplace_back(2, false, 5, 0, TypeMoveAction::AIR_LEFT);


    // Los protocols se encargan. De liberar el shared socket.
    ServerProtocol server(msgbase);
    ClientProtocol client(msgbase);

    server.sendstate(state);

    MatchDto state_recv;
    MatchStatsInfo stats_recv;

    // Assert que se mando/se esta jugando.
    ASSERT_TRUE(client.recvstate(stats_recv, state_recv));

    TesterMatchDTO tester(state_recv);
    tester.assertEquals(state);
}


TEST(TestProtocolMocked, SendReceiveStatsPausedNoPlayer) {

    SimpleMessenger msgbase(20, true);

    MatchStatsInfo stats;

    stats.state = PAUSADA;
    stats.numronda = 3;

    // Los protocols se encargan. De liberar el shared socket.
    ServerProtocol server(msgbase);
    ClientProtocol client(msgbase);

    server.sendstats(stats);

    MatchDto state_recv;
    MatchStatsInfo stats_recv;

    // Assert que se recibio stats no un state.
    ASSERT_FALSE(client.recvstate(stats_recv, state_recv));

    ASSERT_EQ(stats_recv.state, stats.state);
    ASSERT_EQ(stats_recv.numronda, stats.numronda);
    ASSERT_EQ(stats_recv.champion_player, stats.champion_player);
}


TEST(TestProtocolMocked, SendReceiveStatsPaused2PlayersFirstSecondWinner) {

    SimpleMessenger msgbase(20, true);

    MatchStatsInfo stats;

    stats.state = PAUSADA;
    stats.numronda = 3;

    // id, win count
    stats.stats.emplace_back(1, 4);
    stats.stats.emplace_back(3, 10);
    stats.champion_player = 3;

    // Los protocols se encargan. De liberar el shared socket.
    ServerProtocol server(msgbase);
    ClientProtocol client(msgbase);

    server.sendstats(stats);

    MatchDto state_recv;
    MatchStatsInfo stats_recv;

    // Assert que se recibio stats no un state.
    ASSERT_FALSE(client.recvstate(stats_recv, state_recv));

    ASSERT_EQ(stats_recv.state, stats.state);
    ASSERT_EQ(stats_recv.numronda, stats.numronda);
    ASSERT_EQ(stats_recv.champion_player, stats.champion_player);

    ASSERT_EQ(stats_recv.stats.size(), stats.stats.size());
    int count = stats_recv.stats.size();
    for (int ind = 0; ind < count; ind++) {
        ASSERT_EQ(stats_recv.stats[ind].id, stats.stats[ind].id);
        ASSERT_EQ(stats_recv.stats[ind].wins, stats.stats[ind].wins);
    }
}


TEST(TestProtocolMocked, SendReceiveMatchDtoMultipleTimes) {
    SimpleMessenger msgbase(20, true);

    MatchDto state;

    //                      id,alive, x , y, move_action
    state.players.emplace_back(3, true, 10, 5, TypeMoveAction::MOVE_LEFT);
    PlayerDTO& player2 = state.players.emplace_back(2, false, 5, 0, TypeMoveAction::AIR_LEFT);


    // Los protocols se encargan. De liberar el shared socket.
    ServerProtocol server(msgbase);
    ClientProtocol client(msgbase);

    server.sendstate(state);
    state.objects.emplace_back(5, 5, TypeDynamicObject::BOX);
    state.objects.emplace_back(10, 5, TypeDynamicObject::BOX);
    player2.pos.x = 10;
    player2.pos.y = 15;
    server.sendstate(state);

    MatchDto state_recv;
    MatchStatsInfo stats_recv;

    // Assert que se mando/se esta jugando.
    ASSERT_TRUE(client.recvstate(stats_recv, state_recv));
    ASSERT_TRUE(client.recvstate(stats_recv, state_recv));

    TesterMatchDTO tester(state_recv);
    tester.assertEquals(state);
}

TEST(TestProtocolMocked, SendReceiveStatsPaused2PlayersIntercaladosEnvios) {

    SimpleMessenger msgbase(20, true);

    MatchStatsInfo stats;

    stats.state = PAUSADA;
    stats.numronda = 3;

    // id, win count
    stats.stats.emplace_back(1, 4);
    stats.stats.emplace_back(3, 10);
    stats.champion_player = 3;

    MatchDto state1;
    PlayerDTO player1(3, true, 10, 5,
                      TypeMoveAction::MOVE_LEFT);  // id, is alive, x , y, move_action
    state1.players.push_back(player1);


    MatchDto state2;

    //                      id,alive, x , y, move_action
    state2.players.emplace_back(3, true, 10, 5, TypeMoveAction::MOVE_LEFT);
    state2.players.emplace_back(2, false, 5, 0, TypeMoveAction::AIR_LEFT);

    state2.objects.emplace_back(5, 5, TypeDynamicObject::BOX);
    state2.objects.emplace_back(10, 5, TypeDynamicObject::BOX);


    // Los protocols se encargan. De liberar el shared socket.
    ServerProtocol server(msgbase);
    ClientProtocol client(msgbase);

    server.sendstate(state1);

    MatchDto state_recv;
    MatchStatsInfo stats_recv;

    ASSERT_TRUE(client.recvstate(stats_recv, state_recv));

    TesterMatchDTO tester(state_recv);
    tester.assertEquals(state1);


    server.sendstats(stats);


    // Assert que se recibio stats no un state.
    ASSERT_FALSE(client.recvstate(stats_recv, state_recv));

    ASSERT_EQ(stats_recv.state, stats.state);
    ASSERT_EQ(stats_recv.numronda, stats.numronda);
    ASSERT_EQ(stats_recv.champion_player, stats.champion_player);

    ASSERT_EQ(stats_recv.stats.size(), stats.stats.size());
    int count = stats_recv.stats.size();
    for (int ind = 0; ind < count; ind++) {
        ASSERT_EQ(stats_recv.stats[ind].id, stats.stats[ind].id);
        ASSERT_EQ(stats_recv.stats[ind].wins, stats.stats[ind].wins);
    }


    TesterMatchDTO(state_recv).assertEquals(state1);

    server.sendstate(state2);
    MatchDto state_recv2;

    ASSERT_TRUE(client.recvstate(stats_recv, state_recv2));

    TesterMatchDTO(state_recv2).assertEquals(state2);
}



static void simpleMap(struct MapInfo& info){
    info.size.x = 20;
    info.size.y = 30;
    info.background = "somebk1";
    
    info.textures.reserve(6);
    info.textures.emplace_back("b1");
    info.textures.emplace_back("b2");
    info.textures.emplace_back("b3");
    info.textures.emplace_back("d1");
    info.textures.emplace_back("d2");
    info.textures.emplace_back("d3");
    
    for(int x = 0; x < info.size.x;x++){
        info.blocks.emplace_back(x, 10, x%3); // x, y.
    }

    for(int x = 0; x < info.size.x;x++){
        info.decorations.emplace_back(x, 11, 3+ x%3, 1); // x, y.
    }
    
}

TEST(TestProtocolMocked, SendReceiveReceiveMapInfo) {
    SimpleMessenger msgbase(20, true);

    // Los protocols se encargan. De liberar el shared socket.
    ServerProtocol server(msgbase);
    ClientProtocol client(msgbase);
    
    struct MapInfo info; 
    simpleMap(info);
    
    server.sendmapinfo(info);
    
    
    struct MapData data;
    client.recvmapdata(data);
    
    
    ASSERT_EQ(data.background , info.background) << "background is correct";
    ASSERT_EQ(data.textures.size(), info.textures.size()) << "count textures is the same";
    int countBlocks = info.blocks.size();
    int countDec = info.decorations.size();
    
    ASSERT_EQ(data.objects.size(), countBlocks+countDec);
}




TEST(TestProtocolMocked, SendReceiveReceiveMapInfoAtsendAgain) {
    SimpleMessenger msgbase(20, true);

    // Los protocols se encargan. De liberar el shared socket.
    ServerProtocol server(msgbase);
    ClientProtocol client(msgbase);
    
    struct MapInfo info; 
    simpleMap(info);
    
    server.sendmapinfo(info);
    
    
    struct MapData data;
    client.recvmapdata(data);
    
    info.background = "nuevo bk";
    info.textures[2] = "block new";
    
    info.blocks.erase(info.blocks.begin()+1);
    
    
    server.sendmapinfo(info);
    client.recvmapdata(data);
    
    ASSERT_EQ(data.background , info.background) << "background is not correct";
    ASSERT_EQ(data.textures.size(), info.textures.size()) << "count textures is not the same";
    int countBlocks = info.blocks.size();
    int countDec = info.decorations.size();
    
    ASSERT_EQ(data.objects.size(), countBlocks+countDec) << "count objects received is not the same! the sum of blocks and decorations";
}



TEST(TestProtocolMocked, SendReceiveReceiveMapInfoAtResend) {
    SimpleMessenger msgbase(20, true);

    // Los protocols se encargan. De liberar el shared socket.
    ServerProtocol server(msgbase);
    ClientProtocol client(msgbase);
    
    struct MapInfo info; 
    simpleMap(info);
    
    server.sendmapinfo(info);
    
    
    struct MapData data;
    client.recvmapdata(data);
    
    info.background = "nuevo bk";
    info.textures[2] = "block new";
    
    info.blocks.erase(info.blocks.begin()+1);
    
    
    server.resendmapinfo(info);
    

    MatchDto state_recv;
    MatchStatsInfo stats_recv;

    // Assert que se mando/se esta jugando.
    ASSERT_FALSE(client.recvstate(stats_recv, state_recv));
    
    ASSERT_EQ(stats_recv.state, LOADING);
    
    client.recvmapdata(data);
    
    ASSERT_EQ(data.background , info.background) << "background is not correct";
    ASSERT_EQ(data.textures.size(), info.textures.size()) << "count textures is not the same";
    int countBlocks = info.blocks.size();
    int countDec = info.decorations.size();
    
    ASSERT_EQ(data.objects.size(), countBlocks+countDec) << "count objects received is not the same! the sum of blocks and decorations";
}
