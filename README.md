# Lem-in

The *lem-in* program is the 3rd mandatory exercice from the *Algorithm* branch at [42]( https://www.42.fr ), related to [graph theory]( https://en.wikipedia.org/wiki/Graph_theory#Network_flow ). The goal is to solve a specific form of [flow network]( https://en.wikipedia.org/wiki/Flow_network ) problems. The file describing the graph is to be parsed and any error handled properly. Once the graph has been fed to the program, an algorithm must find how to move everything from source to sink in the *lowest amount of steps*. 

## Useful links
- The [Edmonds-Karp algorithm]( https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm )
- the [Dijkstra-s algorithm]( https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm )
- The [BFS algorithm]( https://en.wikipedia.org/wiki/Breadth-first_search )
- The [DFS algorithm]( https://en.wikipedia.org/wiki/Depth-first_search )
- The [Dinic algorithm]( https://en.wikipedia.org/wiki/Dinic%27s_algorithm )
- Description of the [Minimum-cost flow problem]( https://en.wikipedia.org/wiki/Minimum-cost_flow_problem )

### Credit

Thanks to [abaurens]( https://github.com/abaurens ) for his great explanations and this [link to a related lecture]( http://math.mit.edu/~goemans/18438S12/lec22.pdf ).

## Download & Launch

```
git clone https://github.com/AugustinLopez/lem_in.git
cd lem_in
make
```

### Usage

```
./lem-in [-hFAispncelx] < [file]
```

The *lem-in* program is designed to work with a file descriptor. While you can feed it information through the standard input, the best solution is usually to use a redirection.

-h: show a summary of the usage.
-F: The program will not print the *file* content. This option is recommended when using the standard input.
-A: The program will not print the path taken by the ant in the end. This option is recommended when using other options with large maps.
-i: The program will show the number of ants, rooms and steps, as well as the final number of steps it calculated.
-s: the program will show the augmenting path found at the end of each exploration. A red color means that the augmenting path is going up a path that is part of the previous set of solution.
-p: the program will show the list of path found at the end of each exploration.
-n: the program will show the index of each step.
-c: At each step, the program will color ants have reached the end or that are being launched from the start.
-e: The program will show the state of the exploration stack. Not recommended with large maps.
-l: The program will only accept up to INT_MAX ants (instead of LONG_MAX).
-x: The program will return an error if at least 2 rooms share the same XY coordinates.

Recommended options: **-Aisp** ; this will show the augmenting path, the list of path and relevant summary information.

## Implementation

### Parsing

- Rooms are kept in a [red-black tree]( https://en.wikipedia.org/wiki/Red%E2%80%93black_tree ) so we can quickly check during the insertion of a new room if it shares its name with another one.
- The tubes are kept in several linked lists, each rooms keeping track of its own list of tube. The tube from A to B is registered in two linked lists: the one of room A and the one of room B. Because we double the amount of tube, we can quickly translate the original undirected graph into a directed graph.

### Algorithm

- The first pass use a simple BFS algorithm to find the shortest path from start to end. A failed BFS means that there is no path from start to end.
- Subsequent path use a more complex, "home-made" approach.
  - The base approach is BFS, but we keep track of the "depth" of each node. Other scenario may reduce the depth of a node, and a node with a lower depth will be treated in priority.
  - If a node is part of a previously found solution, we try to an "upstream" approach. Going down this solution path (from end to start) allow us to reduce the depth as long as we can go up the solution path. Several condition are necessary in order to go up a path, and it is necessary to "exit" the upstream to find the end.
  - The last scenario is the "rebuild" approach. Normally we can only visit a node once\* during an exploration. But it may be interesting to revisit a node that was previously blocked if it reduces its depth. In that case, the origin path of this node must be corrected. But the depth of each visit made starting from this node must also be corrected: the depth reduction might have opened new, previously blocked path.
  
\*: This is one of the current issue of this build: any node can only have one origin path. In reality, an augmenting path might pass two times in a node that is part of a previous solution. This prevent this *lem-in* to find the best set of path in several scenarios.
