# Quadratic Probing

class HashMap:
    def __init__(self, arr):
        self.arr = [None for i in range(10)]
        self.key = arr
        self.map_values()

    def hash_code(self, key):
        code = key % 10
        return code

    def map_values(self):
        for i in range(len(self.key)):
            code = self.hash_code(self.key[i])
            if self.arr[code] is None:
                self.arr[code] = self.key[i]
            else:
                flag = 0
                s = set()
                s.add(code)
                j = code
                x = 1
                while x < 11:
                    j = code + x**2
                    if j not in s:
                        if self.arr[j % 10] is None:
                            flag = 1
                            self.arr[j % 10] = self.key[i]
                            break
                    s.add(j)
                    x += 1
                if flag == 0:
                    print("Cannot insert :", self.key[i])

    def __getitem__(self, item):
        comparisons = 1
        code = self.hash_code(item)
        if self.arr[code] == item:
            # print(item)
            return item, code, comparisons
        else:
            s = set()
            s.add(code)
            j = code
            x = 1
            while x < 11:
                j = code + x ** 2
                comparisons += 1
                if j not in s:
                    if self.arr[j % 10] == item:
                        # print(item)
                        return item, j % 10, comparisons
                s.add(j)
                x += 1
            # print("Item not found!")
            return "Item not found!", -1, comparisons

    def __delitem__(self, key):
        code = self.hash_code(key)

        if self.arr[code] == key:
            self.arr[code] = None
        else:
            s = set()
            s.add(code)
            j = code
            x = 1
            while x < 11:
                j = code + x ** 2
                if j not in s:
                    if self.arr[j % 10] == key:
                        self.arr[j % 10] = None
                        break
                s.add(j)
                x += 1

    def insert(self, key):
        if None not in self.arr:
            print("Hash Table full!")
            return
        code = self.hash_code(key)
        if self.arr[code] is None:
            self.arr[code] = key
        else:
            flag = 0
            s = set()
            s.add(code)
            j = code
            x = 1
            while x < 11:
                j = code + x ** 2
                if j not in s:
                    if self.arr[j % 10] is None:
                        self.arr[j % 10] = key
                        flag = 1
                        break
                s.add(j)
                x += 1
            if flag == 0:
                print("Insertion Unsuccessful!")


def main():
    members = []
    n = int(input("Enter the number of members:"))
    for i in range(n):
        x = int(input("Enter the mobile numbers of the member: "))
        members.append(x)
    map1 = HashMap(members)
    print("What operations do you want to perform?")

    ans = 1
    while ans:
        print("""
            1. Insert new key
            2. Search key
            3. Delete key
            4. Display
            """)
        option = int(input("Enter the option: "))
        if option == 1:
            key = int(input("Enter the new number :"))
            map1.insert(key)
        elif option == 2:
            key = int(input("Enter the key you want to search: "))
            k, index, comparisons = map1[key]
            print(f"key = {k}\nindex = {index}\ncomparisons = {comparisons}")
        elif option == 3:
            key = int(input("Enter the number you wish to delete :"))
            del map1[key]
        elif option == 4:
            print("The current hash table is : ", map1.arr)
        else:
            print("Invalid input!")

        ans = int(input("Do you want to continue? (1 Yes/ 0 No)"))


main()


"""
4 + 1 = 5
4 + 4 = 8
4 + 9 = 13 % 10 = 3
4 + 16 = 20 % 10 = 0
4 + 25 = 29 % 10 = 9
4 + 36 = 40 % 10 = 0
4 + 49 = 53 % 10 = 3
4 + 64 = 68 % 10 = 8
4 + 81 = 85 % 10 = 5
4 + 100 = 104 % 10 = 4
"""