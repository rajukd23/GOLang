#!/usr/local/bin/python3

def checkPalindrome(str):
    for i in range(0, int(len(str)/2)+1):
        #print ("str[i] : ", str[i], "---", str[len(str)-i-1])
        if str[i] != str[len(str)-i-1]:
            return False

    return True




val = input("enter the string : ")
#print (val)

val = val.lower()
#for c in val:
#    print (c)

print (len(val))
result = set()
# take string from 0 to 1, 0 to 2, 0 to 3.. 0 to n-1
# 1 to 2, 1 to 3, 1 to 4, 1 to 5... 1 to n-1


for i in range(0, len(val)):
    for j in range(i+2, len(val)+1):
        #print ("i : ", i, "j = ", j)
        splitStr = val[i:j]
        #print (splitStr)
        yes = checkPalindrome(splitStr)
        #print ("YES : ", yes, "for string ", splitStr)
        if yes == True:
            result.add(splitStr)

print (result)
