#include <iostream>
#include "Fruit.h"
using namespace std;

int main() {
	Fruit  f = Fruit();
	printf("Fruit vptr   address : %0x\n", &f);                 // eff718
	printf("Fruit vtbl   address : %0x\n", (*(double *)(&f)));  // 827b34
	printf("Fruit no     address : %0x\n", &(f.no));            // eff720
	printf("Fruit weight address : %0x\n", &(f.weight));        // eff728
	printf("Fruit key    address : %0x\n", &(f.key));           // eff730
	printf("Fruit sizeof         : %d\n", sizeof(f));           // 32

	Apple a = Apple();
	printf("Apple vptr   address : %0x\n", &a);                 // eff6e8
	printf("Apple vtbl   address : %0x\n", (*(double *)(&a)));  // 827b40
	printf("Apple no     address : %0x\n", &(a.no));            // eff6f0
	printf("Apple weight address : %0x\n", &(a.weight));        // eff6f8
	printf("Apple key    address : %0x\n", &(a.key));           // eff700
	printf("Apple size   address : %0x\n", &(a.size));          // eff704
	printf("Apple type   address : %0x\n", &(a.type));          // eff70c
	printf("Apple sizeof         : %d\n", sizeof(a));           // 40 

	getchar();
	return 0;
}
// 在64位系统中，内存布局需8字节对齐：
// 1.Fruit 类型大小为 32 字节,其中虚指针 vptr 占 8 字节，no 占 4+4 个字节（int 类型 4 字节，补齐 4 字节）,weight 占 8 字节，char 占 1+7 个字节（char 类型 1 字节，补齐 7 字节），共 32 字节。
// 2.Apple 类型大小为 40 字节,其中虚指针 vptr 占 8 字节，no 占 4+4 个字节（int 类型 4 字节，补齐 4 字节）,weight 占 8 字节，char + size 占 1+3+4 个字节（char类型1字节，补齐 3 字节，int 类型 4 字节），共 40 字节。