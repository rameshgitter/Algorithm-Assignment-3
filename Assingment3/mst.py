import matplotlib.pyplot as plt
import networkx as nx

# Define the graph (replace with your actual data)
edges = [
    (0, 1, 4),
    (0, 7, 8),
    (1, 2, 8),
    (1, 7, 11),
    (2, 3, 7),
    (2, 8, 2),
    (2, 5, 4),
    (3, 4, 9),
    (3, 5, 14),
    (4, 5, 10),
    (5, 6, 2),
    (6, 7, 1),
    (5, 8, 6),
    (7, 8, 7)
]

# Create the graph
G = nx.Graph()
G.add_weighted_edges_from(edges)

# Find the MST using Kruskal's algorithm
mst = nx.minimum_spanning_tree(G, algorithm='kruskal')

# Visualize the MST
pos = nx.spring_layout(G)  # Adjust layout as needed
nx.draw(G, pos, with_labels=True, node_color='lightblue', edge_color="gray")
nx.draw_networkx_edges(mst, pos, width=2, edge_color='red')

plt.title("Minimum Spanning Tree")
plt.show()

