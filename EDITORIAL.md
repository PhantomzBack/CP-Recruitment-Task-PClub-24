---
noteId: "47d85d2018f911ef92103d85969c5460"
tags: []

---

# Editorial

This problem makes use of recursion and a bit of graph theory. It might seem like the problem is an ordinary graph traversal problem but it is more than that.


Let us consider the following example.

```
00000000000000000000000000000000000000000
00000000000000000000000000000000000000000
00000000000000000000000000000000000000000
00000000000000000000000000000000000000000
00000000000000000000000000000000000000000
00000000000000000000000000000000000000000
00000000000000000000000000000000000000000
00000000000000000000000000000000000000000
00000000000000000000000000000000100000000
00000000000000000000000000000001000000000
00000000001000000000000000000010000000000
00000000000100000000000000000100000000000
00000000000010000000000000001000000000000
00000000000001000000000000010000000000000
00000000000000100000000000100000000000000
00000000000000010000000001000000000000000
00000000000000001000000010000000000000000
00000000000000000100000100000000000000000
00000000000000000010001000000000000000000
00000000000000000001010000000000000000000
00000000000000000000100000000000000000000
00000000000000000001010000000000000000000
00000000000000000010001000000000000000000
00000000000000000100000100000000000000000
00000000000000001000000010000000000000000
00000000000000010000000001000000000000000
00000000000000100000000000100000000000000
00000000000001000000000000010000000000000
00000000000010000000000000001000000000000
00000000000100000000000000000100000000000
00000000001000000000000000000010000000000
00000000010000000000000000000001000000000
00000000100000000000000000000000100000000
00000001000000000000000000000000010000000
00000010000000000000000000000000001000000
00000100000000000000000000000000000100000
00001000000000000000000000000000000010000
00010000000000000000000000000000000001000
00100000000000000000000000000000000000000
00000000000000000000000000000000000000000
00000000000000000000000000000000000000000
```
A rough guess would make us say the answer should be $4 \times E$ where $E$ is the number of edges when represented as a graph (The operation of pointing towards the edge, moving, pointing back, returning). But clearly, this is wrong, as you will see in the above example, that we could save on some operations by not stopping at the origin in between and directly traversing to the other side.

The solution therefore uses recursion and recurses over each $source$, a point from where lines seem to originate or intersect. 
Here the $sources$ are the $origin$ as well as the $endpoints$. We can see that the logic for selection of $sources$ is choosing points where two or more $distinct$ lines cross over, or one or more $rays$ originate.

An $edge$ here is a connection between $sources$.

Our code begins at the $origin$ as specified in the problem, and we traverse over to near neighbours which can behave as $sources$.

We use a recursive function $moves$ which calculates the number of moves it would take for the turtle pointer to move to all the edges except the one we traversed to it from and point back towards the edge we traversed from.


In general, we can say that the number of moves needed is 
for an edge $E$, connecting the current source $S$ and another source $P$, we can say
Moves taken to traverse and return to origin = $3+moves(P, dir)$ where $dir$ represents the direction in which the edge is oriented.

But there are a few cases to consider here, if the angle between the direction from which we travelled to this source and an edge is not $180 \degree$, we have two cases...

If it's counterpart line, at an angle of $180 \degree$ is also present:
The number of cases reduces since we do not need to add an additional stop in between at $S$. This is two moves shorter than the moves it would take otherwise for traversing them both independently. 
So in such a case, these two edges would contribute only $moves(P_{1}) + moves(P_{2}) + 4$

Another way we save two moves is when there is an $edge$ pointing along the edge we have just traversed. The two moves we save there are the need to orient the turtle to that edge (at the start or end depending on how we choose to view it), and that we need not stop at the $origin$ and can directly go back to the parent $source$. This is implemented in `solution.cpp`

