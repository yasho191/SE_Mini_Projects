# Linear Probing

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
                for j in range(code, code + len(self.arr)):
                    if self.arr[j % 10] is None:
                        self.arr[j % 10] = self.key[i]
                        flag = 1
                        break
                if flag == 0:
                    print(f"Key {self.key[i]} cannot be inserted!")

    def __getitem__(self, item):
        code = self.hash_code(item)
        comparisons = 1
        if self.arr[code] == item:
            print(item)
            return item, code, comparisons
        else:
            for i in range(code, code + len(self.arr)):
                comparisons += 1
                if self.arr[i % 10] == item:
                    print(item)
                    return item, i % 10, comparisons
            print("Item not found!")
            return "Item not found!"

    def __delitem__(self, key):
        code = self.hash_code(key)

        if self.arr[code] == key:
            self.arr[code] = None
        else:
            for i in range(code, code + len(self.arr)):
                if self.arr[i % 10] == key:
                    self.arr[i % 10] = None
                    break

    def insert(self, key):
        code = self.hash_code(key)
        if None not in self.arr:
            print("Hash Table full!")
            return
        elif self.arr[code] is None:
            self.arr[code] = key
        else:
            for i in range(code, code + len(self.arr)):
                if self.arr[i % 10] is None:
                    self.arr[i % 10] = key
                    break


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
