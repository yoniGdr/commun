#include "transition.hpp"
#include "state_chart.hpp"

Transition::Transition(SimpleState &s, SimpleState &d) : source(&s), dest(&d)
{
    source->add_transition(*this);
}

Transition::Transition(SimpleState &s, SimpleState &d, Evt_t event) :
    source(&s), dest(&d)
{
    guard_fun = [event](Evt_t evt) { return event == evt; };
    source->add_transition(*this);
}

Transition::Transition(SimpleState &s, SimpleState &d, Evt_t event, action_t a) :
    source(&s), dest(&d), action_fun(a)
{
    guard_fun = [event](Evt_t evt) { return event == evt; };
    source->add_transition(*this);
}

Transition::Transition(SimpleState &s, SimpleState &d, guard_t g, action_t a) :
    source(&s), dest(&d), guard_fun(g), action_fun(a)
{
    source->add_transition(*this);
}

bool Transition::guard(Evt_t evt) const
{
    return guard_fun(evt);
}

void Transition::action() const
{
    action_fun();
}


