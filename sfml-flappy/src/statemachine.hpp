#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <memory>
#include <stack>

#include "state.hpp"

namespace evansofts {
    using StateRef = std::unique_ptr<State>;

    class StateMachine {
    public:
        StateMachine(){}
        virtual ~StateMachine(){}

        void AddState(StateRef newState, bool isReplacing= true);
        void RemoveState();

        void ProcessStateChanges();

        StateRef& GetActiveState();
    private:
        std::stack<StateRef> _states;
        StateRef _newState;

        bool _isRemoving;
        bool _isAdding;
        bool _isReplacing;
    };
}


#endif