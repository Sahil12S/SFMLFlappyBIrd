#pragma once

#include <memory>
#include <stack>

#include "State.h"

namespace SSEngine
{
    typedef std::unique_ptr<State> StateRef;

    class StateMachine
    {
    public:
        StateMachine() {}
        ~StateMachine() {}

        /*
         * Add a new state to stack and remove the existing one
         * Since we don't need existing state anymore
         */
        void AddState(StateRef newState, bool isReplacing = true);
        void RemoveState();

        /*
         * Runs at start of each loop in Game class
         */
        void ProcessStateChange();

        /* Return top-level state which in turn will run
         * Drawing, handling input, updating game logic
         */
        StateRef& GetActiveState();

    private:
        std::stack<StateRef> m_States;

        /*
         * Latest state to add
         */
        StateRef m_NewState;

        /*
         * Check for handling states
         sta*/
        bool m_IsRemoving;
        bool m_IsAdding;
        bool m_IsReplacing;
    };
}