//
// Created by Hamza El-Kebir on 6/15/21.
//

#ifndef LODESTAR_SIMPLEMOVINGAVERAGE_HPP
#define LODESTAR_SIMPLEMOVINGAVERAGE_HPP

#include "Lodestar/aux/ArrayStack.hpp"

namespace ls {
    namespace filter {
        /**
         * @brief A statically sized simple moving average filter.
         *
         * @details A simple moving average is the unweighted average of the elements that are currently in the buffer,
         * of which there are at most \c TWindowSize; the buffer is also known as the 'window':
         *
         * \code{.cpp}
         * SimpleMovingAverage<double, 4> sma{};
         * sma.push(1);
         * sma.push(3);
         * assert(sma.average() == 2);
         * sma.push(5);
         * sma.push(3);
         * assert(sma.average() == 3);
         * \endcode
         *
         * @see ls.aux.ArrayStack
         *
         * @tparam TType Type of element; must be addable with itself, and divisible by an unsigned integer.
         * @tparam TWindowSize Maximum size of the window.
         */
        template<typename TType = double, size_t TWindowSize = 1>
        class SimpleMovingAverage {
        public:
            typedef ls::aux::ArrayStack<TType, TWindowSize> TDWindow;

            SimpleMovingAverage() = default;

            /**
             * @brief Push value to moving average window.
             *
             * @param value Value to be included in moving average.
             */
            void push(const TType &value)
            {
                window_.push(value);
            }

            /**
             * @brief Compute unweighted average of elements in window.
             *
             * @details If there are no elements in the window, the value produced by the default constructor of
             * \c TType is returned.
             *
             * @return Unweighted average of values in the window.
             */
            TType average() const
            {
                // TODO: Repplace TType{} by StatusOr<TType>.
                TType ret{};

                if (window_.empty())
                    return ret;

                for (int i = 0; i < window_.size(); i++)
                    ret += window_[i];

                return ret / window_.size();
            }

            /**
             * @brief Clears the window.
             */
            void clear() noexcept
            {
                window_.clear();
            }

            /**
             * @brief Returns the current window size.
             *
             * @return Current window size.
             */
            inline size_t size() const noexcept
            {
                return window_.size();
            }

            /**
             * @brief Returns the maximum window size.
             *
             * @return Maximum window size.
             */
            inline constexpr size_t max_size() const noexcept
            {
                return TWindowSize;
            }

        protected:
            TDWindow window_; //! Window buffer.
        };
    }
}

#endif //LODESTAR_SIMPLEMOVINGAVERAGE_HPP
