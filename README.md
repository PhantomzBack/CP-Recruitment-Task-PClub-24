# MSWLogo...and CP?!

Link: https://polygon.codeforces.com/p5sFWZt/PhantomzBack/mswlogo-whaaat

## Problem
As a responsible elder brother, you were looking after your brother and got him into computers early. You started to teach him ![MSWLogo](https://en.wikipedia.org/wiki/MSWLogo) and he immediately started creating cool figures with it. He started saving screenshots of the figures he created. A few days later, he comes to you complaining that he made a few drawings before but he forgot to save the commands he used to make the drawings, now all he has is those $2n+1\times 2n+1$ bitmaps of the drawings, and wants you to retrieve the commands to make them again. 
Thankfully for you, you taught him only how to move along straight line rotate only to multiples of $45\degree$. 

An image of the text file used.
![An example image](image.png)


The commands for these are given as 

`fd x`: the turtle moves ahead in the direction it is pointing by `x` pixels

`rt angle`: the turtle turns `angle` degrees in the clockwise direction

Note that both $x>0$ and $angle>0$ in the above commands. 

Ofcourse, you don't want an unproductive use of your time, and so decide to challenge yourself, you will try to achieve the goal in the minimum possible commands, using only the two given above.

For this problem, you only need to find the minimum number of chances required to recreate the diagram. Note that it starts with the head pointed towards the upward direction.
The final orientation can be anything so as to minimize commands used.

You can take the following assumptions:

- Since you didn't teach him `penup`, he is forced to start at the centre of the canvas and pointing in upward direction, and the drawing must be connected, phew, thank god you saved that for later.
- The drawings don't form closed shapes on the canvas. That's just his wish, but it makes things a bit simpler for us, great!
- The lines are only $1px$ thick, and diagonally adjacent points are considered 1px thick, an example is shown in the input demonstration given below.
- It is also given that a line is atleast $4px$ long, and it is clearly possible to identify which point lines are originating from. And no two adjacent points can ever have lines originating from them
  
## I/O
### Input: 
The first line gives you the value of n

An array of dimensions $2n+1\times 2n+1$ in the form of 0s and 1s, seperated by newline characters
$2n+1$ rows, each containing $2n+1$ characters
```
0000000000000000000....
0000000000000000000....
0000001111111000000....
0000000000000100000....
0000000000000010000....
0000000000000001000....
⋮ ⋮ ⋮ ⋮ ⋮ ⋮ ⋮ ⋮ ⋮ ⋮ ⋮ ⋮ ⋮
```

### Output:
A single integer $n$ representing the **minimum** number of moves to recreate the diagram.

### Constraints:
The only given constraint is
$1<=n<=500$

## Sample Testcase:
The test case here is shown with a smaller example, using a $11\times11$ grid.

### Input:
```
5
00000000000
00000100000
00000100000
00000100000
00000100000
00000000000
00000000000
00000000000
00000000000
00000000000
```

### Output:
```
1
```

### Explanation:
Using `fd 4`, the same diagram can be created.


