from __future__ import print_function

done = False
prompts = []
with open('prompts.txt') as f:
    while True:
        c = f.readline()
        if not c:
            break
        prompts.append(c)

while(not done):

    print ("\nHello. What would you like to do?\n")
    print ("\t1) See all prompt questions.\n"
            "\t2) Add a new prompt.\n"
            "\t3) Delete a prompt.\n"
            "\t4) Exit\n")
    choice = input("\t> ")


    #print ("You chose", choice)
    options = True
    if (len(prompts)==0):
        print ("There are no prompts")
        options = False
    #else:
    #    print(len(prompts))

    if(choice == 1 and options):
        print ("\n--------------")
        for prompt in prompts:
            print (prompt)
        print ("--------------\n")


    if(choice == 2):
        prompt = raw_input("\nWhat is the new prompt? \n\t>")
        prompts.append(prompt)

    if(choice == 3 and options):
        print ("Which prompt?\n")
        for i in range(0, len(prompts)):
            print(i+1, "-", prompts[i])
        rmv = input("\n\t> ")
        if(rmv > 0 and rmv <= len(prompts)):
            prompts.remove(prompts[rmv-1])
        else:
            print("Option is not valid")

    if(choice == 4):
        break

with open('prompts.txt', 'w') as f:
    for prompt in prompts:
        f.write(prompt)
        #f.write("\n")
