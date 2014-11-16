
fName = "mazeDataFile.txt"

#open file and read lines
with open(fName) as f:
		content = f.readlines()

for h in content:
		print(h, end="")
