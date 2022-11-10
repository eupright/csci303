#include <entity/Coordinate.h>
#include "comparator/Comparator.h"

template<class Comparable>
bool Comparator<Comparable>::lessThanOrEqualTo(Comparable &obj1, Comparable &obj2) {
    return lessThan(obj1, obj2) || equals(obj1, obj2);
}

template class Comparator<int>;
template class Comparator<Coordinate>;
