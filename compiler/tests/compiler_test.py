import pytest
import sys
from os import listdir
from pathlib import Path
HERE = Path(__file__).parent
sys.path.append(str(HERE / '../'))

from  src.parser import Parser
from  src.compiler import Compiler

TESTS_LOC = 'tests/tests/'
BIN_LOC = 'tests/bin/'

def compile(filename: str) -> bytearray:
    with open(filename, 'r') as f:
        program = f.read()
    
    parser = Parser(program)
    compiler = Compiler()

    tokens = parser.tokenize()

    return compiler.compile_tokens(tokens)


@pytest.mark.parametrize('source', listdir(TESTS_LOC))
def test_compilation(source):
    buffer = compile(TESTS_LOC + source)
    assert len(buffer) > 1