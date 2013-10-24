/************************************************************************************************
 * Author: Jonathan Lunt (jml6757@rit.edu)
 *
 * Description: This file contains a hash map which uses open addressing to handle collisions.
 *              The map copies references from heap allocated variables and copies any stack
 *              allocated variables to prevent invalid references. Every object used in the hash
 *              map must define its own hash() function in the HashMap class.
 ************************************************************************************************/

#include <stdlib.h>
#include <stdint.h>

//-----------------------------------------------------------------------------------------------
// Map Entry Class Declaration
//-----------------------------------------------------------------------------------------------

template<class K, class V>
struct _map_entry
{
	K* key;
	V* val;
	uint32_t hash;
	bool int_key;
	bool int_val;
	bool valid;
	_map_entry<K,V>* next;

	_map_entry(K* key, V* val, uint32_t hash, bool int_key, bool int_val);
	~_map_entry();
};
//-----------------------------------------------------------------------------------------------
// Map Entry Function Definitions
//-----------------------------------------------------------------------------------------------
template<class K, class V>
_map_entry<K,V>::_map_entry(K* key, V* val, uint32_t hash, bool int_key, bool int_val)
	: key(key), val(val), hash(hash), int_key(int_key), int_val(int_val), valid(true), next(0)
{

}

template<class K, class V>
_map_entry<K,V>::~_map_entry()
{
	if(int_key) free(key);
	if(int_val) free(val);
}

//-----------------------------------------------------------------------------------------------
// Hash Map Class Declaration
//-----------------------------------------------------------------------------------------------
template<class K, class V>
class HashMap
{
public:
	HashMap();
	HashMap(uint32_t size);
	~HashMap();

	void insert(K & key, V & val);
	void insert(K & key, const V & val);
	void insert(const K & key, V & val);
	void insert(const K & key, const V & val);

	V* get(K & key) const;
	void print_map();
	void print_elements();
	

private:

	
	void insert(K & key, V & val, bool int_key, bool int_val);
	uint32_t key_index(K & key, uint32_t & hash);

	void allocate();
	

	//Hashing functions
	uint32_t hash(uint32_t obj);
	uint32_t hash(char* obj);

private:
	uint32_t size;
	uint32_t count;
	_map_entry<K,V>** map;
	_map_entry<K,V>* first_entry;
	_map_entry<K,V>* last_entry;

	
};


//-----------------------------------------------------------------------------------------------
// Hash Map Constructors/Destructors Definitions
//-----------------------------------------------------------------------------------------------
template<class K, class V>
HashMap<K,V>::HashMap() : size(10), count(0)
{
	allocate();
}

template<class K, class V>
HashMap<K,V>::HashMap(uint32_t size) : size(size), count(0)
{
	allocate();
}

template<class K, class V>
HashMap<K,V>::~HashMap()
{

}

template<class K, class V>
void HashMap<K,V>::allocate()
{
	map = (_map_entry<K,V>**) calloc(size, sizeof(_map_entry<K,V>*));
	last_entry = first_entry = (_map_entry<K,V>*) calloc(1, sizeof(_map_entry<K,V>));
}

//-----------------------------------------------------------------------------------------------
// Hash Map Function Definitions
//-----------------------------------------------------------------------------------------------
template<class K, class V>
void HashMap<K,V>::insert(K & key, V & val)
{
	insert(key, val, false, false);
}

template<class K, class V>
void HashMap<K,V>::insert(K & key, const V & val)
{
	insert(key, *(new V(val)), false, true);
}

template<class K, class V>
void HashMap<K,V>::insert(const K & key, V & val)
{
	insert(*(new K(key)), val, true, false);
}
template<class K, class V>
void HashMap<K,V>::insert(const K & key, const V & val)
{
	insert(*(new K(key)), *(new V(val)), true, true);
}

template<class K, class V>
void HashMap<K,V>::insert(K & key, V & val, bool int_key, bool int_val)
{
	uint32_t key_hash = hash(key);
	uint32_t idx = key_index(key, key_hash);
 	
	//Insert new entry
	if(map[idx] == NULL)
	{
		last_entry = last_entry->next = map[idx] = new _map_entry<K,V>(&key, &val, key_hash, int_key, int_val);
		count++;
	}

	//Modify existing entry
}

template<class K, class V>
uint32_t HashMap<K,V>::key_index(K & key, uint32_t & hash)
{
 	uint32_t i = hash % size;
	return i;
	//TODO: DO OPEN ADDRESSING HERE
}

template<class K, class V>
V* HashMap<K,V>::get(K & key) const
{
	uint32_t key_hash = hash(key);
	uint32_t idx = key_index(key, key_hash);
	if((map[idx] != NULL) && map[idx].valid)
	{
		return *(map[idx].val)
	}

	return NULL;
}


template<class K, class V>
void HashMap<K,V>::print_map() 
{
	printf("\t IDX \t HASH \t KEY \t VAL\n");
	for(uint32_t i = 0; i <size; ++i)
	{
		K* key = map[i]?map[i]->key:0;
		V* val = map[i]?map[i]->val:0;
		uint32_t hash = map[i]?map[i]->hash:0;
		printf("\t %d \t %d \t %d \t %d\n", i, hash,key?*key:0,val?*val:0);

	}
}

template<class K, class V>
void HashMap<K,V>::print_elements() 
{
	printf("\t IDX \t HASH \t KEY \t VAL\n");
	_map_entry<K,V>* entry = first_entry->next;
	for(uint32_t i = 0; i <count; ++i)
	{
		if(entry == NULL) break;
		K* key = entry->key;
		V* val = entry->val;
		uint32_t hash_entry = entry->hash;
		printf("\t %d \t %d \t %d \t %d\n", i, hash_entry,*key,*val);
		entry = entry->next;
	}
}

//-----------------------------------------------------------------------------------------------
// Hashing Functions Definitions
//-----------------------------------------------------------------------------------------------
template<class K, class V>
uint32_t HashMap<K,V>::hash(uint32_t obj)
{
	if(obj == -1) return -2;
	return obj;
}

template<class K, class V>
uint32_t HashMap<K,V>::hash(char* obj)
{
	uint32_t hash = 0;
	uint32_t i;

	for (i = 0; obj[i]!='\0'; i++)
	{
		hash = 1000003*hash ^ obj[i];
	}
	hash ^ i;

	if(hash == -1) return -2;
	return hash;
}
