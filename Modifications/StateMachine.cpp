#include "StateMachine.h"

namespace SSEngine
{
    void StateMachine::AddState(SSEngine::StateRef newState, bool isReplacing)
    {
        this->m_IsAdding = true;
        this->m_IsReplacing = isReplacing;

        this->m_NewState = std::move(newState); // Move semantics of C++11
    }

    void StateMachine::RemoveState()
    {
        this->m_IsRemoving = true;
    }

    void StateMachine::ProcessStateChange()
    {
        if ( this->m_IsRemoving && !this->m_States.empty() )
        {
            // Remove the top state
            this->m_States.pop();

            // If there is an existing state in stack, resume it
            if ( !this->m_States.empty() )
            {
                this->m_States.top()->Resume();
            }

            this->m_IsRemoving = false;
        }

        if ( this->m_IsAdding )
        {
            if ( !this->m_States.empty() )
            {
                if ( this->m_IsReplacing )
                {
                    this->m_States.pop();
                }
                else
                {
                    this->m_States.top()->Pause();
                }
            }
            // Move new state on stack and initialize it.
            this->m_States.push( std::move( this->m_NewState ) );
            this->m_States.top()->Init();
            this->m_IsAdding = false;
        }
    }

    StateRef& StateMachine::GetActiveState()
    {
        return this->m_States.top();
    }
}