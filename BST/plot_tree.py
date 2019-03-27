import plotly.offline as py
import plotly.graph_objs as go
import numpy as np

data = np.loadtxt("output.txt", delimiter="\n")

class Tree:
    def __init__(
        self,
        key,
        coords={0, 0}, 
        left=None, 
        right=None, 
        parent=None, 
        delta_x=100, 
        delta_y=10):

        self.__left = left
        self.__right = right
        self.__parent = parent
        self.__coords = coords
        self.__key = key
        self.delta_x = delta_x
        self.delta_y = delta_y
    
    def add_node(self, key):
        if self.__parent is not None:
            self.delta_x = self.__parent.delta_x / 2
        if key < self.__key:
            if self.__left is not None:
                self.__left.add_node(key)
            else:
                self.__left = Tree(parent=self,
                                   key=key,
                                   coords={
                                        "x":self.__coords["x"] - self.delta_x,
                                        "y":self.__coords["y"] - self.delta_y
                                    }
                                  )
        elif key > self.__key:
            if self.__right is not None:
                self.__right.add_node(key)
            else:
                self.__right = Tree(parent=self,
                                   key=key,
                                   coords={
                                        "x":self.__coords["x"] + self.delta_x,
                                        "y":self.__coords["y"] - self.delta_y
                                    }
                                  )
    
    def _get_data(self, dots, text):
        x = self.__coords["x"]
        y = self.__coords["y"]
        dots.append([x, y])
        text.append(str(self.__key))
        if self.__left is not None:
            self.__left._get_data(dots, text)
            if self.__right is not None:
                dots.append([x, y])
                text.append(str(self.__key))
                self.__right._get_data(dots, text)
        elif self.__right is not None:
            self.__right._get_data(dots, text)
        if self.__left is None and self.__right is None:
            dots.append([None, None])
            text.append(None)

    def plot(self):
        dots = []
        text = []
        self._get_data(dots, text)
        dots = [go.Scatter(
            x=np.array(dots)[:, 0],
            y=np.array(dots)[:, 1],
            mode="markers+lines",
            marker=dict(size=30),
            text=text,
            hoverinfo="text")]
        py.plot(dict(data=dots, layout=dict(hovermode="closest")),
            filename="tree.html")

if __name__=="__main__":
    data = np.loadtxt("input.txt", delimiter="\n")
    tree = Tree(coords={"x": 0, "y": 0}, key=data[0])
    for i in range(1, len(data)):
        tree.add_node(data[i])
    tree.plot()
