/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: hzhashmi
 *
 * Created on February 6, 2024, 2:50 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h> 
#include <unistd.h> 


/*
 * 
 */
int main(int argc, char** argv) {
    char *parent_command, *child_command;
    parent_command=(char *)malloc(100*sizeof(char));
    child_command=(char *)malloc(100*sizeof(char));
    printf("Your Command>");
    fgets(parent_command,100,stdin);
    child_command=strchr(parent_command,'|')+1; 
    if(child_command-1==NULL){ 
        fprintf(stderr,"No Pipe Found");
        exit(1);
    }
    for(;child_command[0]==' ';child_command=child_command+1); 
    for(char *temp=strchr(parent_command,'|')-1;temp[0]==' ';temp[0]='\0',temp--); 

    int pd[2]; 

    if(pipe(pd)<0){ 
        fprintf(stderr,"Error in creating pipe");
        exit(1);
    }

    if(fork()==0){
        dup2(pd[0],0); 
        close(pd[1]);
        system(child_command);
        exit(0);
    }else{
        dup2(pd[1],1); 
        close(pd[0]);
        system(parent_command);
    }
    return(0);
}