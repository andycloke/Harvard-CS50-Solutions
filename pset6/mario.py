# constructs two pyramids in the style of mario games
# http://docs.cs50.net/problems/mario/more/mario.html

def main():
    while True:
        n = int(input('Height: '))
        if n >= 0 and n < 23:        # n must be between 0 and 23
            break
    for i in range(n):
        print((n-1-i) * ' ' + (i+1) * '#' + '  ' + (i+1) * '#')   # print each side of pyramid

if __name__ == "__main__":
    main()
