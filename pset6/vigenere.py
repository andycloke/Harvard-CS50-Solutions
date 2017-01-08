# encrypt messages using vigenere's cipher
# http://docs.cs50.net/problems/caesar/caesar.html

import sys

def main():
    # check correct usage
    if len(sys.argv) != 2:
        sys.exit('Error: vigenere should be called with 1 command line argument');

    # keyword
    keyword = sys.argv[1]

    # length of keyword
    l = len(keyword)

    # check that keyword contains only letters
    for i in range(l):
        if not keyword[i].isalpha():
            sys.exit('Error: keyword must contain only alphabetical characters');

    # get plaintext from user
    p = input('plaintext: ')

    # record ASCI positions of A & a
    intA = ord('A')
    inta = ord('a')

    # set up output for enicphered text
    print('ciphertext: ', end = '');

    # used to incremenet through keyword only when plaintext char is alphabetical
    j = 0

    for i in range(len(p)):
        # get character from keyword, and wrap around if plaintext is longer than keyword
        k = keyword[j % l]

        # shift so that position of 'A' or 'a' is 0
        if k.isupper():
            k = ord(chr(ord(k) - intA))
        else:
            k = ord(chr(ord(k) - inta))

        # if alphabetical character, encrypt. Otherwise leave alone
        if p[i].isupper():
            print(chr((((ord(p[i]) - intA) + k) % 26) + intA), end = '')
            j += 1
        elif p[i].islower():
            print(chr((((ord(p[i]) - inta) + k) % 26) + inta), end = '')
            j += 1
        else:
            print(p[i], end = '')
    print('');
if __name__ == "__main__":
    main()
