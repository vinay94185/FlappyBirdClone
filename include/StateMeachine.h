#ifndef STATEMEACHINE_H
#define STATEMEACHINE_H

#include <memory>
#include <stack>

#include <state.h>

namespace vlc
{
    typedef std::unique_ptr<State> StateRef;

    class StateMachine
    {
    public:
        StateMachine() {}
        ~StateMachine() {}

        void AddState(StateRef newState,bool isReplacing = true);
        void RemoveState();

        void ProcessStateChanges();

        StateRef &GetActiveState();

    private:
        std::stack<StateRef> _states;
        StateRef _newState;

        bool _isRemoving;
        bool _isAdding;
        bool _isReplacing;
    };
}

#endif // STATEMEACHINE_H
