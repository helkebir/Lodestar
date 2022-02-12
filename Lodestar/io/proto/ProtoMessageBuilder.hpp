//
// Created by Hamza El-Kebir on 2/10/22.
//

#ifndef LODESTAR_PROTOMESSAGEBUILDER_HPP
#define LODESTAR_PROTOMESSAGEBUILDER_HPP

#include <Lodestar/blocks/Signal.hpp>
#include <Lodestar/aux/AlwaysFalse.hpp>
#include <Lodestar/io/proto/ProtoMessageType.hpp>

#include <sstream>
#include <ersatz/Codegen.hpp>
#include <Eigen/Dense>
#include <cstdint>

namespace ls {
    namespace io {
        struct ProtoMessageHeraldInfo {
            ProtoMessageType type;
        };

        template<typename TType>
        class ProtoMessageBuilder {
            static_assert(always_false<TType>::value, "Not proto message builder defined for this type.");
        };

        template<typename TType>
        class ProtoMessageBuilder<ls::blocks::Signal<TType>> : ProtoMessageBuilder<TType> {
        };

        template<>
        class ProtoMessageBuilder<bool> {
        public:
            static ProtoMessageHeraldInfo makeHeraldInfo()
            {
                return {ProtoMessageType::bool_t};
            }

            static void defineMessage(::std::stringstream &ss)
            {
                ss << fmt::format("message {} {{\n", "bool_m");
                ss << "  required bool value = 1;\n";
                ss << "}\n";
            }

            static void defineOptions(::std::stringstream &ss)
            {}

            static void defineHeader(::std::stringstream &ss)
            {
                ss << "syntax = \"proto2\";\n\n";
                ss << "package ls.proto;\n\n";
            }
        };

        template<typename TScalar, int NRows, int NCols>
        class ProtoMessageBuilder<Eigen::Matrix<TScalar, NRows, NCols>> {
        public:
            static_assert((NRows >= 0) && (NCols >= 0), "Matrix may not be dynamically sized.");

            static ProtoMessageHeraldInfo makeHeraldInfo()
            {
                return {ProtoMessageType::bool_t};
            }

            inline static ::std::string getFileName()
            {
                return fmt::format("ls.proto.{}", getName());
            }

            inline static ::std::string getProtoFileName()
            {
                return fmt::format("{}.proto", getFileName());
            }

            inline static ::std::string getOptionsFileName()
            {
                return fmt::format("{}.options", getFileName());
            }

            static ::std::string getScalarName()
            {
                if (::std::is_same<TScalar, double>::value)
                    return "double";
                if (::std::is_same<TScalar, float>::value)
                    return "float";
                if (::std::is_same<TScalar, int32_t>::value)
                    return "int32";
                if (::std::is_same<TScalar, uint32_t>::value)
                    return "uint32";
            }

            static ::std::string getShortScalarName()
            {
                if (::std::is_same<TScalar, double>::value)
                    return "d";
                if (::std::is_same<TScalar, float>::value)
                    return "f";
                if (::std::is_same<TScalar, int32_t>::value)
                    return "i";
                if (::std::is_same<TScalar, uint32_t>::value)
                    return "u";
            }

            inline static ::std::string getName()
            {
                return fmt::format("Matrix{}{}x{}", getShortScalarName(), NRows, NCols);
            }

            inline static ::std::string getMessageName()
            {
                return fmt::format("{}_m", getName());
            }

            inline static ::std::string getMessageTypeName()
            {
                return fmt::format("{}_t", getName());
            }

            static void defineMessage(::std::stringstream &ss)
            {
                ss << fmt::format("message {} {{\n", getMessageName());
                ss << fmt::format("  repeated {} coeff = 1;\n", getScalarName());
                ss << "}\n";
            }

            static void defineOptions(::std::stringstream &ss)
            {
                ss << fmt::format("{}.coeff    max_size:{}", getMessageName(), NRows*NCols);
            }

            static void defineHeader(::std::stringstream &ss)
            {
                ss << "syntax = \"proto2\";\n\n";
                ss << "package ls.proto;\n\n";
            }
        };

    }
}


#endif //LODESTAR_PROTOMESSAGEBUILDER_HPP
