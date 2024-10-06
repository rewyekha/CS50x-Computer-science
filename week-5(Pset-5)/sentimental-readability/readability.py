import math


def main():
    # Prompt the user for some text
    text = input("Text: ")

    # Count the number of letters, words, and sentences in the text
    letters = 0
    words = 1
    sentences = 0

    for char in text:
        if char.isalpha():
            letters += 1
        elif char == ' ':
            words += 1
        elif char in '.!?':
            sentences += 1

    # Calculate coleman-Liau index
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = 0.0588 * L - 0.296 * S - 15.8

    # Print the grade level
    index = round(index)

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()
