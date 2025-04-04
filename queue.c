#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {

    uint64_t state_val = serialize(state); //serialize then add to tail
    insert_at_tail(&q->data, state_val);

}

struct game_state dequeue(struct queue *q) { 

    uint64_t state_val = remove_from_head(&q->data); //remove from head, then deserialize
    return deserialize(state_val);

}

int number_of_moves(struct game_state start) { 
    struct queue q; //initialize q structure
    q.data.head = NULL; 

    enqueue(&q, start);

    while(q.data.head != NULL){ //BFS structure
        struct game_state current = dequeue(&q);
        if(checker_function(current)){
            return current.num_steps;
        }
        else{
            struct game_state next;
            next.num_steps = current.num_steps + 1;

            next = current; //checking moving up
            move_up(&next);
            if(!(was_visited(&q, next))){
                enqueue(&q, next);
            }

            next = current; //checking moving down
            move_down(&next);
            if(!(was_visited(&q, next))){
                enqueue(&q, next);
            }

            next = current; //checking moving right
            move_right(&next);
            if(!(was_visited(&q, next))){
                enqueue(&q, next);
            }

            next = current; //checking moving left
            move_left(&next);
            if(!(was_visited(&q, next))){
                enqueue(&q, next);
            }
        }
    }

    return 0; 
}

bool checker_function (struct game_state state){
    uint8_t goal[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};

    for(int i = 0; i < 4; i++){ //iterate through each index to see if it is equal to end state
        for(int j = 0; j < 4; j++){
            if(state.tiles[i][j] != goal[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool was_visited(struct queue *q, struct game_state current){
    uint64_t state_val = serialize(current);
    for(struct list_node *current = q->data.head; current != NULL; current = current->next){ //have we visited this state?
        if(current->value == state_val){
            return true;
        }
    }
    return false;
}
