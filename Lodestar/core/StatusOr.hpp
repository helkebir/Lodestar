//
// Created by Hamza El-Kebir on 6/17/21.
//

#ifndef LODESTAR_STATUSOR_HPP
#define LODESTAR_STATUSOR_HPP

#include "Status.hpp"
#include <type_traits>

namespace ls {
    namespace core {
        template<typename TType>
        class StatusOr {
            // Allow access to private/protected variables/methods in all other StatusOr instances.
            template<typename> friend
            class StatusOr;

        public:
            using type = TType;

            StatusOr();

            StatusOr(const Status &status);

            StatusOr(const TType &value);

            StatusOr(const StatusOr &other);

            template<typename TTypeOther>
            StatusOr(const StatusOr<TTypeOther> &other,
                     typename std::enable_if<std::is_convertible<TTypeOther, TType>::value>::type * = nullptr);

            template<typename TTypeOther>
            StatusOr(const StatusOr<TTypeOther> &other,
                     typename std::enable_if<!std::is_convertible<TTypeOther, TType>::value>::type * = nullptr);

            StatusOr &operator=(const StatusOr &other);

            template<typename TTypeOther>
            typename std::enable_if<std::is_convertible<TTypeOther, TType>::value, StatusOr &>::type
            operator=(const StatusOr<TTypeOther> &other)
            {
                status_ = other.status_;
                if (status_.ok())
                    value_ = other.value_;

                return *this;
            }

            template<typename TTypeOther>
            typename std::enable_if<!std::is_convertible<TTypeOther, TType>::value, StatusOr &>::type
            operator=(const StatusOr<TTypeOther> &other)
            {
                static_assert(std::is_convertible<TTypeOther, TType>::value,
                              "StatusOr value must be convertible.");

                return *this;
            }

            const Status &status() const;

            bool ok() const;

            inline explicit operator bool() const;

            const TType &value() const;

        protected:
            Status status_;
            TType value_;
        };

        template<typename TType>
        inline StatusOr<TType>::StatusOr() : status_(util::UnknownError())
        {}

        template<typename TType>
        inline StatusOr<TType>::StatusOr(const Status &status)
        {
            if (status.ok())
                status_ = util::InternalError(); // OkStatus is not a valid argument.
            else
                status_ = status;
        }

        template<typename TType>
        inline StatusOr<TType>::StatusOr(const TType &value)
        {
            if (!std::is_pointer<decltype(&value)>::value)
                status_ = util::InternalError(); // nullptr is not a valid argument.
            else {
                status_ = util::OkStatus();
                value_ = value;
            }
        }

        template<typename TType>
        inline StatusOr<TType>::StatusOr(const StatusOr &other) : status_(
                other.status_), value_(other.value_)
        {}

        template<typename TType>
        template<typename TTypeOther>
        inline StatusOr<TType>::StatusOr(const StatusOr<TTypeOther> &other,
                                         typename std::enable_if<std::is_convertible<TTypeOther, TType>::value>::type *)
                : status_(other.status_),
                  value_(other.status_.ok() ? other.value_
                                            : TType{})
        {}

        template<typename TType>
        template<typename TTypeOther>
        inline StatusOr<TType>::StatusOr(const StatusOr<TTypeOther> &other,
                                         typename std::enable_if<!std::is_convertible<TTypeOther, TType>::value>::type *)
        {
            static_assert(std::is_convertible<TTypeOther, TType>::value,
                          "StatusOr value must be convertible.");
        }

        template<typename TType>
        inline StatusOr<TType> &
        StatusOr<TType>::operator=(const StatusOr &other)
        {
            status_ = other.status_;
            value_ = other.value_;

            return *this;
        }

        template<typename TType>
        inline const Status &StatusOr<TType>::status() const
        { return status_; }

        template<typename TType>
        inline bool StatusOr<TType>::ok() const
        { return status_.ok(); }

        template<typename TType>
        StatusOr<TType>::operator bool() const
        { return ok(); }

        template<typename TType>
        const TType &StatusOr<TType>::value() const
        {
            if (!status_.ok()) {
                // TODO: Implement StatusOrHelper::Crash(status_) by adding logging mechanism.
            }

            return value_;
        }
    }
}

#endif //LODESTAR_STATUSOR_HPP
