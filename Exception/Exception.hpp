//
// Created by pcsc on 12/3/18.
//

#ifndef MONTE_CARLO_EXCEPTION_HPP
#define MONTE_CARLO_EXCEPTION_HPP

#include <string>
/**
 * Struct for dealing with exceptions which outputs messages
 */
struct Exception {
    Exception(const std::string &mesg) : mesg(mesg) {};
    const std::string &what() { return mesg; };
    std::string mesg;
};

#endif //MONTE_CARLO_EXCEPTION_HPP
