#include "Tree.hpp"



int main(void)
{
    // Node<int> root(1);
    // Tree<int> tree;
    // tree.add_root(&root);
    // Node<int> child(2);
    // tree.add_sub_node(&root, &child);
    // Node<int> child2(3);
    // tree.add_sub_node(&root, &child2);

    // for(Tree<int>::PostOrderIterator it = tree.post_order_begin(); it != tree.post_order_end(); ++it)
    // {
    //     cout << *it << endl;
    // }

    // Node<int> root(1);
    // Tree<int> tree;
    // tree.add_root(&root);
    // Node<int> child(2);
    // tree.add_sub_node(&root, &child);
    // Node<int> child2(3);
    // tree.add_sub_node(&root, &child2);

    Tree<int> tree;
    Node<int> root(1);
    tree.add_root(&root);
    Node<int> child(2);
    tree.add_sub_node(&root, &child);
    Node<int> child2(3);
    tree.add_sub_node(&root, &child2);
    Node<int> child3(4);
    tree.add_sub_node(&child, &child3);
    Node<int> child4(5);
    tree.add_sub_node(&child2, &child4);
    Node<int> child5(6);
    tree.add_sub_node(&child2, &child5);
    vector<int> expected = {4, 2, 5, 6, 3, 1};
    // while(it != tree.post_order_end())
    // {   
    //     CHECK(*it == *vecIt);
    //     ++it;
    //     ++vecIt;
    // }
    // int i = 0;
    // if(tree.post_order_end().current == nullptr)
    // {

    //     cout << "null1" << endl;
    // }
    for(Tree<int>::PostOrderIterator it = tree.post_order_begin(); it != tree.post_order_end(); ++it)
    {
        // if(tree.post_order_end().current == nullptr)
        // {
            
        //     cout << "null2" << endl;
        //     break;   
        // }
        // cout << i++ << endl;
        // if(it.current == nullptr)
        // {

        //     cout << "null3" << endl;
        //     break;   
        // }
        cout << *it << endl;
    }
    
    return 0;
}