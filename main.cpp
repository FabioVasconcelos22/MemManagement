#include <iostream>
#include <iomanip>

//class que recebe para metros tamanho dos blocos e qnts blocos ter
        // metodo de alocador, parametro recebe tamanho) (retornar void*)
        //free/ dialoc shunco de ram (*apontador)

        //excptio se nao tiver memoria disponivel, se tamnho a alocar > bloco;


        //major spoil: linked_list


#include <malloc.h>

class VirtualMemory {

public:

    uint8_t* p1;

    int BlockQnt = 0;
    int BlockSize = 0;

private:

    struct FreeBlock {
        FreeBlock* next;
    };

    FreeBlock* Free;

public:

    VirtualMemory(int size, int qnt) :
        BlockQnt (qnt),
        BlockSize (size)
    {
        p1 = static_cast<uint8_t *>(malloc(qnt * size));

        FreeBlock* block;
        for (int i = 0 ; i < BlockQnt ; ++i) {
            block  = (FreeBlock*) (p1 + BlockSize * i);
            block->next = (FreeBlock*) (p1 + BlockSize * (i+1));
        }

        block->next = nullptr;

        Free = (FreeBlock*) p1;

        DebugMem();

    };

    ~VirtualMemory() {
        std::cout << "Destructed" << std::endl;
    }

    template < typename _t >
    _t* alloc () {
        return new (AllocMem(sizeof(_t))) _t;
    }

    void* AllocMem (int size) {

        if (size > BlockSize) {
            throw "TOO LARGE";
        }

        FreeBlock* aux = Free;

        if(Free == nullptr) {
            throw "FULL_CAPACITY";
        }

        Free = Free->next;

        return aux;
    }

    void* DeallocMem(void* ptr) {

        FreeBlock* aux = Free;

        Free = (FreeBlock*)ptr;

        Free->next = aux;

        return Free;
    }

    void DebugMem () {

        for(int i=0; i<BlockSize*BlockQnt; ++i) {
            std::cout << " " << std::hex << std::setw(2) << std::setfill('0') << (int) p1[i];
        }
        std::cout << std::endl;
    }
private:

};

int main(int argc, char *argv[]) {

    struct my_struct {
        uint8_t x;
        uint16_t y;
        uint32_t z;
        uint64_t w;
    };

    VirtualMemory pool (16, 4);

    my_struct* ptr = pool.alloc < my_struct > ();

    ptr->x = 0x0F;
    ptr->y = 0x0A; // Porque raio isto aparece no 3º byte, em vez do 2º?
    ptr->z = 0xAA;
    ptr->w = 0xBB;

    pool.DebugMem();

    /*int* ptr;
    int* ptr1;
    int* ptr2;

    ptr = (int*)VM.AllocMem(16);
    ptr1 = ptr,

    *ptr = 0xFF;

    VM.DebugMem();

    ptr = (int*)VM.AllocMem(16);
    ptr2 = ptr;

    *ptr = 0xBB;

    //ptr = 0x0F;
    //*(ptr+1) = 0x0A;
    //*(ptr+2) = 0x0B;
    //*(ptr+3) = 0x01;
    //*(ptr+4) = 0x00; //Recebenta a memória

    VM.DebugMem();

    ptr = (int*)VM.DeallocMem(ptr);

    VM.DebugMem();

    ptr = (int*)VM.AllocMem(16);

    *ptr = 0xAB;

    VM.DebugMem();

    ptr1 = (int*)VM.DeallocMem(ptr1);

    VM.DebugMem();

    ptr1 = (int*)VM.AllocMem(16);

    *ptr1 = 0xAB;

    VM.DebugMem();

    ptr = (int*)VM.AllocMem(16);

    *ptr = 0xFF;

    VM.DebugMem();

    ptr = (int*)VM.AllocMem(16);

    *ptr = 0xCC;

    VM.DebugMem();

    ptr1 = (int*)VM.DeallocMem(ptr1);

    VM.DebugMem();

    ptr = (int*)VM.AllocMem(16);

    *ptr = 0x03;

    ptr2 = (int*)VM.DeallocMem(ptr2);

    VM.DebugMem();

    ptr = (int*)VM.AllocMem(16);

    *ptr = 0x01;

    VM.DebugMem();

    //ptr = (int*)VM.AllocMem(16);

    //*ptr = 0x02;

    //VM.DebugMem();*/

    return 0;
}
