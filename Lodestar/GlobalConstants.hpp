//
// Created by Hamza El-Kebir on 12/22/21.
//

#ifndef LODESTAR_GLOBALCONSTANTS_HPP
#define LODESTAR_GLOBALCONSTANTS_HPP

#include <csignal>

#define LS_MAX_CONNECTIONS 99 /// Maximum number of connections any \c Signal<T> may establish.
#define LS_IS_MULTITHREADED true /// Flag for enabling multithreaded operations.

#define LS_CLOCK_SIGNAL SIGUSR1 /// Default main clock signal.
#define LS_EVENT_SIGNAL SIGUSR2 /// Default main event signal.

#endif //LODESTAR_GLOBALCONSTANTS_HPP
