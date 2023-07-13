#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int state[3][3];
	int empty_row;
	int empty_col;
} State;

typedef struct Node {
	State state;
	int level;
	int operation;
	struct Node* parent;
} Node;

typedef struct {
	Node* nodes[10000];
	int front;
	int rear;
} Queue;

State initial_state = {
{{2, 8, 3},
{1, 0, 4},
{7, 6, 5}},
	1,
	1
};

State target_state = {
{{1, 2, 3},
{8, 0, 4},
{7, 6, 5}},
	1,
	1
};

int is_state_equal(State* state1, State* state2) {
	return memcmp(state1, state2, sizeof(State)) == 0;
}

void copy_state(State* dest, State* src) {
	memcpy(dest, src, sizeof(State));
}

int is_valid_position(int row, int col) {
	return (row >= 0 && row < 3 && col >= 0 && col < 3);
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void print_state(State* state) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", state->state[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int is_visited(Queue* queue, State* state) {
	for (int i = queue->front; i <= queue->rear; i++) {
		if (is_state_equal(&queue->nodes[i]->state, state)) {
			return 1;
		}
	}
	return 0;
}

void enqueue(Queue* queue, Node* node) {
	queue->nodes[++queue->rear] = node;
}

Node* dequeue(Queue* queue) {
	return queue->nodes[queue->front++];
}

Node* create_node(State* state, int level, int operation, Node* parent) {
	Node* node = (Node*)malloc(sizeof(Node));
	copy_state(&node->state, state);
	node->level = level;
	node->operation = operation;
	node->parent = parent;
	return node;
}

void extend_node(Queue* open, Queue* close, Node* node) {
	int row = node->state.empty_row;
	int col = node->state.empty_col;
	
	// Move empty space up
	if (is_valid_position(row - 1, col)) {
		State new_state;
		copy_state(&new_state, &node->state);
		swap(&new_state.state[row][col], &new_state.state[row - 1][col]);
		new_state.empty_row = row - 1;
		enqueue(open, create_node(&new_state, node->level + 1, 'U', node));
	}
	
	// Move empty space down
	if (is_valid_position(row + 1, col)) {
		State new_state;
		copy_state(&new_state, &node->state);
		swap(&new_state.state[row][col], &new_state.state[row + 1][col]);
		new_state.empty_row = row + 1;
		enqueue(open, create_node(&new_state, node->level + 1, 'D', node));
	}
	
	// Move empty space left
	if (is_valid_position(row, col - 1)) {
		State new_state;
		copy_state(&new_state, &node->state);
		swap(&new_state.state[row][col], &new_state.state[row][col - 1]);
		new_state.empty_col = col - 1;
		enqueue(open, create_node(&new_state, node->level + 1, 'L', node));
	}
	
	// Move empty space right
	if (is_valid_position(row, col + 1)) {
		State new_state;
		copy_state(&new_state, &node->state);
		swap(&new_state.state[row][col], &new_state.state[row][col + 1]);
		new_state.empty_col = col + 1;
		enqueue(open, create_node(&new_state, node->level + 1, 'R', node));
	}
	
	enqueue(close, node);
}

void print_solution(Node* node) {
	if (node->parent != NULL) {
		print_solution(node->parent);
	}
	print_state(&node->state);
}

void bfs() {
	Queue open_queue;
	Queue close_queue;
	open_queue.front = 0;
	open_queue.rear = -1;
	close_queue.front = 0;
	close_queue.rear = -1;
	
	enqueue(&open_queue, create_node(&initial_state, 0, -1, NULL));
	
	while (open_queue.front <= open_queue.rear) {
		Node* current_node = dequeue(&open_queue);
		
		if (is_state_equal(&current_node->state, &target_state)) {
			print_solution(current_node);
			return;
		}
		
		extend_node(&open_queue, &close_queue, current_node);
	}
	
	printf("No solution found.\n");
}

int main() {
	bfs();
	return 0;
}
