import math

# Function to check if a number is prime
def is_prime(num):
    if num <= 1:
        return False
    for i in range(2, int(math.sqrt(num)) + 1):
        if num % i == 0:
            return False
    return True

# Function to calculate the average of the first n prime numbers
def average_of_primes(n):
    primes = []
    num = 2
    
    while len(primes) < n:
        if is_prime(num):
            primes.append(num)
        num += 1
    
    return sum(primes) / n

# Calculate the average of the first 100 prime numbers
average_100_primes = average_of_primes(100)
print(f"The average of the first 100 prime numbers is: {average_100_primes:.6f}")
