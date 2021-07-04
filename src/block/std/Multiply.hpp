//
// Created by Hamza El-Kebir on 6/12/21.
//

#ifndef LODESTAR_MULTIPLY_HPP
#define LODESTAR_MULTIPLY_HPP

#include "../Block.hpp"
#include "aux/OperationTypes.hpp"
#include "aux/AlgebraicOperators.hpp"
#include "aux/PairUp.hpp"
#include "aux/Pack.hpp"
#include <Eigen/Dense>

namespace ls {
    namespace block {
        template<typename TInputsList, typename TOperators, typename TCollection, typename TEnable = void>
        class MultiplyBlock : public BlockBase {
        };

        /* TODO: Use Collection to make pairs, unpack into left and right typename pack, perform binop check with Conjunction,
         *  specialize using SFINAE (use static_assert for false case), make callbacks using SFINAE-based iterator.
         */
        template<typename... TInputs, AlgebraicOperators... TOperators, template<typename, typename> class ... TPairs, typename... TLeft, typename... TRight>
        class MultiplyBlock<std::tuple<TInputs...>, AlgebraicOperatorsPack<TOperators...>, CollectionImpl<TPairs<TLeft, TRight>...>>
                : public Block<std::tuple<TInputs...>, std::tuple<double>, sizeof...(TInputs)> {
        public:
            using left = Pack<TLeft...>;
            using right = Pack<TRight...>;
        };


//        template <typename... TInputs, AlgebraicOperators... TOperators, typename... TPairsLeft, typename... TPairsRight>
//        class MultiplyBlock<std::tuple<TInputs...>, TOperators..., typename std::enable_if<true>::type> :
//        public Block<std::tuple<TInputs...>, std::tuple<double>, sizeof...(TInputs)> {
//
//        };
    }
}

#endif //LODESTAR_MULTIPLY_HPP
