
# Table of Contents

1.  [Introduction](#org61712f0)
    1.  [Download and compiling the library](#orge54e64f)
2.  [Exercise](#orgc21e6f0)



<a id="org61712f0"></a>

# Introduction

The goal of the following exercises is to implement a statechart on
the Linux OS. 

We will use the `sc_minilib` library :

<https://gitlab-etu.fil.univ-lille1.fr/cle-2021/sc_minilib>


<a id="orge54e64f"></a>

## Download and compiling the library

Compile and execute the fan example:

-   Make a directory "build", go inside it, and type cmake and make :
    
        mkdir build
        cd build
        cmake ..
        make

-   execute the fan example with 
    
        ./examples/fan/fandemo


<a id="orgc21e6f0"></a>

# Exercise

The goal of the exercise is to implement the AC system that you
designed in the previous TP with the `sc_minilib` library.

Add a directory `examples/ac/` to contain the implementation of
the AC controller.

-   add a `CMakeLists.txt` to the directory and modify the
    `examples/CMakeLists.txt` accordingly

To simulate the automatic mode, you can change the external
temperature with an appropriate command. For example, you can use
the following commands:

-   key "\*" to turn on/off the system;
-   key "m" to switch to manual mode and change between "Heating"
    and "Cooling";
-   key "+" and "-" to increase/decrease the desired temperature;
-   key "t" to enter a value of the current tempeature.

**Optional**: To better show the results on the screen, you can use
the ncurses library:

-   <https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html>
-   <https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html#COMPILECURSES>

This allows you to interact with the system in a more natural way
(e.g. by simple keypresses and output at fixed positions in the
screen).

