//
//  HeapSort.h
//  Huffman Tree
//
//  Created by 蘭希 on 12-10-23.
//  Copyright (c) 2012年 蘭希. All rights reserved.
//

#ifndef HeapSort_HeapSort_h
#define HeapSort_HeapSort_h

#define MAXELEMS 100

typedef struct Node {
    Node* lChild;
    Node* rChild;
    int w;
}Node, *Tree;

typedef Node* Elem;

typedef struct {
    Elem* arrayHeap;
    int length;
}HeapStruct, *Heap;

Heap initHeap();
int addElem(Heap, Elem);
Elem getTop(Heap);
Elem* getElem(Heap, int);
int heapAdjust(Heap, int, int);
int heapUp(Heap);
int heapSort(Heap);

int compareW(Elem& a, Elem& b) {
    if (a->w < b->w) return 1;
    return -1;
}

int output(Heap h) {
    for (int i = 1; i <= h->length; i++) {
        std::cout << h->arrayHeap[i]->w << " ";
    }
    std::cout << "\n";
    return 0;
}

Heap initHeap() {
    Heap p = (Heap)malloc(sizeof(HeapStruct));
    p->arrayHeap = (Elem*)malloc(sizeof(Elem)*MAXELEMS);
    p->length = 0;
    return p;
}

int addElem(Heap h, Elem n) {
    if (h->length >= MAXELEMS -1) return  0;   //数组已满，不能再增加了
    h->length++;
    h->arrayHeap[h->length] = n;
    return 1;
}

Elem getTop(Heap h) {
    Elem top = h->arrayHeap[1];    //取出堆顶元素
    h->arrayHeap[1] = h->arrayHeap[h->length];   //把最后一个元素放到堆顶
    h->length--;
    heapAdjust(h, 1, h->length);
    return top;
}

Elem* getElem(Heap h, int k) {
    if (k >= h->length) return NULL;
    return &h->arrayHeap[k];
}

int heapAdjust(Heap h, int m, int n) {
    //arrayHeap[m~n]中只有首个元素m不满足堆的定义
    h->arrayHeap[0] = h->arrayHeap[m];   //调整m号元素，存放在未使用的0号位置
    int i, j;
    for (i = m, j = 2 * i; j <= n; j *= 2) {
        //i：当前筛选元素，j：i的左孩子，j+1：i的右孩子
        if (j < n && compareW(h->arrayHeap[j], h->arrayHeap[j+1]) == -1) {
            j++;    //j+1节点更大（大顶堆：选出两个里面最大的）
        }
        if (compareW(h->arrayHeap[0], h->arrayHeap[j]) == 1) {
            break;  //h.arrayHeap[0]已经是三个元素中最大的，筛选结束
        }
        h->arrayHeap[i] = h->arrayHeap[j];
        i = j;
    }
    h->arrayHeap[i] = h->arrayHeap[0];
    return 0;
}

int heapUp(Heap h) {   //建立堆
    for (int i = h->length/2; i>0; i--) {
        //(int)length/2是完全二叉树最后一个非叶子节点，该节点之后的元素没有孩子节点，自然满足堆的定义
        heapAdjust(h, i, h->length);
    }
    return 0;
}

int heapSort(Heap h) {
    //选择排序 从无序序列中选最大值（堆顶）加入有序序列
    heapUp(h);
    for (int i=h->length; i>1; i--) {
        h->arrayHeap[0] = h->arrayHeap[i];
        h->arrayHeap[i] = h->arrayHeap[1];
        h->arrayHeap[1] = h->arrayHeap[0];
        //把堆顶（最大值）和当前未经排序的[1~i]中最后一个记录i交换，记录i进入有序序列，调换后[1~i-1]只有[1]不满足堆的定义
        heapAdjust(h, 1, i-1);
    }
    return 0;
}

#endif
