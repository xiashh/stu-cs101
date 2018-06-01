import random
import string

n = 10
print(n)

for i in range(n):
    m = random.randint(1,10)
    print(''.join(random.choices(string.ascii_letters, k = m)))