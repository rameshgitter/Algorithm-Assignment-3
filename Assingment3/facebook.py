import networkx as nx 
import matplotlib.pyplot as plt 

g=nx.read_edgelist('/home/ramesh/Desktop/assignment4/Algorithm/Assingment3/facebook_combined.txt',create_using=nx.Graph(),nodetype=int)
print(f"Number of nodes: {g.number_of_nodes()}")
print(f"Number of edges: {g.number_of_edges()}")
#print(nx.info(g))
sp=nx.spring_layout(g)

plt.axis("off")

nx.draw_networkx(g,pos=sp,with_labels=False,node_size=10)

plt.show()





