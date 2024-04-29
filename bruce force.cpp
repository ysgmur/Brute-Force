import random
# mandatory variables
emptySymbol = '[]'
heroSymbol = '[H]'
monsterSymbol = '[M]'
STAMINA = 10
MONSTER_REWARD = 5
bestPath = ''
maxGold = -1
# global constants
area = []
monsters = []
position_of_hero = None
dimension_1 = 8
dimension_2 = 8
class Coordinate:
 def __init__(self, row, column):
 self.row = row
 self.column = column
 def __str__(self):
 return f"{self.row}, {self.column}"
def fill_area():
 for i in range(dimension_1):
 row = []
 for j in range(dimension_2):
 row.append(emptySymbol)
 area.append(row)
def print_area():
 print(" ", end="")
 for i in range(dimension_2):
 print(f"{i:2}", end=" ")
 print()
 for i in range(dimension_1):
 print(f"{i:2}", end=" ")
 for j in range(dimension_2):
 print(area[i][j], end="")
 print()
def is_valid_coordinate(row, column):
 return 0 <= row < dimension_1 and 0 <= column < dimension_2
def valid_monster_position(row, column):
 if not is_valid_coordinate(row, column):
 return False
 if area[row][column] != emptySymbol:
 return False
 for position_of_monster in monsters:
 if abs(position_of_monster.row - row) <= 2 and
abs(position_of_monster.column - column) <= 2:
 return False
 return True
def assign_monsters():
 monsters_assigned = 0
 while monsters_assigned < 5:
 row = random.randint(0, dimension_1 - 1)
 column = random.randint(0, dimension_2 - 1)
 if valid_monster_position(row, column):
 area[row][column] = monsterSymbol
 monsters_assigned += 1
def assign_hero():
 while True:
 row = random.randint(0, dimension_1-1)
 col = random.randint(0, dimension_2-1)
 if valid_monster_position(row, col):
 area[row][col] = 'H'
 return (row, col)
def move(pos, direction):
 if direction == 'L':
 return Coordinate(pos.row, pos.column - 1)
 elif direction == 'R':
 return Coordinate(pos.row, pos.column + 1)
 elif direction == 'U':
 return Coordinate(pos.row - 1, pos.column)
 elif direction == 'D':
 return Coordinate(pos.row + 1, pos.column)
def bruteForce(currentPos, path, gold, stamina, killed):
 global bestPath, maxGold
 if stamina == 0 or gold >= maxGold:
 if gold > maxGold:
 maxGold = gold
 bestPath = path
 return
 for direction in ['U', 'D', 'L', 'R']:
 newPos = move(currentPos, direction)
 if is_valid_coordinate(newPos.row, newPos.column):
 newStamina = stamina - 1
 newKilled = killed.copy()
 newGold = gold
 if newPos in monsters and newPos not in killed:
 newGold += MONSTER_REWARD
 newKilled.append(newPos)
 bruteForce(newPos, path + direction, newGold, newStamina,
newKilled)
def getProfitAndPath(currentPosition, currentStamina, visitedMonsters,
currentPath):
 # Base case: out of stamina or no valid move left
 if currentStamina == 0:
 return (0, [])
 maxProfit = 0
 bestPath = []
 # Try each possible move
 for move in ['U', 'D', 'L', 'R']:
 if move == 'U':
 newRow = currentPosition[0] - 1
 newColumn = currentPosition[1]
 elif move == 'D':
 newRow = currentPosition[0] + 1
 newColumn = currentPosition[1]
 elif move == 'L':
 newRow = currentPosition[0]
 newColumn = currentPosition[1] - 1
 elif move == 'R':
 newRow = currentPosition[0]
 newColumn = currentPosition[1] + 1
 # Check if move is valid
 if is_valid_coordinate(newRow, newColumn):
 # Calculate new profit and stamina
 newProfit = 0
 if area[newRow][newColumn] == monsterSymbol and (newRow,
newColumn) not in visitedMonsters:
 newProfit = MONSTER_REWARD
 visitedMonsters.add((newRow, newColumn))
 newStamina = currentStamina - 1
 # Recurse on next move
 profit, path = getProfitAndPath((newRow, newColumn),
newStamina, visitedMonsters, currentPath + [move])
 profit += newProfit
 if profit > maxProfit:
 maxProfit = profit
 bestPath = path
 return (maxProfit, [currentPath] + bestPath)
def findBestPath():
 global bestPath, maxGold
 fill_area()
 assign_monsters()
 position_of_hero = Coordinate(*assign_hero())
 print_area()
 bruteForce(position_of_hero, '', 0, STAMINA, [])
 print(f"\nMaximum possible gold : {maxGold}")
 if maxGold == 0:
 print("No gold found!")
 else:
 path = ''
 for i in range(0, len(bestPath)):
 if i == 0:
 path += bestPath[i]
 else:
 lastCoord = move(position_of_hero, bestPath[i-1])
 currentCoord = move(lastCoord, bestPath[i])
 if lastCoord.row < currentCoord.row:
 path += 'D'
 elif lastCoord.row > currentCoord.row:
 path += 'U'
 elif lastCoord.column < currentCoord.column:
 path += 'R'
 elif lastCoord.column > currentCoord.column:
 path += 'L'
 print(f"Best path: {path}")
findBestPath()