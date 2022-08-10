from fpylll import *
from mpmath import *
import math

cipher_text = 27988616204345715069368578834410159571047717535959420055403405512316290196978454204078294164647627063800736715982574327624929391498782754528278783434980277601156213771683556345707640415993117617646182721800376568398333414500067202377754293564991383316159034250870453121330762814466672624549989323695215425043

n = 84364443735725034864402554533826279174703893439763343343863260342756678609216895093779263028809246505955647572176682669445270008816481771701417554768871285020442403001649254405058303439906229201909599348669565697534331652019516409514800265887388539283381053937433496994442146419682027649079704982600857517093

### got the below padding from converting ascii value of "Cryptomaniacs: This door has RSA encryption with exponent 5 and the password is" to decimal form
message = (
    "Cryptomaniacs: This door has RSA encryption with exponent 5 and the password is "
)
padding_a = int(
    "".join(["{0:08b}".format(ord(message[i])) for i in range(len(message))]), 2
)

exponent = 5
check = False
mp.dps = 70
for e in range(8, 1024, 8):
    ###K to be the upper bound on m that is the reason K = 2^e
    K = 2**e
    ###left shift the padding
    a = padding_a * (2**e)
    ###coefficients as what we have dicussed in the class
    c_0, c_1, c_2, c_3, c_4 = (
        a**5 - cipher_text,
        5 * a**4,
        10 * a**3,
        10 * a**2,
        5 * a,
    )
    matrix = [
        K**6,
        K**5 * c_4,
        K**4 * c_3,
        K**3 * c_2,
        K**2 * c_1,
        K * c_0,
        0,
        0,
        K**5,
        c_4 * K**4,
        c_3 * K**3,
        c_2 * K**2,
        c_1 * K,
        c_0,
        0,
        0,
        K**4 * n,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        K**3 * n,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        K**2 * n,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        K * n,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        n,
    ]
    ###finding the S polynomial using LLL method as discussed in the class
    polynomial = list(
        LLL.reduction(IntegerMatrix.from_iterable(7, 7, matrix), delta=0.99)[0]
    )
    ###finding roots of polynomial using polyroots function
    roots = polyroots(polynomial, maxsteps=800)
    for root in roots:
        ###check for real postive roots
        if (root.real >= 0) & (root.imag == 0):
            ###finding the candidate for message (m) in decimal form by multiplying root with K as root is of the form m/K
            m = int(K * root)
            ###check if given cipher_text matches with (a+m)^e or not
            if pow(m + a, exponent, n) == cipher_text:
                ### if cipher_text matches then m is indeed the message
                
                ###convert m from decimal to binary and print m in binary form
                m = str(bin(m))[2:]
                print(m)
                ###appending extra zeroes to make m's length to be a multiple of 8
                start = "0" * (8 - len(m) % 8) + m
                ###convert m to actual text message by changing binary to ascii characters and printing the textual password
                print(
                    "Password is ",
                    "".join(
                        [chr(int(start[i : i + 8], 2)) for i in range(0, len(m), 8)]
                    ),
                )
                check = True
                break
    if check:
        break
