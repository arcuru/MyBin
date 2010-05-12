// read_trace.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
//#include "Windows.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned int address;
    unsigned int instr;
    int type;
} memref_struct;

typedef struct
{
    int LRU;// 0 is invalid, 1 is most recent, set_size is oldest
    int address;
} cache_struct;

// Macros to ease reading
#define INSTRUCTION_FETCH 2
#define STORE_INSTRUCTION 1
#define LOAD_INSTRUCTION 0
#define CACHE_HIT 1

static void part1(memref_struct* memref_list,int memref_count);
static void part2(memref_struct* memref_list,int memref_count);
static void part3(memref_struct* memref_list,int memref_count);

int main()
{
    FILE *fp;
    int i;
    int memref_count = 1000000;
    memref_struct* memref_list = (memref_struct*) malloc(memref_count*sizeof(memref_struct));

    // open trace file for reading

    fp = fopen("gcc_trace2.txt", "r");
    if (fp == NULL) printf("data file open error");

    // read first 100 lines of trace file;
    // address holds virtual address in unsigned int format;
    // N.B. - your program must read all 1,000,000 lines but
    //        you might want to test it on the first 100 lines
    //        or so before running it on the entire trace file!

    for (i=0; i<memref_count; ++i)
    {

        // read 1 line of trace file
        // populate array with information contained in trace file

        fscanf(fp, "%d %x %x", &memref_list[i].type, &memref_list[i].address, &memref_list[i].instr);
    }
    fclose(fp);

    part1(memref_list,memref_count);
    printf("\n\n");
    part2(memref_list,memref_count);
    printf("\n\n");
    part3(memref_list,memref_count);

// Delay a bit to see output
//    sleep(5000);

    return 0;
}

static void part1(memref_struct* memref_list,int memref_count)
{
    // Part 1
    // relative percentages of ...
    int regformat_count=0;// register format( 3 register operands )
    int condbranch_count=0;// conditional branch instructions
    int load_count=0;// load instructions
    int store_count=0;// store instructions
    int instr_count=0;
    int i;

    // Loop through information to count occurrences
    for (i=0; i<memref_count; ++i)
    {
        // Ignore if it is not an instruction fetch
        if (memref_list[i].type!=INSTRUCTION_FETCH)
            continue;

        ++instr_count;
        int opcode = (memref_list[i].instr & 0xfc000000) >> 26;



        if (opcode==0)// R-type instruction
        {
            int funccode = (memref_list[i].instr & 0x3f);
            // Only count R-Types that have 3 operands
            if (funccode>>5==1 || funccode==4 || funccode==6 || funccode==7)
                ++regformat_count;
        }
        // I-type instructions
        else if (opcode==1 || (opcode>=4 && opcode<=7))// branching instruction
            ++condbranch_count;
        else if (opcode==43 || opcode==40)// store instructions
            ++store_count;
        else if (opcode==35 || opcode==32 || opcode==15)// load instructions
            ++load_count;
//        else if (opcode>>1==1)// j-type instruction
//        else if (opcode>>2==4)// Coprocessor instructions

        // Ignores J-Type, Coprocessor, and R- and I-Type that aren't branching/load/store or use 3 registers
        // i.e. Ignores immediate instructions (addi, andi, sll)
    }

    printf("\tPart 1\n");
    printf("Register Format Instructions: %2.1f%%\n",100*(double)regformat_count/instr_count);
    printf("Conditional Branch Instructions: %2.1f%%\n",100*(double)condbranch_count/instr_count);
    printf("Load Instructions: %2.1f%%\n",100*(double)load_count/instr_count);
    printf("Store Instructions: %2.1f%%\n",100*(double)store_count/instr_count);
}

static void part2(memref_struct* memref_list,int memref_count)
{
// Part 2
    // Init file for output to graphing program
    FILE* fp;
    fp = fopen("Part2.txt","w");
    fprintf(fp,"\tPart 2\n");
    fprintf(fp,"I_Cache\tD_Cache\tCache Size");
    fprintf(stdout,"\t Part 2\n");
    fprintf(stdout,"I_Cache\tD_Cache\tCache Size");
    int cache_size,i;
    for (cache_size=512; cache_size<=(1024*1024); cache_size*=2)
    {
        // Initialize both caches with all 0's
        int* I_cache = (int*) calloc(sizeof(int),cache_size);
        int* D_cache = (int*) calloc(sizeof(int),cache_size);
        int I_cache_hit=0,D_cache_hit=0;
        int I_cache_miss=0,D_cache_miss=0;
        for (i=0; i<memref_count; ++i)
        {
            if (memref_list[i].type==INSTRUCTION_FETCH)
            {
                // Count miss or hit for I_cache
                if (I_cache[(memref_list[i].address>>2)%cache_size]==memref_list[i].address)
                    ++I_cache_hit;
                else
                {
                    I_cache[(memref_list[i].address>>2)%cache_size] = memref_list[i].address;
                    ++I_cache_miss;
                }
            }
            else if (memref_list[i].type==LOAD_INSTRUCTION)
            {
                // Count miss or hit for D_cache
                if (D_cache[(memref_list[i].address>>2)%cache_size]==memref_list[i].address)
                    ++D_cache_hit;
                else
                {
                    D_cache[(memref_list[i].address>>2)%cache_size] = memref_list[i].address;
                    ++D_cache_miss;
                }
            }
            else if (memref_list[i].type==STORE_INSTRUCTION)//Add address to D_cache
                D_cache[(memref_list[i].address>>2)%cache_size] = memref_list[i].address;

        }
        // Print to file for importing to graphing program
        fprintf(fp,"%2.1f\t%2.1f\t%d\n",100*(double)I_cache_miss/(I_cache_hit+I_cache_miss),100*(double)D_cache_miss/(D_cache_hit+D_cache_miss),cache_size);
        // Print to stdout for viewing on console
        fprintf(stdout,"%2.1f\t%2.1f\t%d\n",100*(double)I_cache_miss/(I_cache_hit+I_cache_miss),100*(double)D_cache_miss/(D_cache_hit+D_cache_miss),cache_size);

        free(I_cache);
        free(D_cache);
    }
    fclose(fp);
}

static int part3_cache_access(cache_struct* cache,int address,int set_size,int cache_size)
{
    int index;
    int index_to_remove=set_size;
    int cache_hit=0;
    int tmpLRU; //This is the LRU value we will be taking out
    //baseindex contains the first index for the set given by this instruction
    int baseindex=set_size*((address>>2)%(cache_size/set_size));
    // Find if it hit or miss
    for (index=0; index<set_size; ++index)
    {
        //check all positions in the set
        if (cache[baseindex+index].address==address)
        {
            //cache hit
            cache_hit=CACHE_HIT;
            tmpLRU=cache[baseindex+index].LRU;
            break;
        }
        if (cache[baseindex+index].LRU==set_size || cache[baseindex+index].LRU==0)
            index_to_remove=index;//if a miss, this is what will be replaced
        if (cache[baseindex+index].LRU==0)
            break;
    }
    if (cache_hit!=CACHE_HIT)
    {
        //A miss, so set values accordingly
        index=index_to_remove;
        tmpLRU=set_size;
    }
    // baseindex+index is where the current data either is in memory or should be
    // This loop puts it in place
    int tmpindex;
    for (tmpindex=0; tmpindex<set_size; ++tmpindex)
    {
        if (tmpindex==index)
        {
            cache[baseindex+tmpindex].LRU=1;
            cache[baseindex+tmpindex].address=address;
        }
        else if (cache[baseindex+tmpindex].LRU<tmpLRU && cache[baseindex+tmpindex].LRU!=0)
            ++cache[baseindex+tmpindex].LRU;
    }

//    //check
//    if (cache_hit!=CACHE_HIT && cache[baseindex+set_size-1].LRU!=0)
//    {
//        int tmpcounter=0;
//        for (index=0; index<set_size; ++index)
//        {
//            tmpcounter+=cache[baseindex+index].LRU;
//        }
//        if (set_size!=1 && tmpcounter!=((set_size/2)*(set_size+1)))
//        {
//            for (index=0; index<set_size; ++index)
//            {
//                printf("%d\t",cache[baseindex+index].address);
//            }
//            printf("%d\n",set_size);
//            exit(0);
//        }
//        else if (set_size==1 && tmpcounter!=set_size)
//            printf("%d\t%d\n",set_size,tmpcounter);
//    }
    return cache_hit;
}

static void part3(memref_struct* memref_list,int memref_count)
{
    // Part 3
    FILE* fp;
    fp = fopen("Part3.txt","w");
    fprintf(fp,"\tPart 3\n");
    fprintf(stdout,"\tPart 3\n");
    int cache_size,i;
    for (cache_size=512; cache_size<=(1024*1024); cache_size*=2)
    {
        fprintf(fp,"Cache Size: %d\n",cache_size);
        fprintf(fp,"I_Cache\tD_Cache\tn-way\n");
        fprintf(stdout,"Cache Size: %d\n",cache_size);
        fprintf(stdout,"I_Cache\tD_Cache\tn-way\n");
        cache_struct* I_cache = (cache_struct*) calloc(sizeof(cache_struct),cache_size);
        cache_struct* D_cache = (cache_struct*) calloc(sizeof(cache_struct),cache_size);
        int I_cache_hit=0,D_cache_hit=0;
        int I_cache_miss=0,D_cache_miss=0;
        // Instead of use a complex data structure, the set-associativity will be implemented
        // using some mathematical manipulation of the index values
        int set_size;
        for (set_size=1; set_size<=8; set_size*=2)
        {
            for (i=0; i<memref_count; ++i)
            {
                if (memref_list[i].type==INSTRUCTION_FETCH)
                {
                    if (part3_cache_access(I_cache,memref_list[i].address,set_size,cache_size)==CACHE_HIT)
                        ++I_cache_hit;
                    else
                        ++I_cache_miss;
                }
                else if (memref_list[i].type==LOAD_INSTRUCTION)
                {
                    if (part3_cache_access(D_cache,memref_list[i].address,set_size,cache_size)==CACHE_HIT)
                        ++D_cache_hit;
                    else
                        ++D_cache_miss;
                }
                else if (memref_list[i].type==STORE_INSTRUCTION)//Add address to D_cache
                    part3_cache_access(D_cache,memref_list[i].address,set_size,cache_size);
                // With only a bit of inefficiency, we can save maintainability by just not caring
                // whether it hit or miss, and the helper function adds it to the cache anyways

            }

            //Save cache_miss_rate in file
            fprintf(fp,"%2.1f\t%2.1f\t%d\n",100*(double)I_cache_miss/(I_cache_hit+I_cache_miss),100*(double)D_cache_miss/(D_cache_hit+D_cache_miss),set_size);
            fprintf(stdout,"%2.1f\t%2.1f\t%d\n",100*(double)I_cache_miss/(I_cache_hit+I_cache_miss),100*(double)D_cache_miss/(D_cache_hit+D_cache_miss),set_size);
            for (i=0; i<cache_size; ++i)
            {
                //Clear data
                I_cache[i].LRU=0;
                I_cache[i].address=0;
                D_cache[i].LRU=0;
                D_cache[i].address=0;
            }
        }

        free(I_cache);
        free(D_cache);
    }
    fclose(fp);
}
