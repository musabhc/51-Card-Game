#ifndef PER_H
#define PER_H
#include "hand.h"
#include <iostream>
class per
{
public:
    std::string line = "--------------------------------------------------------";

    per(const Hand&, const Hand&);
};

#endif // PER_H
