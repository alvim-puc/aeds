# Import necessary modules
import sys

# Read the scores
scores = [int(input()) for _ in range(5)]

# Find the highest score
first = max(scores)
# Find the number of occurrences of the highest score
firstplace = scores.count(first)

# Check if all scores are the same
if firstplace == 5:
    print("5 0")
else:
    # Remove the first occurrence of the highest score from the list
    scores.remove(first)
    # Find the new highest score
    second = max(scores)
    # Find the number of occurrences of the new highest score
    secondplace = scores.count(second)
    # Print the results
    print(f"{firstplace} {secondplace}")
