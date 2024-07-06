#include <gtest/gtest.h>
#include "../Containers/Boat.h"
#include "../people/Parent.h"
#include "../people/Boy.h"
#include "../people/Girl.h"
#include "../people/Policeman.h"
#include "../people/Thief.h"
#include <memory>

class RulesTest : public ::testing::Test {
protected:
    std::unique_ptr<Boat> boat;
    std::unique_ptr<Bank> bank;
    std::unique_ptr<Parent> mother;
    std::unique_ptr<Parent> mistress;
    std::unique_ptr<Parent> father;
    std::unique_ptr<Policeman> policeman;
    std::unique_ptr<Boy> son;
    std::unique_ptr<Boy> son2;
    std::unique_ptr<Girl> daughter;
    std::unique_ptr<Girl> daughter2;
    std::unique_ptr<Thief> thief;

    void SetUp() override {
        boat = std::make_unique<Boat>("Boat", 2);
        bank = std::make_unique<Bank>("Bank");
        mother = std::make_unique<Parent>("mother");
        mistress = std::make_unique<Parent>("mistress");
        father = std::make_unique<Parent>("father");
        policeman = std::make_unique<Policeman>("columbo");
        son = std::make_unique<Boy>("son", father.get(), mother.get());
        son2 = std::make_unique<Boy>("son2", father.get(), mother.get());
        daughter = std::make_unique<Girl>("daughter", father.get(), mother.get());
        daughter2 = std::make_unique<Girl>("daughter2", father.get(), mother.get());
        thief = std::make_unique<Thief>("thief", policeman.get());
    }

    void TearDown() override {
        boat.reset();
        bank.reset();
    }
};

// Test rule: No more than two people are allowed on the boat.
TEST_F(RulesTest, MaxTwoPeopleOnBoat) {
    boat->addPerson(std::move(father));
    boat->addPerson(std::move(mistress));
    ASSERT_FALSE(boat->getStatus().error);
    boat->addPerson(std::move(mother));
    ASSERT_TRUE(boat->isFull());
}

// Test rule: Children and the thief cannot pilot the boat.
TEST_F(RulesTest, ChildrenAndThiefCannotPilot) {
    ASSERT_FALSE(son->canDrive());
    ASSERT_FALSE(daughter->canDrive());
    ASSERT_FALSE(thief->canDrive());
}

// Test the Thief rules
TEST_F(RulesTest, ThiefRules) {

    // The thief can be let alone
    bank->addPerson(std::move(thief));
    ASSERT_FALSE(bank->getStatus().error);

    // The thief cannot be with other people thant the policeman
    bank->addPerson(std::move(father));
    ASSERT_TRUE(bank->getStatus().error);

    // Now adding the Policeman must be valid
    bank->addPerson(std::move(policeman));
    ASSERT_FALSE(bank->getStatus().error);
}

// Test the Boy rules
TEST_F(RulesTest, BoyRules) {

    // The Boy can be let alone
    bank->addPerson(std::move(son));
    ASSERT_FALSE(bank->getStatus().error);

    // The Boy can be with his brother
    bank->addPerson(std::move(son2));
    ASSERT_FALSE(bank->getStatus().error);

    // They can be all three together
    bank->addPerson(std::move(daughter));
    ASSERT_FALSE(bank->getStatus().error);

    // The boy cannot be left alone with his mother without the father
    bank->removePerson("daughter");
    bank->removePerson("son2");
    bank->addPerson(std::move(mother));
    ASSERT_TRUE(bank->getStatus().error);

    // The boy can be left alone with his father
    bank->removePerson("mother");
    bank->addPerson(std::move(father));
    ASSERT_FALSE(bank->getStatus().error);

    // The boy can be left alone with Columbo
    bank->removePerson("father");
    bank->addPerson(std::move(policeman));
    ASSERT_FALSE(bank->getStatus().error);

    // The boy can be accompagned by both parents
    bank->removePerson("columbo");
    bank->addPerson(std::move(father));
    bank->addPerson(std::move(mother));
    ASSERT_FALSE(bank->getStatus().error);
}

// Test the Daughter rules
TEST_F(RulesTest, DaughterRules) {

    // The daughter can be left alone
    bank->addPerson(std::move(daughter));
    ASSERT_FALSE(bank->getStatus().error);

    // The daughter can be with her sister
    bank->addPerson(std::move(daughter2));
    ASSERT_FALSE(bank->getStatus().error);

    // They can be all 3 together
    bank->addPerson(std::move(son));
    ASSERT_FALSE(bank->getStatus().error);

    // The daughter cannot be left alone with her father without the mother
    bank->removePerson("son");
    bank->removePerson("daughter2");
    bank->addPerson(std::move(father));
    ASSERT_TRUE(bank->getStatus().error);

    // The daughter can be left alone with her mother
    bank->removePerson("father");
    bank->addPerson(std::move(mother));
    ASSERT_FALSE(bank->getStatus().error);

    // The daughter can be left alone with Columbo
    bank->removePerson("mother");
    bank->addPerson(std::move(policeman));
    ASSERT_FALSE(bank->getStatus().error);

    // The daughter can be accompagned by both parents
    bank->removePerson("columbo");
    bank->addPerson(std::move(father));
    bank->addPerson(std::move(mother));
    ASSERT_FALSE(bank->getStatus().error);
}

// Test the parents rules
TEST_F(RulesTest, ParentRules) {

    // The father can be let alone
    bank->addPerson(std::move(father));
    ASSERT_FALSE(bank->getStatus().error);

    // The father can be left with his wife
    bank->addPerson(std::move(mother));
    ASSERT_FALSE(bank->getStatus().error);

    // The father can even be left with his mistress, while his wife is present!
    bank->addPerson(std::move(mother));
    ASSERT_FALSE(bank->getStatus().error);

    // The father cannot be left alone with the thief
    bank->addPerson(std::move(thief));
    ASSERT_TRUE(bank->getStatus().error);

    // But if we add the policeman, it's okay
    bank->addPerson(std::move(policeman));
    ASSERT_FALSE(bank->getStatus().error);
}