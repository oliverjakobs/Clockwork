#include "common.h"

#include "chunk.h"
#include "debug.h"

int main(int argc, char** argv)
{
    Chunk chunk;
    chunk_init(&chunk);
    
    uint8_t constant = chunk_add_constant(&chunk, 1.2);
    chunk_write(&chunk, OP_CONSTANT, 123);
    chunk_write(&chunk, constant, 123);

    chunk_write(&chunk, OP_RETURN, 123);

    disassemble_chunk(&chunk, "test chunk");

    chunk_free(&chunk);

    return 0;
}