//
//  main.cpp
//  Huffman Tree
//
//  Created by lenci on 12-12-28.
//  Copyright (c) 2012年 Soochow University. All rights reserved.
//

#include <iostream>
#include "HeapSort.h"

using namespace std;

int inputItems(Heap nodes, int n) {
    //建立堆
    std::cout << "----------------\n";
    for (int i=1; i<= n; i++) {
        Node* aNode = (Node*)malloc(sizeof(Node));
        std::cout << "imput item " << i << "'s w：";
        std::cin >> aNode->w;
        std::cout << "----------------\n";
        aNode->lChild = nullptr;
        aNode->rChild = nullptr;
        
        addElem(nodes, aNode);
    }
    heapUp(nodes);
    
    return 0;
}

int inorder(Tree t) {
    if (t) {
        inorder(t->lChild);
        cout << t->w << " ";
        inorder(t->rChild);
    }
    return 0;
}

int preorder(Tree t) {
    if (t) {
        cout << t->w << " ";
        preorder(t->lChild);
        preorder(t->rChild);
    }
    return 0;
}

int output(Tree huffmanTree) {
    cout << "先序遍历：\n";
    preorder(huffmanTree);
    cout << "\n中序遍历：\n";
    inorder(huffmanTree);
    return 0;
}

Node* huffman(Heap& nodes) {
    while (nodes->length > 1) {
        Node* aNode = (Node*)malloc(sizeof(Node));
        aNode->lChild = getTop(nodes);
        aNode->rChild = getTop(nodes);
        aNode->w = aNode->lChild->w + aNode->rChild->w;
        addElem(nodes, aNode);
        heapUp(nodes);
    }
    
    return getTop(nodes);
}

int main(int argc, const char * argv[])
{

    Heap nodes = initHeap();
    
    std::cout << "请输入n：";
    int n;
    std::cin >> n;
    
    inputItems(nodes, n);
    
    Tree huffmanTree = huffman(nodes);
    
    output(huffmanTree);
    
    return 0;
}

