# kruskals algorithm
class und_graph:
    def __init__(self):
        self.graph = []
        self.nodes = int(input("Enter the number of nodes you want in your graph: "))
        for i in range(self.nodes):
            x = []
            for j in range(self.nodes):
                x.append(0)
            self.graph.append(x)

        self.edges = 0

    def create(self):
        while True:
            n1, n2 = list(map(int, input("Enter the Nodes N1 and N2: ").split()))
            weight = int(input("Enter the weight of the edge: "))
            self.graph[n1][n2] = weight
            self.graph[n2][n1] = weight
            self.edges += 1

            x = int(input("Do you want to insert another node? "))
            if x != 1:
                break

    def display(self):
        for i in range(self.nodes):
            for j in range(self.nodes):
                print(self.graph[i][j], end=" ")
            print()

    def kruskals_algorithm(self):
        visited = [0 for i in range(self.nodes)]
        edge_arr = []
        selected_path = []
        minimum = 0

        for i in range(self.nodes):
            for j in range(self.nodes):
                if [j, i, self.graph[i][j]] not in edge_arr and self.graph[i][j] != 0:
                    edge_arr.append([i, j, self.graph[i][j]])

        edge_arr = sorted(edge_arr, key=lambda x: x[2])

        for k in range(self.nodes - 1):
            if visited[edge_arr[0][0]] != 1 or visited[edge_arr[0][1]] != 1:
                visited[edge_arr[0][0]] = 1
                visited[edge_arr[0][1]] = 1
                selected_path.append(edge_arr[0])
                minimum += edge_arr[0][2]

            edge_arr.pop(0)

        print(minimum)
        print(selected_path)


obj = und_graph()
obj.create()
obj.display()
obj.kruskals_algorithm()








