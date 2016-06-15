
#include <iostream> 
#include <cstdio> 
#include <list> 
using namespace std; 
 
const int TOTAL_MEM=200; 
 
unsigned char Mem[TOTAL_MEM];
  
struct MemBlock{
    int start,end;                      
    MemBlock(int a=0,int b=0):start(a),end(b){} 
};  
list<MemBlock> freeList;

void output(){
    static int step=0; 
    printf("step %d\n",step); 
    list<MemBlock>::iterator itr=freeList.begin(); 
    for(itr;itr!=freeList.end();itr++){
        if((*itr).start<TOTAL_MEM) printf("[%d,%d)\n",(*itr).start,(*itr).end); 
    } 
    step++; 
}
   
void memFree(unsigned char *header,int size){
    list<MemBlock>::iterator itr=freeList.begin(); 
	int start=header-Mem; 
    for(itr;itr!=freeList.end();itr++) 
		if ((*itr).start>=start){
        if (start+size<(*itr).start) 
            freeList.insert(itr, MemBlock(start,start+size));
        else (*itr).start=start;
        break; 
    }      
}

unsigned char* memMalloc(int size) 
{ 
    list<MemBlock>::iterator itr=freeList.begin(); 
    for(itr;itr!=freeList.end();itr++){
        if ((*itr).end-(*itr).start >= size){
            unsigned char* header = Mem+(*itr).start;
            (*itr).start += size;
            if( (*itr).end == (*itr).start){
                freeList.erase(itr); 
            } 
            return header;
        } 
    } 
    return 0;
} 

int main(int argc, const char * argv[]) { 
    freopen("input.txt","r",stdin); 
    freopen("output.txt","w",stdout); 
    freeList.push_back(MemBlock(0,TOTAL_MEM));
    freeList.push_back(MemBlock(TOTAL_MEM+1,TOTAL_MEM+1)); 
    int N; 
    scanf("%d\n",&N); 
    for (int i=0;i<N;i++){ 
        char ch; 
        scanf("%c",&ch); 
        if (ch=='M'){ 
            int x;scanf("%d\n",&x); 
            unsigned char *P=memMalloc(x); 
            output(); 
        }else{ 
            int x,y; 
            scanf("%d%d\n",&x,&y); 
            memFree(Mem+x,y); 
            output(); 
    	} 
	} 
	return 0; 
} 