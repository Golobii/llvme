from src.token import Token
from src.types import Types

class InstructionError(Exception):
    pass

types = Types()

class Compiler:
    def __init__(self) -> None:
        pass

    @staticmethod
    def raise_mv_error(param: Token):
            raise SystemError(f'Err at mv instruction. Expecter register but got: \'{param.type}\'')


    def __compile_mov(self, param1: Token, param2: Token) -> None:
        if param1.type != types.reg:
            self.raise_mv_error(param1)

        if param2.type == types.int:
            self.buffer.append(0x1B)
            self.buffer.append(param2.value)
            self.buffer.append(param1.value)
            return            
        elif param2.type == types.reg:
            self.buffer.append(0x13)
            self.buffer.append(param1.value)
            self.buffer.append(0x12)
            self.buffer.append(param2.value)
            return

        
        self.raise_mv_error(param2)

    def __next(self) -> None:
        current = self.tokens[self._i]

        if current.type == 'ins':
            if current.name == 'mv':
                self.__compile_mov(self.tokens[self._i + 1], self.tokens[self._i + 2])
                self._i += 2
            elif current.name == 'debug':
                self.buffer.append(0xf0)
            else:
                raise InstructionError(f'Token \'{current.name} doesn\'t exist.')


        self._i += 1
        if self._i < len(self.tokens):
            self.__next()
        

    def compile_tokens(self, tokens: list[Token]) -> bytearray:
        self.buffer = bytearray()
        self.tokens = tokens
        self._i = 0

        self.__next()

        self.buffer.append(0xff)

        return self.buffer