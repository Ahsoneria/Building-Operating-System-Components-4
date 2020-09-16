//Ayush Hitesh Soneria 
//170192

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<common.h>

/* XXX NOTE XXX  
       Do not declare any static/global variables. Answers deviating from this 
       requirement will not be graded.
*/
void init_rwlock(rwlock_t *lock)
{
   /*Your code for lock initialization*/
	atomic_add(&(lock->value),0x1000000000000);
}

void write_lock(rwlock_t *lock)
{
   /*Your code to acquire write lock*/
	while(atomic_add(&(lock->value),-0x1000000000000))
	{
		atomic_add(&(lock->value),0x1000000000000);
	}
}

void write_unlock(rwlock_t *lock)
{
   /*Your code to release the write lock*/
	while(atomic_add(&(lock->value),0x0000000000000));
	atomic_add(&(lock->value),0x1000000000000); //lock->value = 0x100000000000;
}


void read_lock(rwlock_t *lock)
{
   //Your code to acquire read lock
	while(atomic_add(&(lock->value),-1) < 0)
	{
		atomic_add(&(lock->value),1);
	}
}

void read_unlock(rwlock_t *lock)
{
   /*Your code to release the read lock*/
	//while(atomic_add(&(lock->value),0) == 0);
	atomic_add(&(lock->value),1);
}
