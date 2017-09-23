import sys

def main():
    args = sys.argv
    print("own name: %s" % args[0])    
    print("%s" % args[1])
    print("%d" % int(args[2]))

main()
