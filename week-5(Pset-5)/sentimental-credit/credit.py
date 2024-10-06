def check_sum(num):
    total = 0
    var = True

    while num > 0:
        if var:
            total += num % 10
            num //= 10
            var = False
        else:
            buffer = (num % 10) * 2
            if buffer > 9:
                total += buffer % 10
                total += buffer // 10
            else:
                total += buffer
            var = True
            num //= 10

    return total % 10 == 0


def main():
    user_input = int(input("Number: "))

    # Validate the checksum
    if not check_sum(user_input):
        print("INVALID")
        return

    digits = 0
    single_digit = 0
    two_digit = 0
    temp = user_input

    # Find the number of digits and the last two digits
    while temp > 0:
        if temp < 10:
            single_digit = temp
        elif temp < 100:
            two_digit = temp
        temp //= 10
        digits += 1

    # Check for AMEX, MASTERCARD, and VISA
    if (two_digit == 34 or two_digit == 37) and digits == 15:
        print("AMEX")
    elif (51 <= two_digit <= 55) and digits == 16:
        print("MASTERCARD")
    elif single_digit == 4 and (digits == 13 or digits == 16):
        print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
