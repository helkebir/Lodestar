//
// Created by helkebir on 6/13/21.
//

#ifndef LODESTAR_NANOPBWRAPPER_HPP
#define LODESTAR_NANOPBWRAPPER_HPP

#include "Eigen/Dense"
#include "Vector.pb.h"
#include "TypeEnum.pb.h"

template<typename TType, bool isStatic = true>
struct NanopbWrapper {
};

template<>
struct NanopbWrapper<npb_Vector2d, true> {
    using npbType = npb_Vector2d;
    using npbTypeEnum = npb_Vector2d;
    using cppType = Eigen::Matrix<double, 2, 1>;

    static cppType unwrap(const npbType &obj)
    {
        cppType ret;
        ret << obj.coeff[0], obj.coeff[1];
        // ret = Eigen::Map<Eigen::Matrix<double, 2, 1>>(obj.coeff, 2, 1);

        return ret;
    }

    static void unwrap(const npbType &obj, cppType &ret)
    {
        ret.setZero();
        ret << obj.coeff[0], obj.coeff[1];
        // ret = Eigen::Map<cppType>(obj.coeff, 2, 1);
    }

    static npbType wrap(const cppType &obj)
    {
        npbType ret;
        ret.coeff[0] = obj(0);
        ret.coeff[1] = obj(1);
        // Eigen::Map<cppType>(ret.coeff, 2, 1) = obj;

        ret.size = 2;
        ret.has_size = true;

        return ret;
    }

    static npbType wrap(const cppType &obj, npbType &ret)
    {
        ret.coeff[0] = obj(0);
        ret.coeff[1] = obj(1);
        // Eigen::Map<cppType>(ret.coeff, 2, 1) = obj;

        ret.size = 2;
        ret.has_size = true;

        return ret;
    }
};

template<>
struct NanopbWrapper<Eigen::Matrix<double, 2, 1>, true> : NanopbWrapper<npb_Vector2d, true> {};

template<>
struct NanopbWrapper<npb_Vector2d, false> {
    using npbType = npb_Vector2d;
    using npbTypeEnum = npb_Vector2d;
    using cppType = Eigen::VectorXd;

    static cppType unwrap(const npbType &obj)
    {
        int32_t size = (obj.size > 2 ? 2 : obj.size);
        cppType ret(size);
        for (int i = 0; i < size; i++)
            ret(i) = obj.coeff[i];
        // ret = Eigen::Map<Eigen::Matrix<double, 2, 1>>(obj.coeff, 2, 1);

        return ret;
    }

    static void unwrap(const npbType &obj, cppType &ret)
    {
        int32_t size = (obj.size > 2 ? 2 : obj.size);
        ret.conservativeResize(size, 1);
        for (int i = 0; i < size; i++)
            ret(i) = obj.coeff[i];

        // ret = Eigen::Map<cppType>(obj.coeff, size, 1);
    }

    static npbType wrap(const cppType &obj)
    {
        npbType ret;
        int32_t size = (obj.rows() > 2 ? 2 : obj.rows());
        for (int i = 0; i < size; i++)
            ret.coeff[i] = obj(i);
        // Eigen::Map<cppType>(ret.coeff, size, 1) = obj;

        ret.size = size;
        ret.has_size = true;

        return ret;
    }

    static npbType wrap(const cppType &obj, npbType &ret)
    {
        int32_t size = (obj.rows() > 2 ? 2 : obj.rows());
        for (int i = 0; i < size; i++)
            ret.coeff[i] = obj(i);
        // Eigen::Map<cppType>(ret.coeff, size, 1) = obj;

        ret.size = size;
        ret.has_size = true;

        return ret;
    }
};

// ============ npb_Vector3d ========================================

template<>
struct NanopbWrapper<npb_Vector3d, true> {
    using npbType = npb_Vector3d;
    using npbTypeEnum = npb_Vector3d;
    using cppType = Eigen::Matrix<double, 3, 1>;

    static cppType unwrap(const npbType &obj)
    {
        cppType ret;
        ret << obj.coeff[0], obj.coeff[1], obj.coeff[2];
        // ret = Eigen::Map<Eigen::Matrix<double, 2, 1>>(obj.coeff, 2, 1);

        return ret;
    }

    static void unwrap(const npbType &obj, cppType &ret)
    {
        ret.setZero();
        ret << obj.coeff[0], obj.coeff[1], obj.coeff[2];
        // ret = Eigen::Map<cppType>(obj.coeff, 2, 1);
    }

    static npbType wrap(const cppType &obj)
    {
        npbType ret;
        ret.coeff[0] = obj(0);
        ret.coeff[1] = obj(1);
        ret.coeff[2] = obj(2);
        // Eigen::Map<cppType>(ret.coeff, 2, 1) = obj;

        ret.size = 3;
        ret.has_size = true;

        return ret;
    }

    static npbType wrap(const cppType &obj, npbType &ret)
    {
        ret.coeff[0] = obj(0);
        ret.coeff[1] = obj(1);
        ret.coeff[2] = obj(2);
        // Eigen::Map<cppType>(ret.coeff, 2, 1) = obj;

        ret.size = 3;
        ret.has_size = true;

        return ret;
    }
};

template<>
struct NanopbWrapper<Eigen::Matrix<double, 3, 1>, true> : NanopbWrapper<npb_Vector3d, true> {};

template<>
struct NanopbWrapper<npb_Vector3d, false> {
    using npbType = npb_Vector3d;
    using npbTypeEnum = npb_Vector3d;
    using cppType = Eigen::VectorXd;

    static cppType unwrap(const npbType &obj)
    {
        int32_t size = (obj.size > 3 ? 3 : obj.size);
        cppType ret(size);
        for (int i = 0; i < size; i++)
            ret(i) = obj.coeff[i];
        // ret = Eigen::Map<Eigen::Matrix<double, 2, 1>>(obj.coeff, 2, 1);

        return ret;
    }

    static void unwrap(const npbType &obj, cppType &ret)
    {
        int32_t size = (obj.size > 3 ? 3 : obj.size);
        ret.conservativeResize(size, 1);
        for (int i = 0; i < size; i++)
            ret(i) = obj.coeff[i];

        // ret = Eigen::Map<cppType>(obj.coeff, size, 1);
    }

    static npbType wrap(const cppType &obj)
    {
        npbType ret;
        int32_t size = (obj.rows() > 3 ? 3 : obj.rows());
        for (int i = 0; i < size; i++)
            ret.coeff[i] = obj(i);
        // Eigen::Map<cppType>(ret.coeff, size, 1) = obj;

        ret.size = size;
        ret.has_size = true;

        return ret;
    }

    static npbType wrap(const cppType &obj, npbType &ret)
    {
        int32_t size = (obj.rows() > 3 ? 3 : obj.rows());
        for (int i = 0; i < size; i++)
            ret.coeff[i] = obj(i);
        // Eigen::Map<cppType>(ret.coeff, size, 1) = obj;

        ret.size = size;
        ret.has_size = true;

        return ret;
    }
};

#endif //LODESTAR_NANOPBWRAPPER_HPP
