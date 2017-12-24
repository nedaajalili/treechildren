#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 51
typedef struct node{
    char *name;
    int numchildren;
    int depth;
    struct node **children;
}node_t;
node_t *loadF(char *,int *);
node_t *searchNode(node_t *root,char *name);
node_t *createNode(char *name);

int main(int argc,char *argv[])
{
    node_t *root;
    int size;

    if(argc!=2){
        printf("error in C.L args");
    }
    root=loadF(argv[1],&size);
    printf("%d",size);

    return 0;
}
node_t *loadF(char *fn,int *size){
    FILE *fp;
    node_t *root,*tmp;
    char name[MAX];
    int nch,i,cnt=0;
    root=NULL;
    fp=fopen(fn,"r");
    if(fp==NULL){
        printf("error!");
        exit(0);
    }
    while(fscanf(fp,"%s %d",name,&nch)!=EOF){
        if(root==NULL){
            tmp=root=createNode(name);
        }else{
            tmp=searchNode(root,name);
        }
        tmp->numchildren=nch;
        tmp->children=(node_t **)malloc(nch*sizeof(node_t *));
        if(tmp->children==NULL){
        printf("error allocation");
        exit(0);
    }
        for(i=0;i<nch;i++){
            fscanf(fp,"%s",name);
            tmp->children[i]=createNode(name);
        }
        cnt++;

    }
    fclose(fp);
    *size=cnt;
    return root;
}
node_t *createNode(char *name){
    node_t *tmp;
    tmp=(node_t *)malloc(1*sizeof(node_t));
    if(tmp==NULL){
        printf("error allocation");
        exit(0);
    }
    tmp->children=NULL;
    tmp->depth=-1;
    tmp->numchildren=0;
    tmp->name=strdup(name);
    //tmp->name=(char *)malloc((strlen(name)+1)*sizeof(char));
    return tmp;
}
node_t *searchNode(node_t *root,char *name){
  node_t *tmp=NULL;
  int i;
  while(root!=NULL){
    if(strcmp(name,root->name)==0){
        tmp=root;
    }else{
        for(i=0;i<(root->numchildren) && tmp==NULL;i++){
            tmp=searchNode(root->children[i],name);
        }
    }
  }
    return tmp;
}
