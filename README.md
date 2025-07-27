# PathQuest
PathQuest is a simple C++ terminal project that visualizes the shortest path from a source to a destination on a 2D grid using Dijkstra's algorithm. Inspired by classic puzzle games, it mimics how a character (like a rabbit) would navigate a maze to reach a goal (like a carrot), avoiding obstacles.

**Features:**
 -Visualizes pathfinding using **Dijkstra’s Algorithm**
- Takes user input for **start** and **end** positions
- Shows **shortest path**, cost, and grid output in terminal
- **Dynamic grid creation** with walls and open cells
- Terminal-based interface, no dependencies

**HOW IT WORKS**

- The grid is represented using a 2D vector of nodes.
- Obstacles are represented as `#`, free cells as `.`, path as `*`, start as `S`, and end as `E`.
- Dijkstra’s algorithm explores the shortest path considering all valid adjacent nodes (non-wall).
- Once destination is reached, the path is reconstructed using a `parent` tracking mechanism and visualized on the grid.

**Tech Stack**:
C++ STL:Vector,'unordered_map','priority_queue'
No external Libraries or Frameworks

**Inspiration**
This was inspired by childhood puzzle games where characters navigate mazes. Rebuilding that logic from scratch using real pathfinding taught me algorithmic problem solving and system design.

Made by Pavan Chandra.

