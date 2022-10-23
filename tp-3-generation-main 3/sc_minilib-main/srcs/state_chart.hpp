#pragma once

#include <string>
#include <vector>
#include <transition.hpp>

/* This class represents a simple state in a state chart diagram.  It
   is also the root of the composite pattern hierarchy.

   +--------------------+
   |    SimpleState     |
   +--------------------+<----+
   | handler(Evt_t evt) |     |
   +--------------------+     |
             A                |
             |                |
             |                |
   +--------------------+     |
   |   CompositeState   |     |
   +--------------------+-----+
   | handler(Evt_t evt) |
   +--------------------+

   It implements the basic machinery for handling events 
   with transitions. Every SimpleState has a set of outgoing 
   transitions. When the handler is called, it simply analyses 
   all transitions looking for one that handles the event. 
*/        
class SimpleState {
    std::vector<Transition> transitions;

    action_t entry_fun = empty_action;
    action_t exit_fun = empty_action;

protected:
    std::string name;
    
public:
    SimpleState(const std::string&n) : name (n) {}
    SimpleState(const std::string&n, action_t en, action_t ex) :
        entry_fun(en), exit_fun(ex), name(n) {}

    virtual std::string get_name() const { return name; }
    
    virtual SimpleState* handler(Evt_t evt);
    virtual void entry() { entry_fun(); }
    virtual void exit() { exit_fun(); }
    
    void add_transition(const Transition &t);
    int get_n_transitions() { return transitions.size(); }
};


class CompositeState : public SimpleState {
    SimpleState *current;
    std::vector<SimpleState *> inner;
    SimpleState *initial;
    bool history = false;
public:
    CompositeState(const std::string&n) : SimpleState(n) {}
    CompositeState(const std::string&n, action_t en, action_t ex) :
        SimpleState(n, en, ex) {}

    std::string get_name() const override { return name + "." + current->get_name(); }
    
    SimpleState * handler(Evt_t evt) override;
    void add_child(SimpleState &child);
    void set_initial(SimpleState &ini);
    SimpleState const& get_current() const { return *current; }
    void reset(); // bring back to the initial state (if not history)
    void set_history(bool h) { history = h; }
    void entry() override;
    void exit() override;
};

class OrthogonalState : public SimpleState {
    std::vector<CompositeState *> regions;
public:
    OrthogonalState(const std::string&n) : SimpleState(n) {}
    OrthogonalState(const std::string&n, action_t en, action_t ex) :
        SimpleState(n, en, ex) {}

    std::string get_name() const override {
        std::string n = name;
        n += ".(";
        int i = 0;
        for (auto *r : regions) {
            i++;
            n += r->get_name();
            if (i < regions.size()) n += "||";
        }
        n += ")";
        return n;
    }
    
    void add_region(CompositeState &r);
    SimpleState *handler(Evt_t evt) override;
    void entry() override;
    void exit() override;
};
