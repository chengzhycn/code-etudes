#ifndef __FILE_H_
#define __FILE_H_

#include "common.h"

#define DEFAULT_FILE "schedule.dat"

typedef struct file_ops file_ops_t;
typedef bool (*fops_pt) (FILE*, void*);
struct file_ops {
    fops_pt fops;
    void * data;
};

bool load_file(char *filename, file_ops_t *load_ops);
bool save_file(char *filename, file_ops_t *save_ops);

#endif /* __FILE_H_ */
