from src.token import Token

class Parser:
    def __init__(self, program: str) -> None:
        self.program = program
        self.tokens = []

        self._i = 0
        self._current = ''

        self.REGISTERS = {
            'r1': 0,
            'r2': 1,
            'r3': 2,
            'r4': 3,
            'r5': 4,
            'r6': 5,
            'r7': 6,
            'r8': 7,

            'acc': 8,
            'ip': 9
        }

        self.INSTRUCTIONS = {
            'mv': 'ins',
            'debug': 'ins'
        }

    def is_instruction(self, word: str) -> bool:
        for instruction in self.INSTRUCTIONS.keys():
            if word == instruction:
                return True

        return False

    def is_reg(self, word: str) -> bool:
        for register in self.REGISTERS.keys():
            if register == word:
                return True

        return False

    def tokenize(self) -> list[Token]:
        current = self.program[self._i]
        
        if current.isdigit():
            num = ''
            while current.isdigit():
                num += current
                self._i += 1
                current = self.program[self._i]
            self.tokens.append(Token('int', int(num)))

        elif current == ' ':
            pass

        elif current == ',':
            pass

        elif current == ';':
            while current != '\n' and self._i + 1 < len(self.program):
                self._i += 1
                current = self.program[self._i]

        elif current.isascii():
            word = ''
            while current != ' ' and current != '\n':
                word += current
                self._i += 1
                current = self.program[self._i]
                while current == ',':
                    self._i += 1
                    current = self.program[self._i]

            
            if self.is_instruction(word):
                self.tokens.append(Token(type='ins', value=0, name=word))
            elif self.is_reg(word):
                self.tokens.append(Token('reg', self.REGISTERS[word]))
            else:
                assert(f'Word: \'{word}\' isn\'t a valid word.')
                

        self._i += 1
        if self._i < len(self.program):
            self.tokenize()
  
        return self.tokens