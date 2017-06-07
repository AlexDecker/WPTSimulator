WPTSimulator for ns-3
=====================

Simulator for Wireless Power Transfer by resonant inductive coupling (Module for ns3). Use it as standalone to run simple WPT simulations with basic communication or use it with ns-3 to allow simulations with both WPT aspects and advanced network protocols.

Standalone Mode
---------------

To execute one of our examples, go to the root folder of the project and type *make*. Then, type *make EXAMPLE="[example number]" run* to execute. Each example cames with a high level explanation about itself. To create your own examples, follow the steps below.

  1. Create a *.cc* file in *examples/* folder
  2. Include "examples.h" on the created file
  3. Write your code in a void function
  4. Create a new entry on the *switch* inside *main.cc* and call your function there
  5. Add the name of your *.cc* file on the variable *OBJECTS* of *examples/makefile*
  6. Go back to the root folder of the project, type *make* and then *make EXAMPLE="[number of your function in the switch]" run*
  
ns-3 mode
---------

Change the *NS3_DIR* variable in the *Makefile* of the root folder to the path to your file. Type *make ns3* to compile the ackage and create the *libwptsim.a* library. Follow the tutorial availiable on https://www.nsnam.org/wiki/HOWTO_use_ns-3_with_other_libraries to include the library on your ns-3 application.
