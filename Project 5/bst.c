#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

struct bst_node {
    int val;
    struct bst_node *left;
    struct bst_node *right;

};
typedef struct bst_node NODE;


struct bst {
    NODE *root;
    int Size;
};

BST_PTR bst_create(){
  BST_PTR t = malloc(sizeof(struct bst));
  t->root = NULL;
  t->Size = 0;
  return t;
}

// a nlog n?
// b. n
// c n^2
static NODE * from_arr(int *a, int n){
    int m;
    NODE *p;
    if(n==0)
        return NULL;
    m=n/2;
    p = malloc(sizeof(NODE));

    p->val = a[m];
    p->left = from_arr(a, m);
    p->right = from_arr(&(a[m+1]), n-(m+1));
    return p;
}

BST_PTR bst_from_sorted_arr(int *a, int n){
  BST_PTR t = bst_create();
  t->root = from_arr(a, n);
  return t;
}

static void free_r(NODE *r){
    if(r==NULL) return;
    free_r(r->left);
    free_r(r->right);
    free(r);
}
void bst_free(BST_PTR t){
    free_r(t->root);
    free(t);
}

static NODE * insert(NODE *r, int x){
    NODE *leaf;
    if(r == NULL){
      leaf = malloc(sizeof(NODE));
      leaf->left = NULL;
      leaf->right = NULL;
      leaf->val = x;
      return leaf;
    }

    if(r->val == x)
        return r;
    if(x < r->val){
        r->left = insert(r->left, x);
        return r;
    }
    else {
        r->right = insert(r->right, x);
        return r;
    }
}

NODE* newNode(int x)
{
    NODE* T = malloc(sizeof(NODE));
    T->val = x;
    T->left = NULL;
    T->right = NULL;
    return T;
}

// TODO
// how about an iterative version?
static NODE *insert_i(NODE *r, int x)
{
    if(r == NULL)
    {
        r = newNode(x);
    }
    else
    {
        NODE* temp;
        temp = r;
        while(temp!=NULL)
        {
            if(temp->val == x)
                break;
            else if(x<temp->val)
                if(temp->left == NULL)
                {
                    temp->left = newNode(x);
                }
                else
                {
                    temp = temp->left;
                }
            else
            {
                if(temp->right == NULL)
                {
                    temp->right = newNode(x);
                }
                else
                {
                    temp = temp->right;
                }
            }
        }
    }
    return r;

}


void bst_insert(BST_PTR t, int x){
    //t->root = insert(t->root, x);

    // TODO:  uncomment the line below if you
    //   implemented iterative insertion (above)
    //   (and of course delete the call to insert()
    //   above.
    t->root = insert_i(t->root, x);
    t->Size++;
}

int bst_contains(BST_PTR t, int x){
    NODE *p = t->root;

    while(p != NULL){

        if(p->val == x)
            return 1;
        if(x < p->val){
            p = p->left;
        }
        else
            p = p->right;
    }
    return 0;
}

// helper functions to find min/max elements in
//   tree rooted at r
static int min_h(NODE *r){
  if(r==NULL)
    return -1; // should never happen!
  while(r->left != NULL)
      r = r->left;
  return r->val;
}

static int max_h(NODE *r){
  if(r==NULL)
    return -1; // should never happen!
  while(r->right != NULL)
      r = r->right;
  return r->val;
}

// recursive helper function to remove x
// returns root of tree after deletion.
// *success is used to communicate if the deletion
//    actually happened or not.
static NODE *remove_r(NODE *r, int x, int *success){
NODE   *tmp;
int sanity;

  if(r==NULL){
    *success = 0;  // no match
    return NULL;
  }
  if(r->val == x){
    *success = 1;

    if(r->left == NULL){
        tmp = r->right;
        free(r);
        return tmp;
    }
    if(r->right == NULL){
        tmp = r->left;
        free(r);
        return tmp;
    }
    // if we get here, r has two children
    r->val = min_h(r->right);
    r->right = remove_r(r->right, r->val, &sanity);
    if(!sanity)
        fprintf(stderr, "ERROR:  remove() failed to delete promoted value?\n");
    return r;
  }
  if(x < r->val){
    r->left = remove_r(r->left, x, success);
  }
  else {
    r->right = remove_r(r->right, x, success);
  }
  return r;  // root unchanged

}


int bst_remove(BST_PTR t, int x){
    int success;
    t->root = remove_r(t->root, x, &success);
    if(success ==1)
    {
        t->Size--;
    }
    return success;
}


static int size(NODE *r){

    if(r==NULL) return 0;
    return size(r->left) + size(r->right) + 1;
}

/** TODO:  modify / augment data structure so bst_size
    takes only O(1) time.
**/
int bst_size(BST_PTR t){
    printf("\nSIZE OF: %d\n", t->Size-1);
    return ((t->Size)-1);
}

static int height(NODE *r){
    int l_h, r_h;

    if(r==NULL) return -1;
    l_h = height(r->left);
    r_h = height(r->right);
    return 1 + (l_h > r_h ? l_h : r_h);

}
int bst_height(BST_PTR t){
    return height(t->root);

}

int bst_min(BST_PTR t){
    return min_h(t->root);
}

int bst_max(BST_PTR t){
    return max_h(t->root);
}

static void indent(int m){
    int i;
    for(i=0; i<m; i++)
        printf("-");
}

static void inorder(NODE *r){
  if(r==NULL) return;
  inorder(r->left);
  printf("[%d]\n", r->val);
  inorder(r->right);

}
void bst_inorder(BST_PTR t){

  printf("========BEGIN INORDER============\n");
  inorder(t->root);
  printf("=========END INORDER============\n");

}

static void preorder(NODE *r, int margin){
  indent(margin);
  if(r==NULL)
    printf(" NULL \n");
  else {
    printf("%d\n", r->val);
    preorder(r->left, margin + 3);
    preorder(r->right, margin+3);
  }
}

void bst_preorder(BST_PTR t){

  printf("========BEGIN PREORDER============\n");
  preorder(t->root, 0);
  printf("=========END PREORDER============\n");

}

static void postorder(NODE *r, int margin)
{
    indent(margin);
    if(r==NULL)
        printf(" NULL \n");
    else
    {
        postorder(r->left, margin + 3);
        postorder(r->right, margin+3);
        printf("%d\n", r->val);
    }

}

// indentation is proportional to depth of node being printed
//   depth is #hops from root.
void bst_postorder(BST_PTR t){

  printf("========BEGIN POSTORDER============\n");
  postorder(t->root, 0);
  printf("=========END POSTORDER============\n");

}

int bst_ith_smallest(BST_PTR t, int i)
{

}

