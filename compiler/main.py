import sys

from src.parser import Parser
from src.compiler import Compiler

DEBUG: bool = False

def main() -> None:
    with open(sys.argv[1], 'r') as f:
        program = f.read()
    
    parser = Parser(program)
    compiler = Compiler()

    tokens = parser.tokenize()

    if DEBUG:
        for token in tokens:
            print(f'({token.type}|{token.value}|{token.name})', end=' ') 
        print()

    buffer = compiler.compile_tokens(tokens)

    with open(sys.argv[2], 'wb') as f:
        f.write(bytes(buffer))


if __name__ == '__main__':
    main()