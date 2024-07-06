#include "gtest/gtest.h"
#include "../utils/ShipList.hpp"
#include "../ship/Tie.hpp"
#include "../ship/TieInterceptor.hpp"
#include "../ship/TieFighter.hpp"
#include "../ship/cargo/CargoShip.hpp"
#include "../ship/cargo/StarDreadnought.hpp"
#include "../ship/cargo/ImperialShuttle.hpp"

/**
 * @test Tests the default constructor of a ShipList
 */
TEST(ShipListTest, ShipListDefaultCtor){
    ShipList list;
    EXPECT_THROW(list.get(0), std::out_of_range);
}

/**
 * @test Tests that the copy constructor actually makes a copy from another object
 */
TEST(ShipListTest, ShipListCopyCtor){
    ShipList original;
    original.add(new TieFighter);
    original.add(new StarDreadnought(1.0, "Star Destroyer"));

    ShipList copy(original); // Use the copy constructor

    // Modify the copy and ensure the original is unaffected
    auto shuttle = new ImperialShuttle(2.0, "Shuttle");
    copy.add(shuttle);

    EXPECT_TRUE(copy.contains(shuttle));
    EXPECT_FALSE(original.contains(shuttle));

    original.clear();
    copy.clear();
}

/**
 * @test Tests if the affectation operator effectively copies the object when necessary
 */
TEST(ShipListTest, ShipListCopyAffectation){
    ShipList original;
    original.add(new TieFighter);
    original.add(new StarDreadnought(1.0, "Star Destroyer"));

    auto copy = original; // Will copy via the affectation operator

    // Modify the copy and ensure the original is unaffected
    auto shuttle = new ImperialShuttle(2.0, "Shuttle");
    copy.add(shuttle);

    EXPECT_TRUE(copy.contains(shuttle));
    EXPECT_FALSE(original.contains(shuttle));

    original.clear();
    copy.clear();
}

/**
 * @test checks that moving a ShipList transfers ownership to the new instance and that the
 * moved-from object is left in a valid but empty state.
 */
TEST(ShipListTest, ShipListMoveCtor){
    ShipList original;
    auto fighter = new TieFighter("Fighter");
    auto dread = new StarDreadnought(1.0, "Star Destroyer");
    original.add(fighter);
    original.add(dread);

    ShipList moved(std::move(original)); // Use the move constructor

    // The original list should be empty after the move
    EXPECT_FALSE(original.contains(fighter));
    EXPECT_FALSE(original.contains(dread));

    // Verify the moved list has the content originally in 'original'
    EXPECT_TRUE(moved.contains(fighter));
    EXPECT_TRUE(moved.contains(dread));

    //The ships addresses should be the same
    EXPECT_EQ(fighter, moved.get(0));
    EXPECT_EQ(dread, moved.get(1));

    original.clear();
    moved.clear();
}

/**
 * @test Tests if the affectation operator effectively moves the object when necessary
 */
TEST(ShipListTest, ShipListMoveAffectation){
    ShipList original;
    auto fighter = new TieFighter("Fighter");
    auto dread = new StarDreadnought(1.0, "Star Destroyer");
    original.add(fighter);
    original.add(dread);

    ShipList moved = std::move(original); // Should use the move constructor

    // The original list should be empty after the move
    EXPECT_FALSE(original.contains(fighter));
    EXPECT_FALSE(original.contains(dread));

    // Verify the moved list has the content originally in 'original'
    EXPECT_TRUE(moved.contains(fighter));
    EXPECT_TRUE(moved.contains(dread));

    //The ships addresses should be the same
    EXPECT_EQ(fighter, moved.get(0));
    EXPECT_EQ(dread, moved.get(1));

    original.clear();
    moved.clear();
}

/**
 * @test Assigning a ShipList to itself should be a no-op
 */
TEST(ShipListTest, SelfCopyAssignment) {
    ShipList list;
    auto shuttle = new ImperialShuttle(1.0, "Ship1");
    auto interceptor = new TieInterceptor();
    list.add(shuttle);
    list.add(interceptor);

    list = list; // Self-assignment

    EXPECT_TRUE(list.contains(shuttle));
    EXPECT_TRUE(list.contains(interceptor));

    list.clear();
}

/**
 * @test After a ShipList has been moved from, it should be in a valid but unspecified state
 */
TEST(ShipListTest, UseMovedFromObject) {
    ShipList original;
    original.add(new TieInterceptor());

    ShipList moved(std::move(original));

    // original should be empty.
    EXPECT_THROW(original.get(0), std::out_of_range);

    original.clear();
    moved.clear();
}

/**
 * @test verifies that ships can be removed correctly from the ShipList.
 */
TEST(ShipListTest, ShipListRemovesCorrectly){
    ShipList list;
    Ship* ship1 = new TieFighter();
    Ship* ship2 = new TieInterceptor();
    list.add(ship1);
    list.add(ship2);

    // No problems here to get the second ship
    EXPECT_NO_THROW(list.get(1));

    list.remove(ship1);  // Remove first ship

    EXPECT_TRUE(list.contains(ship2));
    EXPECT_FALSE(list.contains(ship1));

    // Now it should throw
    EXPECT_THROW(list.get(1), std::out_of_range);

    list.clear();
}

/**
 * @test Ensures that the get method correctly retrieves ships from the ShipList.
 */
TEST(ShipListTest, ShipListGetsCorrectly){
    ShipList list;
    Ship* ship1 = new ImperialShuttle();
    Ship* ship2 = new StarDreadnought();
    list.add(ship1);
    list.add(ship2);

    EXPECT_EQ(list.get(0), ship1);
    EXPECT_EQ(list.get(1), ship2);

    list.clear();
}

/**
 * @test Verifies that the ShipList can be cleared correctly, leaving it empty.
 */
TEST(ShipListTest, ShipListClearsCorrectly){
    ShipList list;
    list.add(new TieFighter);
    list.add(new StarDreadnought());
    list.clear();

    // The list should be empty now
    EXPECT_THROW(list.get(0), std::out_of_range);

    list.clear();
}
/**
 * @test Verifies that an iterator can be obtained from a ShipList and that it initially points to the first element if the list isn't empty
 */
TEST(ShipListTest, ShipListGetsIteratorCorrectly){
    ShipList list;
    auto sd = new StarDreadnought();
    list.add(sd);

    auto it = list.getIterator();
    EXPECT_TRUE(it.hasNext());
    EXPECT_EQ(it.next(), sd);

    list.clear();
}

/**
 * @test Checks that the iterator correctly iterates over all elements.
 */
TEST(ShipListTest, ShipListIteratesCorrectly){
    ShipList list;
    Ship* ship1 = new TieFighter();
    Ship* ship2 = new TieInterceptor();
    Ship* ship3 = new StarDreadnought();
    Ship* ship4 = new ImperialShuttle();
    list.add(ship1);
    list.add(ship2);
    list.add(ship3);
    list.add(ship4);

    auto it = list.getIterator();
    EXPECT_TRUE(it.hasNext());
    EXPECT_EQ(it.next(), ship1);

    EXPECT_TRUE(it.hasNext());
    EXPECT_EQ(it.next(), ship2);

    EXPECT_TRUE(it.hasNext());
    EXPECT_EQ(it.next(), ship3);

    EXPECT_TRUE(it.hasNext());
    EXPECT_EQ(it.next(), ship4);

    EXPECT_FALSE(it.hasNext());  // The iterator should have no more elements

    list.clear();
}

/**
 * @test Checks that const methods can be used on a const ShipList, ensuring read-only operations work as expected.
 */
TEST(ShipListTest, ConstShipListCanBeRead) {
    ShipList tempList;
    Ship* ship1 = new TieFighter();
    Ship* ship2 = new TieInterceptor();

    tempList.add(ship1);
    tempList.add(ship2);

    const ShipList list = tempList;  // Create a const copy for testing
    EXPECT_EQ(list.get(0), ship1);
    EXPECT_TRUE(list.contains(list.get(0)));

    tempList.clear();
}

/**
 * @test Ensures that a const ShipList can be iterated over without modifying it, testing the const-correctness of the iteration process.
 */
TEST(ShipListTest, ConstShipListIteratesCorrectly) {
    ShipList tempList;
    Ship* ship1 = new TieFighter();
    Ship* ship2 = new TieInterceptor();
    Ship* ship3 = new StarDreadnought();
    Ship* ship4 = new ImperialShuttle();
    tempList.add(ship1);
    tempList.add(ship2);
    tempList.add(ship3);
    tempList.add(ship4);

    const ShipList list = tempList; // Create a const copy for testing
    auto it = list.getIterator();

    EXPECT_TRUE(it.hasNext());
    EXPECT_EQ(it.next(), ship1);

    EXPECT_TRUE(it.hasNext());
    EXPECT_EQ(it.next(), ship2);

    EXPECT_TRUE(it.hasNext());
    EXPECT_EQ(it.next(), ship3);

    EXPECT_TRUE(it.hasNext());
    EXPECT_EQ(it.next(), ship4);

    EXPECT_FALSE(it.hasNext());  // The iterator should have no more elements

    tempList.clear();
}

/**
 * @test Verify that attempting to add a nullptr Ship throws the expected exception.
 */
TEST(ShipListTest, AddingRemovingNullShipThrows) {
    ShipList list;
    EXPECT_THROW(list.add(nullptr), std::invalid_argument);
    EXPECT_THROW(list.remove(nullptr), std::invalid_argument);
}

/**
 * @test Verify behavior when trying to remove a Ship that isn't in the list.
 */
TEST(ShipListTest, RemovingNonExistentShip) {
    ShipList list;
    auto interceptor = new TieInterceptor;
    auto fighter = new TieFighter;
    list.add(interceptor);
    EXPECT_FALSE(list.remove(fighter));
    EXPECT_TRUE(list.remove(interceptor));

    list.clear();
}

/**
 * @test Accessing an element in an empty list should throw an exception.
 */
TEST(ShipListTest, GetOnEmptyListThrows) {
    ShipList list;
    EXPECT_THROW(list.get(0), std::out_of_range);
}

/**
 * @test Verify behavior of an iterator obtained from an empty list
 */
TEST(ShipListTest, IteratorOnEmptyList) {
    ShipList list;
    EXPECT_FALSE(list.getIterator().hasNext());
    EXPECT_THROW(list.getIterator().next(), std::out_of_range);
}
