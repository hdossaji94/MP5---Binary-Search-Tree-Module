/* bst.h 
 * Lab5: binary search tree module
 * Version: 1
 * ECE 223, Fall 2015
 * Huzefa Dossaji 
 * Harlan Russell 
 * hdossaj
 */
 

enum balanceoptions {BST, AVL, TWOTHREET};
 
typedef void *data_t;

typedef int bst_key_t;

typedef struct bst_node_tag {
	data_t data_ptr;
	bst_key_t key;
	struct bst_node_tag *left;
	struct bst_node_tag *right;
} bst_node_t;

typedef struct bst_tag {
	bst_node_t *root;
	int tree_policy; // must be an balanceoptions
	int tree_size;
	int num_recent_key_comparisons;
} bst_t;

data_t bst_access (bst_t * t, bst_key_t pick);
data_t bst_search (bst_t *t, bst_node_t * a, bst_key_t pick); //auxillary function


bst_t *bst_construct (int tree_policy);

void bst_destruct (bst_t * t);
void freeTree(bst_node_t *node ); //auxillary function
void freeNode(bst_node_t *node);

int bst_insert (bst_t *t, bst_key_t pick, data_t);
bst_node_t * bst_insert_help(bst_t *t, bst_node_t *node, bst_key_t a, data_t p); //auxillary function

data_t bst_remove (bst_t * t, bst_key_t pick); 
bst_node_t *bst_remove_help(bst_t *t, bst_node_t * node, bst_key_t a); //auxillary function
bst_node_t * find_left_leaf(bst_node_t * node); //auxillary function

int bst_size(bst_t * t);

int bst_stats (bst_t * t);

int bst_int_path_len(bst_t * t);
int bst_len(bst_node_t * node); //auxillary function


void bst_debug_print_tree(bst_t * t);
void ugly_print(bst_node_t *N, int level); //auxillary function

void bst_debug_validate(bst_t * t);
int bst_debug_validate_rec(bst_node_t *N, int min, int max, int *count);
