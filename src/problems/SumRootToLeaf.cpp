#include <iostream>
#include <vector>
#include <queue>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void Print(TreeNode* current)
{
    if (current != NULL)
    {
        std::cout << current->val << " ";
        Print(current->left);
        Print(current->right);
    }
}

TreeNode* Add(TreeNode* parent, int value, int order)
{
    TreeNode* newCell;
    if (value == -1)
        return NULL;
    newCell = new TreeNode(value);
    if (parent != NULL)
    {
        if (order == 0)
            parent->left = newCell;
        else
            parent->right = newCell;
    }
    return newCell;
}

bool IsLeaf(TreeNode* current)
{
    if (current != NULL)
        if (current->left == NULL && current->right == NULL)
            return true;
    return false;
}

void Find(TreeNode* subRoot, std::vector<int> number, std::vector<std::vector<int>>& allNumbers)
{
    if (subRoot != NULL)
    {
        number.push_back(subRoot->val);
        if (IsLeaf(subRoot))
            allNumbers.push_back(number);
        else
        {
            Find(subRoot->left, number, allNumbers);
            Find(subRoot->right, number, allNumbers);
        }
    }
}

int sumNumbers(TreeNode* A) 
{
    int sum(0);
    std::vector<int> number;
    std::vector<std::vector<int>> allSequences;

    Find(A, number, allSequences);
    
    for (auto& row : allSequences)
    {
        int n(0), dec(row.size() - 1);
        for (auto& num : row)
        {
            int powerSet(1);
            for (int i = 0; i < dec; i++)
            {
                powerSet *= 10;
                powerSet %= 1003;
            }

            n += (num % 1003) * powerSet;
            dec--;
        }
        sum += n;
        sum = sum % 1003;
    }

    return sum;
}

int main_SumRootToLeaf()
{

    // 11 1 2 3 -1 -1 4 -1 -1 5 -1 -1
    int n;
    TreeNode* root, * aux(NULL);
    std::queue<TreeNode*> fila;
    std::cin >> n;

    int val;
    std::cin >> val;
    root = Add(NULL, val, 0);
    fila.push(root);
    for (int i = 1; i < n;)
    {
        aux = fila.front();
        fila.pop();
        if (aux == NULL)
            continue;
        for (int j = 0; j < 2; j++, i++)
        {
            std::cin >> val;
            fila.push(Add(aux, val, j));
        }
    }

    Print(root);
    std::cout << std::endl;

    std::cout << sumNumbers(root) << std::endl;

    return 0;
}