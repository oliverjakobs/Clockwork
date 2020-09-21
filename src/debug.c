#include "debug.h"

#include <stdio.h>

void disassemble_chunk(Chunk* chunk, const char* name)
{
    printf("== %s ==\n", name);

    for (size_t offset = 0; offset < chunk->count;)
        offset = disassemble_instruction(chunk, offset);
}

static size_t disassemble_simple(const char* name, size_t offset)
{
    printf("%s\n", name);
    return offset + 1;
}

static size_t disassemble_constant(const char* name, Chunk* chunk, size_t offset)
{
    uint8_t constant = chunk->code[offset + 1];
    
    printf("%-16s %4d '", name, constant);
    print_value(chunk->constants.values[constant]);
    printf("'\n");

    return offset + 2;
}

size_t disassemble_instruction(Chunk* chunk, size_t offset)
{
    printf("%04d ", offset);
    
    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1])
        printf("   | ");
    else
        printf("%4d ", chunk->lines[offset]);

    uint8_t instruction = chunk->code[offset];

    switch (instruction)
    {
    case OP_CONSTANT: return disassemble_constant("OP_CONSTANT", chunk, offset);
    case OP_RETURN: return disassemble_simple("OP_RETURN", offset);
    default:
        printf("Unkown opcode %d\n", instruction);
        return offset + 1;
    }
}