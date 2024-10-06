def get_float(prompt):
    while True:
        try:
            # Get user input as a float
            value = float(input(prompt))

            # Check if the value is non-negative
            if value >= 0:
                return value
            else:
                print("Please enter a non-negative number.")
        except ValueError:
            print("Invalid input. Please enter a valid number.")


def calculate_quarters(cents):
    return cents // 25


def calculate_dimes(cents):
    return cents % 25 // 10


def calculate_nickels(cents):
    return cents % 25 % 10 // 5


def calculate_pennies(cents):
    return cents % 25 % 10 % 25


def main():
    # Prompt the user for the amount of change owed
    amount = get_float("Change owed: ")

    # Convert dollars to cents
    cents = round(amount * 100)

    # Calculate number of quarters, dimes, nickels, and pennies
    quarters = calculate_quarters(cents)
    cents -= quarters * 25

    dimes = calculate_dimes(cents)
    cents -= dimes * 10

    nickels = calculate_nickels(cents)
    cents -= nickels * 5

    pennies = calculate_pennies(cents)
    cents -= pennies * 1

    # Calculate the total number of coins
    coins = quarters + dimes + nickels + pennies

    # Print the total number of coins
    print(coins)


# Execute the main func if this script is run directly
if __name__ == "__main__":
    main()
