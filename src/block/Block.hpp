//
// Created by Hamza El-Kebir on 5/27/21.
//

#ifndef LODESTAR_BLOCK_HPP
#define LODESTAR_BLOCK_HPP

#define INPUT_SLOT_TYPE(BLOCK, SLOTIDX) typename std::tuple_element<SLOTIDX, decltype(BLOCK)::TDInputsTuple>::type
#define INPUT_SLOT_TYPE_TD(BLOCK, SLOTIDX) typename std::tuple_element<SLOTIDX, BLOCK::TDInputsTuple>::type
#define INPUT_SLOT_TYPE_INTERNAL(SLOTIDX) typename std::tuple_element<SLOTIDX, TDInputsTuple>::type

#define INPUT_CALLBACK_TYPE(BLOCK, SLOTIDX) typename std::remove_reference<decltype(*std::begin(std::declval<typename std::tuple_element<SLOTIDX, decltype(BLOCK)::TDInputCallbackTuple>::type &>()))>::type
#define INPUT_CB_TYPE(BLOCK, SLOTIDX) std::function<LS_CB_RETURN_TYPE(INPUT_SLOT_TYPE(BLOCK, SLOTIDX))>
#define INPUT_CB_TYPE_TD(BLOCK, SLOTIDX) std::function<bool(INPUT_SLOT_TYPE_TD(BLOCK, SLOTIDX))>
#define INPUT_CB_TYPE_INTERNAL(SLOTIDX) std::function<LS_CB_RETURN_TYPE(INPUT_SLOT_TYPE_INTERNAL(SLOTIDX))>

#define OUTPUT_SLOT_TYPE(BLOCK, SLOTIDX) typename std::tuple_element<SLOTIDX, decltype(BLOCK)::TDOutputsTuple>::type
#define OUTPUT_SLOT_TYPE_TD(BLOCK, SLOTIDX) typename std::tuple_element<SLOTIDX, BLOCK::TDOutputsTuple>::type
#define OUTPUT_SLOT_TYPE_INTERNAL(SLOTIDX) typename std::tuple_element<SLOTIDX, TDOutputsTuple>::type

#define OUTPUT_CALLBACK_TYPE(BLOCK, SLOTIDX) typename std::remove_reference<decltype(*std::begin(std::declval<typename std::tuple_element<SLOTIDX, decltype(BLOCK)::TDOutputCallbackTuple>::type &>()))>::type
#define OUTPUT_CB_TYPE(BLOCK, SLOTIDX) std::function<bool(OUTPUT_SLOT_TYPE(BLOCK, SLOTIDX))>
#define OUTPUT_CB_TYPE_TD(BLOCK, SLOTIDX) std::function<bool(OUTPUT_SLOT_TYPE_TD(BLOCK, SLOTIDX))>
#define OUTPUT_CB_TYPE_INTERNAL(SLOTIDX) std::function<LS_CB_RETURN_TYPE(OUTPUT_SLOT_TYPE_INTERNAL(SLOTIDX))>

#include <tuple>
#include <array>
#include <functional>
#include <type_traits>
#include <map>
#include <cassert>
#include "aux/Conjunction.hpp"
#include "BlockBase.hpp"
#include "Ticket.hpp"

namespace ls {
    namespace block {
        template<typename TInputsList, typename TOutputsList, size_t TCallbackNumber = LS_MAX_CALLBACKS, size_t TTicketNumber = LS_MAX_TICKETS>
        class Block : public BlockBase {
        };

        template<typename... TInputs, typename... TOutputs, size_t TCallbackNumber, size_t TTicketNumber>
        class Block<std::tuple<TInputs...>, std::tuple<TOutputs...>, TCallbackNumber, TTicketNumber>
                : public BlockBase {
        public:
            typedef std::tuple<TInputs...> TDInputsTuple;
            typedef std::tuple<TOutputs...> TDOutputsTuple;
            typedef std::tuple<std::array<std::function<LS_CB_RETURN_TYPE(
                    TInputs)>, TCallbackNumber>...> TDInputCallbackTuple;
            typedef std::tuple<std::array<std::function<LS_CB_RETURN_TYPE(
                    TOutputs)>, TCallbackNumber>...> TDOutputCallbackTuple;

            typedef TicketBook<sizeof...(TOutputs), TTicketNumber> TDTicketBook;

            Block() : inputs_(TDInputsTuple{}), outputs_(TDOutputsTuple{}), inputCallbacks_(TDInputCallbackTuple{}),
                      outputCallbacks_(TDOutputCallbackTuple{}), ticketBook_(TDTicketBook{})
            {}

            template<size_t TSlotIdx>
            inline INPUT_SLOT_TYPE_INTERNAL(TSlotIdx) getInput()
            {
                return std::get<TSlotIdx>(inputs_);
            }

            template<size_t TSlotIdx>
            inline void setInput(INPUT_SLOT_TYPE_INTERNAL(TSlotIdx) value)
            {
                std::get<TSlotIdx>(inputs_) = value;

                callbackInput<TSlotIdx>(value);
            }

            template<size_t TSlotIdx>
            inline OUTPUT_SLOT_TYPE_INTERNAL(TSlotIdx) getOutput()
            {
                return std::get<TSlotIdx>(outputs_);
            }

            template<size_t TSlotIdx>
            inline void setOutput(OUTPUT_SLOT_TYPE_INTERNAL(TSlotIdx) value)
            {
                std::get<TSlotIdx>(outputs_) = value;

                callbackOutput<TSlotIdx>(value);
            }

            template<size_t TSlotIdx, size_t TArrIdx>
            inline INPUT_CB_TYPE_INTERNAL(TSlotIdx) getInputCallback()
            {
                return std::get<TArrIdx>(std::get<TSlotIdx>(inputCallbacks_));
            }

            template<size_t TSlotIdx, size_t TArrIdx>
            inline void clearInputCallback(size_t idx)
            {
                if (TArrIdx < TCallbackNumber)
                    std::get<TSlotIdx>(inputCallbacks_)[TArrIdx] = INPUT_CB_TYPE_INTERNAL(TSlotIdx){};
            }

            template<size_t TSlotIdx>
            inline void clearInputCallback(size_t idx)
            {
                if (idx < TCallbackNumber)
                    std::get<TSlotIdx>(inputCallbacks_)[idx] = INPUT_CB_TYPE_INTERNAL(TSlotIdx){};
            }

            template<size_t TSlotIdx>
            inline void clearInputCallbacks()
            {
                for (size_t i = 0; i < TCallbackNumber; i++)
                    std::get<TSlotIdx>(inputCallbacks_)[i] = INPUT_CB_TYPE_INTERNAL(TSlotIdx){};
            }

            inline void clearInputCallbacks()
            {
                recursivelyClearInputCallbacks<sizeof...(TInputs) - 1>();
            }

            template<size_t TSlotIdx>
            inline INPUT_CB_TYPE_INTERNAL(TSlotIdx) getInputCallback(size_t idx)
            {
                if (idx < TCallbackNumber)
                    return std::get<TSlotIdx>(inputCallbacks_)[idx];
            }

            template<size_t TSlotIdx, size_t TArrIdx>
            inline void setInputCallback(INPUT_CB_TYPE_INTERNAL(TSlotIdx) value)
            {
                std::get<TArrIdx>(std::get<TSlotIdx>(inputCallbacks_)) = value;
            }

            template<size_t TSlotIdx>
            inline void setInputCallback(INPUT_CB_TYPE_INTERNAL(TSlotIdx) value, size_t idx)
            {
                if (idx < TCallbackNumber)
                    std::get<TSlotIdx>(inputCallbacks_)[idx] = value;
            }

            template<size_t TSlotIdx>
            inline void setInputCallback(INPUT_CB_TYPE_INTERNAL(TSlotIdx) value)
            {
                size_t i = 0;
                while (i < TCallbackNumber) {
                    if (!std::get<TSlotIdx>(inputCallbacks_)[i]) {
                        std::get<TSlotIdx>(inputCallbacks_)[i] = value;
                        break;
                    }

                    i++;
                }
            }

            template<size_t TSlotIdx>
            inline OUTPUT_CB_TYPE_INTERNAL(TSlotIdx) getOutputCallback(size_t idx)
            {
                if (idx < TCallbackNumber)
                    return std::get<TSlotIdx>(outputCallbacks_)[idx];
            }

            template<size_t TSlotIdx, size_t TArrIdx>
            inline void clearOutputCallback(size_t idx)
            {
                if (TArrIdx < TCallbackNumber)
                    std::get<TSlotIdx>(outputCallbacks_)[TArrIdx] = OUTPUT_CB_TYPE_INTERNAL(TSlotIdx){};
            }

            template<size_t TSlotIdx>
            inline void clearOutputCallback(size_t idx)
            {
                if (idx < TCallbackNumber)
                    std::get<TSlotIdx>(outputCallbacks_)[idx] = OUTPUT_CB_TYPE_INTERNAL(TSlotIdx){};
            }

            template<size_t TSlotIdx>
            inline void clearOutputCallbacks()
            {
                for (size_t i = 0; i < TCallbackNumber; i++)
                    std::get<TSlotIdx>(outputCallbacks_)[i] = OUTPUT_CB_TYPE_INTERNAL(TSlotIdx){};
            }

            inline void clearOutputCallbacks()
            {
                recursivelyClearOutputCallbacks<sizeof...(TInputs) - 1>();
            }

            template<size_t TSlotIdx, size_t TArrIdx>
            inline void setOutputCallback(OUTPUT_CB_TYPE_INTERNAL(TSlotIdx) value)
            {
                std::get<TArrIdx>(std::get<TSlotIdx>(outputCallbacks_)) = value;
            }

            template<size_t TSlotIdx>
            inline void setOutputCallback(OUTPUT_CB_TYPE_INTERNAL(TSlotIdx) value, size_t idx)
            {
                if (idx < TCallbackNumber)
                    std::get<TSlotIdx>(outputCallbacks_)[idx] = value;
            }

            template<size_t TSlotIdx>
            inline void setOutputCallback(INPUT_CB_TYPE_INTERNAL(TSlotIdx) value)
            {
                size_t i = 0;
                while (i < TCallbackNumber) {
                    if (!std::get<TSlotIdx>(outputCallbacks_)[i]) {
                        std::get<TSlotIdx>(outputCallbacks_)[i] = value;
                        break;
                    }

                    i++;
                }
            }

            // Recursive full connection if this output and other input are the same.
            /*
             * We use Conjunction to evaluate if TOutputs and TInputsOther are equal (i.e., both blocks mesh together). Note
             * that this is order dependent.
             */
            template<typename... TInputsOther, typename... TOutputsOther, size_t TCallbackNumberOther, size_t TTicketNumberOther>
            inline typename std::enable_if<Conjunction<std::is_same<TOutputs, TInputsOther>...>::value, bool>::type
            connect(Block<std::tuple<TInputsOther...>, std::tuple<TOutputsOther...>, TCallbackNumberOther, TTicketNumberOther> &other)
            {
                return recursivelyConnect<sizeof...(TOutputs) - 1, sizeof...(TOutputs) - 1>(other);
            }

            template<size_t TOutputSlotIdx, size_t TInputSlotIdx, typename... TInputsOther, typename... TOutputsOther, size_t TCallbackNumberOther, size_t TTicketNumberOther>
            inline bool
            connect(Block<std::tuple<TInputsOther...>, std::tuple<TOutputsOther...>, TCallbackNumberOther, TTicketNumberOther> &other)
            {

                // FIXME: Make return type smarter, aka implement Status struct.
                /* FIXME: In callback, dispatch the caller block's BlockBase pointer, so that when a callback is called in a
                 *  block that is also the caller (i.e., callee == caller, or, other == source), a custom exception is thrown
                 *  that is caught by the dispatcher.
                 *  How? Option: carry callstack with you (i.e., array of BlockBase pointers padded with nullpointers), and
                 *  if current callee is in callstack, throw templated exception (RecursionException<BlockBase *>) that is only
                 *  caught by original caller. The drawback is that this requires allocating memory for
                 *  std::array<size_t, N>, where N may not be computable at compile-time.
                 */
                OUTPUT_CB_TYPE_INTERNAL(TOutputSlotIdx) cbNew = [this, &other](
                        OUTPUT_SLOT_TYPE_INTERNAL(TOutputSlotIdx) out) {
                    other.template setInput<TInputSlotIdx>(this->template getOutput<TOutputSlotIdx>());

                    return LS_CB_RETURN_TYPE{};
                };

                // Assign to empty output callback function.
                bool success = false;
                for (size_t i = 0; i < TCallbackNumber; i++) {
                    OUTPUT_CB_TYPE_INTERNAL(TOutputSlotIdx) cb = getOutputCallback<TOutputSlotIdx>(i);

                    if (!cb) {
                        setOutputCallback<TOutputSlotIdx>(cbNew, i);

                        Ticket ticket{};
                        ticket.destAddress = (size_t) &other;
                        ticket.destSlot = TInputSlotIdx;
                        ticket.callbackSlot = i;
                        ticket.active = true;
                        ticket.expired = false;

                        addTicket(ticket, TOutputSlotIdx);

                        success = true;
                        break;
                    }
                }

                assert(success && "Failed to make block-block connection; no open callback slots.");

                return success;
            }

            template<typename... TInputsOther, typename... TOutputsOther, size_t TCallbackNumberOther, size_t TTicketNumberOther>
            inline typename std::enable_if<Conjunction<std::is_same<TOutputs, TInputsOther>...>::value, bool>::type
            disconnect(
                    Block<std::tuple<TInputsOther...>, std::tuple<TOutputsOther...>, TCallbackNumberOther, TTicketNumberOther> &other)
            {
                return recursivelyDisconnect<sizeof...(TOutputs) - 1, sizeof...(TOutputs) - 1>(other);
            }

            template<size_t TOutputSlotIdx, size_t TInputSlotIdx, typename... TInputsOther, typename... TOutputsOther, size_t TCallbackNumberOther, size_t TTicketNumberOther>
            inline bool
            disconnect(
                    Block<std::tuple<TInputsOther...>, std::tuple<TOutputsOther...>, TCallbackNumberOther, TTicketNumberOther> &other)
            {
                auto destAddress = (size_t) &other;

                size_t i = 0;
                for (Ticket ticket: ticketBook_.tickets[TOutputSlotIdx]) {
                    if (ticket.destAddress == destAddress) {
                        removeTicket<TOutputSlotIdx>(i);
                    }
                    i++;
                }

                return true;
            }

            inline Ticket getTicket(size_t slot, size_t idx)
            {
                return ticketBook_.tickets[slot][idx];
            }

        protected:
            TDInputsTuple inputs_;
            TDOutputsTuple outputs_;

            TDInputCallbackTuple inputCallbacks_;
            TDOutputCallbackTuple outputCallbacks_;

            TDTicketBook ticketBook_;

            template<size_t TSlotIdx>
            inline void callbackInput(const INPUT_SLOT_TYPE_INTERNAL(TSlotIdx) &value)
            {
                for (size_t i = 0; i < TCallbackNumber; i++) {
                    INPUT_CB_TYPE_INTERNAL(TSlotIdx) cb = getInputCallback<TSlotIdx>(i);

                    if (cb)
                        getInputCallback<TSlotIdx>(i)(value);
                }
            }

            template<size_t TSlotIdx>
            inline void callbackOutput(const OUTPUT_SLOT_TYPE_INTERNAL(TSlotIdx) &value)
            {
                for (size_t i = 0; i < TCallbackNumber; i++) {
                    OUTPUT_CB_TYPE_INTERNAL(TSlotIdx) cb = getOutputCallback<TSlotIdx>(i);

                    if (cb)
                        getOutputCallback<TSlotIdx>(i)(value);
                }
            }

            bool addTicket(const Ticket &ticket, const size_t slot)
            {
                bool success = false;
                for (size_t i = 0; i < TTicketNumber; i++) {
                    if (!ticketBook_.tickets[slot][i].active) {
                        ticketBook_.tickets[slot][i] = ticket;

                        success = true;
                        break;
                    }
                }

                assert(success && "Failed to add ticket; no inactive tickets.");

                return success;
            }

            template<size_t TSlotIdx>
            bool removeTicket(const size_t ticketNumber)
            {
                Ticket *ticket = &ticketBook_.tickets[TSlotIdx][ticketNumber];
                ticket->destAddress = 0;
                ticket->destSlot = 0;
                ticket->callbackSlot = 0;
                ticket->active = false;

                setOutputCallback<TSlotIdx>(OUTPUT_CB_TYPE_INTERNAL(TSlotIdx){}, ticket->callbackSlot);

                return true;
            }

            template<size_t TOutputSlotIdx, size_t TInputSlotIdx, typename... TInputsOther, typename... TOutputsOther, size_t TCallbackNumberOther, size_t TTicketNumberOther>
            inline typename std::enable_if<Conjunction<std::is_same<TOutputs, TInputsOther>...>::value &&
                                           (TOutputSlotIdx > 0) && (TInputSlotIdx > 0), bool>::type recursivelyConnect(
                    Block<std::tuple<TInputsOther...>, std::tuple<TOutputsOther...>, TCallbackNumberOther, TTicketNumberOther> &other)
            {
                connect<TOutputSlotIdx, TInputSlotIdx>(other);
                return recursivelyConnect<TOutputSlotIdx - 1, TOutputSlotIdx - 1>(other);
            }

            template<size_t TOutputSlotIdx, size_t TInputSlotIdx, typename... TInputsOther, typename... TOutputsOther, size_t TCallbackNumberOther, size_t TTicketNumberOther>
            inline typename std::enable_if<Conjunction<std::is_same<TOutputs, TInputsOther>...>::value &&
                                           (TOutputSlotIdx == 0) && (TInputSlotIdx == 0), bool>::type
            recursivelyConnect(
                    Block<std::tuple<TInputsOther...>, std::tuple<TOutputsOther...>, TCallbackNumberOther, TTicketNumberOther> &other)
            {
                connect<0, 0>(other);
                return true;
            }

            template<size_t TOutputSlotIdx, size_t TInputSlotIdx, typename... TInputsOther, typename... TOutputsOther, size_t TCallbackNumberOther, size_t TTicketNumberOther>
            inline typename std::enable_if<Conjunction<std::is_same<TOutputs, TInputsOther>...>::value &&
                                           (TOutputSlotIdx > 0) && (TInputSlotIdx > 0), bool>::type
            recursivelyDisconnect(
                    Block<std::tuple<TInputsOther...>, std::tuple<TOutputsOther...>, TCallbackNumberOther, TTicketNumberOther> &other)
            {
                disconnect<TOutputSlotIdx, TInputSlotIdx>(other);
                return recursivelyDisconnect<TOutputSlotIdx - 1, TOutputSlotIdx - 1>(other);
            }

            template<size_t TOutputSlotIdx, size_t TInputSlotIdx, typename... TInputsOther, typename... TOutputsOther, size_t TCallbackNumberOther, size_t TTicketNumberOther>
            inline typename std::enable_if<Conjunction<std::is_same<TOutputs, TInputsOther>...>::value &&
                                           (TOutputSlotIdx == 0) && (TInputSlotIdx == 0), bool>::type
            recursivelyDisconnect(
                    Block<std::tuple<TInputsOther...>, std::tuple<TOutputsOther...>, TCallbackNumberOther, TTicketNumberOther> &other)
            {
                disconnect<0, 0>(other);
                return true;
            }

            template<size_t TSlotIdx>
            inline typename std::enable_if<(TSlotIdx > 0), bool>::type recursivelyClearInputCallbacks()
            {
                clearInputCallbacks<TSlotIdx>();
                return recursivelyClearInputCallbacks<TSlotIdx - 1>();
            }

            template<size_t TSlotIdx>
            inline typename std::enable_if<(TSlotIdx == 0), bool>::type recursivelyClearInputCallbacks()
            {
                clearInputCallbacks<0>();
                return true;
            }

            template<size_t TSlotIdx>
            inline typename std::enable_if<(TSlotIdx > 0), bool>::type recursivelyClearOutputCallbacks()
            {
                clearOutputCallbacks<TSlotIdx>();
                return recursivelyClearOutputCallbacks<TSlotIdx - 1>();
            }

            template<size_t TSlotIdx>
            inline typename std::enable_if<(TSlotIdx == 0), bool>::type recursivelyClearOutputCallbacks()
            {
                clearOutputCallbacks<0>();
                return true;
            }
        };
    }
}

#endif //LODESTAR_BLOCK_HPP
