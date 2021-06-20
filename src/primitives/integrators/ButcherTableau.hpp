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
#include <functional>
#include "aux/Indices.hpp"
#include "aux/Conjunction.hpp"

namespace ls {
    namespace primitives {
        namespace detail {
            /**
             * @brief A Butcher tableau row.
             *
             * @details There exist two partial specializations for this type: one for a regular row, which includes
             * a node and several Runge-Kutta coefficients (the exact number being depending on \c (TStage + 1)); the
             * other is a weight row, which only includes an array of \c TStages for the weights.
             *
             * @tparam TScalarType Type of the scalar coefficients.
             * @tparam TStages Number of stages in the integration scheme.
             * @tparam TStage Index of the current stage.
             * @tparam TIsWeights If true, the current row is a weight row.
             */
            template<typename TScalarType, size_t TStages, size_t TStage, bool TIsWeights>
            struct ButcherRowImpl {
            };

            /**
             * @brief Butcher tableau specialization for regular row.
             *
             * @sa ButcherRowImpl
             *
             * @tparam TScalarType Type of the scalar coefficients.
             * @tparam TStages Number of stages in the integration scheme.
             * @tparam TStage Index of the current stage.
             */
            template<typename TScalarType, size_t TStages, size_t TStage>
            struct ButcherRowImpl<TScalarType, TStages, TStage, false> {
                static_assert(TStage >= 0, "Butcher tableau row number must be non-negative.");
                static_assert(TStage < (TStages - 1),
                              "Butcher tableau row number must be smaller than the number of stages minus one.");

                TScalarType node;
                std::array<TScalarType, TStage + 1> rkCoefficients;
            };

            /**
             * @brief Butcher tableau specialization for weight row.
             *
             * @sa ButcherRowImpl
             *
             * @tparam TScalarType Type of the scalar coefficients.
             * @tparam TStages Number of stages in the integration scheme.
             * @tparam TStage Index of the current stage.
             */
            template<typename TScalarType, size_t TStages, size_t TStage>
            struct ButcherRowImpl<TScalarType, TStages, TStage, true> {
                std::array<TScalarType, TStages> weights;
            };
        }

        /**
         * @brief Implements a compile-time structure for simple/extended Butcher tableaus.
         *
         * @details Explicit methods in the Runge-Kutta family of numerical integrators can be described by the
         * following coefficient:
         * <ul>
         *      <li> Runge-Kutta coefficients \c a_ij;
         *      <li> Weights \c b_i;
         *      <li> Nodes \c c_i.
         * </ul>
         *
         *
         * @tparam TStages Number of stages in the integration scheme.
         * @tparam TExtended If true, an extended Butcher tableau is given.
         * @tparam TScalarType Type of the scalar coefficients.
         */
        template<size_t TStages, bool TExtended = true, typename TScalarType = double>
        class ButcherTableau {
            static_assert(TStages > 1, "Butcher tableau must have more than one stage.");
        };

        template<size_t TStages, typename TScalarType>
        class ButcherTableau<TStages, false, TScalarType> {
        public:
            static_assert(TStages > 1, "Butcher tableau must have more than one stage.");

            static const size_t stages = TStages; //! Number of stages.
            using type = TScalarType; //! Coefficient type.

            /**
             * @brief Alias template for \c ButcherRow.
             *
             * @tparam TStage Index of the current stage.
             * @tparam TIsWeights If true, the current row is a weight row.
             */
            template<size_t TStage, bool TIsWeights = (TStage >= (TStages - 1))>
            using ButcherRow = detail::ButcherRowImpl<TScalarType, TStages, TStage, TIsWeights>;

            /**
             * @brief Returns the Runge-Kutta coefficient for the given row number and coefficient index.
             *
             * @tparam TRow Row number (related to stage number).
             * @tparam TCoeffIdx Index of the Runge-Kutta coefficient.
             *
             * @return Runge-Kutta coefficient at (\c TRow, \c TCoeffIdx).
             */
            template<size_t TRow, size_t TCoeffIdx>
            typename std::enable_if<(TRow < (TStages - 1)) && (TCoeffIdx < (TRow + 1)), TScalarType>::type
            inline getCoefficient()
            {
                return std::get<TCoeffIdx>(std::get<TRow>(rows_).rkCoefficients);
            }

            /**
             * @brief Degenerate Runge-Kutta coefficient getter.
             *
             * @tparam TRow Row number (related to stage number).
             * @tparam TCoeffIdx Index of the Runge-Kutta coefficient.
             *
             * @return Runge-Kutta coefficient at (\c TRow, \c TCoeffIdx).
             */
            template<size_t TRow, size_t TCoeffIdx>
            typename std::enable_if<!((TRow < (TStages - 1)) && (TCoeffIdx < (TRow + 1))), TScalarType>::type
            inline getCoefficient()
            {
                static_assert(TRow < (TStages - 1),
                              "Row index must be smaller than the number of stages minus one to access coefficients.");
                static_assert(TCoeffIdx < (TRow + 1), "Coefficient index must be less than or equal to the row index.");

                return TScalarType{};
            }

            /**
             * @brief Sets the Runge-Kutta coefficient at the given row number and coefficient index.
             *
             * @tparam TRow Row number (related to stage number).
             * @tparam TCoeffIdx Index of the Runge-Kutta coefficient.
             *
             * @param coeff Coefficient value to be set.
             */
            template<size_t TRow, size_t TCoeffIdx>
            typename std::enable_if<(TRow < (TStages - 1)) && (TCoeffIdx < (TRow + 1)), void>::type
            inline setCoefficient(TScalarType coeff)
            {
                std::get<TCoeffIdx>(std::get<TRow>(rows_).rkCoefficients) = coeff;
            }

            /**
             * @brief Degenerate Runge-Kutta coefficient setter.
             *
             * @tparam TRow Row number (related to stage number).
             * @tparam TCoeffIdx Index of the Runge-Kutta coefficient.
             *
             * @param coeff Coefficient value to be set.
             */
            template<size_t TRow, size_t TCoeffIdx>
            typename std::enable_if<!((TRow < (TStages - 1)) && (TCoeffIdx < (TRow + 1))), void>::type
            inline setCoefficient(TScalarType coeff)
            {
                static_assert(TRow < (TStages - 1),
                              "Row index must be smaller than the number of stages minus one to access coefficients.");
                static_assert(TCoeffIdx < (TRow + 1), "Coefficient index must be less than or equal to the row index.");
            }

            /**
             * @brief Returns the node value for the given row number.
             *
             * @tparam TRow Row number (related to stage number).
             *
             * @return Node value of \c TRow.
             */
            template<size_t TRow>
            typename std::enable_if<TRow < (TStages - 1), TScalarType>::type
            inline getNode()
            {
                return std::get<TRow>(rows_).node;
            }

            /**
             * @brief Degenerate node getter.
             *
             * @tparam TRow Row number (related to stage number).
             *
             * @return Node value of \c TRow.
             */
            template<size_t TRow>
            typename std::enable_if<TRow >= (TStages - 1), TScalarType>::type
            inline getNode()
            {
                static_assert(TRow < (TStages - 1),
                              "Row index must be smaller than the number of stages minus one to access coefficients.");

                return TScalarType{};
            }

            /**
             * @brief Sets the node value for the given row number.
             *
             * @tparam TRow  Row number (related to stage number).
             *
             * @param node Node value to be set.
             */
            template<size_t TRow>
            typename std::enable_if<TRow < (TStages - 1), void>::type
            inline setNode(TScalarType node)
            {
                std::get<TRow>(rows_).node = node;
            }

            /**
             * @brief Degenerate node setter.
             *
             * @tparam TRow  Row number (related to stage number).
             *
             * @param node Node value to be set.
             */
            template<size_t TRow>
            typename std::enable_if<TRow >= (TStages - 1), void>::type
            inline setNode(TScalarType node)
            {
                static_assert(TRow < (TStages - 1),
                              "Row index must be smaller than the number of stages minus one to access coefficients.");
            }

            /**
             * @brief Returns the weight value at the given index.
             *
             * @tparam TIdx Weight index.
             *
             * @return Weight value at \c TIdx.
             */
            template<size_t TIdx>
            typename std::enable_if<TIdx < TStages, TScalarType>::type
            inline getWeight()
            {
                return std::get<TIdx>(std::get<TStages - 1>(rows_).weights);
            }

            /**
             * @brief Degenerate weight getter.
             *
             * @tparam TIdx Weight index.
             *
             * @return Weight value at \c TIdx.
             */
            template<size_t TIdx>
            typename std::enable_if<TIdx >= TStages, TScalarType>::type
            inline getWeight()
            {
                static_assert(TIdx < TStages, "Weight index must be smaller than the number of stages.");

                return TScalarType{};
            }

            /**
             * @brief Sets the weight value for the given index.
             *
             * @tparam TIdx Weight index.
             *
             * @param weight Weight value to be set.
             */
            template<size_t TIdx>
            typename std::enable_if<TIdx < TStages, void>::type
            inline setWeight(TScalarType weight)
            {
                std::get<TIdx>(std::get<TStages - 1>(rows_).weights) = weight;
            }

            /**
             * @brief Degenerate weight setter.
             *
             * @tparam TIdx Weight index.
             *
             * @param weight Weight value to be set.
             */
            template<size_t TIdx>
            typename std::enable_if<TIdx >= TStages, void>::type
            inline setWeight(TScalarType weight)
            {
                static_assert(TIdx < TStages, "Weight index must be smaller than the number of stages.");
            }

            /**
             * @brief Executes the explicit Runge-Kutta scheme defined in the Butcher tableau.
             *
             * @details The integration scheme integrates y'(t) = f(t, y(t)) from \c t to \c (t + h), where \c y(t) = y.
             *
             * This particular function is the entry point to run a single iteration of the Runge-Kutta scheme
             * encoded in the Butcher tableau.
             *
             * @tparam TType State type.
             * @tparam TStage Index of the current stage.
             *
             * @param f Function to be integrated.
             * @param y Initial state.
             * @param t Initial time.
             * @param h Integration step.
             *
             * @return Integrated state.
             */
            template<typename TType, size_t TStage = 0>
            typename std::enable_if<TStage == 0, TType>::type
            execute(const std::function<TType(TScalarType, TType)> &f, const TType &y, const TScalarType t,
                    const TScalarType h)
            {
                TType kCurr = f(t, y);

                return execute<TType, TStage + 1>(f, y, t, h, kCurr);
            }

            /**
             * @brief Executes the explicit Runge-Kutta scheme defined in the Butcher tableau.
             *
             * @details The integration scheme integrates y'(t) = f(t, y(t)) from \c t to \c (t + h), where \c y(t) = y.
             *
             * This particular function deals with the regular stages of the integration scheme.
             *
             * @tparam TType State type.
             * @tparam TStage Index of the current stage.
             *
             * @param f Function to be integrated.
             * @param y Initial state.
             * @param t Initial time.
             * @param h Integration step.
             *
             * @return Integrated state.
             */
            template<typename TType, size_t TStage = 0, typename... TArgs>
            typename std::enable_if<(TStage > 0) && (TStage < TStages) &&
                                    (Conjunction<std::is_convertible<TArgs, TType>...>::value), TType>::type
            inline execute(const std::function<TType(TScalarType, TType)> &f, const TType &y, const TScalarType t,
                           const TScalarType h,
                           TArgs... vars)
            {
                TType kCurr{}, yCurr = y;

                yCurr += h * sumCoefficients<TType, TStage>(vars...);
                TScalarType tCurr = t + getNode<TStage - 1>() * h;

                kCurr = f(tCurr, yCurr);

                return execute<TType, TStage + 1>(f, y, t, h, vars..., kCurr);
            }

            /**
             * @brief Executes the explicit Runge-Kutta scheme defined in the Butcher tableau.
             *
             * @details The integration scheme integrates y'(t) = f(t, y(t)) from \c t to \c (t + h), where \c y(t) = y.
             *
             * This particular function deals with the final stage of the integration scheme.
             *
             * @tparam TType State type.
             * @tparam TStage Index of the current stage.
             *
             * @param f Function to be integrated.
             * @param y Initial state.
             * @param t Initial time.
             * @param h Integration step.
             *
             * @return Integrated state.
             */
            template<typename TType, size_t TStage = 0, typename... TArgs>
            typename std::enable_if<(TStage > 0) && (TStage == TStages) &&
                                    (Conjunction<std::is_convertible<TArgs, TType>...>::value), TType>::type
            inline execute(const std::function<TType(TScalarType, TType)> &f, const TType &y, const TScalarType t,
                           const TScalarType h,
                           TArgs... vars)
            {
                TType yFinal = y;
                yFinal += h * sumWeights<TType>(vars...);

                return yFinal;
            }

        protected:
            /**
             * Helper struct that will define a tuple of specialized Butcher rows.
             *
             * @sa Repeat
             * @sa Indices
             *
             * @tparam TTimes Number of times the generator must be ran.
             * @tparam TIndices An \c IndexSequence type.
             */
            template<int TTimes, typename TIndices = typename Indices<TTimes>::type>
            struct Rows;

            /**
             * @brief Partial specialization of the \c Rows struct, which defines a tuple of specialized Butcher rows.
             *
             * @tparam TTimes Number of times the generator must be ran.
             * @tparam TIndices Template pack of integers (from 0 to TTimes - 1 by default).
             */
            template<int TTimes, int... TIndices>
            struct Rows<TTimes, IndexSequence<TIndices...>> {
                using type = std::tuple<ButcherRow<TIndices>...>;
            };

            typename Rows<TStages>::type rows_; //! Rows of the Butcher tableau.

            /**
             * @brief Sums Runge-Kutta coefficients multiplied with results from previous stages.
             *
             * @details This function computes sum_(j=0)^i a_ij * k_i, where i is \c TStage.
             *
             * @tparam TType State type.
             * @tparam TStage Index of the current stage.
             * @tparam TArgs Parameter pack of argument (previous stage result) types.
             * @tparam TIndex Typename of the \c Indices object.
             *
             * @param vars Variadic argument list of results of previous stages.
             *
             * @return Sum.
             */
            template<typename TType, size_t TStage = 0, typename... TArgs, typename TIndex = typename Indices<sizeof...(TArgs)>::type>
            typename std::enable_if<
                    (TStage > 0) && (TStage < TStages) &&
                    (Conjunction<std::is_convertible<TArgs, TType>...>::value), TType>::type
            inline sumCoefficients(TArgs... vars)
            {
                return sumCoefficientsImpl<TType, TStage - 1>(TIndex{}, vars...);
            }

            /**
             * @brief Implementation of \c sumCoefficients.
             *
             * @note This separate implementation is required to extract the list of indices at compile time.
             *
             * @tparam TType State type.
             * @tparam TStage Index of the current stage.
             * @tparam TArgs Parameter pack of argument (previous stage result) types.
             * @tparam TIndices Parameter pack of indices.
             *
             * @param vars Variadic argument list of results of previous stages.
             *
             * @return Sum.
             */
            template<typename TType, size_t TStage = 0, typename... TArgs, int... TIndices>
            TType
            inline sumCoefficientsImpl(IndexSequence<TIndices...>, TArgs... vars)
            {
                return sum<TType>((getCoefficient<TStage, (size_t) TIndices>() * vars)...);
            }

            /**
             * @brief Sums weight coefficients multiplied with results from previous stages.
             *
             * @tparam TType State type.
             * @tparam TArgs Parameter pack of argument (previous stage result) types
             * @tparam TIndex TIndex Typename of the \c Indices object.
             *
             * @param vars Variadic argument list of results of previous stages.
             *
             * @return Sum.
             */
            template<typename TType, typename... TArgs, typename TIndex = typename Indices<sizeof...(TArgs)>::type>
            typename std::enable_if<(Conjunction<std::is_convertible<TArgs, TType>...>::value), TType>::type
            inline sumWeights(TArgs... vars)
            {
                return sumWeightsImpl<TType>(TIndex{}, vars...);
            }

            /**
             * @brief Implementation of \c sumWeights.
             *
             * @note This separate implementation is required to extract the list of indices at compile time.
             *
             * @tparam TType State type.
             * @tparam TArgs Parameter pack of argument (previous stage result) types.
             * @tparam TIndices Parameter pack of indices.
             *
             * @param vars Variadic argument list of results of previous stages.
             *
             * @return Sum.
             */
            template<typename TType, typename... TArgs, int... TIndices>
            TType
            inline sumWeightsImpl(IndexSequence<TIndices...>, TArgs... vars)
            {
                return sum<TType>((getWeight<(size_t) TIndices>() * vars)...);
            }

            /**
             * @brief Helper function that sums arguments.
             *
             * @details This particular function is the base case, which simply returns the value that it was given.
             *
             * @tparam TType State type.
             * @tparam TArg Argument type.
             *
             * @param var Argument.
             *
             * @return Argument.
             */
            template<typename TType, typename TArg>
            typename std::enable_if<std::is_convertible<TArg, TType>::value, TType>::type
            inline sum(TArg var)
            {
                return var;
            }

            /**
             * @brief Degenerate case of helper function that sums arguments.
             *
             * @details This function checks convertibility of the argument type to \c TType.
             *
             * @tparam TType State type.
             * @tparam TArg Argument type.
             *
             * @param var Argument.
             */
            template<typename TType, typename TArg>
            typename std::enable_if<!std::is_convertible<TArg, TType>::value, TType>::type
            inline sum(TArg var)
            {
                static_assert(std::is_convertible<TArg, TType>::value, "Summed values must be convertible.");
                return var;
            }

            /**
             * @brief Helper function that sums arguments.
             *
             * @tparam TType State type.
             * @tparam TArg First argument type.
             * @tparam TArgs Template pack of variadic argument list typenames.
             *
             * @param var First argument.
             * @param vars Variadic arguments.
             *
             * @return Sum.
             */
            template<typename TType, typename TArg, typename... TArgs>
            typename std::enable_if<std::is_convertible<TArg, TType>::value &&
                    (Conjunction<std::is_convertible<TArgs, TType>...>::value), TType>::type
            inline sum(TArg var, TArgs... vars)
            {
                return var + sum<TType>(vars...);
            }

            /**
             * @brief Degenerate case of helper function that sums arguments.
             *
             * @tparam TType State type.
             * @tparam TArg First argument type.
             * @tparam TArgs Template pack of variadic argument list typenames.
             *
             * @param var First argument.
             * @param vars Variadic arguments.
             */
            template<typename TType, typename TArg, typename... TArgs>
            typename std::enable_if<!(std::is_convertible<TArg, TType>::value &&
                                      (Conjunction<std::is_convertible<TArgs, TType>...>::value)), TType>::type
            inline sum(TArg var, TArgs... vars)
            {
                static_assert(std::is_convertible<TArg, TType>::value &&
                              (Conjunction<std::is_convertible<TArgs, TType>...>::value),
                              "Summed values must be convertible.");

                return var + sum<TType>(vars...);
            }
        };

// --------------- Extended Butcher tableau -----------------------

        /**
         * @brief Implements a compile-time structure for extended Butcher tableaus.
         *
         * @details Explicit methods in the Runge-Kutta family of numerical integrators can be described by the
         * following coefficient:
         * <ul>
         *      <li> Runge-Kutta coefficients \c a_ij;
         *      <li> Weights \c b_i;
         *      <li> Nodes \c c_i.
         * </ul>
         *
         *
         * @tparam TStages Number of stages in the integration scheme.
         * @tparam TScalarType Type of the scalar coefficients.
         */
        template<size_t TStages, typename TScalarType>
        class ButcherTableau<TStages, true, TScalarType> {
        public:
            static_assert(TStages > 1, "Butcher tableau must have more than one stage.");

            static const size_t stages = TStages; //! Number of stages.
            using type = TScalarType; //! Coefficient type.

            /**
             * @brief Alias template for \c ButcherRow.
             *
             * @tparam TStage Index of the current stage.
             * @tparam TIsWeights If true, the current row is a weight row.
             */
            template<size_t TStage, bool TIsWeights = (TStage >= (TStages - 1))>
            using ButcherRow = detail::ButcherRowImpl<TScalarType, TStages, TStage, TIsWeights>;

            /**
             * @brief Returns the Runge-Kutta coefficient for the given row number and coefficient index.
             *
             * @tparam TRow Row number (related to stage number).
             * @tparam TCoeffIdx Index of the Runge-Kutta coefficient.
             *
             * @return Runge-Kutta coefficient at (\c TRow, \c TCoeffIdx).
             */
            template<size_t TRow, size_t TCoeffIdx>
            typename std::enable_if<(TRow < (TStages - 1)) && (TCoeffIdx < (TRow + 1)), TScalarType>::type
            inline getCoefficient()
            {
                return std::get<TCoeffIdx>(std::get<TRow>(rows_).rkCoefficients);
            }

            /**
             * @brief Degenerate Runge-Kutta coefficient getter.
             *
             * @tparam TRow Row number (related to stage number).
             * @tparam TCoeffIdx Index of the Runge-Kutta coefficient.
             *
             * @return Runge-Kutta coefficient at (\c TRow, \c TCoeffIdx).
             */
            template<size_t TRow, size_t TCoeffIdx>
            typename std::enable_if<!((TRow < (TStages - 1)) && (TCoeffIdx < (TRow + 1))), TScalarType>::type
            inline getCoefficient()
            {
                static_assert(TRow < (TStages - 1),
                              "Row index must be smaller than the number of stages minus one to access coefficients.");
                static_assert(TCoeffIdx < (TRow + 1), "Coefficient index must be less than or equal to the row index.");

                return TScalarType{};
            }

            /**
             * @brief Sets the Runge-Kutta coefficient at the given row number and coefficient index.
             *
             * @tparam TRow Row number (related to stage number).
             * @tparam TCoeffIdx Index of the Runge-Kutta coefficient.
             *
             * @param coeff Coefficient value to be set.
             */
            template<size_t TRow, size_t TCoeffIdx>
            typename std::enable_if<(TRow < (TStages - 1)) && (TCoeffIdx < (TRow + 1)), void>::type
            inline setCoefficient(TScalarType coeff)
            {
                std::get<TCoeffIdx>(std::get<TRow>(rows_).rkCoefficients) = coeff;
            }

            /**
             * @brief Degenerate Runge-Kutta coefficient setter.
             *
             * @tparam TRow Row number (related to stage number).
             * @tparam TCoeffIdx Index of the Runge-Kutta coefficient.
             *
             * @param coeff Coefficient value to be set.
             */
            template<size_t TRow, size_t TCoeffIdx>
            typename std::enable_if<!((TRow < (TStages - 1)) && (TCoeffIdx < (TRow + 1))), void>::type
            inline setCoefficient(TScalarType coeff)
            {
                static_assert(TRow < (TStages - 1),
                              "Row index must be smaller than the number of stages minus one to access coefficients.");
                static_assert(TCoeffIdx < (TRow + 1), "Coefficient index must be less than or equal to the row index.");
            }

            /**
             * @brief Returns the node value for the given row number.
             *
             * @tparam TRow Row number (related to stage number).
             *
             * @return Node value of \c TRow.
             */
            template<size_t TRow>
            typename std::enable_if<TRow < (TStages - 1), TScalarType>::type
            inline getNode()
            {
                return std::get<TRow>(rows_).node;
            }

            /**
             * @brief Degenerate node getter.
             *
             * @tparam TRow Row number (related to stage number).
             *
             * @return Node value of \c TRow.
             */
            template<size_t TRow>
            typename std::enable_if<TRow >= (TStages - 1), TScalarType>::type
            inline getNode()
            {
                static_assert(TRow < (TStages - 1),
                              "Row index must be smaller than the number of stages minus one to access coefficients.");

                return TScalarType{};
            }

            /**
             * @brief Sets the node value for the given row number.
             *
             * @tparam TRow  Row number (related to stage number).
             *
             * @param node Node value to be set.
             */
            template<size_t TRow>
            typename std::enable_if<TRow < (TStages - 1), void>::type
            inline setNode(TScalarType node)
            {
                std::get<TRow>(rows_).node = node;
            }

            /**
             * @brief Degenerate node setter.
             *
             * @tparam TRow  Row number (related to stage number).
             *
             * @param node Node value to be set.
             */
            template<size_t TRow>
            typename std::enable_if<TRow >= (TStages - 1), void>::type
            inline setNode(TScalarType node)
            {
                static_assert(TRow < (TStages - 1),
                              "Row index must be smaller than the number of stages minus one to access coefficients.");
            }

            /**
             * @brief Returns the weight value at the given index.
             *
             * @details This function gets the higher order weight.
             *
             * @tparam TIdx Weight index.
             * @tparam THigherOrder If true, the higher order weights are retrieved.
             *
             * @return Weight value at \c TIdx.
             */
            template<size_t TIdx, bool THigherOrder = true>
            typename std::enable_if<(TIdx < TStages) && THigherOrder, TScalarType>::type
            inline getWeight()
            {
                return std::get<TIdx>(std::get<TStages - 1>(rows_).weights);
            }

            /**
             * @brief Returns the weight value at the given index.
             *
             * @details This function gets the lower order weight.
             *
             * @tparam TIdx Weight index.
             * @tparam THigherOrder If true, the higher order weights are retrieved.
             *
             * @return Weight value at \c TIdx.
             */
            template<size_t TIdx, bool THigherOrder = true>
            typename std::enable_if<(TIdx < TStages) && !THigherOrder, TScalarType>::type
            inline getWeight()
            {
                return std::get<TIdx>(std::get<TStages>(rows_).weights);
            }

            /**
             * @brief Degenerate weight getter.
             *
             * @tparam TIdx Weight index.
             * @tparam THigherOrder If true, the higher order weights are retrieved.
             *
             * @return Weight value at \c TIdx.
             */
            template<size_t TIdx, bool THigherOrder = true>
            typename std::enable_if<TIdx >= TStages, TScalarType>::type
            inline getWeight()
            {
                static_assert(TIdx < TStages, "Weight index must be smaller than the number of stages.");

                return TScalarType{};
            }

            /**
             * @brief Sets the weight value for the given index.
             *
             * @details This function sets the higher order weight.
             *
             * @tparam TIdx Weight index.
             * @tparam THigherOrder If true, the higher order weights are changed.
             *
             * @param weight Weight value to be set.
             */
            template<size_t TIdx, bool THigherOrder = true>
            typename std::enable_if<(TIdx < TStages) && THigherOrder, void>::type
            inline setWeight(TScalarType weight)
            {
                std::get<TIdx>(std::get<TStages - 1>(rows_).weights) = weight;
            }

            /**
             * @brief Sets the weight value for the given index.
             *
             * @details This function sets the lower order weight.
             *
             * @tparam TIdx Weight index.
             * @tparam THigherOrder If true, the higher order weights are changed.
             *
             * @param weight Weight value to be set.
             */
            template<size_t TIdx, bool THigherOrder = true>
            typename std::enable_if<(TIdx < TStages) && !THigherOrder, void>::type
            inline setWeight(TScalarType weight)
            {
                std::get<TIdx>(std::get<TStages>(rows_).weights) = weight;
            }

            /**
             * @brief Degenerate weight setter.
             *
             * @tparam TIdx Weight index.
             * @tparam THigherOrder If true, the higher order weights are changed.
             *
             * @param weight Weight value to be set.
             */
            template<size_t TIdx, bool THigherOrder = true>
            typename std::enable_if<TIdx >= TStages, void>::type
            inline setWeight(TScalarType weight)
            {
                static_assert(TIdx < TStages, "Weight index must be smaller than the number of stages.");
            }

            /**
             * @brief Executes the explicit Runge-Kutta scheme defined in the Butcher tableau.
             *
             * @details The integration scheme integrates y'(t) = f(t, y(t)) from \c t to \c (t + h), where \c y(t) = y.
             *
             * This particular function is the entry point to run a single iteration of the Runge-Kutta scheme
             * encoded in the Butcher tableau.
             *
             * @tparam TType State type.
             * @tparam TStage Index of the current stage.
             * @tparam TIsEmbedded If true, the execution considers and embedded scheme.
             *
             * @param f Function to be integrated.
             * @param y Initial state.
             * @param t Initial time.
             * @param h Integration step.
             *
             * @return Integrated state.
             */
            template<typename TType, size_t TStage = 0, bool TIsEmbedded = false>
            typename std::enable_if<(TStage == 0) && !TIsEmbedded, TType>::type
            execute(const std::function<TType(TScalarType, TType)> &f, const TType &y, const TScalarType t,
                    const TScalarType h)
            {
                TType kCurr = f(t, y);

                return execute<TType, TStage + 1, TIsEmbedded>(f, y, t, h, kCurr);
            }

            /**
             * @brief Executes the explicit Runge-Kutta scheme defined in the Butcher tableau.
             *
             * @details The integration scheme integrates y'(t) = f(t, y(t)) from \c t to \c (t + h), where \c y(t) = y.
             *
             * This particular function is the entry point to run a single iteration of the Runge-Kutta scheme
             * encoded in the Butcher tableau.
             *
             * @tparam TType State type.
             * @tparam TStage Index of the current stage.
             * @tparam TIsEmbedded If true, the execution considers an embedded scheme.
             *
             * @param f Function to be integrated.
             * @param y Initial state.
             * @param t Initial time.
             * @param h Integration step.
             *
             * @return Pair of integrated state (with higher-order scheme) and error.
             */
            template<typename TType, size_t TStage = 0, bool TIsEmbedded = false>
            typename std::enable_if<(TStage == 0) && TIsEmbedded, std::pair<TType, TType>>::type
            execute(const std::function<TType(TScalarType, TType)> &f, const TType &y, const TScalarType t,
                    const TScalarType h)
            {
                TType kCurr = f(t, y);

                return execute<TType, TStage + 1, TIsEmbedded>(f, y, t, h, kCurr);
            }

            /**
             * @brief Executes the explicit Runge-Kutta scheme defined in the Butcher tableau.
             *
             * @details The integration scheme integrates y'(t) = f(t, y(t)) from \c t to \c (t + h), where \c y(t) = y.
             *
             * This particular function deals with the regular stages of the integration scheme.
             *
             * @tparam TType State type.
             * @tparam TStage Index of the current stage.
             * @tparam TIsEmbedded If true, the execution considers an embedded scheme.
             *
             * @param f Function to be integrated.
             * @param y Initial state.
             * @param t Initial time.
             * @param h Integration step.
             *
             * @return Integrated state.
             */
            template<typename TType, size_t TStage = 0, bool TIsEmbedded = false, typename... TArgs>
            typename std::enable_if<(TStage > 0) && (TStage < TStages) && !TIsEmbedded &&
                                    (Conjunction<std::is_convertible<TArgs, TType>...>::value), TType>::type
            execute(const std::function<TType(TScalarType, TType)> &f, const TType &y, const TScalarType t,
                    const TScalarType h,
                    TArgs... vars)
            {
                TType kCurr{}, yCurr = y;

                yCurr += h * sumCoefficients<TType, TStage>(vars...);
                TScalarType tCurr = t + getNode<TStage - 1>() * h;

                kCurr = f(tCurr, yCurr);

                return execute<TType, TStage + 1, TIsEmbedded>(f, y, t, h, vars..., kCurr);
            }

            /**
             * @brief Executes the explicit Runge-Kutta scheme defined in the Butcher tableau.
             *
             * @details The integration scheme integrates y'(t) = f(t, y(t)) from \c t to \c (t + h), where \c y(t) = y.
             *
             * This particular function deals with the regular stages of the integration scheme.
             *
             * @tparam TType State type.
             * @tparam TStage Index of the current stage.
             * @tparam TIsEmbedded If true, the execution considers an embedded scheme.
             *
             * @param f Function to be integrated.
             * @param y Initial state.
             * @param t Initial time.
             * @param h Integration step.
             *
             * @return Pair of integrated state (with higher-order scheme) and error.
             */
            template<typename TType, size_t TStage = 0, bool TIsEmbedded = false, typename... TArgs>
            typename std::enable_if<(TStage > 0) && (TStage < TStages) && TIsEmbedded &&
                                    (Conjunction<std::is_convertible<TArgs, TType>...>::value), std::pair<TType, TType>>::type
            inline execute(const std::function<TType(TScalarType, TType)> &f, const TType &y, const TScalarType t,
                           const TScalarType h,
                           TArgs... vars)
            {
                TType kCurr{}, yCurr = y;

                yCurr += h * sumCoefficients<TType, TStage>(vars...);
                TScalarType tCurr = t + getNode<TStage - 1>() * h;

                kCurr = f(tCurr, yCurr);

                return execute<TType, TStage + 1, TIsEmbedded>(f, y, t, h, vars..., kCurr);
            }

            /**
             * @brief Executes the explicit Runge-Kutta scheme defined in the Butcher tableau.
             *
             * @details The integration scheme integrates y'(t) = f(t, y(t)) from \c t to \c (t + h), where \c y(t) = y.
             *
             * This particular function deals with the final stage of the integration scheme.
             *
             * @tparam TType State type.
             * @tparam TStage Index of the current stage.
             * @tparam TIsEmbedded If true, the execution considers an embedded scheme.
             *
             * @param f Function to be integrated.
             * @param y Initial state.
             * @param t Initial time.
             * @param h Integration step.
             *
             * @return Integrated state.
             */
            template<typename TType, size_t TStage = 0, bool TIsEmbedded = false, typename... TArgs>
            typename std::enable_if<(TStage > 0) && (TStage == TStages) && !TIsEmbedded &&
                                    (Conjunction<std::is_convertible<TArgs, TType>...>::value), TType>::type
            inline execute(const std::function<TType(TScalarType, TType)> &f, const TType &y, const TScalarType t,
                           const TScalarType h,
                           TArgs... vars)
            {
                TType yFinal = y;
                yFinal += h * sumWeights<TType>(vars...);

                return yFinal;
            }

            /**
             * @brief Executes the explicit Runge-Kutta scheme defined in the Butcher tableau.
             *
             * @details The integration scheme integrates y'(t) = f(t, y(t)) from \c t to \c (t + h), where \c y(t) = y.
             *
             * This particular function deals with the final stage of the integration scheme.
             *
             * @tparam TType State type.
             * @tparam TStage Index of the current stage.
             * @tparam TIsEmbedded If true, the execution considers an embedded scheme.
             *
             * @param f Function to be integrated.
             * @param y Initial state.
             * @param t Initial time.
             * @param h Integration step.
             *
             * @return Pair of integrated state (with higher-order scheme) and error.
             */
            template<typename TType, size_t TStage = 0, bool TIsEmbedded = false, typename... TArgs>
            typename std::enable_if<(TStage > 0) && (TStage == TStages) && TIsEmbedded &&
                                    (Conjunction<std::is_convertible<TArgs, TType>...>::value), std::pair<TType, TType>>::type
            inline execute(const std::function<TType(TScalarType, TType)> &f, const TType &y, const TScalarType t,
                           const TScalarType h,
                           TArgs... vars)
            {
                TType yFinal = y;
                TType summedWeightsHigher = sumWeights<TType, true>(vars...);
                TType summedWeightsLower = sumWeights<TType, false>(vars...);
                yFinal += h * summedWeightsHigher;

                std::pair<TType, TType> pair{yFinal, h * (summedWeightsHigher - summedWeightsLower)};

                return pair;
            }

        protected:
            /**
             * Helper struct that will define a tuple of specialized Butcher rows.
             *
             * @sa Repeat
             * @sa Indices
             *
             * @tparam TTimes Number of times the generator must be ran.
             * @tparam TIndices An \c IndexSequence type.
             */
            template<int TTimes, typename TIndices = typename Indices<TTimes>::type>
            struct Rows;

            /**
             * @brief Partial specialization of the \c Rows struct, which defines a tuple of specialized Butcher rows.
             *
             * @tparam TTimes Number of times the generator must be ran.
             * @tparam TIndices Template pack of integers (from 0 to TTimes - 1 by default).
             */
            template<int TTimes, int... TIndices>
            struct Rows<TTimes, IndexSequence<TIndices...>> {
                using type = std::tuple<ButcherRow<TIndices>...>;
            };

            typename Rows<TStages + 1>::type rows_; //! Rows of the Butcher tableau.

            /**
             * @brief Sums Runge-Kutta coefficients multiplied with results from previous stages.
             *
             * @details This function computes sum_(j=0)^i a_ij * k_i, where i is \c TStage.
             *
             * @tparam TType State type.
             * @tparam TStage Index of the current stage.
             * @tparam TArgs Parameter pack of argument (previous stage result) types.
             * @tparam TIndex Typename of the \c Indices object.
             *
             * @param vars Variadic argument list of results of previous stages.
             *
             * @return Sum.
             */
            template<typename TType, size_t TStage = 0, typename... TArgs, typename TIndex = typename Indices<sizeof...(TArgs)>::type>
            typename std::enable_if<
                    (TStage > 0) && (TStage < TStages) &&
                    (Conjunction<std::is_convertible<TArgs, TType>...>::value), TType>::type
            inline sumCoefficients(TArgs... vars)
            {
                return sumCoefficientsImpl<TType, TStage - 1>(TIndex{}, vars...);
            }

            /**
             * @brief Implementation of \c sumCoefficients.
             *
             * @note This separate implementation is required to extract the list of indices at compile time.
             *
             * @tparam TType State type.
             * @tparam TStage Index of the current stage.
             * @tparam TArgs Parameter pack of argument (previous stage result) types.
             * @tparam TIndices Parameter pack of indices.
             *
             * @param vars Variadic argument list of results of previous stages.
             *
             * @return Sum.
             */
            template<typename TType, size_t TStage = 0, typename... TArgs, int... TIndices>
            TType
            inline sumCoefficientsImpl(IndexSequence<TIndices...>, TArgs... vars)
            {
                return sum<TType>((getCoefficient<TStage, (size_t) TIndices>() * vars)...);
            }

            /**
             * @brief Sums weight coefficients multiplied with results from previous stages.
             *
             * @tparam TType State type.
             * @tparam THigherOrder If true, higher order weights are used.
             * @tparam TArgs Parameter pack of argument (previous stage result) types
             * @tparam TIndex TIndex Typename of the \c Indices object.
             *
             * @param vars Variadic argument list of results of previous stages.
             *
             * @return Sum.
             */
            template<typename TType, bool THigherOrder = true, typename... TArgs, typename TIndex = typename Indices<sizeof...(TArgs)>::type>
            typename std::enable_if<(Conjunction<std::is_convertible<TArgs, TType>...>::value), TType>::type
            inline sumWeights(TArgs... vars)
            {
                return sumWeightsImpl<TType, THigherOrder>(TIndex{}, vars...);
            }

            /**
             * @brief Implementation of \c sumWeights.
             *
             * @note This separate implementation is required to extract the list of indices at compile time.
             *
             * @tparam TType State type.
             * @tparam THigherOrder If true, higher order weights are used.
             * @tparam TArgs Parameter pack of argument (previous stage result) types.
             * @tparam TIndices Parameter pack of indices.
             *
             * @param vars Variadic argument list of results of previous stages.
             *
             * @return Sum.
             */
            template<typename TType, bool THigherOrder, typename... TArgs, int... TIndices>
            typename std::enable_if<THigherOrder, TType>::type
            inline sumWeightsImpl(IndexSequence<TIndices...>, TArgs... vars)
            {
                return sum<TType>((getWeight<(size_t) TIndices, true>() * vars)...);
            }

            /**
             * @brief Implementation of \c sumWeights.
             *
             * @note This separate implementation is required to extract the list of indices at compile time.
             *
             * @tparam TType State type.
             * @tparam THigherOrder If true, higher order weights are used.
             * @tparam TArgs Parameter pack of argument (previous stage result) types.
             * @tparam TIndices Parameter pack of indices.
             *
             * @param vars Variadic argument list of results of previous stages.
             *
             * @return Sum.
             */
            template<typename TType, bool THigherOrder, typename... TArgs, int... TIndices>
            typename std::enable_if<!THigherOrder, TType>::type
            inline sumWeightsImpl(IndexSequence<TIndices...>, TArgs... vars)
            {
                return sum<TType>((getWeight<(size_t) TIndices, false>() * vars)...);
            }

            /**
             * @brief Helper function that sums arguments.
             *
             * @details This particular function is the base case, which simply returns the value that it was given.
             *
             * @tparam TType State type.
             * @tparam TArg Argument type.
             *
             * @param var Argument.
             *
             * @return Argument.
             */
            template<typename TType, typename TArg>
            typename std::enable_if<std::is_convertible<TArg, TType>::value, TType>::type
            inline sum(TArg var)
            {
                return var;
            }

            /**
             * @brief Degenerate case of helper function that sums arguments.
             *
             * @details This function checks convertibility of the argument type to \c TType.
             *
             * @tparam TType State type.
             * @tparam TArg Argument type.
             *
             * @param var Argument.
             */
            template<typename TType, typename TArg>
            typename std::enable_if<!std::is_convertible<TArg, TType>::value, TType>::type
            inline sum(TArg var)
            {
                static_assert(std::is_convertible<TArg, TType>::value, "Summed values must be convertible.");
                return var;
            }

            /**
             * @brief Helper function that sums arguments.
             *
             * @tparam TType State type.
             * @tparam TArg First argument type.
             * @tparam TArgs Template pack of variadic argument list typenames.
             *
             * @param var First argument.
             * @param vars Variadic arguments.
             *
             * @return Sum.
             */
            template<typename TType, typename TArg, typename... TArgs>
            typename std::enable_if<std::is_convertible<TArg, TType>::value &&
                    (Conjunction<std::is_convertible<TArgs, TType>...>::value), TType>::type
            inline sum(TArg var, TArgs... vars)
            {
                return var + sum<TType>(vars...);
            }

            /**
             * @brief Degenerate case of helper function that sums arguments.
             *
             * @tparam TType State type.
             * @tparam TArg First argument type.
             * @tparam TArgs Template pack of variadic argument list typenames.
             *
             * @param var First argument.
             * @param vars Variadic arguments.
             */
            template<typename TType, typename TArg, typename... TArgs>
            typename std::enable_if<!(std::is_convertible<TArg, TType>::value &&
                                      (Conjunction<std::is_convertible<TArgs, TType>...>::value)), TType>::type
            inline sum(TArg var, TArgs... vars)
            {
                static_assert(std::is_convertible<TArg, TType>::value &&
                              (Conjunction<std::is_convertible<TArgs, TType>...>::value),
                              "Summed values must be convertible.");

                return var + sum<TType>(vars...);
            }
        };
    }
}

#endif //LODESTAR_BUTCHERTABLEAU_HPP
