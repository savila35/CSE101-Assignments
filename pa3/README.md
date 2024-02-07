# pa3

#### Files

> List.h
	
Header for List ADT, written as part of pa1.
> List.c

Implementation of List ADT, written as part of pa1.
> Graph.h

Header for Graph ADT, written as part of pa2 and altered to fit pa3
requirements.  
> Graph.c

Implementation of Graph ADT, written as part of pa2 and altered to fit pa3
requirements. Added functions for DFS and returning discover and finish
times. Added their respective arrays to the Graph object struct. 
In order to track the discover and finishing times of verticies, I declared a 
local variable `time` in the DFS function and sent its address to the `visit()`
helper funciton as a parameter.

> GraphTest.c

Contains tests to ensure proper functionality of Graph ADT implementation.
> FindComponents.c

Finds the strongly connected components of a given graph.
