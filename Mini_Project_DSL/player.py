# DSL Mini Project
# Yashowardhan Shinde SC69
# Sudoku Game
# Player Flow

# Functions:
"""
1. display
2. find_empty
3. validate
4. solve_puzzle
6. flow
7. main
8. permanent_elements
9. player_input
10. submit_puzzle
"""


import boards
import time


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


def permanent_elements(board):
    # collecting the elements which cannot be changed
    permanent = []
    # Iterate over the Array and store position of all the elements which are non-zero
    for i in range(len(board)):
        for j in range(len(board[0])):
            if board[i][j] != 0:
                permanent.append([i, j])

    return permanent


def player_input(board, permanent):
    # Taking Input from the player
    print("Make Your Move :")
    row = int(input("Enter the row (1-9):"))
    col = int(input("Enter the column (1-9):"))

    # checking if the input is in proper range or not
    if row > 9 or col > 9:
        print("Invalid position")
        return False
    # checking if the element at position row-1, col-1 can be changed or not
    elif [row-1, col-1] in permanent:
        print("You can not change the value at this position.")
        return False
    else:
        value = int(input("Enter the value you want to enter (1-9):"))
        # checking if value entered is valid or not
        if value > 9:
            print("Invalid Input")
            return False
        else:
            board[row-1][col-1] = value
            return True


def submit_puzzle(board, i):

    if i == 1:
        x = list([x for x in boards.sudoku_board_1])
    elif i == 2:
        x = list([x for x in boards.sudoku_board_2])
    else:
        x = list([x for x in boards.sudoku_board_3])

    # finding the correct solution of the puzzle
    x = solve_puzzle(x)
    # If solution matches te current array then the game is over
    if board == x:
        print(board)
        print("Congratulations You have Successfully solved the Sudoku Puzzle!!")
        return True
    else:
        print("Your solution is not correct please try other solutions!!")
        return False


def flow(player_board, fixed, i):
    # Run Until Player wins or quits
    while True:
        player_input(player_board, fixed)
        for i in range(3):
            print()
        display(player_board)
        sub = input("Do you want to submit your answer?\n Yes/No :")
        if sub == "Yes":
            x = submit_puzzle(player_board, i)
            if x:
                break

        q = input("Do you want to Quit?\n Yes/ No :")
        if q == "Yes":
            break


def main():
    a = int(input("Press 1 to start the game :"))

    if a == 1:
        print("Welcome to this Sudoku Game. \nThere are 3 levels in this game : \n1. Easy\n2. Medium\n3. Hard")
        option = int(input("Enter your choice :"))

        if option == 1:
            player_board = [
                [7, 8, 0, 4, 0, 0, 1, 2, 0],
                [6, 0, 0, 0, 7, 5, 0, 0, 9],
                [0, 0, 0, 6, 0, 1, 0, 7, 8],
                [0, 0, 7, 0, 4, 0, 2, 6, 0],
                [0, 0, 1, 0, 5, 0, 9, 3, 0],
                [9, 0, 4, 0, 6, 0, 0, 0, 5],
                [0, 7, 0, 3, 0, 0, 0, 1, 2],
                [1, 2, 0, 0, 0, 7, 4, 0, 0],
                [0, 4, 9, 2, 0, 6, 0, 0, 7]]
            display(player_board)
            fixed = permanent_elements(player_board)
            flow(player_board, fixed, 1)

        elif option == 2:
            player_board = [
                [3, 0, 6, 5, 0, 8, 4, 0, 0],
                [5, 2, 0, 0, 0, 0, 0, 0, 0],
                [0, 8, 7, 0, 0, 0, 0, 3, 1],
                [0, 0, 3, 0, 1, 0, 0, 8, 0],
                [9, 0, 0, 8, 6, 3, 0, 0, 5],
                [0, 5, 0, 0, 9, 0, 6, 0, 0],
                [1, 3, 0, 0, 0, 0, 2, 5, 0],
                [0, 0, 0, 0, 0, 0, 0, 7, 4],
                [0, 0, 5, 2, 0, 6, 3, 0, 0]]
            display(player_board)
            fixed = permanent_elements(player_board)
            flow(player_board, fixed, 2)

        elif option == 3:
            player_board = [
                [0, 0, 5, 7, 1, 0, 3, 2, 9],
                [0, 0, 0, 3, 6, 2, 8, 0, 0],
                [0, 0, 4, 0, 0, 0, 0, 0, 0],
                [1, 0, 0, 0, 0, 0, 9, 8, 0],
                [0, 8, 3, 9, 0, 0, 2, 5, 0],
                [0, 0, 6, 0, 0, 3, 1, 0, 0],
                [3, 0, 0, 1, 0, 6, 0, 0, 0],
                [4, 0, 9, 8, 0, 0, 0, 0, 7],
                [0, 7, 0, 0, 2, 9, 5, 0, 0]]
            display(player_board)
            fixed = permanent_elements(player_board)
            flow(player_board, fixed, 3)

        else:
            print("Invalid Input!")


timer_start = time.time()
main()
timer_end = time.time()
print("Total Time Taken :", timer_end - timer_start, " sec.")
