#include <cs50.h>
#include <stdio.h>

bool check_sum(long num);

int main(void)
{
    int digits = 0, single_digit = 0, two_digit = 0;
    long user_input = get_long("Number: ");

    // Call the checksum function
    if (!check_sum(user_input))
    {
        printf("INVALID\n");
        return 0;
    }

    long temp = user_input;

    // Calculate the number of digits and capture the last two digits
    while (temp > 0)
    {
        if (temp < 10)
        {
            single_digit = temp;
        }
        else if (temp < 100)
        {
            two_digit = temp;
        }
        temp /= 10;
        digits++;
    }

    // Print for debugging
    printf("digits: %i\n", digits);
    printf("single_digit: %i\n", single_digit);
    printf("two_digit: %i\n", two_digit);

    // Validate the card type based on number of digits and the first two digits
    if ((two_digit == 34 || two_digit == 37) && digits == 15)
    {
        printf("AMEX\n");
    }
    else if ((two_digit == 51 || two_digit == 52 || two_digit == 53 || two_digit == 54 ||
              two_digit == 55) &&
             digits == 16)
    {
        printf("MASTERCARD\n");
    }
    else if (single_digit == 4 && (digits == 13 || digits == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

bool check_sum(long num)
{
    int total = 0, buffer = 0;
    bool var = true;

    while (num > 0)
    {
        if (var)
        {
            total += num % 10; // Add the last digit
            num /= 10;
            var = false;
        }
        else
        {
            buffer = num % 10;
            buffer *= 2;
            if (buffer > 9) // Add the digits of the product
            {
                total += buffer % 10; // Add the second digit
                total += buffer / 10; // Add the first digit
            }
            else
            {
                total += buffer;
            }
            var = true;
            num /= 10;
        }
    }
    printf("total: %i\n", total);

    return (total % 10 == 0);
}
