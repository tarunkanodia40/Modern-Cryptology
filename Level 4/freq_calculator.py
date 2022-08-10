candidate_keys = []

for i in range(0, 8):
    candidate_keys.append([0] * 64)

number_of_Sboxes = 8

file = open("generated_keys.txt", "r")

f = file.read().splitlines()
for i in range(len(f) // 8):
    for j in range(number_of_Sboxes):
        temp = f[i * number_of_Sboxes + j].split(" ")
        for k in list(temp):
            if k != "":
                candidate_keys[j][int(k, 2)] += 1
# print(candidate_keys)
print("key_bit        maximum        average")
for itr in range(number_of_Sboxes):
    maximum = max(candidate_keys[itr])
    average = sum(candidate_keys[itr]) / 64
    key_bit = -1
    for j_itr in range(64):
        if candidate_keys[itr][j_itr] == maximum:
            key_bit = j_itr
            break
    if key_bit > 0:
        print(str(key_bit) + "  " + str(maximum) + "  " + str(average) + "\n")
