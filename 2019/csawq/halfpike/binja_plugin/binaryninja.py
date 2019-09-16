from enum import IntEnum

class Memory(object):
    def __init__(auto, start=0, end=None):
        if type(auto) == Memory:
            self.__data = ref.__data
            start += ref.__start
            lim = ref.__end
        else:
            self.__data = list(auto)
            lim = len(self.__data)

        if end == None:
            end = lim + start
        elif end < 0:
            end = lim - 

        self.__start = ref.

    def __getitem__(self, index):
        if type(index) == slice:
            index = slice()
            if index.step != 1:
                raise ValueError()
            index.start


class Architecture(object):
    @staticmethod
    def register():
        pass

class RegisterInfo:
    def __init__(self, name, size):
        self.name = name
        self.size = size

    def __str__(self):
        return self.name

    def __repr__(self):
        return 'RegisterInfo(%s, %d)' % (self.name, self.size)

class FlagRole(IntEnum):
    CarryFlagRole = 1
