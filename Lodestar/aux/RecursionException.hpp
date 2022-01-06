//
// Created by Hamza El-Kebir on 5/27/21.
//

#ifndef LODESTAR_RECURSIONEXCEPTION_HPP
#define LODESTAR_RECURSIONEXCEPTION_HPP

#include <exception>

/*
 * ptrToEffectiveEnd is computed to limit the subsequent find calls to the range of the array in which addresses have
 * been previously initialized.
 */
#define INIT_RECURSION_GUARD(CALLSTACK, CURRENT_ADDRESS) \
{try {                                                    \
    {auto ptrToEffectiveEnd = std::find(std::get<0>(CALLSTACK).begin(), std::get<0>(CALLSTACK).end(), decltype(CURRENT_ADDRESS){}); \
    auto idx = std::find(std::get<0>(CALLSTACK).begin(), ptrToEffectiveEnd, CURRENT_ADDRESS); \
    if (idx != ptrToEffectiveEnd) {                      \
        throw RecursionException<std::size_t>(std::get<1>(CALLSTACK)); \
    } \
    std::get<0>(CALLSTACK)[std::get<2>(CALLSTACK)] = CURRENT_ADDRESS; \
    std::get<1>(CALLSTACK) = CURRENT_ADDRESS; \
    std::get<2>(CALLSTACK)++;}

#define OPEN_RECURSION_GUARD(CALLSTACK, CURRENT_ADDRESS) \
{try {                                                   \
std::get<1>(CALLSTACK) = CURRENT_ADDRESS;

#define CLOSE_RECURSION_GUARD(CALLSTACK, CURRENT_ADDRESS) \
} catch (const RecursionException<std::size_t> &rexception) { \
    if (rexception.getInstance() == CURRENT_ADDRESS) std::get<1>(CALLSTACK) = CURRENT_ADDRESS; \
    else throw rexception; \
}}

#define OPEN_CATCH_RECURSION_GUARD(CALLSTACK, CURRENT_ADDRESS) } \
catch (const RecursionException<std::size_t> &rexception) {  \
    if (rexception.getInstance() != CURRENT_ADDRESS) { throw rexception; }

#define CLOSE_CATCH_RECURSION_GUARD(CALLSTACK, CURRENT_ADDRESS) \
    std::get<1>(CALLSTACK) = CURRENT_ADDRESS;                   \
}}

template <typename TType>
class RecursionException : public std::exception {
public:
    RecursionException(TType instance) : instance_(instance) {}

    virtual ~RecursionException() noexcept {}

    virtual const char* what() const noexcept {
        std::cout << instance_ << std::endl;
        return std::to_string(instance_).c_str();
    }

    virtual const TType getInstance() const noexcept {
        return instance_;
    }
protected:
    TType instance_;
};

#endif //LODESTAR_RECURSIONEXCEPTION_HPP
