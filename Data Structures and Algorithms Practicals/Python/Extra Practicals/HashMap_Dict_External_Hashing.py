# External Hash
# Dictionary

class HashMap:
    def __init__(self, key_arr, value_arr):
        self.arr = [[] for i in range(10)]
        self.input_arr = key_arr
        self.output_arr = value_arr
        self.map_values()

    def __getitem__(self, key):
        code = self.hash_code(key)
        if len(self.arr[code]) > 1:
            for i in range(len(self.arr[code])):
                if self.arr[code][i][0] == key:
                    print(self.arr[code][i][1])
        elif len(self.arr[code]) == 1:
            print(self.arr[code][0][1])
        else:
            print("Item not found...")

    def __delitem__(self, key):
        code = self.hash_code(key)
        if len(self.arr[code]) > 1:
            for i in range(len(self.arr[code])):
                if self.arr[code][i][0] == key:
                    self.arr[code].pop(i)
        elif len(self.arr[code]) == 1:
            self.arr[code].pop(0)

    def __setitem__(self, key, value):
        code = self.hash_code(key)
        self.arr[code].append([key, value])

    def hash_code(self, input):
        ord_code = 0
        for i in range(len(input)):
            ord_code += ord(input[i])
        return ord_code % 10

    def map_values(self):
        for i in range(len(self.input_arr)):
            code = self.hash_code(self.input_arr[i])
            self.arr[code].append([self.input_arr[i], self.output_arr[i]])

    def get_value(self, key):
        code = self.hash_code(key)
        if len(self.arr[code]) > 1:
            for i in range(len(self.arr[code])):
                if self.arr[code][i][0] == key:
                    return self.arr[code][i][1]
        elif len(self.arr[code]) == 1:
            return self.arr[code][0][1]
        return "Item not found..."

    def set_value(self, key, value):
        code = self.hash_code(key)
        self.arr[code].append([key, value])


hash_map = HashMap(["1", "3", "2", "4"], [1, 2, 3, 4])
hash_map.set_value("6", 5)
print(hash_map.arr)

