//
// Created by Hamza El-Kebir on 2/15/22.
//

#ifndef LODESTAR_EXECUTECOMMAND_HPP
#define LODESTAR_EXECUTECOMMAND_HPP

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

namespace ls {
    namespace cli {
        class ExecuteCommand {
        public:
            static bool commandExists(const ::std::string &cmd);

            template<unsigned int NBufferSize = 512>
            static ::std::string getStdout(const ::std::string &cmd)
            {
                static std::array<char, NBufferSize> buffer{};
                std::string result;
                std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
                if (!pipe) {
                    throw std::runtime_error("popen() failed!");
                }
                while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
                    result += buffer.data();
                }
                return result;
            }
        };
    }
}


#endif //LODESTAR_EXECUTECOMMAND_HPP
