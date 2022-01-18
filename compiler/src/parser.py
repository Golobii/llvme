from src.token import Token
from src.types import Types

class Parser:
    def __init__(self, program: str) -> None:
        self.program = program
        self.tokens = []

        self._i = 0
        self._current = ''

        self.types = Types()

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

        self.INSTRUCTIONS = ['mv', 'debug', 'jmp', 'inca', 'jne', 'cmp', 'incr', 'add'] 

    def is_instruction(self, word: str) -> bool:
        for instruction in self.INSTRUCTIONS:
            if word == instruction:
                return True

        return False

    def is_reg(self, word: str) -> bool:
        for register in self.REGISTERS.keys():
            if register == word:
                return True

        return False

    def __over_program_len(self, i: int = -1) -> bool:
        if i == -1:
            num = self._i
        else:
            num = i

        if num + 1 < len(self.program):
            return False

        return True

    def tokenize(self) -> list[Token]:
        current = self.program[self._i]
        
        if current.isdigit():
            isHex = False
            num = ''
            while (current.isdigit() or current == 'x') and not self.__over_program_len():
                num += current
                self._i += 1
                current = self.program[self._i]
                if current == 'x':
                    if isHex:
                        raise SyntaxError(f'Invalid number {num}.')

                    isHex = True

            if isHex:
                num = int(num, base=16)
            else:
                num = int(num)

            self.tokens.append(Token(type=self.types.int, value=num))

        elif current == ' ':
            pass

        elif current == ',':
            pass

        elif current == '\n':
            pass

        elif current == '$':
            self.tokens.append(Token(self.types.cma, 0))

        elif current == ';':
            while current != '\n' and not self.__over_program_len():
                self._i += 1
                current = self.program[self._i]

        elif current.isascii():
            word = ''
            word += current
            while not self.__over_program_len():
                self._i += 1
                current = self.program[self._i]
                if current == ' ' or current == '\n':
                    break
                elif current == ',':
                    continue
                word += current
            
            if self.is_instruction(word):
                self.tokens.append(Token(type=self.types.instruction, value=0, name=word))
            elif self.is_reg(word):
                self.tokens.append(Token(self.types.reg, self.REGISTERS[word]))
            elif word[-1] == ':':
                self.tokens.append(Token(type=self.types.label, value=0, name=word))
            else:
                raise SyntaxError(f'Word: \'{word}\' isn\'t a valid word.')
                

        self._i += 1
        if self._i < len(self.program):
            self.tokenize()
  
        return self.tokens