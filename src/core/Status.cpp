//
// Created by Hamza El-Kebir on 6/17/21.
//

#include "Status.hpp"

namespace ls {
    namespace core {
//        inline
//        Status &Status::operator=(const Status &other)
//        {
//            errorCode_ = other.errorCode_;
//            return *this;
//        }

        inline
        bool Status::operator==(const Status &other) const
        {
            return errorCode_ == other.errorCode_;
        }

        std::string Status::toString() const
        {
            if (errorCode_ == StatusCode::Ok)
                return "OK";

            return statusCodeToString(errorCode_);
        }

        namespace util {
            Status OkStatus()
            {
                return Status();
            }

            Status UnknownError()
            {
                return Status(StatusCode::Unknown);
            }

            Status InternalError()
            {
                return Status(StatusCode::Internal);
            }
        }
    }
}