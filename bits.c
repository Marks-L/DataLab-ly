/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y); // 各自取反 或运算 整体取反
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y); // a ^ b = (a | b) & ~(a & b) = ~(~a & ~b) & ~(a & b)
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    // 先判断是否为0 0 -> 1 非0 -> 1
    int xz = !x;
    int yz = !y;

    // 如果都为0 返回1（2个0）
    if(xz && yz) return 1;

    // 如果不同时为0 返回0（1个0，1个非0）
    else if(xz ^ yz) return 0;

    // 都不为0 判断符号位是否相同 如果不同（异或）输出0（2个非0）
    else if((x >> 31) ^ (y >> 31)) return 0;

    // 否则输出1（以上已穷举所有可能组合）
    else return 1;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    // int类型共32位，最大值为2^31-1，此处用二分法不断缩小原数大小并将最高位不断右移直至为0

    // 先判断是否大于 2^16-1 若大于 右移16位 将高位区16位数移至低位区
    int b16 = v > 0xFFFF;
    v = v >> (b16 << 4);

    // 再判断是否大于 2^8-1 若大于 右移8位 将高位区8位数移至低位区
    int b8 = v > 0xFF;
    v = v >> (b8 << 3);

    // 再判断是否大于 2^4-1 若大于 右移4位 将高位区4位数移至低位区
    int b4 = v > 0xF;
    v = v >> (b4 << 2);

    // 再判断是否大于 2^2-1 若大于 右移2位 将高位区2位数移至低位区
    int b2 = v > 0x3;
    v = v >> (b2 << 1);

    // 再判断是否大于 1
    int b1 = v > 0x1;


    return (b16 << 4) | (b8 << 3) | (b4 << 2) | (b2 << 1) | b1;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    // 16进制数，2个字符（8位）为1个字节 取第n个和第m个字节对应的位置
    int nx = n << 3;
    int mx = m << 3;

    // 取出字节并清零其他位
    int nbyte = (x >> nx) & 0xFF;
    int mbyte = (x >> mx) & 0xFF;

    // 用1给两个字节所在位置占位
    int mask = (0xFF << nx) | (0xFF << mx);

    // 先清零原数中对应字节的值 再合并
    return (x & ~mask) | (nbyte << mx) | (mbyte << nx);

}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    v = ((v >> 1) & 0x55555555) | ((v << 1) & 0xAAAAAAAA); // 交换相邻两位
    v = ((v >> 2) & 0x33333333) | ((v << 2) & 0xCCCCCCCC); // 交换相邻四位
    v = ((v >> 4) & 0x0F0F0F0F) | ((v << 4) & 0xF0F0F0F0); // 交换相邻八位
    v = (v >> 24) | ((v & 0x00FF0000) >> 8) | (v & 0x0000FF00) << 8 | (v << 24); // 交换字节顺序
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    // 负数算术右移会在前面置 1，要消除这部分影响 用 mask 将该部分强制置零
    int mask = ((1 << 31) >> n) << 1; // 将掩码最左侧的n位置1
    return (x >> n) & ~mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    /* 整体思路 利用二分，将 x 的部分最高位依次挪到最低位 和全1做与运算 随即和全1做异或运算再做非运算
    * 结果为1 则全1 x左移对应位数 结果为0 x不变
    */
    int b16 = !(((x >> 16) & 0xFFFF) ^ 0xFFFF);
    x = x << (b16 << 4);

    int b8 = !(((x >> 24) & 0xFF) ^ 0xFF);
    x = x << (b8 << 3);

    int b4 = !(((x >> 28) & 0xF) ^ 0xF);
    x = x << (b4 << 2);

    int b2 = !(((x >> 30) & 0x3) ^ 0x3);
    x = x << (b2 << 1);

    int b1 = !(((x >> 31) & 0x1) ^ 0x1);

    int b0 = b1 & ((x >> 30) & 1);

    return (b16 << 4) + (b8 << 3) + (b4 << 2) + (b2 << 1) + b1 + b0;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    // 整数的浮点型表示转换
    unsigned ux = x; // 转化为无符号数
    unsigned sign = ux & 0x80000000; // 取符号位
    int exp = 158; // 127 + 31 = 158 指数位最多左移31位

    if(!ux) return 0; // ux 为 0 直接返回 0
    if(sign) ux = -ux; // 负数取反（绝对值）
    
    // 将 ux 左移，直到最高位为 1
    while(!(ux & 0x80000000)) {
        ux = ux << 1;
        exp -= 1;
    }

    // 提取尾数部分
    unsigned frac = (ux >> 8) & 0x7FFFFF;
    unsigned rest = ux & 0xFF;

    if(rest > 128)
        frac += 1;
    else if(rest == 128) {
        if(frac & 1)
            frac += 1;
    }

    if(frac >> 23) {
        frac = 0;
        exp += 1;
    }
    return sign | (exp << 23) | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    // 浮点数乘二 需考虑特殊情况： NaN, 0
    unsigned sign = uf & 0x80000000;    // 取符号位
    unsigned exp = uf & 0x7F800000;     // 取指数位
    unsigned frac = uf & 0x007FFFFF;    // 取尾数位

    if(exp == 0x7F800000) return uf;    // 指数全1，表示 NaN 或无穷大，直接返回原数

    else if(exp == 0) return sign | (frac << 1); // 指数为0，表示非规格化数，尾数左移1位

    else if(exp == 0x7F000000) return sign | 0x7F800000; // 指数为 254，处理成无穷大

    else return sign | (exp + 0x00800000) | frac;} // 指数加1，尾数不变

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = (uf2 >> 31) & 1;        // 取符号位
    unsigned exp = (uf2 >> 20) & 0x7FF;     // 取指数位
    unsigned frac1 = uf2 & 0xFFFFF;         // 取尾数的高20位
    unsigned value;

    // 指数为 0 返回 0
    if(!exp) 
        return 0;
    // 指数全 1 返回 0x80000000
    if(exp >= 0x7FF) 
        return 0x80000000;

    // 补充隐藏 1
    frac1 = frac1 | (1 << 20);

    // 计算实际指数
    int E = exp - 1023;
    // 指数小于 0，舍去，返回 0
    if(E < 0) 
        return 0;
    // 指数大于 30 溢出，返回 0x80000000
    else if(E > 30)  
        return 0x80000000;
    
    /*
    * M = [1 frac1][uf1]
    * M = 1.frac * 2^52 
    * 输出 value = 1.frac * 2^E = 1.frac * 2^(E - 52) = 1.frac / 2^(52 - E)
    * frac1 有20+1位，uf1 有32位
    * E <= 20 时，52 - E >= 32，直接右移 52 - E 位即可，舍去uf1的32位，即右移 20 - E 位
    * E > 20 时，52 - E < 32，先将 frac1 左移 E - 20 位，再将 uf1 右移 52 - E 位，最后将两者按位或
    */
    else if(E <= 20) 
        value = frac1 >> (20 - E);
    else
        value = (frac1 << (E - 20)) | (uf1 >> (52 - E));

    if(sign)
        return -value;
    
    return value;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x < -149)
        return 0;
    else if(x < -126)
        return 1 << (x + 149); // 非规格化数，指数为 0，直接移位
    else if(x <= 127)
        return (x + 127) << 23; // [-126,127]内，直接挪动指数位
    else
        return 0x7F800000; // INF

}
