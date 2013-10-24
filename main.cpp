#include <stdio.h>
#include "hash_map.hpp"
#include <stdint.h>

int main () 
{
	HashMap<uint32_t, uint32_t> hash_map(14);
	uint32_t x = 2;
	hash_map.insert(1, 1);
	hash_map.insert(2, 2323);
	hash_map.insert(3, 2);
	hash_map.insert(19, 1);
	printf("-----------------------------------------------------------------\n");
	printf("Map Layout\n");
	printf("-----------------------------------------------------------------\n");
	hash_map.print_map();
	printf("-----------------------------------------------------------------\n");
	printf("Elements\n");
	printf("-----------------------------------------------------------------\n");
	hash_map.print_elements();
	printf("%d\n", hash_map.get(x));
}