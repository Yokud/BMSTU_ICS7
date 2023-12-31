#include "buffer.h"


int write_buffer(cbuffer_t *const buf, const char element)
{
    if (buf == NULL) 
        return BUF_ERR;

    buf->buffer[buf->write_pos++] = element;
    buf->write_pos %= N;

    return OK;
}


int read_buffer(cbuffer_t *buf, char *const element)
{
    if (buf == NULL)
        return BUF_ERR;

    if (element == NULL)
        return ELEM_ERR;

    *element = buf->buffer[buf->read_pos++];
    buf->read_pos %= N;

    return OK;
}