import sys

from src.parser import Parser
from src.compiler import compile_tokens

def main() -> None:
    with open(sys.argv[1], 'r') as f:
        program = f.read()
    
    parser = Parser(program)

    tokens = parser.tokenize()
    for token in tokens:
        print(f'({token.type}|{token.value}|{token.name})', end=' ') 
    print()

    buffer = compile_tokens(tokens)

    with open(sys.argv[2], 'wb') as f:
        f.write(bytes(buffer))


if __name__ == '__main__':
    main()