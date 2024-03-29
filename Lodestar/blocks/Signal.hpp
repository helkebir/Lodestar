//
// Created by Hamza El-Kebir on 12/22/21.
//

#ifndef LODESTAR_SIGNAL_HPP
#define LODESTAR_SIGNAL_HPP

#include <type_traits>
#include <iostream>
#include <tuple>
#include <cassert>

#include "SignalBase.hpp"
#include "BlockProto.hpp"
#include "Lodestar/GlobalConstants.hpp"
#include "Lodestar/aux/DynamicData.hpp"
#include "Lodestar/aux/TemplateTraits.hpp"

namespace ls {
    namespace blocks {
        template<typename TObject = void *, typename TIndicated = TObject>
        class Signal : public SignalBase {
        public:
            using Object = TObject;
            using type = TIndicated;


            //    static Signal<TObject> withBlockIdx(int blockId)
            //    {
            //        auto s = Signal<TObject>{};
            //        s.blockId = blockId;
            //
            //        return s;
            //    }

            Signal() : object{}, SignalBase(next()) {};

            //    Signal(Object obj) : object(obj) {};

            Signal(const TObject &obj) : object(obj), SignalBase(next()) {};

            //    Signal(Object *obj) : object(*obj) {};

            Signal(const TObject *obj) : object(*obj), SignalBase(next()) {};

            unsigned int id() const
            {
                return id_;
            }

            operator TObject() const
            {
                return object;
            }

            operator const TObject *() const
            {
                return &object;
            }

            operator TObject *()
            {
                return &object;
            }

            Signal<TObject>& operator=(const TObject &obj)
            {
                object = obj;
                propagate();
                return *this;
            }

            Signal<TObject>& operator=(const Signal<TObject> &signal)
            {
                object = signal.object;
                propagate();
                return *this;
            }

            template <typename TObject2, typename std::enable_if<std::is_convertible<TObject2, TObject>::value, TObject2>::type* = nullptr>
            Signal<TObject>& operator=(const TObject2 &obj)
            {
                object = obj;
                propagate();
                return *this;
            }

            template <typename TObject2, typename std::enable_if<!std::is_convertible<TObject2, TObject>::value, TObject2>::type* = nullptr>
            Signal<Object>& operator=(const TObject2 &obj)
            {
                static_assert(std::is_convertible<TObject2, TObject>::value, "Signal object type is not convertible.");
                return *this;
            }

            template <typename TObject2, typename std::enable_if<std::is_convertible<TObject2, TObject>::value, TObject2>::type* = nullptr>
            Signal<TObject>& operator=(const Signal<TObject2> &signal)
            {
                object = signal.object;
                propagate();
                return *this;
            }

            template <typename TObject2, typename std::enable_if<!std::is_convertible<TObject2, TObject>::value, TObject2>::type* = nullptr>
            Signal<Object>& operator=(const Signal<TObject2> &signal)
            {
                static_assert(std::is_convertible<TObject2, TObject>::value, "Signal object type is not convertible.");
                return *this;
            }

            template<typename TObject1, typename TObject2>
            friend typename std::enable_if<std::is_convertible<TObject1, TObject2>::value, Signal<TObject1>>::type
            operator+(const Signal<TObject1> &signal1, const Signal<TObject2> &signal2);

            template<typename TObject1, typename TObject2>
            friend typename std::enable_if<!std::is_convertible<TObject1, TObject2>::value, Signal<TObject1>>::type
            operator+(const Signal<TObject1> &signal1, const Signal<TObject2> &signal2);

            template<typename TObject1, typename TObject2>
            friend typename std::enable_if<std::is_convertible<TObject1, TObject2>::value, Signal<TObject1>>::type
            operator-(const Signal<TObject1> &signal1, const Signal<TObject2> &signal2);

            template<typename TObject1, typename TObject2>
            friend typename std::enable_if<!std::is_convertible<TObject1, TObject2>::value, Signal<TObject1>>::type
            operator-(const Signal<TObject1> &signal1, const Signal<TObject2> &signal2);

            template<typename TObject1, typename TObject2>
            friend typename std::enable_if<std::is_convertible<TObject1, TObject2>::value, Signal<TObject1>>::type
            operator*(const Signal<TObject1> &signal1, const Signal<TObject2> &signal2);

            template<typename TObject1, typename TObject2>
            friend typename std::enable_if<!std::is_convertible<TObject1, TObject2>::value, Signal<TObject1>>::type
            operator*(const Signal<TObject1> &signal1, const Signal<TObject2> &signal2);

            template<typename TObject1, typename TObject2>
            friend typename std::enable_if<std::is_convertible<TObject1, TObject2>::value, Signal<TObject1>>::type
            operator/(const Signal<TObject1> &signal1, const Signal<TObject2> &signal2);

            template<typename TObject1, typename TObject2>
            friend typename std::enable_if<!std::is_convertible<TObject1, TObject2>::value, Signal<TObject1>>::type
            operator/(const Signal<TObject1> &signal1, const Signal<TObject2> &signal2);

            // TODO: Implement operator==, !=, <, etc. Feed-through to corresponding TObject methods.

            bool isDynamicData() const
            {
                return std::is_same<TObject, ls::aux::DynamicData>::value;
            }

            template <typename TInstance, typename TShadow = TObject>
            typename std::enable_if<!std::is_same<TShadow, ls::aux::DynamicData>::value, bool>::type isType() const
            {
                return std::is_same<TInstance, TObject>::value;
            }

            template <typename TInstance, typename TShadow = TObject>
            typename std::enable_if<std::is_same<TShadow, ls::aux::DynamicData>::value, bool>::type isType() const
            {
                return object.data.template is<TInstance>();
            }

            template <typename TInstance>
            static bool isSignal()
            {
                return ls::aux::TemplateTraits::isInstance<TInstance, Signal>::value;
            }

            template <typename TInstance>
            static bool isSignal(const TInstance &)
            {
                return ls::aux::TemplateTraits::isInstance<TInstance, Signal>::value;
            }

            bool connect(Signal<TObject> * other)
            {
                // If self is input, no connections can be made.
                if (isInput)
                    return false;

                // If other is not input, no connections can be made.
                if (!other->isInput)
                    return false;

                SignalBase::connectionPtrs.insert(other);
                connectionNumber++;

                other->connectionPtrs.insert(this);
                other->connectionNumber++;

                static_assert(other->connectionNumber < 2, "There cannot be multiple connections to an input slot.");

                return true;
            }

            bool connect(Signal<TObject> & other)
            {
                // If self is input, no connections can be made.
                if (isInput)
                    return false;

                // If other is not input, no connections can be made.
                if (!other.isInput)
                    return false;

                SignalBase::connectionPtrs.insert(&other);
                connectionNumber++;

                other.connectionPtrs.insert(this);
                other.connectionNumber++;

                assert(other.connectionNumber < 2 && "There cannot be multiple connections to an input slot.");

                return true;
            }

            bool disconnect(Signal<TObject> * other)
            {
                auto res1 = SignalBase::connectionPtrs.erase(other);
                auto res2 = other->connectionPtrs.erase(this);

                if ((res1 == 1) && (res2 == 1)) {
                    connectionNumber--;
                    other->connectionNumber--;

                    return true;
                }

                return false;
            }

            bool disconnect(Signal<TObject> & other)
            {
                auto res1 = SignalBase::connectionPtrs.erase(&other);
                auto res2 = other.connectionPtrs.erase(this);

                if ((res1 == 1) && (res2 == 1)) {
                    connectionNumber--;
                    other.connectionNumber--;

                    return true;
                }

                return false;
            }

            void propagate()
            {
                if (!isInput)
                    for (int i = 0; i < connectionNumber; i++)
                        static_cast<Signal<TObject>*>(getConnection(i))->operator=(object);
            }

            template <typename TInstance>
            static typename std::enable_if<ls::aux::TemplateTraits::isInstance<TInstance, Signal>::value, TInstance>::type toSignal(const TInstance &obj)
            {
                return obj;
            }

            template <typename TInstance>
            static typename std::enable_if<!ls::aux::TemplateTraits::isInstance<TInstance, Signal>::value, Signal<TInstance>>::type toSignal(const TInstance &obj)
            {
                return Signal<TInstance>{obj};
            }

            Object object;
        };

        template<typename TObject1, typename TObject2>
        typename std::enable_if<std::is_convertible<TObject1, TObject2>::value, Signal<TObject1>>::type
        operator+(const Signal<TObject1> &signal1, const Signal<TObject2> &signal2)
        {
            TObject1 obj = signal1.object + signal2.object;
            return Signal<TObject1>{obj};
        }

        template<typename TObject1, typename TObject2>
        typename std::enable_if<!std::is_convertible<TObject1, TObject2>::value, Signal<TObject1>>::type
        operator+(const Signal<TObject1> &signal1, const Signal<TObject2> &signal2)
        {
            static_assert(std::is_convertible<TObject1, TObject2>::value, "Signal object type is not convertible.");
            return signal1;
        }

        template<typename TObject1, typename TObject2>
        typename std::enable_if<std::is_convertible<TObject1, TObject2>::value, Signal<TObject1>>::type
        operator-(const Signal<TObject1> &signal1, const Signal<TObject2> &signal2)
        {
            TObject1 obj = signal1.object - signal2.object;
            return Signal<TObject1>{obj};
        }

        template<typename TObject1, typename TObject2>
        typename std::enable_if<!std::is_convertible<TObject1, TObject2>::value, Signal<TObject1>>::type
        operator-(const Signal<TObject1> &signal1, const Signal<TObject2> &signal2)
        {
            static_assert(std::is_convertible<TObject1, TObject2>::value, "Signal object type is not convertible.");
            return signal1;
        }

        template<typename TObject1, typename TObject2>
        typename std::enable_if<std::is_convertible<TObject1, TObject2>::value, Signal<TObject1>>::type
        operator*(const Signal<TObject1> &signal1, const Signal<TObject2> &signal2)
        {
            TObject1 obj = signal1.object * signal2.object;
            return Signal<TObject1>{obj};
        }

        template<typename TObject1, typename TObject2>
        typename std::enable_if<!std::is_convertible<TObject1, TObject2>::value, Signal<TObject1>>::type
        operator*(const Signal<TObject1> &signal1, const Signal<TObject2> &signal2)
        {
            static_assert(std::is_convertible<TObject1, TObject2>::value, "Signal object type is not convertible.");
            return signal1;
        }

        template<typename TObject1, typename TObject2>
        typename std::enable_if<std::is_convertible<TObject1, TObject2>::value, Signal<TObject1>>::type
        operator/(const Signal<TObject1> &signal1, const Signal<TObject2> &signal2)
        {
            TObject1 obj = signal1.object / signal2.object;
            return Signal<TObject1>{obj};
        }

        template<typename TObject1, typename TObject2>
        typename std::enable_if<!std::is_convertible<TObject1, TObject2>::value, Signal<TObject1>>::type
        operator/(const Signal<TObject1> &signal1, const Signal<TObject2> &signal2)
        {
            static_assert(std::is_convertible<TObject1, TObject2>::value, "Signal object type is not convertible.");
            return signal1;
        }

        template <typename TObject>
        static std::ostream& operator<<(std::ostream& os, const Signal<TObject>& signal)
        {
            os << (TObject) signal;
            return os;
        }
    }
}


#endif //LODESTAR_SIGNAL_HPP
