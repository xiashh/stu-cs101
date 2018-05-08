import random


num_nodes = 1000
num_edges = 1000
max_dis = 123
max_regions = 4

print(num_nodes)
print(num_edges)
print(max_regions)

for i in range(num_edges):
    print(random.randrange(num_nodes),' ',
          random.randrange(num_nodes),' ',
          random.randrange(max_dis))