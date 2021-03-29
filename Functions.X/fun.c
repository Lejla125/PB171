/* 
 * File:   fun.c
 * Author: lejla
 *
 * Created on 27 March 2021, 15:51
 */

#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    printf("%d\n", bitValue(5));
    uint8_t a = 14;
    bitWrite(&a, 0, 1);
    printf("%d\n",a);
    printf("%d", bitRead(8,3));
    
    
    return (EXIT_SUCCESS);
}

