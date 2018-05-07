import random


num_nodes = 10000
num_edges = 10000
max_dis = 12379
max_regions = 1

print(num_nodes)
print(num_edges)
print(max_regions)

for i in range(num_edges):
    print(random.randrange(num_nodes),' ',
          random.randrange(num_nodes),' ',
          random.randrange(max_dis))