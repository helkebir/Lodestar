//
// Created by Hamza El-Kebir on 6/18/21.
//

#ifndef LODESTAR_BUTCHERTABLEAU_HPP
#define LODESTAR_BUTCHERTABLEAU_HPP

#include <type_traits>
#include <tuple>
#include <array>
#include <string>
#include <string_view>
#include "aux/Indices.hpp"

namespace ls {
    namespace primitives {
        namespace detail {
            template<typename TScalarType, size_t TStages, size_t TStage, bool TIsWeights>
            struct ButcherRowImpl {
            };

            template<typename TScalarType, size_t TStages, size_t TStage>
            struct ButcherRowImpl<TScalarType, TStages, TStage, false> {
                static_assert(TStage >= 0, "Butcher tableau row number must be non-negative.");
                static_assert(TStage < (TStages - 1),
                              "Butcher tableau row number must be smaller than the number of stages minus one.");

                TScalarType node;
                std::array<TScalarType, TStage + 1> rkCoefficients;
            };

            template<typename TScalarType, size_t TStages, size_t TStage>
            struct ButcherRowImpl<TScalarType, TStages, TStage, true> {
                std::array<TScalarType, TStages> weights;
            };
        }

        template<size_t TStages, typename TScalarType = double>
        class ButcherTableau {
        public:
            static_assert(TStages > 1, "Butcher tableau must have more than one stage.");

//            operator std::string() const {
//                std::string ret;
//
//                for (int i = 0; i < (TStages - 1); i++) {
//
//                }
//            }

            template<size_t TRow, size_t TCoeffIdx>
            typename std::enable_if<(TRow < (TStages - 1)) && (TCoeffIdx < (TRow + 1)), TScalarType>::type
            getCoefficient()
            {
                return std::get<TCoeffIdx>(std::get<TRow>(rows).rkCoefficients);
            }

            template<size_t TRow, size_t TCoeffIdx>
            typename std::enable_if<!((TRow < (TStages - 1)) && (TCoeffIdx < (TRow + 1))), TScalarType>::type
            getCoefficient()
            {
                static_assert(TRow < (TStages - 1),
                              "Row index must be smaller than the number of stages minus one to access coefficients.");
                static_assert(TCoeffIdx < (TRow + 1), "Coefficient index must be less than or equal to the row index.");

                return TScalarType{};
            }

            template<size_t TRow, size_t TCoeffIdx>
            typename std::enable_if<(TRow < (TStages - 1)) && (TCoeffIdx < (TRow + 1)), void>::type
            setCoefficient(TScalarType coeff)
            {
                std::get<TCoeffIdx>(std::get<TRow>(rows).rkCoefficients) = coeff;
            }

            template<size_t TRow, size_t TCoeffIdx>
            typename std::enable_if<!((TRow < (TStages - 1)) && (TCoeffIdx < (TRow + 1))), void>::type
            setCoefficient(TScalarType coeff)
            {
                static_assert(TRow < (TStages - 1),
                              "Row index must be smaller than the number of stages minus one to access coefficients.");
                static_assert(TCoeffIdx < (TRow + 1), "Coefficient index must be less than or equal to the row index.");
            }

            template<size_t TRow>
            typename std::enable_if<TRow < (TStages - 1), TScalarType>::type
            getNode()
            {
                return std::get<TRow>(rows).node;
            }

            template<size_t TRow>
            typename std::enable_if<TRow >= (TStages - 1), TScalarType>::type
            getNode()
            {
                static_assert(TRow < (TStages - 1),
                              "Row index must be smaller than the number of stages minus one to access coefficients.");

                return TScalarType{};
            }

            template<size_t TRow>
            typename std::enable_if<TRow < (TStages - 1), void>::type
            setNode(TScalarType node)
            {
                std::get<TRow>(rows).node = node;
            }

            template<size_t TRow>
            typename std::enable_if<TRow >= (TStages - 1), void>::type
            setNode(TScalarType node)
            {
                static_assert(TRow < (TStages - 1),
                              "Row index must be smaller than the number of stages minus one to access coefficients.");
            }

            template<size_t TIdx>
            typename std::enable_if<TIdx < TStages, TScalarType>::type
            getWeight()
            {
                return std::get<TIdx>(std::get<TStages - 1>(rows).weights);
            }

            template<size_t TIdx>
            typename std::enable_if<TIdx >= TStages, TScalarType>::type
            getWeight()
            {
                static_assert(TIdx < TStages, "Weight index must be smaller than the number of stages.");

                return TScalarType{};
            }

            template<size_t TIdx>
            typename std::enable_if<TIdx < TStages, void>::type
            setWeight(TScalarType weight)
            {
                std::get<TIdx>(std::get<TStages - 1>(rows).weights) = weight;
            }

            template<size_t TIdx>
            typename std::enable_if<TIdx >= TStages, void>::type
            setWeight(TScalarType weight)
            {
                static_assert(TIdx < TStages, "Weight index must be smaller than the number of stages.");
            }

            template<size_t TStage, bool TIsWeights = (TStage == (TStages - 1))>
            using ButcherRow = detail::ButcherRowImpl<TScalarType, TStages, TStage, TIsWeights>;

        protected:
            template<int TTimes, typename TIndices = typename Indices<TTimes>::type>
            struct Rows;

            template<int TTimes, int... TIndices>
            struct Rows<TTimes, IndexSequence<TIndices...>> {
                using type = std::tuple<ButcherRow<TIndices>...>;
            };

            typename Rows<TStages>::type rows;

//            template<size_t TRow>
//            typename std::enable_if<TRow == 0, std::string>::tyoe toString(std::string s = "")
//            {
//                s += std::to_string()
//            }
//
//            template<size_t TRow>
//            typename std::enable_if<TRow == TStages, std::string>::tyoe toString(std::string s)
//            {
//
//            }

        };
    }
}

#endif //LODESTAR_BUTCHERTABLEAU_HPP
