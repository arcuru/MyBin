#include "C_Euler.h"

int64 Euler_17()
{
    int count=1;
    int letters=0;
    while ( count <= 1000 ) {
        int single=count%10;
        int tens=(count/10)%10;
        int hundreds=(count/100)%10;
        if ( tens != 1 ) {
            if ( (single == 1) || (single == 2) || (single == 6) ) {
                letters=letters+3;
            } else if ( (single == 4) || (single == 5) || (single == 9) ) {
                letters=letters+4;
            } else if ( single !=0 ) {
                letters=letters+5;
            }
        } else if ( single == 0 ) {
            letters=letters+3;
        } else if ( single <= 2 ) {
            letters=letters+6;
        } else if ( ( single <= 4 ) || ( single >= 8 ) ) {
            letters=letters+8;
        } else if ( single == 7 ) {
            letters=letters+9;
        } else {
            letters=letters+7;
        }

        if ( ( tens == 2 ) || ( tens == 3 ) || ( tens >= 8 ) ) {
            letters=letters+6;
        } else if ( ( tens >= 4 ) && ( tens <= 6 ) ) {
            letters=letters+5;
        } else if ( tens == 7 ) {
            letters=letters+7;
        }

        if ( ( hundreds >= 1 ) && ( (tens+single) > 0 ) ) {
            letters=letters+10;
        } else if ( hundreds >= 1 ) {
            letters=letters+7;
        }

        if ( ( hundreds == 1 ) || ( hundreds == 2 ) || ( hundreds == 6 ) ) {
            letters=letters+3;
        } else if ( ( hundreds == 4 ) || ( hundreds == 5 ) || ( hundreds == 9 ) ) {
            letters=letters+4;
        } else if ( hundreds !=0 ) {
            letters=letters+5;
        }
        if ( ( single + tens + hundreds ) == 0 ) {
            letters=letters+11;
        }
        count++;
    }
    return (int64)letters;
}
