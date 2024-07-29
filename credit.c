#include <cs50.h>
#include <stdio.h>

long get_card(void);
bool check_american_express(long number);
bool check_mastercard(long number);
bool check_visa(long number);
bool checksum(long number);

int main(void)
{
    // Get user's input
    long number = get_card();

    // Checksum
    if (checksum(number))
    {
        // Check which card it is
        if (check_american_express(number))
        {
            printf("AMEX\n");
        }
        else if (check_mastercard(number))
        {
            printf("MASTERCARD\n");
        }
        else if (check_visa(number))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

long get_card(void)
{
    long n;
    do
    {
        n = get_long("Number: ");
    }
    while (n < 1);
    return n;
}

// Check if it is American Express
// 15 digits, starts with 34 or 37
bool check_american_express(long number)
{
    int count = 0;
    long first2 = number;

    // Get number of digits
    while (number)
    {
        int digit = number % 10;
        count++;

        // Check how the number starts
        while (first2 >= 100)
        {
            first2 /= 10;
        }
        number /= 10;
    }

    // Does it fulfill all the requirements?
    if (count == 15 && (first2 == 34 || first2 == 37))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Check if it is MasterCard
// 16 digits, starts with 51, 52, 53, 54 or 55
bool check_mastercard(long number)
{
    int count = 0;
    long first2 = number;

    // Get number of digits
    while (number)
    {
        int digit = number % 10;
        count++;

        // Check how the number starts
        while (first2 >= 100)
        {
            first2 /= 10;
        }
        number /= 10;
    }

    // Does it fulfill all the requirements?
    if (count == 16 && (first2 == 51 || first2 == 52 || first2 == 53 || first2 == 54 || first2 == 55))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Check if it is Visa
// 13 or 16 digits, starts with 4
bool check_visa(long number)
{
    int count = 0;
    long temp = number;
    int digit = 0;

    // Get number of digits
    while (number)
    {
        digit = number % 10;
        long first2 = temp;
        number /= 10;
        count++;
    }

    // Does it fulfill all the requirements?
    if (digit == 4 && (count == 13 || count == 16))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool checksum(long number)
{
    int count = 0;
    int sum1 = 0;
    int sum2 = 0;
    int total = 0;

    // 1. Multiply every other digit by 2, starting with the number’s second-to-last digit,
    //and then add those products’ digits together.
    while (number)
    {
        int digit = number % 10;
        number /= 10;
        count++;
        // Get the every other digit, multiply them by 2 and sum them
        if (count % 2 == 0)
        {
            digit *= 2;
            // If after the multiplication the digit has 2 digits, separate them and sum them
            while (digit)
            {
                int digit2 = digit % 10;
                digit /= 10;
                sum1 += digit2;
            }
        }
        // Sum the other numbers that are not multiplied by 2
        else
        {
            sum2 += digit;
        }
    }

    // 2. Add the sum to the sum of the digits that weren’t multiplied by 2.
    total = sum1 + sum2;

    // 3. If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0),
    // the number is valid!
    if (total % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}