# Lem-in

The *lem-in* program is the 3rd mandatory exercice from the *Algorithm* branch at [42]( https://www.42.fr ), related to [graph theory]( https://en.wikipedia.org/wiki/Graph_theory#Network_flow ). The goal is to solve a specific form of [flow network]( https://en.wikipedia.org/wiki/Flow_network ) problems. The file describing the graph is to be parsed and any error handled properly. Once the graph has been fed to the program, an algorithm must find how to move everything from source to sink in the *lowest amount of steps*. 

## Useful links
- The [Edmonds-Karp algorithm]( https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm )
- the [Dijkstra-s algorithm]( https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm )
- The [BFS algorithm]( https://en.wikipedia.org/wiki/Breadth-first_search )
- The [DFS algorithm]( https://en.wikipedia.org/wiki/Depth-first_search )
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
./lem-in
```

The *lem-in* program is designed to work with a file descriptor. While you can feed it information through the standard input, the best solution is usually to use a redirection, as shown below:

```
./lem-in << /path/to/file
```
