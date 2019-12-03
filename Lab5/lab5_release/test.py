import os
import sys
import filecmp

try:
    testnum = sys.argv[1];
except Exception as e:
    print(e.what())
    exit()

infile = "Lab5Test/{}".format(testnum)
outfile = "Lab5Test/{}.1.out".format(testnum, testnum)

cmd1 = "./bin/Lab5 < {} > result".format(infile)
os.system(cmd1)

result = filecmp.cmp("result", outfile)
print("Tescase {} PASS : {}".format(testnum, result))

if not result:
    print("TestCase : \n")
    os.system("cat {}".format(infile))
    print("********Comparing ::**********\n")
    os.system("diff result {}".format(outfile))
os.system("rm result")
