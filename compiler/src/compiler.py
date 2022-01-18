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


    def __compile_mv(self, param1: Token, param2: Token) -> None:
        if param1.type != types.reg:
            self.raise_mv_error(param1)

        if param2.type == types.int:
            self.buffer.append(0x1b)
            self.buffer.append(param2.value)
            self.buffer.append(param1.value)
            return            
        elif param2.type == types.reg:
            self.buffer.append(0x13)
            self.buffer.append(param1.value)
            self.buffer.append(0x12)
            self.buffer.append(param2.value)
            return
        elif param2.type == types.cma:
            self.buffer.append(0x01b)
            self.buffer.append(self._i + 1)
            self.buffer.append(param1.value)
            return

        
        self.raise_mv_error(param2)

    # Used in the compilation of all the jump instructions. Default inst. value is regular jmp.
    def __compile_jmp(self, location: Token, instruction = 0x14) -> None:
        if location.type == types.instruction:
            raise SyntaxError('Jump location can\'t be a register.')


        if location.type == types.int:
            self.buffer.append(instruction)
            self.buffer.append(location.value)
            return
        elif location.type == types.label:
            self.buffer.append(instruction)
            addr = self.labels[location.name]
            self.buffer.append(addr)
            return
        elif location.type == types.reg:
            self.buffer.append(0x1A)
            self.buffer.append(location.value)
            self.buffer.append(self._i + 4)
            self.buffer.append(instruction)
            return
        
        raise SyntaxError('Bruh')


    def __compile_cmp(self, val1: Token, val2: Token) -> None:
        # TODO: Check types

        self.buffer.append(0x1c)
        self.buffer.append(val1.value)
        self.buffer.append(val2.value)

    @staticmethod
    def raise_add_error(token: Token) -> None:
            raise SyntaxError('Err at add ins. Expected reg, got ' +
            f'\'{token.type}\'')

    def get_token(self, i: int = -1) -> Token:
        if i >= 0:
            return self.tokens[i]

        self._i += 1
        return self.tokens[self._i]

    # TODO
    def __compile_add(self) -> None:
        i = 1
        if self.tokens[self._i + 1].type != types.reg:
            self.raise_add_error(self.tokens[self._i + 1])


    def __next(self) -> None:
        current = self.tokens[self._i]

        if current.type == types.instruction:
            if current.name == 'mv':
                self.__compile_mv(self.get_token(), self.get_token())
            elif current.name == 'debug':
                self.buffer.append(0xf0)
            elif current.name == 'jmp':
                self.__compile_jmp(self.get_token())
            elif current.name == 'inca':
                self.buffer.append(0x17)
            elif current.name == 'jne':
                self.__compile_jmp(self.get_token(), instruction=0x1d)
            elif current.name == 'cmp':
                self.__compile_cmp(self.get_token(), self.get_token())
            elif current.name == 'incr':
                self.buffer.append(0x1f)
                self.buffer.append(self.get_token().value)
            elif current.name == 'add':
                self.__compile_add()
            else:
                raise InstructionError(f'Token \'{current.name} doesn\'t exist.')

        elif current.type == types.label:
            self.labels[current.name] = self._i


        self._i += 1
        if self._i < len(self.tokens):
            self.__next()
        

    def compile_tokens(self, tokens: list[Token]) -> bytearray:
        self.buffer = bytearray()
        self.tokens = tokens
        self._i = 0
        self.labels = {}

        self.__next()

        if self.buffer[-1] != 0xff:
            self.buffer.append(0xff)

        return self.buffer