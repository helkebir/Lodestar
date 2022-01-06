//
// Created by Hamza El-Kebir on 6/19/21.
//

#ifndef LODESTAR_RUNGEKUTTAFEHLBERG78_HPP
#define LODESTAR_RUNGEKUTTAFEHLBERG78_HPP

#include "ButcherTableau.hpp"

namespace ls {
    namespace primitives {
        namespace detail {
            class RungeKuttaFehlberg78Impl {
                friend class RungeKuttaFehlberg78;

            protected:
                /**
                 * @brief Constructor initializes Butcher tables.
                 *
                 * @details RKF78 is an embedded explicit RK-scheme, and has higher order error-order 8, and
                 * lower-order error order 7.
                 *
                 * @sa <a href="https://github.com/nasa/trick/blob/master/trick_source/er7_utils/integration/rkf78/src/rkf78_butcher_tableau.cc">RKFehlberg78ButcherTableau</a> in NASA's Trick framework.
                 */
                RungeKuttaFehlberg78Impl()
                {
                    btSimple.setNode<0>(2.0 / 27.0);
                    btSimple.setCoefficient<0, 0>(2.0 / 27.0);

                    btSimple.setNode<1>(1.0 / 9.0);
                    btSimple.setCoefficient<1, 0>(1.0 / 36.0);
                    btSimple.setCoefficient<1, 1>(1.0 / 12.0);

                    btSimple.setNode<2>(1.0 / 6.0);
                    btSimple.setCoefficient<2, 0>(1.0 / 24.0);
                    btSimple.setCoefficient<2, 1>(0.0);
                    btSimple.setCoefficient<2, 2>(1.0 / 8.0);

                    btSimple.setNode<3>(5.0 / 12.0);
                    btSimple.setCoefficient<3, 0>(5.0 / 12.0);
                    btSimple.setCoefficient<3, 1>(0.0);
                    btSimple.setCoefficient<3, 2>(-25.0 / 16.0);
                    btSimple.setCoefficient<3, 3>(25.0 / 16.0);

                    btSimple.setNode<4>(1.0 / 2.0);
                    btSimple.setCoefficient<4, 0>(1.0 / 20.0);
                    btSimple.setCoefficient<4, 1>(0.0);
                    btSimple.setCoefficient<4, 2>(0.0);
                    btSimple.setCoefficient<4, 3>(1.0 / 4.0);
                    btSimple.setCoefficient<4, 4>(1.0 / 5.0);

                    btSimple.setNode<5>(5.0 / 6.0);
                    btSimple.setCoefficient<5, 0>(-25.0 / 108.0);
                    btSimple.setCoefficient<5, 1>(0.0);
                    btSimple.setCoefficient<5, 2>(0.0);
                    btSimple.setCoefficient<5, 3>(125.0 / 108.0);
                    btSimple.setCoefficient<5, 4>(-65.0 / 27.0);
                    btSimple.setCoefficient<5, 5>(-125.0 / 54.0);

                    btSimple.setNode<6>(1.0 / 6.0);
                    btSimple.setCoefficient<6, 0>(31.0 / 300.0);
                    btSimple.setCoefficient<6, 1>(0.0);
                    btSimple.setCoefficient<6, 2>(0.0);
                    btSimple.setCoefficient<6, 3>(0.0);
                    btSimple.setCoefficient<6, 4>(61.0 / 225.0);
                    btSimple.setCoefficient<6, 5>(-2.0 / 9.0);
                    btSimple.setCoefficient<6, 6>(13.0 / 900.0);

                    btSimple.setNode<7>(2.0 / 3.0);
                    btSimple.setCoefficient<7, 0>(2.0);
                    btSimple.setCoefficient<7, 1>(0.0);
                    btSimple.setCoefficient<7, 2>(0.0);
                    btSimple.setCoefficient<7, 3>(-53.0 / 6.0);
                    btSimple.setCoefficient<7, 4>(704.0 / 45.0);
                    btSimple.setCoefficient<7, 5>(-107.0 / 9.0);
                    btSimple.setCoefficient<7, 6>(67.0 / 90.0);
                    btSimple.setCoefficient<7, 7>(3.0);

                    btSimple.setNode<8>(1.0 / 3.0);
                    btSimple.setCoefficient<8, 0>(-91.0 / 108.0);
                    btSimple.setCoefficient<8, 1>(0.0);
                    btSimple.setCoefficient<8, 2>(0.0);
                    btSimple.setCoefficient<8, 3>(23.0 / 108.0);
                    btSimple.setCoefficient<8, 4>(-976.0 / 135.0);
                    btSimple.setCoefficient<8, 5>(311.0 / 54.0);
                    btSimple.setCoefficient<8, 6>(-19.0 / 60.0);
                    btSimple.setCoefficient<8, 7>(17.0 / 6.0);
                    btSimple.setCoefficient<8, 8>(-1.0 / 12.0);

                    btSimple.setNode<9>(1.0);
                    btSimple.setCoefficient<9, 0>(2383.0 / 4100.0);
                    btSimple.setCoefficient<9, 1>(0.0);
                    btSimple.setCoefficient<9, 2>(0.0);
                    btSimple.setCoefficient<9, 3>(-341.0 / 164.0);
                    btSimple.setCoefficient<9, 4>(4496.0 / 1025.0);
                    btSimple.setCoefficient<9, 5>(-301.0 / 82.0);
                    btSimple.setCoefficient<9, 6>(2133.0 / 4100.0);
                    btSimple.setCoefficient<9, 7>(45.0 / 82.0);
                    btSimple.setCoefficient<9, 8>(45.0 / 164.0);
                    btSimple.setCoefficient<9, 9>(18.0 / 41.0);

                    btSimple.setNode<10>(0.0);
                    btSimple.setCoefficient<10, 0>(3.0 / 205.0);
                    btSimple.setCoefficient<10, 1>(0.0);
                    btSimple.setCoefficient<10, 2>(0.0);
                    btSimple.setCoefficient<10, 3>(0.0);
                    btSimple.setCoefficient<10, 4>(0.0);
                    btSimple.setCoefficient<10, 5>(-6.0 / 41.0);
                    btSimple.setCoefficient<10, 6>(-3.0 / 205.0);
                    btSimple.setCoefficient<10, 7>(-3.0 / 41.0);
                    btSimple.setCoefficient<10, 8>(3.0 / 41.0);
                    btSimple.setCoefficient<10, 9>(6.0 / 41.0);
                    btSimple.setCoefficient<10, 10>(0.0);

                    btSimple.setNode<11>(1.0);
                    btSimple.setCoefficient<11, 0>(-1777.0 / 4100.0);
                    btSimple.setCoefficient<11, 1>(0.0);
                    btSimple.setCoefficient<11, 2>(0.0);
                    btSimple.setCoefficient<11, 3>(-341.0 / 164.0);
                    btSimple.setCoefficient<11, 4>(4496.0 / 1025.0);
                    btSimple.setCoefficient<11, 5>(-289.0 / 82.0);
                    btSimple.setCoefficient<11, 6>(2193.0 / 4100.0);
                    btSimple.setCoefficient<11, 7>(51.0 / 82.0);
                    btSimple.setCoefficient<11, 8>(33.0 / 164.0);
                    btSimple.setCoefficient<11, 9>(12.0 / 41.0);
                    btSimple.setCoefficient<11, 10>(0.0);
                    btSimple.setCoefficient<11, 11>(1.0);

                    btSimple.setWeight<0>(0.0);
                    btSimple.setWeight<1>(0.0);
                    btSimple.setWeight<2>(0.0);
                    btSimple.setWeight<3>(0.0);
                    btSimple.setWeight<4>(0.0);
                    btSimple.setWeight<5>(34.0 / 105.0);
                    btSimple.setWeight<6>(9.0 / 35.0);
                    btSimple.setWeight<7>(9.0 / 35.0);
                    btSimple.setWeight<8>(9.0 / 280.0);
                    btSimple.setWeight<9>(9.0 / 280.0);
                    btSimple.setWeight<10>(0.0);
                    btSimple.setWeight<11>(41.0 / 840.0);
                    btSimple.setWeight<12>(41.0 / 840.0);

                    // Extended

                    btExtended.setNode<0>(2.0 / 27.0);
                    btExtended.setCoefficient<0, 0>(2.0 / 27.0);

                    btExtended.setNode<1>(1.0 / 9.0);
                    btExtended.setCoefficient<1, 0>(1.0 / 36.0);
                    btExtended.setCoefficient<1, 1>(1.0 / 12.0);

                    btExtended.setNode<2>(1.0 / 6.0);
                    btExtended.setCoefficient<2, 0>(1.0 / 24.0);
                    btExtended.setCoefficient<2, 1>(0.0);
                    btExtended.setCoefficient<2, 2>(1.0 / 8.0);

                    btExtended.setNode<3>(5.0 / 12.0);
                    btExtended.setCoefficient<3, 0>(5.0 / 12.0);
                    btExtended.setCoefficient<3, 1>(0.0);
                    btExtended.setCoefficient<3, 2>(-25.0 / 16.0);
                    btExtended.setCoefficient<3, 3>(25.0 / 16.0);

                    btExtended.setNode<4>(1.0 / 2.0);
                    btExtended.setCoefficient<4, 0>(1.0 / 20.0);
                    btExtended.setCoefficient<4, 1>(0.0);
                    btExtended.setCoefficient<4, 2>(0.0);
                    btExtended.setCoefficient<4, 3>(1.0 / 4.0);
                    btExtended.setCoefficient<4, 4>(1.0 / 5.0);

                    btExtended.setNode<5>(5.0 / 6.0);
                    btExtended.setCoefficient<5, 0>(-25.0 / 108.0);
                    btExtended.setCoefficient<5, 1>(0.0);
                    btExtended.setCoefficient<5, 2>(0.0);
                    btExtended.setCoefficient<5, 3>(125.0 / 108.0);
                    btExtended.setCoefficient<5, 4>(-65.0 / 27.0);
                    btExtended.setCoefficient<5, 5>(-125.0 / 54.0);

                    btExtended.setNode<6>(1.0 / 6.0);
                    btExtended.setCoefficient<6, 0>(31.0 / 300.0);
                    btExtended.setCoefficient<6, 1>(0.0);
                    btExtended.setCoefficient<6, 2>(0.0);
                    btExtended.setCoefficient<6, 3>(0.0);
                    btExtended.setCoefficient<6, 4>(61.0 / 225.0);
                    btExtended.setCoefficient<6, 5>(-2.0 / 9.0);
                    btExtended.setCoefficient<6, 6>(13.0 / 900.0);

                    btExtended.setNode<7>(2.0 / 3.0);
                    btExtended.setCoefficient<7, 0>(2.0);
                    btExtended.setCoefficient<7, 1>(0.0);
                    btExtended.setCoefficient<7, 2>(0.0);
                    btExtended.setCoefficient<7, 3>(-53.0 / 6.0);
                    btExtended.setCoefficient<7, 4>(704.0 / 45.0);
                    btExtended.setCoefficient<7, 5>(-107.0 / 9.0);
                    btExtended.setCoefficient<7, 6>(67.0 / 90.0);
                    btExtended.setCoefficient<7, 7>(3.0);

                    btExtended.setNode<8>(1.0 / 3.0);
                    btExtended.setCoefficient<8, 0>(-91.0 / 108.0);
                    btExtended.setCoefficient<8, 1>(0.0);
                    btExtended.setCoefficient<8, 2>(0.0);
                    btExtended.setCoefficient<8, 3>(23.0 / 108.0);
                    btExtended.setCoefficient<8, 4>(-976.0 / 135.0);
                    btExtended.setCoefficient<8, 5>(311.0 / 54.0);
                    btExtended.setCoefficient<8, 6>(-19.0 / 60.0);
                    btExtended.setCoefficient<8, 7>(17.0 / 6.0);
                    btExtended.setCoefficient<8, 8>(-1.0 / 12.0);

                    btExtended.setNode<9>(1.0);
                    btExtended.setCoefficient<9, 0>(2383.0 / 4100.0);
                    btExtended.setCoefficient<9, 1>(0.0);
                    btExtended.setCoefficient<9, 2>(0.0);
                    btExtended.setCoefficient<9, 3>(-341.0 / 164.0);
                    btExtended.setCoefficient<9, 4>(4496.0 / 1025.0);
                    btExtended.setCoefficient<9, 5>(-301.0 / 82.0);
                    btExtended.setCoefficient<9, 6>(2133.0 / 4100.0);
                    btExtended.setCoefficient<9, 7>(45.0 / 82.0);
                    btExtended.setCoefficient<9, 8>(45.0 / 164.0);
                    btExtended.setCoefficient<9, 9>(18.0 / 41.0);

                    btExtended.setNode<10>(0.0);
                    btExtended.setCoefficient<10, 0>(3.0 / 205.0);
                    btExtended.setCoefficient<10, 1>(0.0);
                    btExtended.setCoefficient<10, 2>(0.0);
                    btExtended.setCoefficient<10, 3>(0.0);
                    btExtended.setCoefficient<10, 4>(0.0);
                    btExtended.setCoefficient<10, 5>(-6.0 / 41.0);
                    btExtended.setCoefficient<10, 6>(-3.0 / 205.0);
                    btExtended.setCoefficient<10, 7>(-3.0 / 41.0);
                    btExtended.setCoefficient<10, 8>(3.0 / 41.0);
                    btExtended.setCoefficient<10, 9>(6.0 / 41.0);
                    btExtended.setCoefficient<10, 10>(0.0);

                    btExtended.setNode<11>(1.0);
                    btExtended.setCoefficient<11, 0>(-1777.0 / 4100.0);
                    btExtended.setCoefficient<11, 1>(0.0);
                    btExtended.setCoefficient<11, 2>(0.0);
                    btExtended.setCoefficient<11, 3>(-341.0 / 164.0);
                    btExtended.setCoefficient<11, 4>(4496.0 / 1025.0);
                    btExtended.setCoefficient<11, 5>(-289.0 / 82.0);
                    btExtended.setCoefficient<11, 6>(2193.0 / 4100.0);
                    btExtended.setCoefficient<11, 7>(51.0 / 82.0);
                    btExtended.setCoefficient<11, 8>(33.0 / 164.0);
                    btExtended.setCoefficient<11, 9>(12.0 / 41.0);
                    btExtended.setCoefficient<11, 10>(0.0);
                    btExtended.setCoefficient<11, 11>(1.0);

                    btExtended.setWeight<0, true>(0.0);
                    btExtended.setWeight<1, true>(0.0);
                    btExtended.setWeight<2, true>(0.0);
                    btExtended.setWeight<3, true>(0.0);
                    btExtended.setWeight<4, true>(0.0);
                    btExtended.setWeight<5, true>(34.0 / 105.0);
                    btExtended.setWeight<6, true>(9.0 / 35.0);
                    btExtended.setWeight<7, true>(9.0 / 35.0);
                    btExtended.setWeight<8, true>(9.0 / 280.0);
                    btExtended.setWeight<9, true>(9.0 / 280.0);
                    btExtended.setWeight<10, true>(0.0);
                    btExtended.setWeight<11, true>(41.0 / 840.0);
                    btExtended.setWeight<12, true>(41.0 / 840.0);

                    btExtended.setWeight<0, false>(41.0 / 840.0);
                    btExtended.setWeight<1, false>(0.0);
                    btExtended.setWeight<2, false>(0.0);
                    btExtended.setWeight<3, false>(0.0);
                    btExtended.setWeight<4, false>(0.0);
                    btExtended.setWeight<5, false>(0.0);
                    btExtended.setWeight<6, false>(34.0 / 105.0);
                    btExtended.setWeight<7, false>(9.0 / 35.0);
                    btExtended.setWeight<8, false>(9.0 / 35.0);
                    btExtended.setWeight<9, false>(9.0 / 280.0);
                    btExtended.setWeight<10, false>(9.0 / 280.0);
                    btExtended.setWeight<11, false>(41.0 / 480.0);
                    btExtended.setWeight<12, false>(0.0);
                }

                ls::primitives::ButcherTableau<13, false> btSimple;
                ls::primitives::ButcherTableau<13, true> btExtended;
            };

            class RungeKuttaFehlberg78 {
            public:
                static ls::primitives::ButcherTableau<13, true> &getButcherTableau()
                {
                    static RungeKuttaFehlberg78Impl *boshImpl = new RungeKuttaFehlberg78Impl();

                    return boshImpl->btExtended;
                }

                static ls::primitives::ButcherTableau<13, false> &getButcherTableauSimple()
                {
                    static RungeKuttaFehlberg78Impl *boshImpl = new RungeKuttaFehlberg78Impl();

                    return boshImpl->btSimple;
                }

            private:
                RungeKuttaFehlberg78() = default;

                // Delete copy/move so extra instances can't be created/moved.
                RungeKuttaFehlberg78(const RungeKuttaFehlberg78 &) = delete;

                RungeKuttaFehlberg78 &operator=(const RungeKuttaFehlberg78 &) = delete;

                RungeKuttaFehlberg78(RungeKuttaFehlberg78 &&) = delete;

                RungeKuttaFehlberg78 &operator=(RungeKuttaFehlberg78 &&) = delete;
            };
        }

        template<typename TType, typename TScalarType = double>
        class RungeKuttaFehlberg78 {
        public:
            typedef std::function<TType(TScalarType, TType)> TDFunction;

            static const short int kLowerErrorOrder = 7;
            static const short int kLigherErrorOrder = 8;
            static const short int kStages = 13;

            /**
             * @brief Simple integration using the eighth-order scheme in the Runge-Kutta-Fehlberg method.
             *
             * @param f Function to be integrated.
             * @param t Initial time.
             * @param y Initial state.
             * @param h Integration step.
             * @param N Number of integration scheme executions.
             */
            static void integrateSimple(const TDFunction &f, TScalarType &t, TType &y, TScalarType h, size_t N = 1);

            /**
             * @brief Integrate using the Runge-Kutta-Fehlberg method (rk78) with truncation error output.
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
        void RungeKuttaFehlberg78<TType, TScalarType>::integrateSimple(const TDFunction &f, TScalarType &t, TType &y,
                                                                       const TScalarType h, size_t N)
        {
            for (int i = 0; i < N; i++) {
                y = detail::RungeKuttaFehlberg78::getButcherTableauSimple().template execute(f, y, t, h);
                t += h;
            }
        }

        template<typename TType, typename TScalarType>
        TType RungeKuttaFehlberg78<TType, TScalarType>::integrateEmbedded(const TDFunction &f, TScalarType &t, TType &y,
                                                                          const TScalarType h, size_t N)
        {
            std::pair<TType, TType> ye;
            for (int i = 0; i < N; i++) {
                ye = detail::RungeKuttaFehlberg78::getButcherTableau().template execute<TType, 0, true>(f, y, t, h);
                y = ye.first;
                t += h;
            }

            return ye.second;
        }
    }
}

#endif //LODESTAR_RUNGEKUTTAFEHLBERG78_HPP
