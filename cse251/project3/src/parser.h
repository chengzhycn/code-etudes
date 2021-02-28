#ifndef __PARSER_H_
#define __PARSER_H_

#define __USE_XOPEN
#include <time.h>

#include "common.h"

bool event_date_parser(const char *in, struct tm *date);
bool event_time_parser(const char *in, struct tm *date);
bool event_datetime_parser(const char *in, struct tm *date);
bool event_name_parser(const char *in, char *name, unsigned int len);
bool event_num_parser(const char *in, int *num);

#endif /* __PARSER_H_ */
