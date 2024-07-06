#include <gtest/gtest.h>
#include "../Containers/Container.h"
#include "../people/Parent.h"

// Test that a person can be successfully added to a container
TEST(ContainerTest, AddPerson) {
    Container container("TestContainer");
    auto person = std::make_unique<Parent>("TestParent");
    container.addPerson(std::move(person));

    ASSERT_FALSE(container.isEmpty());
    ASSERT_EQ(container.size(), 1);
}

// Test moving a person from one container to another
TEST(ContainerTest, MovePersonBetweenContainers) {
    Container container1("StartContainer"), container2("TargetContainer");
    container1.addPerson(std::make_unique<Parent>("MovableParent"));
    container2.addPerson(container1.removePerson("MovableParent"));

    ASSERT_TRUE(container1.isEmpty());
    ASSERT_FALSE(container2.isEmpty());
    ASSERT_EQ(container2.size(), 1);
}

// Ensure the correct person is in the target container after transfer.
TEST(ContainerTest, CorrectPersonAfterTransfer) {
    Container container1("Source"), container2("Destination");
    std::string personName = "UniqueParent";
    container1.addPerson(std::make_unique<Parent>(personName));

    auto person = container1.removePerson(personName);
    container2.addPerson(std::move(person));

    auto retrievedPerson = container2.removePerson(personName);
    ASSERT_NE(retrievedPerson, nullptr);
    ASSERT_EQ(retrievedPerson->getName(), personName);
}

// Validate the container's response to adding an empty (nullptr) unique pointer.
TEST(ContainerTest, AddingEmptyPointer) {
    Container container("EmptyTest");
    std::unique_ptr<Person> emptyPerson;
    container.addPerson(std::move(emptyPerson));  // Should handle this gracefully

    ASSERT_TRUE(container.isEmpty());  // Container should still be empty
}


// Check the container's integrity after an attempt to remove a non-existent person.
TEST(ContainerTest, IntegrityAfterFailedRemoval) {
    Container container("StableContainer");
    container.addPerson(std::make_unique<Parent>("StableParent"));

    auto nonExistent = container.removePerson("NonExistent");
    ASSERT_TRUE(nonExistent == nullptr);  // No person found
    ASSERT_FALSE(container.isEmpty());    // Container should not be affected
    ASSERT_EQ(container.size(), 1);       // Still has the original person
}

//Perform operations that stress the container's ability to handle a large number of unique persons
TEST(ContainerTest, StressTest) {
    Container bigContainer("BigContainer");
    int numPersons = 1000;  // A large number of persons
    for (int i = 0; i < numPersons; i++) {
        bigContainer.addPerson(std::make_unique<Parent>("Parent" + std::to_string(i)));
    }

    ASSERT_EQ(bigContainer.size(), numPersons);  // Should handle a large number of additions

    for (int i = 0; i < numPersons; i++) {
        auto person = bigContainer.removePerson("Parent" + std::to_string(i));
        ASSERT_NE(person, nullptr);  // Each person should be successfully removed
    }

    ASSERT_TRUE(bigContainer.isEmpty());  // All persons should have been removed
}