# DSL Mini Project
# Yashowardhan Shinde SC69
# Sudoku Game
# Backtracking Algorithm

def display(board):
    # Print Line after every 3 rows
    for i in range(len(board)):
        if i % 3 == 0:
            print("-------------------------------------")

        # Print | after every 3 columns
        # Print individual elements
        for j in range(len(board[0])):
            if j % 3 == 0:
                print("|", end='  ')

            if board[i][j] == 0:
                print("_", end='  ')
            else:
                print(board[i][j], end='  ')

            # Print | at the end of every row
            if j == 8:
                print("|")
    # Print the last rows of dashes
    print("-------------------------------------")


def find_empty(board):

    # Iterate over the array and if element == 0 return the position
    for i in range(len(board)):
        for j in range(len(board[0])):
            if board[i][j] == 0:
                return i, j  # row, column
    return None


def validate(board, num, pos):
    # Checking if the current value is valid or not

    # Check if Number exists in the row more than once
    # If Yes return False as it is not acceptable
    temp_row = board[pos[0]]
    # print(temp_row)
    if temp_row.count(num) > 0:
        return False

    # Check if Number exists in the same column more than once
    # If yes return False as it is not acceptable
    temp_col = [board[i][pos[1]] for i in range(len(board))]
    # print(temp_col)
    if temp_col.count(num) > 0:
        return False

    # Check if Number exists in the same Inner Box more than Once
    # If yes return False as this is not acceptable
    x_pos = pos[0] // 3
    y_pos = pos[1] // 3

    # x_pos and y_pos will always have value between 0-2
    # if x_pos = 0 and y_pos = 0 it means the element is in first mini block
    # Similarly there will be 9 mini blocks
    # We will iterate through the block in which the current element is present
    # If we find that element we will return False
    for i in range(x_pos*3, x_pos*3 + 3):
        for j in range(y_pos*3, y_pos*3 + 3):
            if board[i][j] == num and (i, j) != pos:
                return False

    return True


def solve_puzzle(board):

    # print(board)
    # Find an empty position in the 2D array
    # If we don't find any value then return True
    # This means that all position of the Puzzle are full and we have successfully solved the Puzzle
    # But if we find a empty position the else part will be executed.
    position = find_empty(board)
    if not position:
        return board
    else:
        # The solution is a recursive algorithm which goes on until the last position of Puzzle is filled
        # Initialize the row and column position
        row, col = position

        # for that position we will now find a valid value
        for i in range(1, 10):
            # We will try all the values from 1 to 9
            # If our value is validated we will set that position to be the value we got
            if validate(board, i, (row, col)):
                board[row][col] = i

                # We will check if all the conditions are satisfied or not
                # If Yes we will return True and call the solve() function
                if solve_puzzle(board):
                    return board

                # If the condition fails we will backtrack and set the previous position element as 0
                # And we will start over again
                board[row][col] = 0

        return False



