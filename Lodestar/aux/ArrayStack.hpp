//
// Created by Hamza El-Kebir on 6/15/21.
//

#ifndef LODESTAR_ARRAYSTACK_HPP
#define LODESTAR_ARRAYSTACK_HPP

#include <array>
#include <cassert>
#include <stdexcept>

namespace ls {
    namespace aux {
        /**
         * @brief A statically sized stack with full member access.
         *
         * @tparam TType Type of element.
         * @tparam TSize Maximum size of stack.
         */
        template<typename TType, size_t TSize>
        struct ArrayStack {
        public:
            ArrayStack() : size_(0)
            {}

            using type = ArrayStack<TType, TSize>;
            using arrayType = std::array<TType, TSize>;

            /**
             * @brief Construct a stack filled with the default values of \c TType.
             *
             * @return Stack filled with default constructed value of \c TType.
             */
            static type zero()
            {
                type a;
                a.fill(TType{});

                return a;
            }

            /**
             * @brief Gives current stack size.
             *
             * @return Current stack size.
             */
            inline size_t size() const noexcept
            {
                return size_;
            }

            /**
             * @brief Gives maximum stack size.
             *
             * @return Maximum stack size.
             */
            inline constexpr size_t max_size() const noexcept
            {
                return TSize;
            }

            /**
             * @brief Clears the stack.
             *
             * @details Note that this function simply changes the size of the stack to 0, allowing internally stored
             * elements to be overwritten.
             */
            inline void clear() noexcept
            {
                size_ = 0;
            }

            /**
             * @brief Returns a reference to the element at \c idx.
             *
             * @details This function throws an \c out_of_range exception for illegal \c idx value (negative, or
             * greater than size).
             *
             * @param idx Element index.
             *
             * @return Reference to element at \c idx.
             */
            inline TType &operator[](size_t idx)
            {
                if (idx < 0)
                    throw std::out_of_range("ArrayStack index less than zero.");
                if (idx >= size_)
                    throw std::out_of_range("ArrayStack index greater than size.");

                return array_[idx];
            }

            /**
             * @brief Returns a const reference to the element at \c idx.
             *
             * @details This function throws an \c out_of_range exception for illegal \c idx value (negative, or
             * greater than size).
             *
             * @param idx Element index.
             *
             * @return Const reference to element at \c idx.
             */
            inline const TType &operator[](size_t idx) const
            {
                if (idx < 0)
                    throw std::out_of_range("ArrayStack index less than zero.");
                if (idx >= size_)
                    throw std::out_of_range("ArrayStack index greater than size.");

                return array_[idx];
            }

            /**
             * @brief Fills the stack to full capacity with \c value.
             *
             * @param value Value to fill stack with.
             */
            inline void fill(const TType &value)
            {
                std::fill_n(begin(), max_size(), value);
                size_ = max_size();
            }

            /**
             * @brief Returns true if stack is empty.
             *
             * @details An empty stack is simply one for which `size() == 0`.
             *
             * @return True if stack is empty.
             */
            inline bool empty() const noexcept
            {
                return (size_ == 0);
            }

            /**
             * @brief Pushes value to front of ArrayStack.
             *
             * @details By pushing a value to the front, all other elements are shifted right. If the new size would
             * have been greater than the maximum size, the last element is popped.
             *
             * @param value Value to push to front.
             */
            inline void push(const TType &value)
            {
                // Pop last element
                if (size_ == TSize)
                    pop_back();

                // Shift right
                for (int i = size_ - 1; i >= 0; i--)
                    array_[i + 1] = array_[i];

                array_[0] = value;
                size_++;
            }

            /**
             * @brief Pops first element.
             *
             * @details All subsequent values are shifted to the left, and the size is decremented by 1.
             */
            inline void pop_front()
            {
                // Shift left
                for (int i = 0; i < size_ - 1; i++)
                    array_[i] = array_[i + 1];

                size_--;
            }

            /**
             * @brief Pops last element.
             */
            inline void pop_back()
            {
                if (size_ == 0)
                    return;

                size_--;
            }

            /**
             * @brief Returns a reference to the front value in the stack.
             *
             * @details Raises \c out_of_range exception if the current stack size is 0.
             *
             * @return Reference to front value.
             */
            inline TType &front()
            {
                // TODO: Replace exception by StatusOr<TType>.
                if (size_ == 0)
                    throw std::out_of_range("ArrayStack has size 0.");

                return array_[0];
            }

            /**
             * @brief Returns a const reference to the front value in the stack.
             *
             * @details Raises \c out_of_range exception if the current stack size is 0.
             *
             * @return Const reference to front value.
             */
            inline const TType &front() const
            {
                // TODO: Replace exception by StatusOr<TType>.
                if (size_ == 0)
                    throw std::out_of_range("ArrayStack has size 0.");

                return array_[0];
            }

            /**
             * @brief Returns a reference to the rear value in the stack.
             *
             * @details Raises \c out_of_range exception if the current stack size is 0.
             *
             * @return Reference to rear value.
             */
            inline TType &back()
            {
                // TODO: Replace exception by StatusOr<TType>.
                if (size_ == 0)
                    throw std::out_of_range("ArrayStack has size 0.");

                return array_[size_ - 1];
            }

            /**
             * @brief Returns a const reference to the rear value in the stack.
             *
             * @details Raises \c out_of_range exception if the current stack size is 0.
             *
             * @return Const reference to rear value.
             */
            inline const TType &back() const
            {
                // TODO: Replace exception by StatusOr<TType>.
                if (size_ == 0)
                    throw std::out_of_range("ArrayStack has size 0.");

                return array_[size_ - 1];
            }

            /**
             * @brief Returns an iterator the beginning of the stack.
             *
             * @return Iterator the beginning of the stack.
             */
            inline typename arrayType::iterator begin() noexcept
            {
                return array_.begin();
            }

            /**
             * @brief Returns a const iterator the beginning of the stack.
             *
             * @return Const iterator the beginning of the stack.
             */
            inline typename arrayType::const_iterator begin() const noexcept
            {
                return array_.begin();
            }

            /**
             * @brief Returns an iterator the end of the stack.
             *
             * @return Iterator the end of the stack.
             */
            inline typename arrayType::iterator end() noexcept
            {
                return array_.begin() + size_;
            }

            /**
             * @brief Returns a const iterator the end of the stack.
             *
             * @return Const iterator the end of the stack.
             */
            inline typename arrayType::const_iterator end() const noexcept
            {
                return array_.begin() + size_;
            }

        protected:
            arrayType array_;
            size_t size_;
        };
    }
}

#endif //LODESTAR_ARRAYSTACK_HPP
