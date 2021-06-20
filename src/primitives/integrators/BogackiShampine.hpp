//
// Created by Hamza El-Kebir on 6/18/21.
//

#ifndef LODESTAR_BOGACKISHAMPINE_HPP
#define LODESTAR_BOGACKISHAMPINE_HPP

#include "primitives/integrators/ButcherTableau.hpp"

namespace ls {
    namespace primitives {
        namespace detail {

            class BogackiShampineImpl {
                friend class BogackiShampine;

            protected:
                BogackiShampineImpl()
                {
                    btSimple.setNode<0>(1.0 / 2.0);
                    btSimple.setCoefficient<0, 0>(1.0 / 2.0);

                    btSimple.setNode<1>(3.0 / 4.0);
                    btSimple.setCoefficient<1, 0>(0.0);
                    btSimple.setCoefficient<1, 1>(3.0 / 4.0);

                    btSimple.setNode<2>(1.0);
                    btSimple.setCoefficient<2, 0>(2.0 / 9.0);
                    btSimple.setCoefficient<2, 1>(1.0 / 3.0);
                    btSimple.setCoefficient<2, 2>(4.0 / 9.0);

                    btSimple.setWeight<0>(2.0 / 9.0);
                    btSimple.setWeight<1>(1.0 / 3.0);
                    btSimple.setWeight<2>(4.0 / 9.0);
                    btSimple.setWeight<3>(0.0);

                    btExtended.setNode<0>(1.0 / 2.0);
                    btExtended.setCoefficient<0, 0>(1.0 / 2.0);

                    btExtended.setNode<1>(3.0 / 4.0);
                    btExtended.setCoefficient<1, 0>(0.0);
                    btExtended.setCoefficient<1, 1>(3.0 / 4.0);

                    btExtended.setNode<2>(1.0);
                    btExtended.setCoefficient<2, 0>(2.0 / 9.0);
                    btExtended.setCoefficient<2, 1>(1.0 / 3.0);
                    btExtended.setCoefficient<2, 2>(4.0 / 9.0);

                    btExtended.setWeight<0, true>(2.0 / 9.0);
                    btExtended.setWeight<1, true>(1.0 / 3.0);
                    btExtended.setWeight<2, true>(4.0 / 9.0);
                    btExtended.setWeight<3, true>(0.0);

                    btExtended.setWeight<0, false>(7.0 / 24.0);
                    btExtended.setWeight<1, false>(1.0 / 4.0);
                    btExtended.setWeight<2, false>(1.0 / 3.0);
                    btExtended.setWeight<3, false>(1.0 / 8.0);
                }

                ls::primitives::ButcherTableau<4, false> btSimple;
                ls::primitives::ButcherTableau<4, true> btExtended;
            };

            class BogackiShampine {
            public:
                static ls::primitives::ButcherTableau<4, true> &getButcherTableau()
                {
                    static BogackiShampineImpl *boshImpl = new BogackiShampineImpl();

                    return boshImpl->btExtended;
                }

                static ls::primitives::ButcherTableau<4, false> &getButcherTableauSimple()
                {
                    static BogackiShampineImpl *boshImpl = new BogackiShampineImpl();

                    return boshImpl->btSimple;
                }

            private:
                BogackiShampine() = default;

                // Delete copy/move so extra instances can't be created/moved.
                BogackiShampine(const BogackiShampine &) = delete;

                BogackiShampine &operator=(const BogackiShampine &) = delete;

                BogackiShampine(BogackiShampine &&) = delete;

                BogackiShampine &operator=(BogackiShampine &&) = delete;
            };
        }

        template<typename TType, typename TScalarType = double>
        class BogackiShampine {
        public:
            typedef std::function<TType(TScalarType, TType)> TDFunction;

            static const short int kLowerErrorOrder = 2;
            static const short int kLigherErrorOrder = 3;
            static const short int kStages = 4;

            /**
             * @brief Simple integration using the third-order scheme in the Bogacki-Shampine method.
             *
             * @param f Function to be integrated.
             * @param t Initial time.
             * @param y Initial state.
             * @param h Integration step.
             * @param N Number of integration scheme executions.
             */
            static void integrateSimple(TDFunction f, TScalarType &t, TType &y, TScalarType h, size_t N = 1);

            /**
             * @brief Integrate using the Bogacki-Shampine method (ode23) with truncation error output.
             *
             * @param f Function to be integrated.
             * @param t Initial time.
             * @param y Initial state.
             * @param h Integration step.
             * @param N Number of integration scheme executions.
             *
             * @return Local truncation error.
             */
            static TType integrateEmbedded(TDFunction f, TScalarType &t, TType &y, TScalarType h, size_t N = 1);

            // TODO: Add integrate function with maximum allowable error (adaptive step size).
        };

        template<typename TType, typename TScalarType>
        void BogackiShampine<TType, TScalarType>::integrateSimple(TDFunction f, TScalarType &t, TType &y, const TScalarType h,
                                                            size_t N)
        {
            for (int i = 0; i < N; i++) {
                y = detail::BogackiShampine::getButcherTableauSimple().template execute(f, y, t, h);
                t += h;
            }
        }

        template<typename TType, typename TScalarType>
        TType BogackiShampine<TType, TScalarType>::integrateEmbedded(TDFunction f, TScalarType &t, TType &y,
                                                                     const TScalarType h, size_t N)
        {
            std::pair<TType, TType> ye;
            for (int i = 0; i < N; i++) {
                ye = detail::BogackiShampine::getButcherTableau().template execute<TType, 0, true>(f, y, t, h);
                y = ye.first;
                t += h;
            }

            return ye.second;
        }
    }
}

#endif //LODESTAR_BOGACKISHAMPINE_HPP
