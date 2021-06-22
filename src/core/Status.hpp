//
// Created by Hamza El-Kebir on 6/17/21.
//

#ifndef LODESTAR_STATUS_HPP
#define LODESTAR_STATUS_HPP

#include <string>

namespace ls {
    namespace core {
        enum class StatusCode : int {
            Ok = 0,
            Unknown = 1,
            Internal = 2,
        };

        // TODO: Add efficient way of encoding compile-time string messages with minimal overhead.
        class Status {
        public:
            Status() : errorCode_(StatusCode::Ok)
            {};

            Status(StatusCode errorCode) : errorCode_(errorCode)
            {};

            Status(const Status &other) : errorCode_(other.errorCode_)
            {};

            Status &operator=(const Status &s) = default;

            ~Status() = default;

            inline bool ok() const
            {
                return errorCode_ == StatusCode::Ok;
            }

            inline StatusCode code() const
            {
                return errorCode_;
            }

            bool operator==(const Status &s) const;

            bool operator!=(const Status &s) const
            {
                return !operator==(s);
            }

            std::string toString() const;

        protected:
            StatusCode errorCode_;
        };

        inline
        std::string statusCodeToString(StatusCode code)
        {
            switch (code) {
                case StatusCode::Ok:
                    return "OK";
                case StatusCode::Unknown:
                    return "UNKNOWN";
            }

            return "UNKNOWN";
        }

        namespace util {
            Status OkStatus();

            Status UnknownError();

            Status InternalError();
        }
    }
}

#endif //LODESTAR_STATUS_HPP
