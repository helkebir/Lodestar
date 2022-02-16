//
// Created by Hamza El-Kebir on 2/15/22.
//

#include "ExecuteCommand.hpp"

bool ls::cli::ExecuteCommand::commandExists(const std::string &cmd)
{
    static ::std::string cmdAugmented;
    cmdAugmented = "which " + cmd + " > /dev/null 2>&1";
    return system(cmdAugmented.c_str()) == 0;
}
