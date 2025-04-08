#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { 
  struct list_node *node = calloc(1, sizeof(struct list_node));

  if(node == NULL){
    return NULL; 
  }

  node->value = value;
  node->next = NULL;
  return node;
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node *new = new_node(value);

  if(new == NULL){
    return;
  }

  new->next = list->head;
  list->head = new;
}

void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node *new = new_node(value);

  if(new == NULL){
    return;
  }
  if(list->head == NULL){
    return;
  }
  struct list_node *current = list->head;
  while(current->next != NULL){
    current = current->next;
  }
  current->next = new;
}

size_t remove_from_head(struct linked_list *list) { 
  if(list->head == NULL){
    return 0;
  }

  struct list_node *node = list->head;
  size_t value = node->value;
  list->head = node->next;
  free(node);

  return value; 
}

size_t remove_from_tail(struct linked_list *list) { 

  if(list->head == NULL){
    return 0;
  }

  if(list->head->next == NULL){
    size_t value = list->head->value;
    free(list->head);
    list->head = NULL;
    return(value);
  }

  struct list_node *node = list->head;
  while((node->next != NULL) && (node->next->next != NULL)){
    node = node->next;
  }

  size_t value = node->next->value;
  free(node->next);
  node->next = NULL;
  return value; 
}

void free_list(struct linked_list list) {
  while(list.head != NULL){
    struct list_node *node = list.head;
    list.head = list.head->next;
    free(node);
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
