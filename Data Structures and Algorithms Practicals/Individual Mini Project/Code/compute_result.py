import matplotlib.pyplot as plt


# Formula for calculation will be =
# Calculate total marks for all parameters (sum of max marks)
# Calculate total marks obtained by the student
# For Attendance marks = (days attended/ total working days)*max_marks[attendance]
# For extracurricular marks = (full marks if 1 and 0 if 0)
# Divide marks obtained by the student by total marks
# Multiply this value with max_internal_marks
def calculate_result(max_marks, student_records, total, days):
    # result array will store the final result of every student
    results = []
    # parameters = evaluation parameters
    # values = max value of every parameter
    parameters = list(max_marks.keys())
    values = list(max_marks.values())

    # iterate over all the student records and calculate the result
    for record in student_records.values():
        # marks array will store marks of a student
        marks = []
        for paras in parameters:
            if paras.lower() == "attendance":
                attendance_percentage = record[paras] / days
                marks.append(attendance_percentage * max_marks[paras])
            elif paras.lower() == "extracurricular":
                if record[paras]:
                    marks.append(max_marks[paras])
                else:
                    marks.append(0)
            else:
                marks.append(record[paras])

        total_marks = sum(values)
        marks_obtained = sum(marks)
        internal_marks_percentage = marks_obtained / total_marks
        internal_marks = internal_marks_percentage * total
        # Add result parameter to all the records
        record["Result"] = internal_marks
        results.append(internal_marks)

    return student_records, results


# Search a record
def search_student_record(student_records):
    # take input from the user for thr roll number
    roll_no = int(input("Enter the roll number of student: "))
    try:
        record = student_records[roll_no]
        print("Record found: ")
        print("Roll Number : ", roll_no)
        # Print the record if found
        for para in list(record.keys()):
            print(f"{para} : {record[para]}")
        print()
    except KeyError as error:
        print("Record not present!")


# General Report
def generate_report(max_marks, student_records, days):
    parameters = list(max_marks.keys())
    values = list(max_marks.values())
    total_records = len(student_records)
    print(parameters)
    report = dict()
    for i in parameters:
        report[i] = 0

    for record in student_records.values():
        for para in parameters:
            if para.lower() == "attendance":
                attendance_percentage = record[para] / days
                report[para] += attendance_percentage * max_marks[para]
            elif para.lower() == "extracurricular":
                if record[para]:
                    report[para] += max_marks[para]
                else:
                    report[para] += 0
            else:
                report[para] += record[para]

    average_values = []
    print("The average values for parameters to be evaluated: ")
    for j in report.keys():
        report[j] /= total_records
        report[j] /= max_marks[j]
        report[j] *= 100
        if j.lower() != "extracurricular":
            average_values.append(report[j])
        print(f"The average for {j} is".ljust(50) + f": {round(report[j])}%")

    max_min_values = dict()
    for para in parameters:
        if para.lower() != "extracurricular":
            max_min_values[para] = []

    for r in student_records.values():
        for para in parameters:
            if para.lower() != "extracurricular":
                max_min_values[para].append(r[para])

    print()
    print("The Maximum values for the parameters are: ")
    maximum_values = []
    for para in parameters:
        if para.lower() != "extracurricular":
            if para.lower() == "attendance":
                maximum_values.append((max(max_min_values[para]) / days) * 100)
            else:
                maximum_values.append((max(max_min_values[para]) / max_marks[para]) * 100)
            print(f"Maximum for {para} is".ljust(50) + f": {max(max_min_values[para])}")

    print()

    print("The Minimum values for the parameters are: ")
    minimum_values = []
    for para in parameters:
        if para.lower() != "extracurricular":
            # if the parameter is attendance a special formula is needed
            # days_attended/total_work_days
            if para.lower() == "attendance":
                minimum_values.append((min(max_min_values[para]) / days) * 100)
            else:
                minimum_values.append((min(max_min_values[para]) / max_marks[para]) * 100)
            print(f"Minimum for {para} is".ljust(50) + f": {min(max_min_values[para])}")

    # Plot a bar graph which shows average highest and lowest values of every parameter
    fig = plt.figure(figsize=(15, 10))
    ax = fig.add_axes([0, 0, 1, 1])
    width = 0.25
    ax.bar([i for i in range(7)], average_values, width=width, color="lightblue", label="Average Values")
    ax.bar([i + 0.25 for i in range(7)], maximum_values, width=width, color="lightgreen", label="Maximum Values")
    ax.bar([i + 0.50 for i in range(7)], minimum_values, width=width, color="pink", label="Minimum Values")
    ax.grid(zorder=0)
    plt.title("General Report Visualization")
    plt.xlabel("Parameters")
    plt.ylabel("Values")
    plt.xticks([i + 0.25 for i in range(len(maximum_values))],
               [para for para in parameters if para != "Extracurricular"])
    plt.legend(loc="upper right")
    plt.show()
