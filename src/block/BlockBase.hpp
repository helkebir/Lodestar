//
// Created by Hamza El-Kebir on 5/27/21.
//

#ifndef LODESTAR_BLOCKBASE_HPP
#define LODESTAR_BLOCKBASE_HPP

#define LS_MAX_CALLBACKS 20
#define LS_MAX_TICKETS 10
#define LS_CB_RETURN_TYPE bool

class BlockBase {
protected:
    virtual ~BlockBase() = default;
};

#endif //LODESTAR_BLOCKBASE_HPP
