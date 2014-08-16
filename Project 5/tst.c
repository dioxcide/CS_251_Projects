#include <assert.h>
#include "bst.h"


// example of using assertions
void test_insert(BST_PTR t){

  int i, x;

  for(i=0; i<10; i++){
    x = rand() % 100;
    bst_insert(t, x);
    assert(bst_contains(t,x));
  }
}

void test_contains(BST_PTR t){
  bst_insert(t, 1234);

  assert(bst_contains(t, 1234));

}

int main(){
  int i;

  int a[] = {8, 2, 7, 9, 11, 3, 2, 6};


  BST_PTR t = bst_create();

  for(i=0; i<8; i++)
    bst_insert(t, a[i]);

  assert(bst_size(t) == 7);

  test_insert(t);

  test_contains(t);

  bst_inorder(t);

  bst_preorder(t);

  bst_postorder(t);

  bst_ith_smallest(t, 1)

  bst_size(t);

  bst_free(t);
}
