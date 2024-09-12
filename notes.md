# Frequency Analysis and substitution cipher solve algorithm

1. Make an empty list of all the guesses we have made for the key
2. Assume the cipher text is actually plain text, and everything is correct.
3. When/if that fails, find the highest frequency letter unguessed and assign it the value of the corresponding frequency letter from our table
4. Re-run the evaluation. If the result is better, keep it and proceed. If not, move to the next most frequent option for the current character in question
5. If the evaluation was positive, find the longest word with the fewest pieces unknown, and find the closest word in the dictionary to make our next guesses.
6. Again, evaluate the influence of that guess. If poor, try something else. If good, keep it and move on.
7. Never make a guess you've already made.
