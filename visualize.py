import matplotlib.pyplot as plt
import numpy as np

def load_data(filename="path_data.txt"):
    with open(filename) as f:
        rows, cols = map(int, f.readline().split())
        grid = [list(f.readline().strip()) for _ in range(rows)]
        sx, sy = map(int, f.readline().split())
        num_targets = int(f.readline())
        targets = []
        costs = {}
        paths = {}
        for _ in range(num_targets):
            tx, ty, cost = map(int, f.readline().split())
            path_len = int(f.readline())
            path = [tuple(map(int, f.readline().split())) for _ in range(path_len)]
            targets.append((tx, ty))
            costs[(tx, ty)] = cost
            paths[(tx, ty)] = path
    return grid, (sx, sy), targets, costs, paths

def visualize(grid, start, targets, costs, paths):
    rows, cols = len(grid), len(grid[0])
    img = np.zeros((rows, cols))

    for i in range(rows):
        for j in range(cols):
            if grid[i][j] == '#':
                img[i][j] = -1  # obstacle
            elif grid[i][j] == '.':
                img[i][j] = 0
            elif grid[i][j] == 'S':
                img[i][j] = 1
            elif grid[i][j] == 'T':
                img[i][j] = 2

    fig, ax = plt.subplots()
    cmap = plt.cm.get_cmap('YlOrRd', 4)
    ax.imshow(img, cmap=cmap)

    # Draw path arrows step-by-step
    for target in targets:
        path = paths.get(target, [])
        for i in range(1, len(path)):
            x0, y0 = path[i - 1]
            x1, y1 = path[i]
            dx, dy = y1 - y0, x1 - x0
            ax.arrow(y0, x0, dx * 0.8, dy * 0.8, head_width=0.2, head_length=0.2, fc='blue', ec='blue')
            mx, my = (y0 + y1) / 2, (x0 + x1) / 2
            ax.text(mx, my, '1', fontsize=8, color='black', ha='center', va='center')

    # Annotate target costs
    for (x, y), cost in costs.items():
        label = "X" if cost == -1 else str(cost)
        ax.text(y, x, label, va='center', ha='center', color='black', fontsize=9, fontweight='bold')

    # Mark start
    ax.text(start[1], start[0], 'S', va='center', ha='center', color='blue', fontsize=12, fontweight='bold')

    plt.title("Dijkstra Path Visualization")
    plt.xticks(range(cols))
    plt.yticks(range(rows))
    plt.grid(True, color='black', linewidth=0.5)
    plt.show()

if __name__ == "__main__":
    grid, start, targets, costs, paths = load_data()
    visualize(grid, start, targets, costs, paths)
