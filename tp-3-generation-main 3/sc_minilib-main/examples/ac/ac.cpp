
#include <sm_defs.h>
#include <timeout.h>
#include <iostream>
#include <state_chart.hpp>
#include <display.h> 
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#define LOG_AREA_X 10
#define LOG_AREA_Y 20
#define LIMIT_TIME 1800

using namespace std;
int c;

void sig_handler(int signum){
    c = get_input();
    
  //printf("Inside handler function\n");
}
 




void* func(void* arg)
{
    // detach the current thread
    // from the calling thread
    pthread_detach(pthread_self());
  
    printf("Inside the thread\n");
  
    // exit the current thread
    pthread_exit(NULL);
}


class MainSM : public StateMachine {
    SimpleState *root_state;
public:
    MainSM(SimpleState &root) : root_state(&root) {}
    void handler(Evt_t evt) {
        root_state->handler(evt);
    }
};  
enum Events {ONOFF, PLUS, MODE, MINUS, ExtTempChange, TICK};

void print_state( const char * state) {
    std::stringstream ss;
    ss << "Mode : " << state;        
    print_line(1, ss.str().c_str());
    show_display();
}

void print_timer(int timer) {
    string res = "Timer: " + to_string(timer);
    const char * str = res.c_str();
    print_line(10, str);
    show_display();
}

void print_temp(int tD, int tE ){
    
    string tempD = "desired temperature : " + to_string(tD) + "°";
    string tempE = "current temperature : " + to_string(tE) + "°";  // temperatureExt
    print_line(12, tempD.c_str());
    print_line(11, tempE.c_str());    // temperatureExt
    show_display();
}

int main()
{
    // the root state
    OrthogonalState ACmachine("ACmachine");
    // the state machine structure (thread)
    MainSM sm(ACmachine);
    // global variable for this machine
    int ExtTemp = 20;
    int desTemp = ExtTemp;
    //int time = 0; 
    time_t debut;

    debut = time(NULL);

    init_display(2,2,60,15);

    print_line(5, "(*) : on/off");
    print_line (6,"(+/-) : increase/decrease temperature "); 
    print_line(7, "(m) for change mode");
    print_line(8, "(t) enter current temperature ");
    print_line(9, "(q) : quit simulation");
    //print_line_int(10, "Timer : %d", time);
    
    CompositeState Region1("AC");
    //CompositeState Region2("TimeOut");

    ACmachine.add_region(Region1);
    //ACmachine.add_region(Region2);

    // FIRST REGION

    SimpleState OffState("OffState");
    CompositeState Manuel("Manuel");
    CompositeState Automatique("Automatique");
    
    SimpleState Chauffage("Chauffage");
    SimpleState Refroidissement("Refroidissement");
    SimpleState Pause("Pause");

    SimpleState Chauffage2("Chauffage");
    SimpleState Refroidissement2("Refroidissement");
    SimpleState Pause2("Pause");
    
    Region1.add_child(Manuel);
    Region1.add_child(Automatique);
    Region1.add_child(OffState);
    Region1.set_initial(OffState);

    Manuel.add_child(Chauffage);
    Manuel.add_child(Refroidissement);
    Manuel.add_child(Pause);
    Manuel.set_initial(Pause);
    Manuel.set_history(true);

    Automatique.add_child(Chauffage2);
    Automatique.add_child(Refroidissement2);
    Automatique.add_child(Pause2);
    Automatique.set_initial(Pause2);
    Automatique.set_history(true);


    Transition AutomatiqueChangeTemp(Automatique, Automatique, 
                        ExtTempChange,
                        [&desTemp,&ExtTemp](){desTemp = ExtTemp;});

    // Transition en manuel

    Transition OffStateManuel(OffState, Manuel, 
                        ONOFF,
                        empty_action);

    Transition Pause_Chauffage(Pause, Chauffage,
                        MODE,
                        [](){});

    Transition Chauffage_Refroidissement(Chauffage, Refroidissement,
                        MODE,
                        [](){});

    Transition Refroidissement_Pause(Refroidissement, Pause,
                        MODE,
                        [](){});
    
    Transition Manuel_Automatique_Plus(Manuel, Automatique,
                        PLUS,
                        [&sm](){sm.send(ExtTempChange);});
    
    Transition Manuel_Automatique_Minus(Manuel, Automatique,
                        MINUS,
                        [&sm](){sm.send(ExtTempChange);});
    

    // Transition en automatique 

    Transition Pause2_Refroidissement2(Pause2, Refroidissement2, 
                            [&desTemp,&ExtTemp](Evt_t evt) {
                                return (evt == MINUS ) and (desTemp +1 < ExtTemp);
                             },
                             [&desTemp](){desTemp--;});


    Transition Refroidissement2_Chauffage2(Refroidissement2, Chauffage2, 
                            [&desTemp,&ExtTemp](Evt_t evt) {
                                return (evt == PLUS ) and (desTemp -1 > ExtTemp );
                             },
                             empty_action );

    Transition Chauffage2_Refroidissement2(Chauffage2, Refroidissement2, 
                            [&desTemp,&ExtTemp](Evt_t evt) {
                                return (evt == MINUS ) and (desTemp +1 < ExtTemp);
                             },
                             empty_action );

    Transition Chauffage2_Pause2(Chauffage2, Pause2, 
                            [&desTemp,&ExtTemp](Evt_t evt) {
                                return (evt == MINUS ) and (desTemp -1 <= ExtTemp && ExtTemp <= desTemp +1);
                             },
                             [&desTemp](){desTemp--;});

    Transition Refroidissement2_Pause2(Refroidissement2, Pause2, 
                            [&desTemp,&ExtTemp](Evt_t evt) {
                                return (evt == PLUS ) and (desTemp -1 <= ExtTemp && ExtTemp <= desTemp +1);
                             },
                            [&desTemp](){desTemp++;});     
    
    Transition Pause2_chauffage2(Pause2, Chauffage2, 
                            [&desTemp,&ExtTemp](Evt_t evt) {
                                return (evt == PLUS ) and (desTemp -1 > ExtTemp );
                             },
                            [&desTemp](){desTemp++;});   


    Transition Automatique_Manuel(Automatique, Manuel,
                       MODE,
                       [](){});
 
    Transition Automatique_Automatique1(Automatique, Automatique,
                       PLUS,
                       [&desTemp](){desTemp++;});

    
    Transition Automatique_Automatique2(Automatique, Automatique,
                       MINUS,
                       [&desTemp](){desTemp--;});

   
    Transition Manuel_OffState(Manuel, OffState, 
                        ONOFF,
                        [](){});
    
    Transition Automatique_OffState(Automatique, OffState, 
                        ONOFF,
                        empty_action ); 
/*
    Transition Automatique_OffState2(Automatique, OffState, 
                    [&time](Evt_t evt) {
                        return (evt ==  TICK) and (time >= LIMIT_AUTOMATIC_TIME);
                    },
                    empty_action ); 
    


    // SECOND REGION

    SimpleState Time(Region2);
    Region2.add_child(Time);
    Region2.set_initial(Time);
    Transition addTime(Time, Time, 
                        TICK, 
                        [&time, &Region1](){ time++; 
                                                     print_timer(time);
                                                     print_state(Region1.get_current().get_name().c_str()); });
*/
    // Main loop
    string res;
    time_t apres;

    
    while (1) {
           /* apres = time(NULL);
            if((apres-debut)/3600  >= 10 ){
                break;
            }*/
            //int *c;
            signal(SIGALRM,sig_handler); // Register signal handler
 
            alarm(5);  // Scheduled alarm after 2 seconds
            
            if(c == '*'){
                
                sm.send(ONOFF);
            }
            else if(c == 'm'){
                res = "Bouton m pressed";
                print_line(3, res.c_str());
                sm.send(MODE);
            }
            else if (c == '+'){
                res = "Bouton plus pressed";
                print_line(3, res.c_str());
                sm.send(PLUS);
            }
            else if(c == '-'){
                res = "Bouton minus pressed";
                print_line(3, res.c_str());
                sm.send(MINUS);
            }
            else if (c == 't') {
                res = "Bouton t pressed / Enter a temperature";
                char str[10];
                print_line(3, res.c_str());
                getStr(str);
                ExtTemp = (int) atoi(str);
                sm.send(ExtTempChange);
            }
            else if (c == 'q') {
                print_at(LOG_AREA_X, LOG_AREA_Y, "Bye");
                show_display();
                break;
            }

            print_temp(desTemp, ExtTemp);
            print_state(Region1.get_current().get_name().c_str());
            
    }
    end_display();

    return 0;
}




