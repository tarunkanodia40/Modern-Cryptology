mpp = {}

for i in range(16):
    enc = format(i, '0>4b')
    mpp[enc] = chr(ord('f') + i)

file = open("plaintexts.txt", "w+")

for i in range(8):
    for j in range(128):
        bin_j = format(j, '0>8b')
        inp = 'ff'*i + mpp[bin_j[:4]] + mpp[bin_j[4:]] + 'ff'*(7-i)
        file.write(inp)
        file.write(" ")
    file.write("\n")

file.close()