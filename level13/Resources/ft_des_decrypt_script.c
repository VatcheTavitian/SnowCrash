#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>      // for printf
#include <string.h>     // for strdup
#include <stdbool.h>    // for true

char * ft_des(char *param_1)
{
    char cVar1;
    char *pcVar2;
    unsigned int uVar3;
    char *pcVar4;
    unsigned int local_20;
    int local_1c;
    int local_18;
    int local_14;

    pcVar2 = strdup(param_1);  // copy the string to modify it
    local_1c = 0;
    local_20 = 0;

    while (true) {
        uVar3 = 0xffffffff;
        pcVar4 = pcVar2;

        do {
            if (uVar3 == 0) break;
            uVar3 = uVar3 - 1;
            cVar1 = *pcVar4;
            pcVar4++;
        } while (cVar1 != '\0');

        if (~uVar3 - 1 <= local_20) {
            return pcVar2;
        }

        if (local_1c == 6) {
            local_1c = 0;
        }

        int shift = "0123456"[local_1c] - '0';

        if ((local_20 & 1) == 0) {
            for (local_14 = 0; local_14 < shift; local_14++) {
                pcVar2[local_20]--;
                if (pcVar2[local_20] == 0x1f) {
                    pcVar2[local_20] = '~';
                }
            }
        } else {
            for (local_18 = 0; local_18 < shift; local_18++) {
                pcVar2[local_20]++;
                if (pcVar2[local_20] == 0x7f) {
                    pcVar2[local_20] = ' ';
                }
            }
        }

        local_20++;
        local_1c++;
    }
}

int main() {
    char *token = ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I");
    printf("Your token is: %s\n", token);
    free(token);
    return 0;
}

