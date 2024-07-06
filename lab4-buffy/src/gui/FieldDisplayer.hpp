#ifndef POA_LABO4_FIELDDISPLAYER_HPP
#define POA_LABO4_FIELDDISPLAYER_HPP

#include "src/Field.hpp"
#include "src/Constants.hpp"

/**
 * Class used to display a simulation field
 *
 * @authors Walid Slimani, Timothée Van Hove
 */
class FieldDisplayer {
public:

    /**
     * Display a field
     * @param field the field to display
     */
    static void display(const Field& field) ;
};


#endif //POA_LABO4_FIELDDISPLAYER_HPP
