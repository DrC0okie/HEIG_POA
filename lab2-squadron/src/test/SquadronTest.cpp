#include "gtest/gtest.h"
#include "../utils/ShipList.hpp"
#include "../ship/Tie.hpp"
#include "../ship/TieInterceptor.hpp"
#include "../ship/TieFighter.hpp"
#include "../ship/cargo/CargoShip.hpp"
#include "../ship/cargo/StarDreadnought.hpp"
#include "../ship/cargo/ImperialShuttle.hpp"
#include "../squadron/Squadron.hpp"

/**
 * @test Verifies that the value constructor works with static, dynamic and const squadrons
 */
TEST(SquadronTest, valueConstructor) {
    const auto name = "sq";
    Squadron sq1(name);
    const Squadron sq2(name);
    auto sq3 = new Squadron(name);
    const auto sq4 = new Squadron(name);
    EXPECT_EQ(sq1.getName(), name);
    EXPECT_EQ(sq2.getName(), name);
    EXPECT_EQ(sq3->getName(), name);
    EXPECT_EQ(sq4->getName(), name);

    delete sq3;
    delete sq4;
}

/**
 * @test Verifies that the copy constructor works with static, dynamic and const squadrons
 */
TEST(SquadronTest, CopyConstructor) {
    const auto name = "sq";
    const auto leader1Name = "leader1";
    const auto leader2Name = "leader2";
    Squadron sq1(name);
    const Squadron sq2(name);
    auto sq3 = new Squadron(name);
    const Squadron* sq4 = new Squadron(name);

    Ship* leader1 = new TieFighter(leader1Name);
    Ship* leader2 = new TieInterceptor(leader2Name);

    sq1.setLeader(*leader1);
    sq3->setLeader(*leader2);

    Squadron sq1Copy(sq1);
    Squadron sq2Copy(sq2);
    Squadron sq3Copy(*sq3);
    Squadron sq4Copy(*sq4);

    // The copied squadron must have the same name as the original
    EXPECT_EQ(sq1Copy.getName(), name);
    EXPECT_EQ(sq2Copy.getName(), name);
    EXPECT_EQ(sq3Copy.getName(), name);
    EXPECT_EQ(sq4Copy.getName(), name);

    // The copied squadron must have the same leader name as the original
    EXPECT_EQ(sq1Copy.getLeader()->getNickname(), leader1Name);
    EXPECT_EQ(sq3Copy.getLeader()->getNickname(), leader2Name);

    // The copied squadron must have a different address than the original
    EXPECT_NE(&sq1Copy, &sq1);
    EXPECT_NE(&sq2Copy, &sq2);
    EXPECT_NE(&sq3Copy, sq3);
    EXPECT_NE(&sq4Copy, sq4);

    delete sq3;
    delete sq4;
    delete leader1;
    delete leader2;
}

/**
 * @test Verifies that the move constructor works with static, dynamic and const squadrons
 */
TEST(SquadronTest, MoveConstructor) {
    const auto name = "sq";
    Squadron sq1(name);
    const Squadron sq2(name);
    auto* sq3 = new Squadron(name);
    const Squadron* sq4 = new Squadron(name);

    Ship* leader1 = new TieFighter();
    Ship* leader2 = new TieInterceptor();

    // Set leaders (except for sq2 and sq4 that are const)
    sq1.setLeader(*leader1);
    sq3->setLeader(*leader2);

    // Move squadrons
    // The move does not work with the const squadrons. A copy is done instead.
    Squadron newSq1(std::move(sq1));
    Squadron newSq2(std::move(sq2));
    Squadron newSq3(std::move(*sq3));
    Squadron newSq4(std::move(*sq4));

    // Values should be the same as before the move
    EXPECT_EQ(newSq1.getName(), name);
    EXPECT_EQ(newSq2.getName(), name);
    EXPECT_EQ(newSq3.getName(), name);
    EXPECT_EQ(newSq4.getName(), name);

    // Moved non-const leaders must have the same address as in the original squadron
    EXPECT_EQ(newSq1.getLeader(), leader1);
    EXPECT_EQ(newSq3.getLeader(), leader2);

    // The original leaders must be nullptr
    EXPECT_EQ(sq1.getLeader(), nullptr);
    EXPECT_EQ(sq3->getLeader(), nullptr);

    // The original names must be empty for the non-const members
    EXPECT_EQ(sq1.getName(), "");
    EXPECT_EQ(sq3->getName(), "");

    // The original names must be kept for the const members as they have been copied
    EXPECT_EQ(sq2.getName(), name);
    EXPECT_EQ(sq4->getName(), name);

    delete sq3;
    delete sq4;
    delete leader1;
    delete leader2;
}

/**
 * @test Verifies that the copy assignment work with static and dynamic squadrons
 */
TEST(SquadronTest, CopyAssignment) {
    const auto name1 = "sq1";
    const auto name2 = "sq2";
    const auto name3 = "sq3";
    const auto name4 = "sq4";

    const auto leader1Name = "leader1";
    const auto leader2Name = "leader2";
    const auto leader3Name = "leader3";
    const auto leader4Name = "leader4";

    const auto member1Name = "member1";
    const auto member2Name = "member2";
    const auto member3Name = "member3";
    const auto member4Name = "member4";

    Ship* leader1 = new TieFighter(leader1Name);
    Ship* leader2 = new TieInterceptor(leader2Name);
    Ship* leader3 = new StarDreadnought(1.0, leader3Name);
    Ship* leader4 = new ImperialShuttle(2.0, leader4Name);

    Ship* member1 = new ImperialShuttle(2.0, member1Name);
    Ship* member2 = new StarDreadnought(1.0, member2Name);
    Ship* member3 = new TieInterceptor(member3Name);
    Ship* member4 = new TieFighter(member4Name);

    Squadron sq1(name1);
    Squadron sq2(name2);
    auto sq3 = new Squadron(name3);
    auto sq4 = new Squadron(name4);

    // Set leaders and members
    sq1.setLeader(*leader1);
    sq1.addShip(*member1);
    sq2.setLeader(*leader2);
    sq2.addShip(*member2);
    sq3->setLeader(*leader3);
    sq3->addShip(*member3);
    sq4->setLeader(*leader4);
    sq4->addShip(*member4);

    // Assign sq3 to sq1 and sq2 to sq4
    sq1 = *sq3;
    *sq4 = sq2;

    // The assigned squadron must have a new name
    EXPECT_EQ(sq1.getName(), name3);
    EXPECT_EQ(sq4->getName(), name2);

    //The assigned squadron must have a new leader
    EXPECT_EQ(sq1.getLeader(), leader3);
    EXPECT_EQ(sq4->getLeader(), leader2);

    //The assigned squadron must have a new member (deep copy)
    EXPECT_EQ(sq1.get(1), member3);
    EXPECT_EQ(sq1.get(1)->getNickname(), member3Name);
    EXPECT_EQ(sq4->get(1), member2);
    EXPECT_EQ(sq4->get(1)->getNickname(), member2Name);

    //The original squadron must have the same name as before
    EXPECT_EQ(sq3->getName(), name3);
    EXPECT_EQ(sq2.getName(), name2);

    // The original squadron must have the same leader as before (name and address)
    EXPECT_EQ(sq3->getLeader(), leader3);
    EXPECT_EQ(sq2.getLeader(), leader2);
    EXPECT_EQ(sq3->getLeader()->getNickname(), leader3->getNickname());
    EXPECT_EQ(sq2.getLeader()->getNickname(), leader2->getNickname());

    // The original squadron must have the same member as before (name and address)
    EXPECT_EQ(sq3->get(1), member3);
    EXPECT_EQ(sq2.get(1), member2);
    EXPECT_EQ(sq3->get(1)->getNickname(), member3->getNickname());
    EXPECT_EQ(sq2.get(1)->getNickname(), member2->getNickname());

    delete sq3;
    delete sq4;
    delete leader1;
    delete leader2;
    delete leader3;
    delete leader4;
    delete member1;
    delete member2;
    delete member3;
    delete member4;
}

/**
 * @test Verifies that the move assignment work with static and dynamic squadrons
 */
TEST(SquadronTest, moveAssignment) {
    const auto name1 = "sq1";
    const auto name2 = "sq2";
    const auto name3 = "sq3";
    const auto name4 = "sq4";

    const auto leader1Name = "leader1";
    const auto leader2Name = "leader2";
    const auto leader3Name = "leader3";
    const auto leader4Name = "leader4";

    const auto member1Name = "member1";
    const auto member2Name = "member2";
    const auto member3Name = "member3";
    const auto member4Name = "member4";

    Ship* leader1 = new TieFighter(leader1Name);
    Ship* leader2 = new TieInterceptor(leader2Name);
    Ship* leader3 = new StarDreadnought(1.0, leader3Name);
    Ship* leader4 = new ImperialShuttle(2.0, leader4Name);

    Ship* member1 = new ImperialShuttle(2.0, member1Name);
    Ship* member2 = new StarDreadnought(1.0, member2Name);
    Ship* member3 = new TieInterceptor(member3Name);
    Ship* member4 = new TieFighter(member4Name);

    Squadron sq1(name1);
    Squadron sq2(name2);
    auto sq3 = new Squadron(name3);
    auto sq4 = new Squadron(name4);

    // Set leaders and members
    sq1.setLeader(*leader1);
    sq1.addShip(*member1);
    sq2.setLeader(*leader2);
    sq2.addShip(*member2);
    sq3->setLeader(*leader3);
    sq3->addShip(*member3);
    sq4->setLeader(*leader4);
    sq4->addShip(*member4);

    // Assign sq3 to sq1 and sq2 to sq4
    sq1 = std::move(*sq3);
    *sq4 = std::move(sq2);

    // The assigned squadron must have a new name
    EXPECT_EQ(sq1.getName(), name3);
    EXPECT_EQ(sq4->getName(), name2);

    //The assigned squadron must have a new leader
    EXPECT_EQ(sq1.getLeader(), leader3);
    EXPECT_EQ(sq4->getLeader(), leader2);

    //The assigned squadron must have a new member
    EXPECT_EQ(sq1.get(1), member3);
    EXPECT_EQ(sq4->get(1), member2);

    //The original squadron must have no name
    EXPECT_EQ(sq3->getName(), "");
    EXPECT_EQ(sq2.getName(), "");

    // The original squadron must have no leader
    EXPECT_EQ(sq3->getLeader(), nullptr);
    EXPECT_EQ(sq2.getLeader(), nullptr);

    // The original squadron must have no members (throw an exception)
    EXPECT_THROW(sq3->get(0), std::out_of_range);
    EXPECT_THROW(sq2.get(0), std::out_of_range);

    delete sq3;
    delete sq4;
    delete leader1;
    delete leader2;
    delete leader3;
    delete leader4;
    delete member1;
    delete member2;
    delete member3;
    delete member4;
}

/**
 * @test Verifies that the self-assignment has no effect on statically and dynamically allocated squadrons
 */
TEST(SquadronTest, selfAssignment) {
    const auto name1 = "sq1";
    const auto name2 = "sq2";
    const auto leader1Name = "leader1";
    const auto leader2Name = "leader2";
    const auto member1Name = "member1";
    const auto member2Name = "member2";
    Ship* leader1 = new TieFighter(leader1Name);
    Ship* leader2 = new TieInterceptor(leader2Name);
    Ship* member1 = new ImperialShuttle(2.0, member1Name);
    Ship* member2 = new StarDreadnought(1.0, member2Name);

    Squadron sq1(name1);
    auto sq2 = new Squadron(name2);

    // Set leaders and members
    sq1.setLeader(*leader1);
    sq2->setLeader(*leader2);
    sq1.addShip(*member1);
    sq2->addShip(*member2);

    Squadron* sq1Address = &sq1;
    Squadron* sq2Address = sq2;

    sq1 = sq1;
    sq2 = std::move(sq2);

    // Must have the same address
    EXPECT_EQ(&sq1, sq1Address);
    EXPECT_EQ(sq2, sq2Address);

    // Must have the same leader and leader name
    EXPECT_EQ(sq1.getLeader(), leader1);
    EXPECT_EQ(sq2->getLeader(), leader2);
    EXPECT_EQ(sq1.getLeader()->getNickname(), leader1Name);
    EXPECT_EQ(sq2->getLeader()->getNickname(), leader2Name);

    // Must have the same members and member names
    EXPECT_EQ(sq1.get(1), member1);
    EXPECT_EQ(sq2->get(1), member2);
    EXPECT_EQ(sq1.get(1)->getNickname(), member1Name);
    EXPECT_EQ(sq2->get(1)->getNickname(), member2Name);

    delete sq2;
    delete leader1;
    delete leader2;
    delete member1;
    delete member2;
}

/**
 * @test Verifies that addShip in place, really adds a ship to the squadron.
 */
TEST(SquadronTest, addShipInPlace) {
    Squadron squad("squad");

    const auto memberName = "Tie";
    TieFighter tie(memberName);

    // squad must be empty before add
    EXPECT_THROW(squad.get(0), std::out_of_range);
    squad.addShip(tie);

    // Tie Fighter must be in the squad and have the same name
    EXPECT_EQ(dynamic_cast<const TieFighter*>(squad.get(0)), &tie);
    EXPECT_EQ(dynamic_cast<const TieFighter*>(squad.get(0))->getNickname(), memberName);
}

/**
 * @test Verifies that we can chain operations with addShip in place.
 */
TEST(SquadronTest, addShipInPlaceChain) {
    Squadron squad("squad");

    const auto member1Name = "Tie1";
    TieFighter fighter(member1Name);
    const auto member2Name = "SD1";
    StarDreadnought sd(1.0, member2Name);

    squad.addShip(fighter).addShip(sd);

    // Fighter and SD must be in the squad and have the same name
    EXPECT_EQ(dynamic_cast<const TieFighter*>(squad.get(0)), &fighter);
    EXPECT_EQ(dynamic_cast<const StarDreadnought*>(squad.get(1)), &sd);
    EXPECT_EQ(dynamic_cast<const TieFighter*>(squad.get(0))->getNickname(), member1Name);
    EXPECT_EQ(dynamic_cast<const StarDreadnought*>(squad.get(1))->getNickname(), member2Name);
}

/**
 * @test Verifies that addShip that returns a copy, doesn't modify the original const squadron.
 */
TEST(SquadronTest, addShipCopy) {
    const Squadron squad("squad");

    const auto memberName = "Tie";
    TieFighter tie(memberName);

    // squad must be empty before add
    EXPECT_THROW(squad.get(0), std::out_of_range);
    Squadron squad2 = squad.addShip(tie);

    // Tie Fighter must NOT be in the original squad
    EXPECT_THROW(squad.get(0), std::out_of_range);

    // Tie Fighter must be in the copied squad
    EXPECT_EQ(dynamic_cast<const TieFighter*>(squad2.get(0)), &tie);
}

/**
 * @test Verifies that removeShip in place, really removes a ship from the squadron.
 */
TEST(SquadronTest, removeShipInPlace) {
    Squadron squad("squad");

    const auto memberName1 = "Tie";
    TieFighter tie(memberName1);
    const auto memberName2 = "SD";
    StarDreadnought sd(1.0, memberName2);
    squad.addShip(tie);
    squad.addShip(sd);

    // Fighter and SD must be in the squad and have the same name
    EXPECT_EQ(dynamic_cast<const TieFighter*>(squad.get(0)), &tie);
    EXPECT_EQ(dynamic_cast<const TieFighter*>(squad.get(0))->getNickname(), memberName1);
    EXPECT_EQ(dynamic_cast<const StarDreadnought*>(squad.get(1)), &sd);
    EXPECT_EQ(dynamic_cast<const StarDreadnought*>(squad.get(1))->getNickname(), memberName2);

    // Remove the tie member
    Squadron squad2 = squad.removeShip(tie);

    // Original squadron must not be empty, SD is still in there
    EXPECT_EQ(squad.get(0)->getNickname(), memberName2);

    //Same for returned squadron
    EXPECT_EQ(squad2.get(0)->getNickname(), memberName2);

    // Remove SD
    squad.removeShip(sd);

    // Original squadron must be empty
    EXPECT_THROW(squad.get(0), std::out_of_range);

    //Same for returned squadron, as it is a ref to the original one
    EXPECT_THROW(squad.get(0), std::out_of_range);
}

/**
 * @test Verifies that we can remove-chain the ships
 */
TEST(SquadronTest, removeShipInPlaceChain) {
    Squadron squad("squad");

    const auto member1Name = "Tie1";
    TieFighter fighter(member1Name);
    const auto member2Name = "SD1";
    StarDreadnought sd(1.0, member2Name);

    squad.addShip(fighter).addShip(sd);

    //remove in a different order
    squad.removeShip(sd).removeShip(fighter);

    // Squad must be empty
    EXPECT_THROW(squad.get(0), std::out_of_range);
}

/**
 * @test Verifies that removeShip that returns a copy, doesn't modify the original const squadron.
 */
TEST(SquadronTest, removeShipCopy) {
    const Squadron squad("squad");

    const auto memberName = "Tie";
    TieFighter tie(memberName);

    //initialize a const squad
    const Squadron squad2 = squad.addShip(tie);

    Squadron squad3 = squad2.removeShip(tie);

    // Tie Fighter must still be in the second squad
    EXPECT_EQ(squad2.get(0)->getNickname(), memberName);

    // Tie Fighter must NOT be in the copied squad
    EXPECT_THROW(squad3.get(0), std::out_of_range);
}

/**
 * @test Verifies that we can add and chain add ship to squadron in both order
 */
TEST(SquadronTest, addOperators) {
    Squadron squad("squad");

    TieFighter tf("1");
    TieInterceptor ti("2");
    StarDreadnought sd(1.0, "3");
    ImperialShuttle is(2.0, "4");

    // Squad2 should have only tf
    auto squad2 = squad + tf;
    EXPECT_EQ(squad2.get(0)->getNickname(), "1");

    // Squad2 should have only sd
    squad2 = squad + sd;
    EXPECT_EQ(squad2.get(0)->getNickname(), "3");

    // Squad2 should have only ti
    squad2 = ti + squad;
    EXPECT_EQ(squad2.get(0)->getNickname(), "2");

    // Squad2 should have only is
    squad2 = is + squad;
    EXPECT_EQ(squad2.get(0)->getNickname(), "4");

    // Squad2 should have every member (chain)
    squad2 = squad2 + tf + ti + sd + is;
    for (unsigned i = 0; i < 4; i++) {
        EXPECT_NO_THROW(squad2.get(i)->getNickname());
    }
}

/**
 * @test Verifies that we can sub and chain sub ship to squadron
 */
TEST(SquadronTest, subOperator) {
    Squadron squad("squad");

    TieFighter tf("1");
    TieInterceptor ti("2");
    StarDreadnought sd(1.0, "3");
    ImperialShuttle is(2.0, "4");

    // squad2 should have no member (chain)
    Squadron squad2 = squad + tf + ti + sd + is - tf - ti - sd - is;
    EXPECT_THROW(squad2.get(0), std::out_of_range);

    // Re-add members
    squad2 = squad2 + tf + ti + sd + is;

    // squad3 must not have tf
    Squadron squad3 = squad2 - tf;
    EXPECT_EQ(squad3.get(0)->getNickname(), "2");
    EXPECT_EQ(squad3.get(1)->getNickname(), "3");
    EXPECT_EQ(squad3.get(2)->getNickname(), "4");

    // squad3 must not have ti
    squad3 = squad2 - ti;
    EXPECT_EQ(squad3.get(0)->getNickname(), "1");
    EXPECT_EQ(squad3.get(1)->getNickname(), "3");
    EXPECT_EQ(squad3.get(2)->getNickname(), "4");

    // squad3 must not have sd
    squad3 = squad2 - sd;
    EXPECT_EQ(squad3.get(0)->getNickname(), "1");
    EXPECT_EQ(squad3.get(1)->getNickname(), "2");
    EXPECT_EQ(squad3.get(2)->getNickname(), "4");

    // squad3 must not have is
    squad3 = squad2 - is;
    EXPECT_EQ(squad3.get(0)->getNickname(), "1");
    EXPECT_EQ(squad3.get(1)->getNickname(), "2");
    EXPECT_EQ(squad3.get(2)->getNickname(), "3");
}

/**
 * @test Checks that the add assignment operator work as intended
 */
TEST(SquadronTest, addAssignmentOperator) {
    Squadron squad("squad");
    TieFighter tf("1");
    StarDreadnought sd(1.0, "2");

    // squad should have only tf
    squad += tf;
    EXPECT_EQ(squad.get(0)->getNickname(), "1");

    // squad should have tf and sd
    squad += sd;
    EXPECT_EQ(squad.get(0)->getNickname(), "1");
    EXPECT_EQ(squad.get(1)->getNickname(), "2");
}

/**
 * @test Checks that the add assignment operator work as intended
 */
TEST(SquadronTest, subAssignmentOperator) {
    Squadron squad("squad");
    TieFighter tf("1");
    StarDreadnought sd(1.0, "2");

    squad += tf;
    squad += sd;

    // Squad should only have tf
    squad -= sd;
    EXPECT_EQ(squad.get(0)->getNickname(), "1");

    // squad should have no member
    squad -= tf;
    EXPECT_THROW(squad.get(0), std::out_of_range);
}

/**
 * @test Checks that the squadron name is the same as the one given in constructor
 */
TEST(SquadronTest, getName) {
    const auto name = "iLoveTests";
    Squadron squad(name);
    EXPECT_EQ(squad.getName(), name);
}

/**
 * @test Checks that setName effectively changes the squadron name
 */
TEST(SquadronTest, setName) {
    const auto name = "Squad";
    const auto newName = "newSquad";
    Squadron squad(name);
    EXPECT_EQ(squad.getName(), name);

    squad.setName(newName);
    EXPECT_EQ(squad.getName(), newName);
}

/**
 * @test Checks that getLeader effectively get the leader ship of the squadron
 */
TEST(SquadronTest, getLeader) {
    const auto leaderName = "SD";
    StarDreadnought sd(1.0, leaderName);
    Squadron squad("mySquad");
    squad.setLeader(sd);
    EXPECT_EQ(squad.getLeader()->getNickname(), leaderName);
}

/**
 * @test Checks that setLeader effectively sets the leader ship of the squadron
 */
TEST(SquadronTest, setLeader) {
    const auto leader1Name = "Leader1";
    const auto leader2Name = "Leader2";
    const auto member3Name = "Member3";
    Squadron squad("squad");
    StarDreadnought sd(1.0, leader1Name);
    TieFighter tf(leader2Name);

    //Squad must be empty
    EXPECT_THROW(squad.get(0), std::out_of_range);

    // Setting the squad leader when the leader is not a member of the squad must add it to the squad
    squad.setLeader(sd);
    EXPECT_EQ(squad.get(0)->getNickname(), leader1Name);
    EXPECT_EQ(squad.getLeader()->getNickname(), leader1Name);

    // Adding a second leader that is not a member, also adds it to the squad
    squad.setLeader(tf);
    EXPECT_EQ(squad.get(0)->getNickname(), leader1Name);
    EXPECT_EQ(squad.get(1)->getNickname(), leader2Name);
    EXPECT_EQ(squad.getLeader()->getNickname(), leader2Name);

    // Setting the leader if it is already in the squad should not duplicate it in the members.
    ImperialShuttle is(2.0, member3Name);
    squad.addShip(is);
    EXPECT_EQ(squad.get(2)->getNickname(), member3Name);
    squad.setLeader(is);
    EXPECT_EQ(squad.getLeader()->getNickname(), member3Name);
    EXPECT_THROW(squad.get(3), std::out_of_range);
}

/**
 * @test Verifies that revoking the leader do not remove it from the members
 */
TEST(SquadronTest, revokeLeader) {
    const auto leader1Name = "Leader1";
    Squadron squad("squad");
    StarDreadnought sd(1.0, leader1Name);
    squad.setLeader(sd);
    squad.revokeLeader();

    //Squad have no leader
    EXPECT_EQ(squad.getLeader(), nullptr);

    // The old leader must still be part of the squad members
    EXPECT_EQ(squad.get(0)->getNickname(), leader1Name);
}

/**
 * @test Tests that getShip returns a ship if present, or throws if not
 */
TEST(SquadronTest, getShip) {
    const auto memberName = "SD";
    Squadron squad("squad");
    StarDreadnought sd(1.0, memberName);
    squad += sd;

    EXPECT_EQ(squad.get(0)->getNickname(), memberName);
    EXPECT_THROW(squad.get(1), std::out_of_range);

    squad -= sd;
    EXPECT_THROW(squad.get(0), std::out_of_range);
}

/**
 * @test Verifies that the consumption of the squad is the same as the member consumption sum
 */
TEST(SquadronTest, getConsumption) {
    const double distance = 10.0;
    const double speed = 30.0;
    Squadron squad("squad");
    TieFighter tf("1");
    TieInterceptor ti("2");
    StarDreadnought sd(1.0, "3");
    ImperialShuttle is(2.0, "4");

    auto accumulatedConsumption =
            tf.getConsumption(distance, speed) + ti.getConsumption(distance, speed) +
            sd.getConsumption(distance, speed) + is.getConsumption(distance, speed);

    squad = squad + tf + ti + sd + is;

    EXPECT_EQ(squad.getConsumption(distance, speed), accumulatedConsumption);
}

/**
 * @test Checks that a ship can belong to multiple squadrons and removing it from one does not affect the other
 */
TEST(SquadronTest, multipleSquadronMustShareSameShips) {
    const auto memberName = "SD";
    const auto newMemberName = "newName";
    Squadron squad1("squad1"), squad2("squad2");
    StarDreadnought sd(1.0, memberName);
    squad1 += sd;
    squad2 += sd;

    // Changing the ship should have impact on both squadrons
    sd.setNickname(newMemberName);
    EXPECT_EQ(squad1.get(0)->getNickname(), newMemberName);
    EXPECT_EQ(squad2.get(0)->getNickname(), newMemberName);

    // Promoting the member as leader should have impact only this one squadron
    squad1.setLeader(sd);
    EXPECT_EQ(squad1.getLeader()->getNickname(), newMemberName);
    EXPECT_EQ(squad2.getLeader(), nullptr);

    // revoking also must impact only this one squad
    squad1.revokeLeader();
    EXPECT_EQ(squad1.getLeader(), nullptr);
    EXPECT_EQ(squad2.getLeader(), nullptr);

    // Getting and changing name should also change it in both squadrons
    squad1.get(0)->setNickname(memberName);
    EXPECT_EQ(squad1.get(0)->getNickname(), memberName);
    EXPECT_EQ(squad2.get(0)->getNickname(), memberName);
}