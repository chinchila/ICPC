import random as r
r.random(0) #random float beetween 0 and 1
r.uniform(2.5, 100) #random float beetween 2.5 and 100
r.randrange(10) #random int beetween 0 and 10-1
r.choice(['win', 'lose', 'draw']) #Single random element from a sequence
r.shuffle(V) #random permutation of V

#random permutation of the numbers beetween 1 and n, with n radom
n = r.randrange(100)
def f(n):
     V=[]
     for i in range(n):
             V.append(i)
     r.shuffle(V)
     return V

