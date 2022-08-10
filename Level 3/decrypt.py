"""
################################################
##########Question in Assignemnt 3#############
################################################
Password for this level is an element of the multiplicative
	group Z_p^* where p = 455470209427676832372575348833 is a prime.
	You carefully look around and find three pairs of numbers of the
	form (a, password * g^a) where g is a element in Z_p^* and a is
	an integer. The g in each pair is the same.

			(429,  431955503618234519808008749742)
			(1973, 176325509039323911968355873643)
			(7596, 98486971404861992487294722613)

	You desperately start searching for more numbers and find

			5_ _ _50_ _4_ _ _ _ _31_ _ _ _ _94_ _9

	This looks like g but most of the entries are missing. Speak
	out the password loudly to pass this level!
"""

import math

## Given three pairs in the question

x = (429, 431955503618234519808008749742)
y = (1973, 176325509039323911968355873643)
z = (7596, 98486971404861992487294722613)

### a prime number is also given
p = 455470209427676832372575348833

### calculating the inverse of password*g^x[0] (mod p) with the help of fermats little theorem
P = pow(x[1], p - 2, p)  # fermats therom (inverse calculation)

### P1 is a pair which contains (y[0]-x[0]) and (g^(y[0]-x[0])) (mod p) (password will cancel out by its inverse in multiplication)
P1 = (y[0] - x[0], (P * y[1]) % p)

### P2 is a pair which contains (z[0]-x[0]) and (g^(z[0]-x[0])) (mod p) (password will cancel out by its inverse in multiplication)
P2 = (z[0] - x[0], (P * z[1]) % p)


### important point to note is that gcd of y[0] - x[0] and z[0] - x[0] is 1

### iterate until we get P1[0] as gcd of y[0] - x[0] and z[0] - x[0] which is 1.
while P1[0] != 1:

    ### calculating the inverse of P1[1] (mod p) in t1 with the help of fermats little theorem
    t1 = pow(P1[1], p - 2, p)

    t2 = P2[0] - P1[0]
    t3 = (P2[1] * t1) % p

    # P2 is a pair which contains (P2[0]-P1[0]) and (g^(P2[0]-P1[0])) (mod p)
    P2 = (t2, t3)

    ### P with minimum P[0] value will become P (gcd algorithm)
    if P2[0] < P1[0]:
        P = P2
        P2 = P1
        P1 = P

### at the end of one iteration P1 will store (a,g^a(mod p)) pair

### After exiting the above while loop P1 will be (1,g(mod p)) pair

## getting g value from P[1]
g = P1[1]

### calculating the inverse of g(mod p) in g_inv with the help of fermats little theorem
g_inv = pow(g, p - 2, p)

### calculating g_inv^x[0](mod p) in g_inv_power_a
g_inv_power_a = pow(g_inv, x[0], p)

### As x[1] = password*g^x[0](mod p), multiplying(mod p) it with g_inv^x[0](mod p) will give the password
password = (g_inv_power_a * x[1]) % p

### printing g and password
print(g, password)