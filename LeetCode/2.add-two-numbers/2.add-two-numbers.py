#
# @lc app=leetcode id=2 lang=python3
#
# [2] Add Two Numbers
#
# https://leetcode.com/problems/add-two-numbers/description/
#
# algorithms
# Medium (30.61%)
# Total Accepted:    774.6K
# Total Submissions: 2.5M
# Testcase Example:  '[2,4,3]\n[5,6,4]'
#
# You are given two non-empty linked lists representing two non-negative
# integers. The digits are stored in reverse order and each of their nodes
# contain a single digit. Add the two numbers and return it as a linked list.
#
# You may assume the two numbers do not contain any leading zero, except the
# number 0 itself.
#
# Example:
#
#
# Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
# Output: 7 -> 0 -> 8
# Explanation: 342 + 465 = 807.
#
#
#
# Definition for singly-linked list.
#class ListNode(object):
#    def __init__(self, x):
#        self.val = x
#        self.next = None


class Solution:
    def addTwoNumbers(self, l1, l2):
        ex = 0
        ret = None
        last = None
        while (l1 and l2):
            num = l1.val + l2.val + ex
            ex, num = num // 10, num % 10
            node = ListNode(num)
            if not ret:
                ret = node
                last = ret
            else:
                last.next = node
                last = node
            l1 = l1.next
            l2 = l2.next
        if l1:
            while l1:
                num = l1.val + ex
                ex, num = num // 10, num % 10
                node = ListNode(num)
                if not ret:
                    ret = node
                    last = node
                else:
                    last.next = node
                    last = node
                l1 = l1.next
        else:
            while l2:
                num = l2.val + ex
                ex, num = num // 10, num % 10
                node = ListNode(num)
                if not ret:
                    ret = node
                    last = node
                else:
                    last.next = node
                    last = node
                l2 = l2.next
        if ex:
            node = ListNode(ex)
            last.next = node
            last = node
        return ret
