# calculate minimum coins necessary to give someone change
# http://docs.cs50.net/problems/greedy/greedy.html

def main():
    while True:
        change = float(input('Change Required: '))
        if change > 0:
            break

    counter = 0
    while change > 0.25:
        change = change - 0.25
        counter += 1
    while change > 0.10:
        change = change - 0.10
        counter += 1
    while change > 0.05:
        change = change - 0.05
        counter += 1
    while round(change, 2) > round (0, 2):  # round needed to avoid errors due to floating point approximation
        change = change - 0.01
        counter += 1
    print(counter)


if __name__ == "__main__":
    main()
