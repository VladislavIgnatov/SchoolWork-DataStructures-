#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include "MemoryManager.h"

using namespace std;


ostream & operator<<(ostream & out, const MemoryManager &M)
{
	blocknode *tmp = M.firstBlock;
	assert(tmp);
	while (tmp)
	{
		
		out << "[" << tmp->bsize << ",";

		if (tmp->free)
			out << "free] ";
		else
			out << "allocated] ";
		if (tmp->next)
			out << " -> ";
		tmp = tmp->next;
	}
	return out;
}

MemoryManager::MemoryManager(unsigned int memtotal) : memsize(memtotal)
{
	baseptr = new unsigned char[memsize];
	firstBlock = new blocknode(memsize, baseptr);
}

blocknode *MemoryManager::getFirstPtr()
{
	return firstBlock;
}

unsigned char * MemoryManager::malloc(unsigned int request)
// Finds the first block in the list whose size is >= request
// If the block's size is strictly greater than request
// the block is split, with the newly create block being free. 
// It then changes the original block's free status to false
{
	blocknode *tmp = firstBlock;

	if (tmp == 0){
		cout << endl << "Error: not list detected" << endl;
	}

	while (tmp)
	{
		if ((tmp->bsize >= request) && (tmp->free == true))
		{
			
			splitBlock(tmp,request);
			return tmp->bptr;
		}

		tmp = tmp->next;
	}
	return NULL;
}

void MemoryManager::splitBlock(blocknode *p, unsigned int chunksize)
// Utility function. Inserts a block after that represented by p
// changing p's blocksize to chunksize; the new successor node 
// will have blocksize the original blocksize of p minus chunksize and 
// will represent a free block.  
// Preconditions: p represents a free block with block size > chunksize
// and the modified target of p will still be free.
{
	if (p->free == false || p->bsize < chunksize){
		cout << endl << "Error : (p->free == false || p->bsize <= chunksize) is true" << endl;
		return;
	}

	blocknode * newnode = new blocknode(p->bsize, p->bptr + chunksize);

	if (p->next != 0)
	{
		newnode->next = p->next;
		newnode->next->prev = newnode;
	}

	p->free = false; 
	if (p->bsize == chunksize){
		return;
	}
	newnode->bsize = p->bsize - chunksize;
	newnode->prev = p; // prev
	p->bsize = chunksize; 
	p->next = newnode; // next
}

void MemoryManager::free(unsigned char *blockptr)
// makes the block represented by the blocknode free
// and merges with successor, if it is free; also 
// merges with the predecessor, it it is free
{
	blocknode *tmp = getFirstPtr();
	
	while (tmp)
	{
		if (tmp->bptr == blockptr)
		{
			tmp->free = true;
			
			mergeForward(tmp);
		}
		tmp = tmp->next;
	}
	return;
}

void MemoryManager::mergeForward(blocknode *p)
// merges two consecutive free blocks
// using a pointer to the first blocknode;
// following blocknode is deleted
{
	blocknode *old;

	//check if node is false cant merge false nodes
	if (p->free == false) 
		return;

	if (p->prev != 0)
	{
		if ((p->free == true) && (p->prev->free == true))
		{
			p = p->prev;
			p->bsize += p->next->bsize;
			old = p->next;
			p->next = p->next->next;
			if (p->next != 0)
			{
				p->next->prev = p;
				
			}
			
		}
	}
	
	if (p->next != 0){
		if ((p->free == true) && (p->next->free == true))
		{
			p->bsize += p->next->bsize;
			old = p->next;
			p->next = p->next->next;
		}
		
	}
	
	
	return;
}
