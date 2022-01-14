from src.token import Token

def compile_tokens(tokens: list[Token]) -> bytearray:
    buffer = bytearray()

    i = 0
    current = tokens[i]

    buffer.append(0x1B)
    buffer.append(0x01)
    buffer.append(0x00)
    buffer.append(0xf0)

    buffer.append(0xff)

    return buffer