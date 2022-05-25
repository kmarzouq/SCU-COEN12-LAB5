#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include "pqueue.h"
// defines Queue data structure Big O(1)
struct pqueue {
    int count;
    int length;
    void **data;
    int (*compare)();
};
// creates the Queue and allocates memory for it Big O(1)
PQ *createQueue(int (*compare)()){
    struct pqueue *pq;
    pq= malloc(sizeof(struct pqueue));
    assert(pq!=NULL);
    pq->count=0;
    pq->length=10;
    pq->data=malloc(sizeof(void*)*pq->length);
    assert(pq->data!=NULL);
    pq->compare = compare;
    return pq;
}
// destroys given Queue Big O(1)
void destroyQueue(PQ *pq){
    assert(pq!=NULL);
    free(pq->data);
    free(pq);
}
// returns number of entries Big O(1)
int numEntries(PQ *pq){
    assert(pq!=NULL);
    return pq->count;
}
// adds an entry into the queue Big O(log(n))
void addEntry(PQ *pq,void *entry){
    assert(pq!=NULL && entry!=NULL);
    pq->count++;
    void *z;
    if(pq->count>pq->length){
        pq->data=realloc(pq->data, sizeof(void*)*pq->length*2);
        pq->length =pq->length*2;
    }
    int i;
    i = pq->count-1;
    pq->data[pq->count-1]=entry;

    while(pq->count>1 && (*pq->compare)(pq->data[(i-1)/2], pq->data[i])>0){
        z=pq->data[(i-1)/2];
        pq->data[(i-1)/2] = pq->data[i];
        pq->data[i]=z;
        i=((i-1)/2);
    }
}
// removes an entry from Queue Big O(log(n))
void *removeEntry(PQ *pq){
    assert(pq!=NULL);
    int i;
    void *z;
    void *x;
    i= 0;
    pq->count--;
    z = pq->data[i];
    pq->data[i] = pq->data[pq->count];
    int smaller;
    while((2*i+1 < pq->count) ){
        smaller = 2*i+1;
        if(2*i+2 < pq->count){
    	    if ((*pq->compare)(pq->data[(2*i+2)], pq->data[2*i+1])<0){
        	    smaller = 2*i+2;
                    	}
        }

        
        if((*pq->compare)(pq->data[(smaller)], pq->data[i])<0){
            x=pq->data[smaller];
            pq->data[smaller] = pq->data[i];
            pq->data[i]=x;
            i=smaller;
        }
        else{
            break;
        }
        
    }
    return z;
}

