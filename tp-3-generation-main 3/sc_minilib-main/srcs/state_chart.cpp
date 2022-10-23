#include "state_chart.hpp"
#include <iostream>

using namespace std;

SimpleState *SimpleState::handler(Evt_t evt)
{
    SimpleState *next = nullptr;
    for (auto const& t : transitions) {
        if (t.guard(evt)) {
            if (this != t.next()) this->exit();
            t.action();
            next = t.next();
            if (this != next) next->entry();
            return next;
        }
    }
    return nullptr;
}

void SimpleState::add_transition(const Transition &t)
{
    transitions.push_back(t);
}

void CompositeState::set_initial(SimpleState &ini)
{
    initial = &ini;
    current = &ini;
}

void CompositeState::add_child(SimpleState &child)
{
    inner.push_back(&child);
}

void CompositeState::reset()
{
    if (not history) {
        current = initial;
    }
}

void CompositeState::entry()
{
    reset();
    SimpleState::entry();
    current->entry();
}

void CompositeState::exit()
{
    current->exit();
    SimpleState::exit();
}

SimpleState * CompositeState::handler(Evt_t evt)
{
    SimpleState *next = nullptr;
    next = current->handler(evt);
    if (next != nullptr) {
        current = next;
        return nullptr;
    }
    else return SimpleState::handler(evt);
}

SimpleState* OrthogonalState::handler(Evt_t evt)
{
    for (auto *c : regions) 
        c->handler(evt);
    return SimpleState::handler(evt);
}

void OrthogonalState::add_region(CompositeState &r)
{
    regions.push_back(&r);
}

void OrthogonalState::entry()
{
    SimpleState::entry();
    for(auto *s : regions) s->entry();
}

void OrthogonalState::exit()
{
    for(auto *s: regions) s->exit();
    SimpleState::exit();
}
