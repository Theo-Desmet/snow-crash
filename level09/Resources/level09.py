import sys

def decrypt(str) -> str:
    new_str = ""
    for (index, c) in enumerate(str):
        ascii_val: int = ord(c)
        ascii_val -= index
        new_c = chr(ascii_val)
        new_str += new_c
    return new_str

def main():
    if len(sys.argv) != 2:
        print "Missing argument"
        return
    print decrypt(sys.argv[1])

if __name__ == '__main__':
    main()
