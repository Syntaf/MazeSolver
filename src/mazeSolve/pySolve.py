
fName = "mazeDataFile.txt"

#open file and read lines
with open(fName) as f:
		content = f.readlines()

ROWS = None
COLS = None

#get rows and columns in text file from first line
words = content[0].split(" ")
for c in range(0,len(words)):
	if words[c] == "ROWS":
		ROWS = words[c+1]
	elif words[c] == "COLS":
		COLS = words[c+1]

#create empty list
maze_map = [[0 for x in range(int(COLS))] for x in range(int(ROWS))]

#loop through and establish walls
for h in content:
	print(h, end="")
