 /* bst.c                 
 * Huzefa Dossaji          
 * hdossaj
 * ECE 223 Fall 2015
 * MP5
 *
 * Purpose: file contains functions for lab5.c to use. contains functions to do anything to the 
 * binary search tree such as create new nodes and leaves and remove them as well. will print out
 * the resulting tree as well. 
 *
 * Assumptions: User would like to develop a ideal binary search tree
 *
 * Bugs: THERE ARE NO BUGS DETECTED EVEN WITH ALL MY EXTENSIVE TESTING
 */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "bst.h"   
#include <limits.h>

#define TRUE 1
#define FALSE 0
/*Find the tree element with the matching key and return a pointer to the data block that is stored in
this node in the tree. If the key is not found in the tree then return NULL */
data_t bst_access (bst_t * t, bst_key_t pick)
{
   if(t->root !=NULL){
   	t->num_recent_key_comparisons = 0; 
   	return bst_search(t, t->root, pick);
   }
   return NULL;
}
// auxillary function to help bst_access
data_t bst_search (bst_t *t, bst_node_t * node, bst_key_t pick){
	 //root is null or key is present at root (base case)
	 t->num_recent_key_comparisons++;
    if (node == NULL || node->key == pick){
    	if(node == NULL){
    		return NULL;
    	}
       return node->data_ptr;
    }   
    
    // if Key is greater than root's key
    	t->num_recent_key_comparisons++;
    if (node->key < pick){
       return bst_search(t,node->right, pick);
       }
 
    //  if Key is smaller than root's key
    t->num_recent_key_comparisons++;
    return bst_search(t,node->left, pick);


}
/*Create the header block for the tree and save the tree_policy in the header block.  */
bst_t *bst_construct (int tree_policy){

	bst_t * tree_head = NULL;
	tree_head = (bst_t*)malloc(sizeof(bst_t));
		
	tree_head->root = NULL;
	tree_head->tree_policy = BST;
	tree_head->tree_size = 0; 
	tree_head->num_recent_key_comparisons = 0;
		
		

	return tree_head;
}
/*Free all items stored in the tree including the memory block with the data and the bst_node_t
structure. Also frees the header block. */
void bst_destruct (bst_t *t){
	
	if(t->root !=NULL){
		freeTree(t->root);
	}
	t->root = NULL;
	free(t->root);
	free(t);

	
}
// auxillary function to help out bst_destruct
void freeTree(bst_node_t *node ){    
           //Tree's root note is passed as argument
           if(node!=NULL)
	  {
	    freeTree(node->left);
	    freeTree(node->right);
	    
	    freeNode(node);
	  }
	  
           
}
// auxillary function to help out bst_destruct
void freeNode(bst_node_t *node){
	

	    free(node->data_ptr);
	    node->left = NULL;
	    node->right = NULL;
	    /*free(node->left);
	    free(node->right);*/
	    free(node);
	    
}

/*Insert the memory block pointed to by data_t into the tree with the associated key. The function
must return 0 if the key is already in BST The function must return 1 if the key was not already 
in the BST but was instead added to the tree.  */
int bst_insert (bst_t *t, bst_key_t a, data_t p){
	int ret; 
	t->num_recent_key_comparisons=0;
	if(t->root ==NULL){
		bst_node_t *new = NULL;
    		new = (bst_node_t*)malloc(sizeof(bst_node_t));
    		new->data_ptr = p;
    		new->key = a;
    		new->left = NULL;
    		new->right = NULL;
    		t->root = new; 
    		t->tree_size++;
    		return 1;
	}else{
		data_t check = bst_access(t, a);
		if(check != NULL){
			ret = 0;
		}else{
			ret = 1;
		}
		
		bst_insert_help(t, t->root, a, p);
		if(ret == 1){
			t->tree_size++;
		}
		return ret;
		 	
		
	}

}
// auxillary function to help out bst_insert
bst_node_t * bst_insert_help(bst_t *t, bst_node_t *node, bst_key_t a, data_t p){
	
	
	/*  tree is nonempty and key is already in tree*/
	t->num_recent_key_comparisons++;
	if (node != NULL && node->key == a){
	
		free(node->data_ptr);
		node->data_ptr = p; 		
    		
    		return node;
	
	}
	/* If the tree is empty, return a new node */
    	if (node == NULL){
    	
    		bst_node_t *new = NULL;
    		new = (bst_node_t*)malloc(sizeof(bst_node_t));
    		new->data_ptr = p;
    		new->key = a;
    		new->left = NULL;
    		new->right = NULL;
    		
    		
    		return new;
 	}
 	
    	/* Otherwise, traverse down the tree */
    	t->num_recent_key_comparisons++;
   	if (a < node->key)
        	node->left =  bst_insert_help(t,node->left, a, p);
    	else if (a > node->key){
    		t->num_recent_key_comparisons++;
        	node->right = bst_insert_help(t,node->right, a, p);   
 	}
    
    	return node; 

}
/*Remove the item in the tree with the matching key. Return the pointer to the data memory block
and free the bst_node_t memory block. If the key is not found in the tree, return NULL.  */
data_t bst_remove (bst_t * t, bst_key_t a){
	t->num_recent_key_comparisons=0;
	data_t * remove = bst_access(t, a);
	if(remove != NULL){
		t->tree_size--;
	}

	bst_node_t * first = NULL;
	first = bst_remove_help(t, t->root, a);
	
	t->root = first; 
	
	
	return remove; 
	
}

// auxillary function to help out bst_remove
bst_node_t *bst_remove_help(bst_t *t, bst_node_t * node, bst_key_t a)
{
    // base case

    if (node == NULL) return node;
 
    // If the key in node is smaller than the root's key,
      if (a < node->key){
    	t->num_recent_key_comparisons++;
        node->left = bst_remove_help(t,node->left, a);
        }
 
    // If the key in node is greater than the root's key,
    else if (a > node->key){
   	 t->num_recent_key_comparisons++;
        node->right = bst_remove_help(t,node->right, a);
        }
 
   
    // if you get here then that is the node to be deleted
    	
    else
    {
    	t->num_recent_key_comparisons++;
        // node with only one child or no child
        if (node->left == NULL)
        {
            bst_node_t *temp = node->right;
            	
            	
		node->left = NULL;
		node->right = NULL;
		free(node);

    		
            return temp;
        }
        else if (node->right == NULL)
        {
            bst_node_t *temp = node->left;
            
		
		node->left = NULL;
		node->right = NULL;
		free(node);
    		
            return temp;
        }
 
              bst_node_t* temp = find_left_leaf(node->right);
 
       
        node->key = temp->key;
        node->data_ptr = temp->data_ptr;
        node->right = bst_remove_help(t,node->right, temp->key);
    }
    return node;
}
// auxillary function to help bst_remove and bst_remove_help, finds the leftmost leaf so bst can be in order
bst_node_t * find_left_leaf(bst_node_t * node)
{
    bst_node_t * need = node;
 
    /* loop down to find the leftmost leaf */
    while (need->left != NULL)
        need = need->left;
 
    return need;
}

/*Return the number of keys in the BST.  */
int bst_size(bst_t * t){

	int keys;
	keys = t->tree_size;
	return keys;
	
}

/*Return num_recent_key_comparisons, the number of key comparisons for the most recent call
to bst_access, bst_insert, or bst_remove. */
int bst_stats (bst_t * t){
	
	int comparisons;
	comparisons = t->num_recent_key_comparisons; 
	return comparisons; 

}

/*Return the internal path length of the tree */
int bst_int_path_len(bst_t * t){

	return bst_len(t->root);

}

//auxillary function to find the internal path length recursively 
int bst_len(bst_node_t * node){
	
	bst_node_t * e = node; 
	int l = 0;
	int r = 0;
	
	if(e==NULL){
		return 0;
	}
	if(e->left){
		l=bst_len(e->left);
	}
	if(e->right){
		r=bst_len(e->right);
	}
	return l > r ? l+1 : r+1;

}

// calls out ugly_print 
void bst_debug_print_tree(bst_t * t){
	
	ugly_print(t->root, 1);	


}

// recursively prints out the entire tree in order. auxillary function to help out bst_debug_print_tree
void ugly_print(bst_node_t *N, int level) {
	if (N == NULL) return ;
	ugly_print(N->right, level+1) ;
	int i;
	for (i=0; i<level; i++) printf("     "); /* 5 spaces */
	printf("%5d\n", N->key); /* field width is 5 */
	ugly_print(N->left, level+1);
}

//function to check bst for errors, validations
void bst_debug_validate(bst_t *T)
{
	 int size = 0;
	 assert(bst_debug_validate_rec(T->root, INT_MIN, INT_MAX, &size) == TRUE);
	 assert(size == T->tree_size);
}

//function to check bst for errors, validations
int bst_debug_validate_rec(bst_node_t *N, int min, int max, int *count)
{
	 if (N == NULL) return TRUE;
	 if (N->key <= min || N->key >= max) return FALSE;
	 assert(N->data_ptr != NULL);
	 *count += 1;
	 return bst_debug_validate_rec(N->left, min, N->key, count) &&
	 bst_debug_validate_rec(N->right, N->key, max, count);
}

