[Home](../../README.md)

# Project 4: Implement Route Planner

---

_How would you explain A-Star in layman terms?_

Answer:

* __A* search__ is a very popular path-finding algorithm, most commonly used in problems such as searching for the best possible route to a target destination. A* search looks for the cheapest path, for example in terms of mileage, by minimizing both the cost of passing through a particular node (i.e., location) and the cost to reach the goal from that node. A* relies partly on heuristics, or "shortcuts" which are not necessarily accurate or realistic (for example, the straight-line distance), but are effective in finding a satisfactory solution fast [1] [4]. Think of A* search as the algorithm that underpins popular applications like Google Maps or many GPS softwares.

---

_How does A-Star search algorithm differ from Uniform cost search? What about Best First search?_

Answer:

* __Uniform cost search__ is an _uninformed search strategy_, a family of techniques that do not use extra information (e.g., heuristics) beyond the basic formulation of a problem when searching for a goal: they simply "generate successors and discriminate between goal and non-goal nodes" [4], but know nothing about which non-goal node is a better candidate to reach the goal state. Thus, uniform cost search aims to expand the node with the lowest path cost $g(n)$ (the cost to reach a particular node $n$ from the start node) but - unlike A* search - does not employ any heuristic function $h(n)$ to evaluate how good such node actually is. One major drawback of this strategy is that it expands uniformly in all directions (like the contours of a topological map) because the search is not really directed towards the goal. So on average, this technique could waste a considerable amount of resources (time, space) in exploring paths that may not be the best, and could be prohibitive if the search space is very big. Uniform cost search relies on cost function: $f(n) = g(n)$.

* __Best-First search__ is an _informed search strategy_ which uses extra information (i.e., heuristics) to assess the cost of a solution from a certain node $n$. Among best-first strategies, _greedy best-first_ will always expand first the path which, according to the heuristic, is closest to the goal. Hence, it may disregard shortest possible paths because, by choosing those, it would take a temporary detour farther away from the goal. It has evaluation function: $f(n) = h(n)$, with $h(n)$ the estimated cost of the cheapest path from the state at node $n$. On the contrary, A* search is willing to take a temporarily longer path if the total cost to reach the goal is overall smaller. The evaluation function for A* search is: $f(n) = g(n) + h(n)$, where $f(n)$ is the "estimated cost of the cheapest solution through node $n$". In other words, A* attempts to minimize in terms of both the shortest path via $g(n)$, and the goal via $h(n)$.

---

_What is a heuristic?_

Answer:

* Heuristics are problem-solving techniques that use practical methods, or shortcuts, which are not necessarily optimal but nevertheless useful to reaching a satisfactory solution fast [1]. These shortcuts are used whenever more rigorous methods either fail, or would take too long, to find an acceptable solution [2].

* A heuristic function $h(n)$ - a component of _informed search strategies_, which increase the basic definition of a problem with targeted knowledge [4] - basically imparts the direction to a goal $G$. _Best-first strategies_ like A* search, define $h(n)$ as:

  $h(n)$ = estimated cost of the cheapest path from the state at node $n$ to a goal state.

---

_What is a consistent heuristic?_

* Formally, a heuristic function $h(n)$ is _consistent_ if, for each node $n$ and every successor $n'$ (which are all nodes that spawn from $n$ as a consequence of an action such as driving from $n$ to a different location), the _estimated cost_ $h(n)$ of reaching the goal from $n$ is never greater than the sum of the step cost to travel from $n$ to $n'$ and the actual cost to travel from $n'$ to the goal itself [3] [4].

* This is the basic _triangle inequality_ [4]: each side of a triangle cannot be longer than the sum of the other two.

---

_What is an admissible heuristic?_

Answer:

* A heuristic is _admissible_ if it never overestimates the cost of reaching the goal $G$ [4].
* That is, for each node $n$, $h(n)$ must always be strictly smaller than the true cost (i.e., the distance) of getting to the goal along the current path. For this reason, we also say that an admissible function $h$ is optimistic.
* An example of admissible heuristic is the straight-line distance because it's the shortest possible path between two points, and thus can never overestimate the true distance to the goal.

---

__Some__ admissible heuristic are consistent.

Explanation:

* Not all admissible heuristics are also consistent, although finding an example is not particularly easy [4].

* Admissibility always requires that a heuristic never overestimate the cost of reaching the goal from a particular node $n$. However, it does not tell anything, at each step of the process, about the relationship between the heuristic and the sum between the step cost to reach a successor node $n'$ from $n$ plus that to reach the goal from $n'$. Admissibility guarantees that the non-overestimation requirement holds _overall_, but does not guarantee that the same works for all intermediate steps towards reaching the goal (i.e., consistency).

---

__All__ Consistent heuristic are admissible.

Explanation:

* As consistency is a stronger requirement than admissibility, _all_ consistent heuristics are also admissible [4].

* Consistency requires that the estimated cost $h(n)$ of reaching the goal from node $n$ be never greater than the step cost of reching $n'$ from $n$ plus the actual cost of reaching the goal from $n'$. This is the basic triangle inequality [4], in which the length of a side cannot be greater than the sum of that of the other two. Hence, the heuristic function never overestimates the cost to reach the goal, but equals it at most (the definition of admissibile heuristic).

## Resources

1. https://en.wikipedia.org/wiki/Heuristic
2. https://en.wikipedia.org/wiki/Heuristic_(computer_science)
3. https://en.wikipedia.org/wiki/Consistent_heuristic
4. Russell S., Norvig P.: "Artificial Intelligence: A Modern Approach", 4th Ed. (2020)
