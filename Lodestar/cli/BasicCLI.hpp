//
// Created by Hamza El-Kebir on 2/15/22.
//

#ifndef LODESTAR_BASICCLI_HPP
#define LODESTAR_BASICCLI_HPP

#include <CLI11/CLI11.hpp>
#include <Lodestar/blocks/aux/Executor.hpp>
#include <LodestarConfig.hpp>

namespace ls {
    namespace cli {
        class BasicCLI {
        public:
            struct BasicCLIOptions {
                bool graph = false;
                bool dotFile = false;
                bool version = false;
                ls::blocks::aux::Executor *ex;
            };

            static CLI::App &makeApp(CLI::App &app, BasicCLIOptions &opts, ls::blocks::aux::Executor &ex)
            {
                opts.ex = &ex;

                app.description("A Lodestar application.");
                app.add_flag("-v,--version", opts.version, "Lodestar version");
                app.add_flag("-g,--graph", opts.graph, "Display graph");
                app.add_flag("-d,--dot-file", opts.dotFile, "Output graph as dot file");

                return app;
            }

            static int
            runApp(int argc, char **argv, CLI::App &app, BasicCLIOptions &opts)
            {
                CLI11_PARSE(app, argc, argv);

                if (opts.graph) {
                    if (opts.dotFile) {
                        ::std::stringstream ss;
                        opts.ex->makeDotFile(ss);
                        ::std::cout << ss.str() << ::std::endl;
                    } else {
                        ::std::cout << opts.ex->getAsciiGraph(true, true) << ::std::endl;
                    }
                } else if (opts.version) {
                    ::std::cout << "Lodestar v" << LS_VERSION_MAJOR << "." << LS_VERSION_MAJOR << "."
                                << LS_VERSION_PATCH << ::std::endl;
                }

                return 0;
            }
        };
    }
}


#endif //LODESTAR_BASICCLI_HPP
