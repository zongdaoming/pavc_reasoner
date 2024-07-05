#include<iostream>
#include<bits/stdc++.h>
#include<string>
using namespace std;

struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 寻找回文串的核心思想是从中心向两端扩展：
string palindrome(string s, int left, int left){
    while(left >= 0 && right<s.length()
        && s[left] == s[right]){
        // 双指针向两边展开
        left--;
        right++;
    }
    // 返回以s[left]和s[right]为中心的最长palindrome
    return s.substr(left+1, right-left+1);
}

bool isPalindrome(string s){
    // 一左一右两个指针相向而行
    int left = 0, right = s.length() - 1;
    while(left<right){
        if(s[left]!=s[left]){
            return false;
        }
    left++;
    right--;
    }
    return true;
}


// 首先，我们要实现一个 reverse 函数反转一个区间之内的元素。在此之前我们再简化一下，给定链表头结点，如何反转整个链表？
// 使用迭代的方案

ListNode* reverse(ListNode* a){
    ListNode *pre, *cur, *nex;
    pre = nullptr;
    cur = a;
    nex = a;
    while(cur!=nullptr){
        nex = cur->next;
        // 逐点反转
        cur->next = pre;
        // 更新指针位置
        pre = cur;
        cur = nex;
    }
    // 返回反转后的头节点
    return pre;

}


// 这次使用迭代思路来实现的，借助动画理解应该很容易。

// 「反转以 a 为头结点的链表」其实就是「反转 a 到 null 之间的结点」，那么如果让你「反转 a 到 b 之间的结点」，你会不会？


// 反转区间 [a, b) 的元素，注意是左闭右开
ListNode* reverse(ListNode* a, ListNode* b) {
    ListNode *pre, *cur, *nxt;
    pre = nullptr; cur = a; nxt = a;
    // while 终止的条件改一下就行了
    while (cur != b) {
        nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    // 返回反转后的头结点
    return pre;
}

// 逻辑上最容易理解的
ListNode* reverseKGroup(ListNode* head, int k){
    if(head == nullptr)  return nullptr;
    // 区间 [a, b) 包含 k 个待反转元素
    ListNode *a, *b;
    a=b=head;
    for(int i =0; i<k; i++){
        // 不足k个，不需要反转，base case
        if(b==nullptr) return head;
        b = b->next;
    }
    // 反转前k个元素
    ListNode* newHead = reverse(a,b);
    a->next = reverseKGroup(b,k);
    return newHead;
}



