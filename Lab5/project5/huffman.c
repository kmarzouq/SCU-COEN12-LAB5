#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include "pqueue.h"
#include "pack.h"
//This funciton creates a node given data and assigns itself as the parent to left and right nodes big O(1)
struct node *mknode(int data, struct node *left, struct node *right){
    struct node *nn;
    nn = malloc(sizeof(struct node));
    nn->count = data;
    nn->parent = NULL;
    if(left!=NULL){
        left->parent=nn;
    }
    if(right!=NULL){
        right->parent=nn;
    }
    return nn;
}
// compares the values of 2 nodes Big O(1)
int cmp(struct node *t1,struct node *t2){
    return (t1->count < t2->count) ? -1 : (t1->count > t2->count);
}
// finds the depth of a leaf Big O(1)
static int depth(struct node *n){
    return n->parent == NULL ? 0:1+depth(n->parent);
}
//The main function which conducts Huffman Encoding. Big O(n)
int main(int argc ,char* argv[]){
    int counts[257]; 
    struct node *nodes[257]; 
    int x;
    
    for(x=0; x<257 ;x++){
        counts[x]=0;
        nodes[x]= NULL;
    }
    int c;
    FILE *fp = fopen(argv[1],"r");
    while((c=fgetc(fp))!=EOF){
        counts[c]++;
    } 
    fclose(fp);
    struct pqueue *priority;
    priority = createQueue(cmp);
    for(x=0;x<257;x++){
        if(counts[x]>0){
            nodes[x] = mknode(counts[x],NULL,NULL);
            addEntry(priority,nodes[x]);

            }
    }
    nodes[256]=mknode(0,NULL,NULL);
    addEntry(priority, nodes[256]);
    while(numEntries(priority) > 1){
        struct node *l;
        l  = removeEntry(priority);
        struct node *r;
        r = removeEntry(priority);
        struct node *n = mknode(l->count+r->count,l,r);
        addEntry(priority,n);
    }
    for(x=0;x<257;x++){
        if(nodes[x]!=NULL){
            if(!(isprint(x))){
                printf("%03o: %d x %d bits = %d \n", x, counts[x],depth(nodes[x]), counts[x]*depth(nodes[x]));
            }
            else{
                printf("%c : %d x %d bits = %d \n",x,counts[x],depth(nodes[x]), counts[x]*depth(nodes[x]));
            }
        }
    }
    pack (argv[1], argv[2], nodes);
    destroyQueue(priority);
    return;
}

