/* 
 * File:   parse_int.h
 * Author: lejla
 *
 * Created on 01 September 2021, 12:45
 */

#ifndef PARSE_INT_H
#define	PARSE_INT_H

#include <stdint.h>
#include "buffer.h"

int8_t getStartIndex(const struct buffer * const buffer);
int8_t getEndIndex(const struct buffer * const buffer, const int8_t start_index);
int8_t isNegative(struct buffer * const buffer, const int8_t start_index);
int32_t parse_int(struct buffer * const buffer, int8_t start, const int8_t end, const int8_t negative);

#endif	/* PARSE_INT_H */

