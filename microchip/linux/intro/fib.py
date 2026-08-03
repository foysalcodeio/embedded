#!/usr/bin/env python
print ("My Fibonacci Calculator")

# init terms 

n1, n2 = 0, 1
count = 0 

#get number of terms

nTerms = int(input("How many terms? "))

# validate nTerms

if nTerms <= 0:
	print("Please enter a positive integer")
elif nTerms == 1:
	print("Fibonacci sequence upto",nTerms)
	print(n1)
else:
	print("Fibonacci sequence:")
	while count < nTerms:
		print(n1)
		nth = n1 + n2
		n1 = n2
		n2 = nth
		count +=1



