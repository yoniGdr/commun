SC MINILIB
==========

Version: 0.2 (beta)
Author: Giuseppe Lipari (glipari@univ-lille.fr)

Intro
-----

A minimal C++ library for implementing State Machines (StateCharts) on
Linux / POSIX.

At the lowest level, the library uses pthreads to implement the basic
event engine of a state machine.

The highest level is implemented based on the "Composite Pattern" for
hierarchical states. The current version only supports a minimal
subset of the StateChart semantic:
- Hierarchical states
- Orthogonal (parallel) regions
- Shallow history
- Entry / exit actions to / from states (do() actions are not
  currently supported)


COMPILING 
---------

To compile the library and the examples:

	mkdir build
	cd build 
	cmake ..
	make 
	
To execute the fan example:

	./build/examples/fan/fandemo


TO BE DONE
----------
- No-event transitions based on the concept of internal TICK events
- do actions (with arbitrary periods)
- Join and synchronization
- final states


