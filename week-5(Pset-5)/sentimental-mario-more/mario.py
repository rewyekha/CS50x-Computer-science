def get_positive_int(prompt):
    while True:
        try:
            # get the user imput and convert to int
            number = int(input(prompt))
            # Check if the number is between 1 and 8 (inclusive)
            if 1 <= number <= 8:
                return number
            else:
                print("Invalid input. Please enter a number between 1 and 8.")
        except ValueError:
            print("Invalid input. Please enter a valid Integer.")


def main():
    # Get the height of the pyramid from the user
    height = get_positive_int("Height: ")

    for i in range(height):

        for j in range(height - i - 1):
            print(" ", end="")

        for j in range(i + 1):
            print("#", end="")

        # print gap between the two pyramids
        print("  ", end="")

        for j in range(i + 1):
            print("#", end="")

        print()


# execute the main func if this script is run directly
if __name__ == "__main__":
    main()
