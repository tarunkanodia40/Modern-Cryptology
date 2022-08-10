import operator
import numpy as np
from colored import fg
red = fg('red')
green = fg('green')
text="omkf pi hdn cmgef icphsck .H krg vphqkc c,fic mco kqgf ioqag eo qfcmckf oq ficpihdn cm .Kg dcgeficu hfcm pi hdn cmklo uuncdgmc oqfc mc kfoq afihqfiokgq c!Fi cpgy cvkc yeg mfio kdck kha cokh kodjuck vn k fofvfo gqpojicmoqli opiyoa of kihsc nccqki oefc ynr2 juhpck. Fi c jhkklgm yok oMxr9V1x ya flofigvffic xvgfck. Fio kokfice"
text=text.lower()
freq={}
count=0
#text=text.replace(" ", "")
for i in range(len(text)):
    if(text[i]=='.' or text[i]==','):
        continue
    count=count+1
    if text[i] in freq.keys():
        freq[text[i]]=freq[text[i]]+1
    else:
        freq[text[i]]=1
for key in freq:
    freq[key] = (100*freq[key])/float(count)

freq = sorted(freq.items(), key=operator.itemgetter(1))
#print(freq)

decrypted = np.zeros(len(text),dtype = "int32")


def decode(encrypt,decrypt):
    global decrypted,text
    for i in range(len(text)):
        if text[i]==encrypt and decrypted[i]==0:
            decrypted[i]=1
            string_list = list(text)
            string_list[i] = decrypt
            text = "".join(string_list)

#print(freq)                           

decode('c',"e")
decode('f',"t")
decode('h',"a")
decode('k',"s")
decode('g',"o")
decode('o',"i")
decode('q',"n")
decode('i',"h")
decode('l',"w")
decode('m',"r")
decode('y',"d")
decode('x',"q")
decode('v',"u")
decode('a',"g")
decode('p',"c")
decode('e',"f")
decode('d',"m")
decode('n',"b")
decode('s',"v")
decode('u',"l")
decode('r',"y")
decode('j',"p")
decode('2',"6")#6 places backward shifted
decode('9',"3")
decode('1',"5")
#print(decrypted)
for i in range(len(text)):
    if decrypted[i]==1:
        print(green+text[i],end='')
    else:
        print(red+text[i],end='')
print("\n\n")
#print(freq)
# print(text)

