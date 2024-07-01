#include "Tree.hpp"


int main(void)
{
    Tree<int,3> tree;
    Node<int> root(1);
    tree.add_root(&root);
    Node<int> child(2);
    tree.add_sub_node(&root, &child);
    Node<int> child2(3);
    tree.add_sub_node(&root, &child2);
    tree.add_sub_node(&child, nullptr);
    Node<int> child3(4);
    tree.add_sub_node(&child, &child3);
    Node<int> child4(5);
    tree.add_sub_node(&child2, &child4);
    Node<int> child5(6);
    tree.add_sub_node(&child2, &child5);

    vector<int> expected = {1, 2, 4, 3, 5, 6};
    Dfs_scan<int> it = tree.pre_order_begin();
    auto vecIt = expected.begin();
    while(it != tree.pre_order_end())
    {   
        cout << *it << endl;
        it++;
    }

    tree.draw();
    
    return 0;
}