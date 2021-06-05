//
// Created by Hamza El-Kebir on 5/27/21.
//

#ifndef LODESTAR_TICKET_HPP
#define LODESTAR_TICKET_HPP

struct Ticket {
    size_t destAddress;
    size_t destSlot;
    size_t callbackSlot;
    bool active = false;
    bool expired = false;
};

template<size_t TOutputs, size_t TTicketNumber = LS_MAX_TICKETS>
struct TicketBook {
    std::array<std::array<Ticket, TTicketNumber>, TOutputs> tickets;
};

#endif //LODESTAR_TICKET_HPP
