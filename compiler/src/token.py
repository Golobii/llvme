class Token:
    def __init__(self, type: str, value: int, name: str = '') -> None:
        self.type = type
        self.value = value
        self.name = name