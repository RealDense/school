dict = {}
str = "I have a lovely bunch of coconuts"

for i in str:
  if i.isalpha():
    if i in dict:
      dict[i.lower()] += 1
    else:
      dict[i.lower()] = 1

for i in dict:
  if dict[i] == 1:
    print(i)