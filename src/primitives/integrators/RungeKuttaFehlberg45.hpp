//
// Created by Hamza El-Kebir on 6/19/21.
//

#ifndef LODESTAR_RUNGEKUTTAFEHLBERG45_HPP
#define LODESTAR_RUNGEKUTTAFEHLBERG45_HPP

#include "primitives/integrators/ButcherTableau.hpp"

namespace ls {
    namespace primitives {
        namespace detail {
            class RungeKuttaFehlberg45Impl {
                friend class RungeKuttaFehlberg45;

            protected:
                /**
                 * @brief Constructor initializes Butcher tables.
                 *
                 * @details RKF45 is an embedded explicit RK-scheme, and has higher order error-order 5, and
                 * lower-order error order 4.
                 */
                RungeKuttaFehlberg45Impl()
                {
                    btSimple.setNode<0>(1.0 / 4.0);
                    btSimple.setCoefficient<0, 0>(1.0 / 4.0);

                    btSimple.setNode<1>(3.0 / 8.0);
                    btSimple.setCoefficient<1, 0>(3.0 / 32.0);
                    btSimple.setCoefficient<1, 1>(9.0 / 32.0);

                    btSimple.setNode<2>(12.0 / 13.0);
                    btSimple.setCoefficient<2, 0>(1932.0 / 2197.0);
                    btSimple.setCoefficient<2, 1>(-7200.0 / 2197.0);
                    btSimple.setCoefficient<2, 2>(7296.0 / 2197.0);

                    btSimple.setNode<3>(1.0);
                    btSimple.setCoefficient<3, 0>(439.0 / 216.0);
                    btSimple.setCoefficient<3, 1>(-8.0);
                    btSimple.setCoefficient<3, 2>(3680.0 / 513.0);
                    btSimple.setCoefficient<3, 3>(-845.0 / 4104.0);

                    btSimple.setNode<4>(1.0 / 2.0);
                    btSimple.setCoefficient<4, 0>(-8.0 / 27.0);
                    btSimple.setCoefficient<4, 1>(2.0);
                    btSimple.setCoefficient<4, 2>(-3544.0 / 2565.0);
                    btSimple.setCoefficient<4, 3>(1859.0 / 4104.0);
                    btSimple.setCoefficient<4, 4>(-11.0 / 40.0);

                    btSimple.setWeight<0>(16.0 / 135.0);
                    btSimple.setWeight<1>(0.0);
                    btSimple.setWeight<2>(6656.0 / 12825.0);
                    btSimple.setWeight<3>(28561.0 / 56430.0);
                    btSimple.setWeight<4>(-9.0 / 50.0);
                    btSimple.setWeight<5>(2.0 / 55.0);

                    // Extended

                    btExtended.setNode<0>(1.0 / 4.0);
                    btExtended.setCoefficient<0, 0>(1.0 / 4.0);

                    btExtended.setNode<1>(3.0 / 8.0);
                    btExtended.setCoefficient<1, 0>(3.0 / 32.0);
                    btExtended.setCoefficient<1, 1>(9.0 / 32.0);

                    btExtended.setNode<2>(12.0 / 13.0);
                    btExtended.setCoefficient<2, 0>(1932.0 / 2197.0);
                    btExtended.setCoefficient<2, 1>(-7200.0 / 2197.0);
                    btExtended.setCoefficient<2, 2>(7296.0 / 2197.0);

                    btExtended.setNode<3>(1.0);
                    btExtended.setCoefficient<3, 0>(439.0 / 216.0);
                    btExtended.setCoefficient<3, 1>(-8.0);
                    btExtended.setCoefficient<3, 2>(3680.0 / 513.0);
                    btExtended.setCoefficient<3, 3>(-845.0 / 4104.0);

                    btExtended.setNode<4>(1.0 / 2.0);
                    btExtended.setCoefficient<4, 0>(-8.0 / 27.0);
                    btExtended.setCoefficient<4, 1>(2.0);
                    btExtended.setCoefficient<4, 2>(-3544.0 / 2565.0);
                    btExtended.setCoefficient<4, 3>(1859.0 / 4104.0);
                    btExtended.setCoefficient<4, 4>(-11.0 / 40.0);

                    btExtended.setWeight<0, true>(16.0 / 135.0);
                    btExtended.setWeight<1, true>(0.0);
                    btExtended.setWeight<2, true>(6656.0 / 12825.0);
                    btExtended.setWeight<3, true>(28561.0 / 56430.0);
                    btExtended.setWeight<4, true>(-9.0 / 50.0);
                    btExtended.setWeight<5, true>(2.0 / 55.0);

                    btExtended.setWeight<0, false>(25.0 / 216.0);
                    btExtended.setWeight<1, false>(0.0);
                    btExtended.setWeight<2, false>(1408.0 / 2565.0);
                    btExtended.setWeight<3, false>(2197.0 / 4104.0);
                    btExtended.setWeight<4, false>(-1.0 / 5.0);
                    btExtended.setWeight<5, false>(0.0);
                }

                ls::primitives::ButcherTableau<6, false> btSimple;
                ls::primitives::ButcherTableau<6, true> btExtended;
            };

            class RungeKuttaFehlberg45 {
            public:
                static ls::primitives::ButcherTableau<6, true> &getButcherTableau()
                {
                    static RungeKuttaFehlberg45Impl *boshImpl = new RungeKuttaFehlberg45Impl();

                    return boshImpl->btExtended;
                }

                static ls::primitives::ButcherTableau<6, false> &getButcherTableauSimple()
                {
                    static RungeKuttaFehlberg45Impl *boshImpl = new RungeKuttaFehlberg45Impl();

                    return boshImpl->btSimple;
                }

            private:
                RungeKuttaFehlberg45() = default;

                // Delete copy/move so extra instances can't be created/moved.
                RungeKuttaFehlberg45(const RungeKuttaFehlberg45 &) = delete;

                RungeKuttaFehlberg45 &operator=(const RungeKuttaFehlberg45 &) = delete;

                RungeKuttaFehlberg45(RungeKuttaFehlberg45 &&) = delete;

                RungeKuttaFehlberg45 &operator=(RungeKuttaFehlberg45 &&) = delete;
            };
        }

        template<typename TType, typename TScalarType = double>
        class RungeKuttaFehlberg45 {
        public:
            typedef std::function<TType(TScalarType, TType)> TDFunction;

            static const short int kLowerErrorOrder = 4;
            static const short int kLigherErrorOrder = 5;
            static const short int kStages = 6;

            /**
             * @brief Simple integration using the fifth-order scheme in the Runge-Kutta-Fehlberg method.
             *
             * @param f Function to be integrated.
             * @param t Initial time.
             * @param y Initial state.
             * @param h Integration step.
             * @param N Number of integration scheme executions.
             */
            static void integrateSimple(const TDFunction &f, TScalarType &t, TType &y, TScalarType h, size_t N = 1);

            /**
             * @brief Integrate using the Runge-Kutta-Fehlberg method (rk45) with truncation error output.
             *
             * @param f Function to be integrated.
             * @param t Initial time.
             * @param y Initial state.
             * @param h Integration step.
             * @param N Number of integration scheme executions.
             *
             * @return Local truncation error.
             */
            static TType integrateEmbedded(const TDFunction &f, TScalarType &t, TType &y, TScalarType h, size_t N = 1);

            // TODO: Add integrate function with maximum allowable error (adaptive step size).
        };

        template<typename TType, typename TScalarType>
        void RungeKuttaFehlberg45<TType, TScalarType>::integrateSimple(const TDFunction &f, TScalarType &t, TType &y,
                                                                       const TScalarType h, size_t N)
        {
            for (int i = 0; i < N; i++) {
                y = detail::RungeKuttaFehlberg45::getButcherTableauSimple().template execute(f, y, t, h);
                t += h;
            }
        }

        template<typename TType, typename TScalarType>
        TType RungeKuttaFehlberg45<TType, TScalarType>::integrateEmbedded(const TDFunction &f, TScalarType &t, TType &y,
                                                                          const TScalarType h, size_t N)
        {
            std::pair<TType, TType> ye;
            for (int i = 0; i < N; i++) {
                ye = detail::RungeKuttaFehlberg45::getButcherTableau().template execute<TType, 0, true>(f, y, t, h);
                y = ye.first;
                t += h;
            }

            return ye.second;
        }
    }
}

#endif //LODESTAR_RUNGEKUTTAFEHLBERG45_HPP
