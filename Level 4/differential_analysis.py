final_reverse_permutation = [
    57,
    49,
    41,
    33,
    25,
    17,
    9,
    1,
    59,
    51,
    43,
    35,
    27,
    19,
    11,
    3,
    61,
    53,
    45,
    37,
    29,
    21,
    13,
    5,
    63,
    55,
    47,
    39,
    31,
    23,
    15,
    7,
    58,
    50,
    42,
    34,
    26,
    18,
    10,
    2,
    60,
    52,
    44,
    36,
    28,
    20,
    12,
    4,
    62,
    54,
    46,
    38,
    30,
    22,
    14,
    6,
    64,
    56,
    48,
    40,
    32,
    24,
    16,
    8,
]

permutaion_inverse = [
    9,
    17,
    23,
    31,
    13,
    28,
    2,
    18,
    24,
    16,
    30,
    6,
    26,
    20,
    10,
    1,
    8,
    14,
    25,
    3,
    4,
    29,
    11,
    19,
    32,
    12,
    22,
    7,
    5,
    27,
    15,
    21,
]

Exp_box = [
    32,
    1,
    2,
    3,
    4,
    5,
    4,
    5,
    6,
    7,
    8,
    9,
    8,
    9,
    10,
    11,
    12,
    13,
    12,
    13,
    14,
    15,
    16,
    17,
    16,
    17,
    18,
    19,
    20,
    21,
    20,
    21,
    22,
    23,
    24,
    25,
    24,
    25,
    26,
    27,
    28,
    29,
    28,
    29,
    30,
    31,
    32,
    1,
]


def write_file(filename, val):
    file = open(filename, "w")
    for i in val:
        file.write(i + "\n")
    file.close()


mapping = {
    "d": "0000",
    "e": "0001",
    "f": "0010",
    "g": "0011",
    "h": "0100",
    "i": "0101",
    "j": "0110",
    "k": "0111",
    "l": "1000",
    "m": "1001",
    "n": "1010",
    "o": "1011",
    "p": "1100",
    "q": "1101",
    "r": "1110",
    "s": "1111",
}

file = open("ciphertexts_outputs.txt", "r")
outputs = file.read().split("\n")
output_bits = []
for i in range(len(outputs)):
    temp = ""
    for j in range(16):
        temp += mapping[outputs[i][j]]
    output_bits.append(temp)


end_outputs = []

for j in range(len(output_bits)):
    s = ""
    for i in range(64):
        s += output_bits[j][final_reverse_permutation[i] - 1]
    end_outputs.append(s)

Expansion_outputs = []
for j in range(len(end_outputs)):
    s = ""
    for i in range(48):
        s += end_outputs[j][Exp_box[i] - 1]
    Expansion_outputs.append(s)

input_S_box = []
for j in range(len(Expansion_outputs) // 2):
    s = ""
    for i in range(48):
        s += str(
            int(Expansion_outputs[2 * j + 1][i]) ^ int(Expansion_outputs[2 * j][i])
        )
    input_S_box.append(s)


output_XOR = []
for j in range(len(end_outputs) // 2):
    s = ""
    for i in range(64):
        s += str(int(end_outputs[2 * j + 1][i]) ^ int(end_outputs[2 * j][i]))
    output_XOR.append(s)

L5 = "00000100000000000000000000000000"
XOR_permutaion = []
for j in range(len(output_XOR)):
    s = ""
    for i in range(32):
        s += str(int(output_XOR[j][32 + i]) ^ int(L5[i]))
    XOR_permutaion.append(s)


output_S_box = []
for j in range(len(XOR_permutaion)):
    s = ""
    for i in range(32):
        s += XOR_permutaion[j][permutaion_inverse[i] - 1]
    output_S_box.append(s)

write_file("output_expansion.txt", Expansion_outputs)
write_file("input_S_box.txt", input_S_box)
write_file("output_S_box.txt", output_S_box)
