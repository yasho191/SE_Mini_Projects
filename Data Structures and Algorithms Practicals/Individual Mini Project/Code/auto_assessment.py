import os
import openpyxl
import warnings
import file_details
import compute_result

warnings.filterwarnings("ignore")


# The main function has the complete code flow
def main():
    os.chdir("/Users/yashowardhanshinde/Desktop/DSA Practicals/Individual Mini Project/Input_Files")

    while True:
        # File_list will contain all the files in the input directory
        file_list = []
        for file in os.listdir():
            # The default file that is created cannot not be processed so we will not list that file
            if file != ".DS_Store":
                file_list.append(file)

        # Display the files to the user
        i = 1
        print("The files found in the input directory are:")
        for file in file_list:
            print(f"{i}. {file}")
            i += 1

        # Take input from user for selection of the file to be used
        file_to_be_processed = int(input("Enter the file you want to process: "))
        # All results and reports will be created here.
        assessment(file_list[file_to_be_processed - 1])

        # After execution of the earlier selected file if user wants to process another file he can do so
        flag = int(input("Do you want to process any other files? "))
        if not flag:
            break


def assessment(file):
    # Try catch block for avoiding incompatible file error
    try:
        # open the excel file as wb(workbook)
        wb = openpyxl.load_workbook(file)
        ws = wb.active

        print("The file has been detected...")
        print(f"File name: {file}")
        print()

        # Initial analysis is done the function will return the total parameters in the file and will also return a list
        # of all the parameters
        columns, sep = file_details.get_details(ws)
        print("The total parameters found in the file are: ", columns)
        print()

        print()
        # collecting the data in the excel file and saving it in a hashmap from where we can access the records
        # parameters to the function are worksheet(ws) and list of parameters(sep)
        # sep = student_evaluation_parameters
        print("Collecting student data...")
        student_records = file_details.get_records(ws, sep)
        print("Records fetched successfully.")

        # Now the user will decide the parameters which should be considered for evaluation of marks
        # 1 - Consider it | 0 - Do not consider
        # For parameters like attendance special input is taken (days which represents total working days)
        print()
        max_values, days = file_details.get_max_values(columns, sep)
        # Get input from user for max_internal_marks
        # final result will be calculated based on this value
        max_internal_marks = int(input("Enter the total internal marks: "))
        print()
        print()

        # Now is the time to calculate the results of all the students
        # Parameters: Student records(hashmap), max_values(hashmaps of max marks for that parameter)
        # days, max_internal marks
        # Function returns updated student records and result array with final marks
        print("Maximum marks of all parameters collected!")
        print("Ready for calculating results....")
        print("Result Calculation started...")
        student_records, results = compute_result.calculate_result(max_values, student_records, max_internal_marks,
                                                                   days)
        print("Results have been successfully calculated!")
        print("For getting the output file select Save and Exit before you exit the program!")
        print()

        # The user can now perform 3 operations
        # Search a student | record generate a report | Save and Exit
        while True:
            print("Menu: ")
            print("1. Search Record")
            print("2. Generate general Report")
            print("3. Save and Exit")
            option = int(input("Enter your choice: "))

            if option == 1:
                print("You can look up the student records by entering their roll numbers")
                # Search By Roll Number as Roll Number is unique for all students
                # Look Up time = O(1)
                compute_result.search_student_record(student_records)
                print()
            elif option == 2:
                print("Generating general report for given data...")
                # The report generated will have :
                # 1. Average Marks for every Parameter Except for Extracurricular
                # 2. Minimum Marks obtained by a student in every Parameter
                # 3. Maximum Marks obtained by a student in every parameter.
                compute_result.generate_report(max_values, student_records, days)
                print("Report successfully generated for given data")
                print()
            elif option == 3:
                print("Saving the results and generating final file...")
                # The function save all the results and save the file in the output files folder
                file_details.put_results(ws, results, columns)
                wb.save(filename=f"/Users/yashowardhanshinde/Desktop/DSA Practicals/Individual Mini Project/Output_Files/{file}")
                print("File created successfully find the file in Output_File folder....")
                print("Process complete without any error!")
                break
            else:
                print("Invalid Option!")
                print()

            cont = int(input("Do you want to continue using the current file? "))
            if not cont:
                break
    except:
        print("Program encountered an unexpected error!")
        print()


main()
