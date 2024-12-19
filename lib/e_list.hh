
/*
implementation
    - PUSH
        chunk = last_chunk
        isChunkFree = last_chunk_has_free_slot
        if isChunkFree
            size += 1
            chunk[size_for_this_chunk] = element
        else
            new_chunk = add_chunk()
            new_chunk[size_for_this_chunk] = element
    - INDEX_ACCESS
        


*/


#define CHUNK_SIZE 4
namespace dst{
    namespace EList{   
        template<typename T>
        class EList;

        template<typename T>
        class Chunk{
            friend class EList<T>;
            T *values = nullptr;
            Chunk<T>* prev = nullptr;
        };

        template<typename T>
        class EList{
            Chunk<T>* tail = nullptr;
            Chunk<T>* head = nullptr;
            int size = 0;
            int chunks = 0;

            public:
                EList(){
                    chunks = 1;
                }

                void push(T value){
                    //
                }
        };
    }
}