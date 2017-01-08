# encrypt messages using caesar's cipher
# http://docs.cs50.net/problems/caesar/caesar.html

import sys

def main():
    # check correct usage
    if len(sys.argv) != 2:
        sys.exit('Usage: caesar.py 13');

    # convert key to int and wrap it around alphabet
    k = int(sys.argv[1]) % 26

    # get plaintext from user
    p = input('plaintext: ')

    # record ASCI positions of A & a
    intA = ord('A')
    inta = ord('a')

    # set up output for enicphered text
    print('ciphertext: ', end = '');

    for i in range(len(p)):
        # if alphabetical character, encrypt. Otherwise leave alone
        if p[i].isupper():
            print(chr((((ord(p[i]) - intA) + k) % 26) + intA), end = '')
        elif p[i].islower():
            print(chr((((ord(p[i]) - inta) + k) % 26) + inta), end = '')
        else:
            print(p[i], end = '')
    print('');
if __name__ == "__main__":
    main()
