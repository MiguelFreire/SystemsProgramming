#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#define INBOUND_FIFO "INBOUND_FIFO"
#define OUTBOUND_FIFO "OUTBOUND_FIFO"
#define NUM_REGIONS 10
#define MESSAGE_MAX_SIZE 100

#define COPY 0
#define PASTE 1

#include <sys/types.h>

typedef struct Message {
    int region;
    char data[MESSAGE_MAX_SIZE];
    int size;
    int type;
} Message;


Message new_message(int region, char *data, int type);
Message new_copy_message(int region, char *data);
Message new_paste_message(int region);
int clipboard_connect(char * clipboard_dir);
int clipboard_copy(int clipboard_id, int region, void *buf, size_t count);
int clipboard_paste(int clipboard_id, int region, void *buf, size_t count);

#endif