//
// Created by Hamza El-Kebir on 6/18/21.
//

#ifndef LODESTAR_BACKWARDDIFFERENCE_HPP
#define LODESTAR_BACKWARDDIFFERENCE_HPP

#include "Eigen/Dense"

namespace ls {
    namespace primitives {
        template<typename TType, size_t TSamples, size_t TOrder, typename TScalarType = double>
        class BackwardDifference {
            static_assert(TSamples > 1, "Number of samples must be greater than one.");

            static_assert(TOrder > 1, "Differentiation order must be greater than one.");

            static_assert(TSamples > TOrder, "Number of samples must be greater than order.");

            static_assert(
                    // First order
                    (TSamples == 2 && TOrder == 1) ||
                    (TSamples == 3 && TOrder == 1) ||
                    (TSamples == 4 && TOrder == 1) ||
                    (TSamples == 5 && TOrder == 1) ||
                    (TSamples == 6 && TOrder == 1) ||
                    (TSamples == 7 && TOrder == 1) ||
                    // Second order
                    (TSamples == 3 && TOrder == 2) ||
                    (TSamples == 4 && TOrder == 2) ||
                    (TSamples == 5 && TOrder == 2) ||
                    (TSamples == 6 && TOrder == 2) ||
                    (TSamples == 7 && TOrder == 2) ||
                    // Third order
                    (TSamples == 4 && TOrder == 3) ||
                    (TSamples == 5 && TOrder == 3) ||
                    (TSamples == 6 && TOrder == 3) ||
                    (TSamples == 7 && TOrder == 3), "Combination of samples and order is not supported.");
        };

// ------- First derivative ---------

        /**
         * @brief Computes the first-order backward finite difference difference given two samples.
         *
         * @tparam TType State type.
         * @tparam TScalarType Spacing type.
         */
        template<typename TType, typename TScalarType>
        class BackwardDifference<TType, 2, 1, TScalarType> {
        protected:
            static TType compute(const TType &xNeg1, const TType &x0)
            {
                return x0 - xNeg1;
            }

        public:
            static TType compute(const TType &xNeg1, const TType &x0, TScalarType h)
            {
                return compute(xNeg1, x0) / h;
            }

            static const int kOrder = 1;
            static const int kErrorOrder = 1;
        };

        /**
         * @brief Computes the first-order backward finite difference difference given three samples.
         *
         * @tparam TType State type.
         * @tparam TScalarType Spacing type.
         */
        template<typename TType, typename TScalarType>
        class BackwardDifference<TType, 3, 1, TScalarType> {
        protected:
            static TType compute(const TType &xNeg2, const TType &xNeg1, const TType &x0)
            {
                return (3.0 / 2.0) * x0 - 2.0 * xNeg1 + (1.0 / 2.0) * xNeg2;
            }

        public:
            static TType compute(const TType &xNeg2, const TType &xNeg1, const TType &x0, TScalarType h)
            {
                return compute(xNeg2, xNeg1, x0) / h;
            }

            static const int kOrder = 1;
            static const int kErrorOrder = 2;
        };

        /**
         * @brief Computes the first-order backward finite difference difference given four samples.
         *
         * @tparam TType State type.
         * @tparam TScalarType Spacing type.
         */
        template<typename TType, typename TScalarType>
        class BackwardDifference<TType, 4, 1, TScalarType> {
        protected:
            static TType compute(const TType &xNeg3, const TType &xNeg2, const TType &xNeg1, const TType &x0)
            {
                return (11.0 / 6.0) * x0 - 3.0 * xNeg1 + (3.0 / 2.0) * xNeg2 - (1.0 / 3.0) * xNeg3;
            }

        public:
            static TType
            compute(const TType &xNeg3, const TType &xNeg2, const TType &xNeg1, const TType &x0, TScalarType h)
            {
                return compute(xNeg3, xNeg2, xNeg1, x0) / h;
            }

            static const int kOrder = 1;
            static const int kErrorOrder = 3;
        };

        /**
         * @brief Computes the first-order backward finite difference difference given five samples.
         *
         * @tparam TType State type.
         * @tparam TScalarType Spacing type.
         */
        template<typename TType, typename TScalarType>
        class BackwardDifference<TType, 5, 1, TScalarType> {
        protected:
            static TType
            compute(const TType &xNeg4, const TType &xNeg3, const TType &xNeg2, const TType &xNeg1, const TType &x0)
            {
                return (25.0 / 12.0) * x0 - 4.0 * xNeg1 + 3.0 * xNeg2 - (4.0 / 3.0) * xNeg3 + (1.0 / 4.0) * xNeg4;
            }

        public:
            static TType
            compute(const TType &xNeg4, const TType &xNeg3, const TType &xNeg2, const TType &xNeg1, const TType &x0,
                    TScalarType h)
            {
                return compute(xNeg4, xNeg3, xNeg2, xNeg1, x0) / h;
            }

            static const int kOrder = 1;
            static const int kErrorOrder = 4;
        };

        /**
         * @brief Computes the first-order backward finite difference difference given six samples.
         *
         * @tparam TType State type.
         * @tparam TScalarType Spacing type.
         */
        template<typename TType, typename TScalarType>
        class BackwardDifference<TType, 6, 1, TScalarType> {
        protected:
            static TType
            compute(const TType &xNeg5, const TType &xNeg4, const TType &xNeg3, const TType &xNeg2, const TType &xNeg1,
                    const TType &x0)
            {
                return (137.0 / 60.0) * x0 - 5.0 * xNeg1 + 5.0 * xNeg2 - (10.0 / 3.0) * xNeg3 + (5.0 / 4.0) * xNeg4 -
                       (1.0 / 6.0) * xNeg5;
            }

        public:
            static TType
            compute(const TType &xNeg5, const TType &xNeg4, const TType &xNeg3, const TType &xNeg2, const TType &xNeg1,
                    const TType &x0, TScalarType h)
            {
                return compute(xNeg5, xNeg4, xNeg3, xNeg2, xNeg1, x0) / h;
            }

            static const int kOrder = 1;
            static const int kErrorOrder = 5;
        };

        /**
         * @brief Computes the first-order backward finite difference difference given seven samples.
         *
         * @tparam TType State type.
         * @tparam TScalarType Spacing type.
         */
        template<typename TType, typename TScalarType>
        class BackwardDifference<TType, 7, 1, TScalarType> {
        protected:
            static TType
            compute(const TType &xNeg6, const TType &xNeg5, const TType &xNeg4, const TType &xNeg3, const TType &xNeg2,
                    const TType &xNeg1, const TType &x0)
            {
                return (49.0 / 20.0) * x0 - 6.0 * xNeg1 + (15.0 / 2.0) * xNeg2 - (20.0 / 3.0) * xNeg3 +
                       (15.0 / 4.0) * xNeg4 - (6.0 / 5.0) * xNeg5 + (1.0 / 6.0) * xNeg6;
            }

        public:
            static TType
            compute(const TType &xNeg6, const TType &xNeg5, const TType &xNeg4, const TType &xNeg3, const TType &xNeg2,
                    const TType &xNeg1, const TType &x0, TScalarType h)
            {
                return compute(xNeg6, xNeg5, xNeg4, xNeg3, xNeg2, xNeg1, x0) / h;
            }

            static const int kOrder = 1;
            static const int kErrorOrder = 6;
        };

// ------- Second derivative ---------

        /**
         * @brief Computes the second-order backward finite difference difference given three samples.
         *
         * @tparam TType State type.
         * @tparam TScalarType Spacing type.
         */
        template<typename TType, typename TScalarType>
        class BackwardDifference<TType, 3, 2, TScalarType> {
        protected:
            static TType compute(const TType &xNeg2, const TType &xNeg1, const TType &x0)
            {
                return x0 - 2 * xNeg1 + xNeg2;
            }

        public:
            static TType compute(const TType &xNeg2, const TType &xNeg1, const TType &x0, TScalarType h)
            {
                return compute(xNeg2, xNeg1, x0) / (h * h);
            }

            static const int kOrder = 2;
            static const int kErrorOrder = 1;
        };

        /**
         * @brief Computes the second-order backward finite difference difference given four samples.
         *
         * @tparam TType State type.
         * @tparam TScalarType Spacing type.
         */
        template<typename TType, typename TScalarType>
        class BackwardDifference<TType, 4, 2, TScalarType> {
        protected:
            static TType compute(const TType &xNeg3, const TType &xNeg2, const TType &xNeg1, const TType &x0)
            {
                return 2 * x0 - 5 * xNeg1 + 4 * xNeg2 - 1 * xNeg3;
            }

        public:
            static TType
            compute(const TType &xNeg3, const TType &xNeg2, const TType &xNeg1, const TType &x0, TScalarType h)
            {
                return compute(xNeg3, xNeg2, xNeg1, x0) / (h * h);
            }

            static const int kOrder = 2;
            static const int kErrorOrder = 2;
        };

        /**
         * @brief Computes the second-order backward finite difference difference given five samples.
         *
         * @tparam TType State type.
         * @tparam TScalarType Spacing type.
         */
        template<typename TType, typename TScalarType>
        class BackwardDifference<TType, 5, 2, TScalarType> {
        protected:
            static TType
            compute(const TType &xNeg4, const TType &xNeg3, const TType &xNeg2, const TType &xNeg1, const TType &x0)
            {
                return (35.0 / 12.0) * x0 - (26.0 / 3.0) * xNeg1 + (19.0 / 2.0) * xNeg2 - (14.0 / 3.0) * xNeg3 +
                       (11.0 / 12.0) * xNeg4;
            }

        public:
            static TType
            compute(const TType &xNeg4, const TType &xNeg3, const TType &xNeg2, const TType &xNeg1, const TType &x0,
                    TScalarType h)
            {
                return compute(xNeg4, xNeg3, xNeg2, xNeg1, x0) / (h * h);
            }

            static const int kOrder = 2;
            static const int kErrorOrder = 3;
        };

        /**
         * @brief Computes the second-order backward finite difference difference given six samples.
         *
         * @tparam TType State type.
         * @tparam TScalarType Spacing type.
         */
        template<typename TType, typename TScalarType>
        class BackwardDifference<TType, 6, 2, TScalarType> {
        protected:
            static TType
            compute(const TType &xNeg5, const TType &xNeg4, const TType &xNeg3, const TType &xNeg2, const TType &xNeg1,
                    const TType &x0)
            {
                return (15.0 / 4.0) * x0 - (77.0 / 6.0) * xNeg1 + (107.0 / 6.0) * xNeg2 - 13.0 * xNeg3 +
                       (61.0 / 12.0) * xNeg4 - (5.0 / 6.0) * xNeg5;
            }

        public:
            static TType
            compute(const TType &xNeg5, const TType &xNeg4, const TType &xNeg3, const TType &xNeg2, const TType &xNeg1,
                    const TType &x0, TScalarType h)
            {
                return compute(xNeg5, xNeg4, xNeg3, xNeg2, xNeg1, x0) / (h * h);
            }

            static const int kOrder = 2;
            static const int kErrorOrder = 4;
        };

        /**
         * @brief Computes the second-order backward finite difference difference given seven samples.
         *
         * @tparam TType State type.
         * @tparam TScalarType Spacing type.
         */
        template<typename TType, typename TScalarType>
        class BackwardDifference<TType, 7, 2, TScalarType> {
        protected:
            static TType
            compute(const TType &xNeg6, const TType &xNeg5, const TType &xNeg4, const TType &xNeg3, const TType &xNeg2,
                    const TType &xNeg1, const TType &x0)
            {
                return (203.0 / 45.0) * x0 - (87.0 / 5.0) * xNeg1 + (117.0 / 4.0) * xNeg2 - (254.0 / 9.0) * xNeg3 +
                       (33.0 / 2.0) * xNeg4 - (27.0 / 5.0) * xNeg5 + (137.0 / 180.0) * xNeg6;
            }

        public:
            static TType
            compute(const TType &xNeg6, const TType &xNeg5, const TType &xNeg4, const TType &xNeg3, const TType &xNeg2,
                    const TType &xNeg1, const TType &x0, TScalarType h)
            {
                return compute(xNeg6, xNeg5, xNeg4, xNeg3, xNeg2, xNeg1, x0) / (h * h);
            }

            static const int kOrder = 2;
            static const int kErrorOrder = 5;
        };

// ------- Third derivative ---------

        /**
         * @brief Computes the third-order backward finite difference difference given four samples.
         *
         * @tparam TType State type.
         * @tparam TScalarType Spacing type.
         */
        template<typename TType, typename TScalarType>
        class BackwardDifference<TType, 4, 3, TScalarType> {
        protected:
            static TType compute(const TType &xNeg3, const TType &xNeg2, const TType &xNeg1, const TType &x0)
            {
                return 1.0 * x0 - 3.0 * xNeg1 + 3.0 * xNeg2 - 1.0 * xNeg3;
            }

        public:
            static TType
            compute(const TType &xNeg3, const TType &xNeg2, const TType &xNeg1, const TType &x0, TScalarType h)
            {
                return compute(xNeg3, xNeg2, xNeg1, x0) / (h * h * h);
            }

            static const int kOrder = 3;
            static const int kErrorOrder = 1;
        };

        /**
         * @brief Computes the third-order backward finite difference difference given five samples.
         *
         * @tparam TType State type.
         * @tparam TScalarType Spacing type.
         */
        template<typename TType, typename TScalarType>
        class BackwardDifference<TType, 5, 3, TScalarType> {
        protected:
            static TType
            compute(const TType &xNeg4, const TType &xNeg3, const TType &xNeg2, const TType &xNeg1, const TType &x0)
            {
                return (5.0 / 2.0) * x0 - 9.0 * xNeg1 + 12.0 * xNeg2 - 7.0 * xNeg3 + (3.0 / 2.0) * xNeg4;
            }

        public:
            static TType
            compute(const TType &xNeg4, const TType &xNeg3, const TType &xNeg2, const TType &xNeg1, const TType &x0,
                    TScalarType h)
            {
                return compute(xNeg4, xNeg3, xNeg2, xNeg1, x0) / (h * h * h);
            }

            static const int kOrder = 3;
            static const int kErrorOrder = 2;
        };

        /**
         * @brief Computes the third-order backward finite difference difference given six samples.
         *
         * @tparam TType State type.
         * @tparam TScalarType Spacing type.
         */
        template<typename TType, typename TScalarType>
        class BackwardDifference<TType, 6, 3, TScalarType> {
        protected:
            static TType
            compute(const TType &xNeg5, const TType &xNeg4, const TType &xNeg3, const TType &xNeg2, const TType &xNeg1,
                    const TType &x0)
            {
                return (17.0 / 4.0) * x0 - (71.0 / 4.0) * xNeg1 + (59.0 / 2.0) * xNeg2 - (49.0 / 2.0) * xNeg3 +
                       (41.0 / 4.0) * xNeg4 - (7.0 / 4.0) * xNeg5;
            }

        public:
            static TType
            compute(const TType &xNeg5, const TType &xNeg4, const TType &xNeg3, const TType &xNeg2, const TType &xNeg1,
                    const TType &x0, TScalarType h)
            {
                return compute(xNeg5, xNeg4, xNeg3, xNeg2, xNeg1, x0) / (h * h * h);
            }

            static const int kOrder = 3;
            static const int kErrorOrder = 3;
        };

        /**
         * @brief Computes the third-order backward finite difference difference given seven samples.
         *
         * @tparam TType State type.
         * @tparam TScalarType Spacing type.
         */
        template<typename TType, typename TScalarType>
        class BackwardDifference<TType, 7, 3, TScalarType> {
        protected:
            static TType
            compute(const TType &xNeg6, const TType &xNeg5, const TType &xNeg4, const TType &xNeg3, const TType &xNeg2,
                    const TType &xNeg1, const TType &x0)
            {
                return (49.0 / 8.0) * x0 - 29.0 * xNeg1 + (461.0 / 8.0) * xNeg2 - 62.0 * xNeg3 + (307.0 / 8.0) * xNeg4 -
                       13.0 * xNeg5 + (15.0 / 8.0) * xNeg6;
            }

        public:
            static TType
            compute(const TType &xNeg6, const TType &xNeg5, const TType &xNeg4, const TType &xNeg3, const TType &xNeg2,
                    const TType &xNeg1, const TType &x0, TScalarType h)
            {
                return compute(xNeg6, xNeg5, xNeg4, xNeg3, xNeg2, xNeg1, x0) / (h * h * h);
            }

            static const int kOrder = 3;
            static const int kErrorOrder = 4;
        };

    }
}

#endif //LODESTAR_BACKWARDDIFFERENCE_HPP
