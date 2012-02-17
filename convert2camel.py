import sys, os

for line in open(sys.argv[1]):
	for word in line.split():
		if "_" in word:
			print word