#include <iostream>

using namespace std;

class Node
{
public:
    Node* prev, * next;
    char digit;
    Node(char d)
    {
        digit = d;
        prev = next = NULL;
    }
};

class List
{
public:
    Node* front, * back;

    List()
    {
        front = NULL;
        back = NULL;
    }

    ~List()
    {
        Node* current;
        while (front != NULL)
        {
            current = front;
            front = front->next;
            delete current;
        }
    }

    void Push(char digit)
    {
        Node* newNode;
        newNode = new Node(digit);

        newNode->prev = back;
        if (back != NULL)
            back->next = newNode;
        back = newNode;

        if (front == NULL)
            front = newNode;
    }

    void Remove(Node* node)
    {
        if (node == back)
            back = back->prev;
        if (node == front)
            front = front->next;
        if (node->prev != NULL)
            (node->prev)->next = node->next;
        if (node->next != NULL)
            (node->next)->prev = node->prev;
        delete node;
    }
};

class Solution
{
public:
    string removeKdigits(string num, int k)
    {
        List newNum;
        int size = num.length() - k;

        for (int i = 0; i < size; i++)
            newNum.Push(num[i]);

        for (int i = size; i < num.size(); i++)
        {
            char removedDigit(num[i]), insertDigit(num[i]);
            Node* nodeRemoved(NULL), * currentNode(newNum.back);
            while (currentNode != NULL)
            {
                if (removedDigit < currentNode->digit)
                    nodeRemoved = currentNode;
                removedDigit = currentNode->digit;
                currentNode = currentNode->prev;
            }

            if (nodeRemoved != NULL)
            {
                newNum.Remove(nodeRemoved);
                newNum.Push(insertDigit);
            }
        }

        string out("");
        Node* currentNode(newNum.front);
        while (currentNode != NULL)
        {
            if (out.length() > 0 || currentNode->digit != '0')
                out.push_back(currentNode->digit);
            currentNode = currentNode->next;
        }

        if (out.length() > 0)
            return out;
        else
            return "0";
    }
};

int main_RemoveKDigits()
{
    Solution s;

    cout << s.removeKdigits("10200", 1);

    return 0;
}