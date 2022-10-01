/**
 * Miguel Rodríguez Novoa
 * Oscar Olveira Miniño
 */

#include <stdio.h>
//#include "rational_pointer.h"
#include "rational_struct.h"

int main() {
    Rational r1, r2, r3, r4, s;
    r1 = createRational(2, 3);
    r2 = createRational(5, 7);
    r3 = createRational(7, 3);
    r4 = createRational(5, 4);
    s = sum(r1, r2);
    printf("A suma  e %d/%d\n", numerator(s), denominator(s));
    s = sum(r3, r4);
    printf("A suma e %d/%d\n", numerator(s), denominator(s));
}
