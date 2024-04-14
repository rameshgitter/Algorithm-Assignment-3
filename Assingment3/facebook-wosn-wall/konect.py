import networkx as nx
import matplotlib.pyplot as plt

# Read data from the text file
file_path = 'out.facebook-wosn-wall.txt'  # Replace 'your_file.txt' with the path to your text file
edges = []
with open(file_path, 'r') as file:
    for line in file:
        # Skip lines starting with '%'
        if line.startswith('%'):
            continue
        
        # Split line into columns and handle non-numeric characters
        try:
            data = line.strip().split()
            u, v, weight, timestamp = map(int, data[:4])
            edges.append((u, v, {'weight': weight, 'timestamp': timestamp}))
        except (ValueError, IndexError):
            print(f"Issue parsing line: {line.strip()}")

# Create a graph
G = nx.Graph()

# Add edges with weights and timestamps
G.add_edges_from(edges)

# Draw the graph
pos = nx.spring_layout(G)  # Adjust layout as desired
nx.draw(G, pos, with_labels=True, font_weight='bold')

# Add edge labels (weights) and node labels (timestamps)
edge_labels = {(u, v): d['weight'] for u, v, d in edges}
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

node_labels = {n: d['timestamp'] for n, d in G.nodes(data=True)}
nx.draw_networkx_labels(G, pos, labels=node_labels)

plt.title('Graph from Text File')
plt.show()

