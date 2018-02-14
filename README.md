# MP5---Binary-Search-Tree-Module

[PLEASE SEE mp5.pdf FILE FOR FULL INSTRUCTIONS AND EXPLANATION!](mp5.pdf)

The goal of this machine problem is to design and implement a binary search tree (BST) module.

Use a modular design similar to the design for the list.c module from MP2, or the mem.c module from MP4. In particular, develop one header file that contains key definitions of the data structures that are needed for the interface and the prototype definitions for the functions that are the interfaces to the BST module. Also, expand upon the provided lab5.c file with new unit test drivers. Be sure to also submit a makefile that builds your program.

Two additional documents should be submitted. One is a test plan that describes details of your implementation and demonstrates, with a test script, how you verified that the code works correctly. The verification should include detailed prints from your program to show that you program operates correctly. The second document describes your performance evaluation, and the details are described below.

The following functions are required.

data_t bst_access (bst_t *, bst_key_t); - 
Find the tree element with the matching key and return a pointer to the data block that is stored in this node in the tree. If the key is not found in the tree then return NULL

bst_t *bst_construct (int tree_policy); - 
Create the header block for the tree and save the tree_policy in the header block. The tree_policy must be one of the labels defined with an enum as shown above. While the definition allows for multiple types of trees, you are only required to implement the BST option. Initialize the root pointer to null. The tree_size stores the current number of keys in the tree. The num_recent_key_comparisons stores the number of key comparisons during the most recent access, insert, or remove. Use Standish’s definitions for the number of comparisons even if your implementation is slightly different. That is, there is one comparison to determine if the key is found at the current level and if the key is not found one more comparison to determine if the next step is to the left or right. Do not count checks for null pointers.

void bst_destruct (bst_t *); - 
Free all items stored in the tree including the memory block with the data and the bst_node_t structure. Also frees the header block.

int bst_insert (bst_t *, bst_key_t, data_t); - 
Insert the memory block pointed to by data_t into the tree with the associated key. The function must return 0 if the key is already in BST (in which case the data memory block is replaced). The function must return 1 if the key was not already in the BST but was instead added to the tree. You are required to implement the BST policy only. If you elect to implement more than one type of tree, then the insertion method should conform to the tree_policy that is defined when the tree was initially constructed.

data_t bst_remove (bst_t *, bst_key_t); - 
Remove the item in the tree with the matching key. Return the pointer to the data memory block and free the bst_node_t memory block. If the key is not found in the tree, return NULL. You are required to implement the BST policy only. If you elect to implement more than one type of tree, then the deletion method should conform to the tree_policy that is defined when the tree was initially constructed.

int bst_size(bst_t *); - 
Return the number of keys in the BST.

int bst_stats (bst_t *); - 
Return num_recent_key_comparisons, the number of key comparisons for the most recent call to bst_access, bst_insert, or bst_remove.

int bst_int_path_len(bst_t *); - 
Return the internal path length of the tree

In addition you should make at least two debugging functions. See below for examples of these functions.

void bst_debug_print_tree(bst_t *);
void bst_debug_validate(bst_t *);

