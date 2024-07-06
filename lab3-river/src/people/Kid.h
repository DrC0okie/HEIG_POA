/**
 * @file Kid.h
 * @authors Walid Slimani, Timothée Van Hove
 */

#ifndef RIVER_KID_H
#define RIVER_KID_H

#include <memory>
#include "Parent.h"
#include "../Containers/Container.h"

/**
 * @class Class representing a Kid that depends on a Parent and can't stay with another Parent
 */
class Kid : public Person {
public:
    /**
     * Constructor
     * @param name The name of the Kid
     * @param dependsOn The Parent pointer the Kid depends on
     * @param cantStayWith The Parent pointer the Kid can't stay with
     */
    Kid(const std::string& name, const Parent* dependsOn, const Parent* cantStayWith);

    [[nodiscard]] bool isValid(const Container& c) const override;

    /**
     * Destructor
     */
    ~Kid() override;

protected:
    const Parent* dependsOn;
    const Parent* cantStayWith;
};


#endif //RIVER_KID_H
