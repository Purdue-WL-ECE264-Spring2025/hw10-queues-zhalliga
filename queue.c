#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {

    uint64_t state_val = serialize(state);
    insert_at_tail(&q->data, state_val);

}

struct game_state dequeue(struct queue *q) { 

    uint64_t state_val = remove_from_head(&q->data);
    return deserialize(state_val);

}

int number_of_moves(struct game_state start) { 
    struct queue q = {0}; //initialize q structure
    enqueue(&q, start);

    while(q.data.head != NULL){
        struct game_state current = dequeue(&q);
        if(checker_function(current)){
            return current.num_steps;
        }
        else{
            
        }
    }

    return 0; 
}

bool checker_function (struct game_state state){
    uint8_t goal[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(state.tiles[i][j] != goal[i][j]){
                return false;
            }
        }
    }
    return true;
}
