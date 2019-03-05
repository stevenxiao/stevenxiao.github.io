/*
 * @lc app=leetcode id=2 lang=cpp
 *
 * [2] Add Two Numbers
 *
 * https://leetcode.com/problems/add-two-numbers/description/
 *
 * algorithms
 * Medium (30.61%)
 * Total Accepted:    774.6K
 * Total Submissions: 2.5M
 * Testcase Example:  '[2,4,3]\n[5,6,4]'
 *
 * You are given two non-empty linked lists representing two non-negative
 * integers. The digits are stored in reverse order and each of their nodes
 * contain a single digit. Add the two numbers and return it as a linked list.
 * 
 * You may assume the two numbers do not contain any leading zero, except the
 * number 0 itself.
 * 
 * Example:
 * 
 * 
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 * Explanation: 342 + 465 = 807.
 * 
 * 
 */

/**
 * Definition for singly-linked list.
 **/

// #include <iostream>

// using namespace std;

// struct ListNode
// {
//     int val;
//     ListNode *next;
//     ListNode(int x) : val(x), next(nullptr) {}
// };

int length(ListNode *l)
{
    int len = 0;
    while (l)
    {
        len++;
        l = l->next;
    }
    return len;
}

class Solution
{
  public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        if (!l1)
            return l2;
        if (!l2)
            return l1;
        ListNode *tl1 = l1;
        ListNode *tl2 = l2;
        ListNode *pre = nullptr;

        int ex = 0;
        if (length(l1) < length(l2))
        {
            tl1 = l2;
            tl2 = l1;
        }
        ListNode *ret = tl1;
        while (tl1 && tl2)
        {
            tl1->val = tl1->val + tl2->val + ex;
            ex = tl1->val / 10;
            tl1->val = tl1->val % 10;
            pre = tl1;
            tl1 = tl1->next;
            tl2 = tl2->next;
        }

        while (tl1)
        {
            tl1->val = tl1->val + ex;
            ex = tl1->val / 10;
            tl1->val = tl1->val % 10;
            pre = tl1;
            tl1 = tl1->next;
        }
        if (ex)
        {
            ListNode *node = new ListNode(ex);
            pre->next = node;
            pre = node;
            ex = 0;
        }
        return ret;
    }
};

// int main()
// {
//     ListNode *r = new ListNode(5);
//     //r->next = new ListNode(4);
//     //r->next->next = new ListNode(3);

//     ListNode *r2 = new ListNode(5);
//     //r2->next = new ListNode(6);
//     //r2->next->next = new ListNode(4);

//     r = Solution().addTwoNumbers(r, r2);

//     while (r)
//     {
//         cout << r->val << "\t";
//         r = r->next;
//     }
// }
