#include "gtest/gtest.h"
#include "../utils/ShipList.hpp"
#include "../ship/Tie.hpp"
#include "../ship/TieInterceptor.hpp"
#include "../ship/TieFighter.hpp"
#include "../ship/cargo/CargoShip.hpp"
#include "../ship/cargo/StarDreadnought.hpp"
#include "../ship/cargo/ImperialShuttle.hpp"

/**
 * @test Checks that every Ship derived class instance receives a unique sequential ID upon construction.
 * @note This test must be executed first, otherwise other tests will increment ship Ids
 */
TEST(ShipTest, uniqueIdIncrementMustWork) {

    TieFighter* tf;
    for (unsigned i = 0; i < 10; i++) {
        tf = new TieFighter();
        if (i == 9) {
            EXPECT_EQ(tf->getId(), 10);
        }
        delete tf;
    }

    TieInterceptor* ti;
    for (unsigned i = 0; i < 8; i++) {
        ti = new TieInterceptor();
        if (i == 7) {
            EXPECT_EQ(ti->getId(), 8);
        }
        delete ti;
    }

    StarDreadnought* sd;
    for (unsigned i = 0; i < 19; i++) {
        sd = new StarDreadnought();
        if (i == 18) {
            EXPECT_EQ(sd->getId(), 19);
        }
        delete sd;
    }

    ImperialShuttle* is;
    for (unsigned i = 0; i < 3; i++) {
        is = new ImperialShuttle();
        if (i == 2) {
            EXPECT_EQ(is->getId(), 3);
        }
        delete is;
    }
}

/**
 * @test Checks that the Ship constructor correctly assigns a nickname.
 */
TEST(ShipTest, NicknameAssignmentMustWork) {
    Ship* ship1 = new TieFighter("ship1");
    Ship* ship2 = new TieInterceptor("ship2");
    Ship* ship3 = new StarDreadnought(1.0, "ship3");
    Ship* ship4 = new ImperialShuttle(2.0, "ship4");

    EXPECT_EQ(ship1->getNickname(), "ship1");
    EXPECT_EQ(ship2->getNickname(), "ship2");
    EXPECT_EQ(ship3->getNickname(), "ship3");
    EXPECT_EQ(ship4->getNickname(), "ship4");
}

/**
 * @test Checks setNickname method changes the nickname appropriately.
 */
TEST(ShipTest, setNicknameMustChangeName) {
    Ship* ship1 = new TieFighter("ship1");
    ship1->setNickname("Ship2");
    EXPECT_EQ(ship1->getNickname(), "Ship2");
    delete ship1;
}

/**
 * @test Checks getConsumption with valid input parameters returns the expected fuel consumption.
 * @note the consumption results must be calculated by hand for the validation
 */
TEST(ShipTest, getConsumptionMustReturnCorrectValue) {
    //Tie Fighter : speed = 100 MGLT, weight = 6 tons. Expected consumption near 0.759835
    Ship* ship = new TieFighter("ship1");
    EXPECT_NEAR(ship->getConsumption(1.0, ship->getMaxSpeed()), 0.75983, 1e-5);
    delete ship;

    //Tie Interceptor speed = 110 MGLT, weight = 5 tons. Expected consumption near 0.705306
    ship = new TieInterceptor("ship2");
    EXPECT_NEAR(ship->getConsumption(1.0, ship->getMaxSpeed()), 0.70530, 1e-5);
    delete ship;

    //Star Dreadnought speed = 40, weight = 9e9 + 10 tons. Expected consumption near 3618.091242
    ship = new StarDreadnought(10.0, "ship3");
    EXPECT_NEAR(ship->getConsumption(1.0, ship->getMaxSpeed()), 3618.09124, 1e-5);
    delete ship;

    //Imperial Shuttle speed = 54, weight = 440 tons. Expected consumption near 5.009481
    ship = new ImperialShuttle(80, "ship4");
    EXPECT_NEAR(ship->getConsumption(1.0, ship->getMaxSpeed()), 5.00948, 1e-5);
    delete ship;
}

/**
 * @test Checks getConsumption throws an exception for negative distances or if the speed exceeds the ship's maximum speed.
 */
TEST(ShipTest, getConsumptionMustThrowWithInvalidInputs) {
    Ship* ship = new TieFighter("ship1");
    EXPECT_THROW(ship->getConsumption(-1, 10), std::invalid_argument);
    EXPECT_THROW(ship->getConsumption(1, 120), std::invalid_argument);
    delete ship;
}

/**
 * @test Checks that getModel method returns the correct value
 */
TEST(ShipTest, getModelMustBeValid) {
    //Tie Fighter
    Ship* ship = new TieFighter("ship1");
    EXPECT_EQ(ship->getModel(), "TIE/LN");
    delete ship;

    //Tie Interceptor
    ship = new TieInterceptor("ship2");
    EXPECT_EQ(ship->getModel(), "TIE/IN");
    delete ship;

    //Star Dreadnought
    ship = new StarDreadnought(10.0, "ship3");
    EXPECT_EQ(ship->getModel(), "Super-class Star Destroyer");
    delete ship;

    //Imperial Shuttle
    ship = new ImperialShuttle(80, "ship4");
    EXPECT_EQ(ship->getModel(), "Lambda-class shuttle");
    delete ship;
}

/**
 * @test Checks that getWeight returns valid value
 */
TEST(ShipTest, getWeightMustReturnValidValue) {
    //Tie Fighter
    Ship* ship = new TieFighter("ship1");
    EXPECT_EQ(ship->getWeight(), 6.0);
    delete ship;

    //Tie Interceptor
    ship = new TieInterceptor("ship2");
    EXPECT_EQ(ship->getWeight(), 5.0);
    delete ship;

    //Star Dreadnought
    ship = new StarDreadnought(10.0, "ship3");
    EXPECT_EQ(ship->getWeight(), 9e9 + 10.0);
    delete ship;

    //Imperial Shuttle
    ship = new ImperialShuttle(80, "ship4");
    EXPECT_EQ(ship->getWeight(), 360 + 80.0);
    delete ship;
}

/**
 * @test Checks that getMaxSpeed returns valid value
 */
TEST(ShipTest, getSpeedMustReturnValidValue) {
    //Tie Fighter
    Ship* ship = new TieFighter("ship1");
    EXPECT_EQ(ship->getMaxSpeed(), 100.0);
    delete ship;

    //Tie Interceptor
    ship = new TieInterceptor("ship2");
    EXPECT_EQ(ship->getMaxSpeed(), 110.0);
    delete ship;

    //Star Dreadnought
    ship = new StarDreadnought(10.0, "ship3");
    EXPECT_EQ(ship->getMaxSpeed(), 40.0);
    delete ship;

    //Imperial Shuttle
    ship = new ImperialShuttle(80, "ship4");
    EXPECT_EQ(ship->getMaxSpeed(), 54.0);
    delete ship;
}

/**
 * @test Checks that setLoad correctly updates currentLoad
 */
TEST(ShipTest, cargoSetLoadMustSetCorrectly) {
    CargoShip* cargo = new StarDreadnought;
    cargo->setLoad(20);
    EXPECT_EQ(cargo->getWeight(), 9e9 + 20);
    delete cargo;

    cargo = new ImperialShuttle;
    cargo->setLoad(20);
    EXPECT_EQ(cargo->getWeight(), 360 + 20);
    delete cargo;
}

/**
 * @test Checks that setLoad throws an exception for negative loads or when load exceeds maxLoad.
 */
TEST(ShipTest, cargoSetLoadInvalidMustThrow) {
    CargoShip* cargo = new StarDreadnought;
    EXPECT_THROW(cargo->setLoad(250'001), std::invalid_argument);
    delete cargo;

    cargo = new ImperialShuttle;
    EXPECT_THROW(cargo->setLoad(81), std::invalid_argument);
    delete cargo;
}

/**
 * @test The construction of CargoShip derived classes throws an exception with invalid load values
 */
TEST(ShipTest, constructionCargoThrowsWithInvalidValues) {
    EXPECT_THROW(new StarDreadnought(250'001, ""), std::invalid_argument);
    EXPECT_THROW(new ImperialShuttle(81, ""), std::invalid_argument);
}
