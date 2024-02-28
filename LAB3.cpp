#include <iostream>
using namespace std;

typedef struct node
{
    char elem;
    node *left;
    node *right;
    node *parent;
} BiTree;

void Input(char *a, int num);//输入前序遍历与中序遍历
int index_root_in_b(char ROOT, char *b, int num);//输入的元素在中序遍历的位置
void create(BiTree *ROOT, int index_root, char *a, char *b, int num, int LEN_OF_LEFT, int LEN, int ROOT_IN_B);//创建数
void POST_ORDER_traversal(BiTree *ROOT);//后序遍历
void LEVEL_output(BiTree *ROOT , int level);//输出level层的元素
void PATH_TO_ELEM(BiTree *T);//输出到该节点的路径
void FIND_THE_ELEM(BiTree *ROOT, char elem,BiTree ** T);//寻找目标元素所在节点
int LEVEL_OF_TREE(BiTree *ROOT);//求节点高度
void LEVEL_traversal(BiTree * ROOT);//层次遍历
int main()
{
    int num;
    char ELEM_TO_FIND;
    cout << "Input the number of elements:";
    cin >> num;
    char *a = (char *)malloc(sizeof(char) * num);
    char *b = (char *)malloc(sizeof(char) * num);
    Input(a, num);
    Input(b, num);
    cout << "Input the elem to find:";
    cin >> ELEM_TO_FIND;
    char ROOT_elem = a[0];
    int index_root = 0;
    BiTree *ROOT = (BiTree *)malloc(sizeof(BiTree));
    ROOT->elem = ROOT_elem;
    ROOT->left = NULL;
    ROOT->right = NULL;
    ROOT->parent = NULL;
    create(ROOT, 0, a, b, num, index_root_in_b(ROOT->elem, b, num), num, -1);
    cout << "the post order traversal:" << endl;
    POST_ORDER_traversal(ROOT);
    cout << endl;
    BiTree * T = new BiTree;
    cout << "the level order traversal:" << endl;
    LEVEL_traversal(ROOT);
    FIND_THE_ELEM(ROOT , ELEM_TO_FIND , &T);
    if (T->elem >= 'A' && T->elem <= 'Z')
    {
        cout << "a path to the elem to find is:" << endl;
        PATH_TO_ELEM(T);
        cout << endl;
    }
    else cout << "NOT FOUND";
    return 0;
}

void Input(char *a, int num)
{
    cout << "Input:";
    for (int i = 0; i < num; i++)
    {
        cin >> a[i];
    }
}

int index_root_in_b(char ROOT, char *b, int num)
{
    int index;
    for (int i = 0; i < num; i++)
    {
        if (ROOT == b[i])
        {
            index = i;
            break;
        }
    }
    return index;
}

void create(BiTree *ROOT, int index_root, char *a, char *b, int num, int LEN_OF_LEFT, int LEN, int ROOT_IN_B)
{

    //int ROOT_INDEX_IN_B = index_root_in_b(ROOT->elem, b, num);
    BiTree *left = new BiTree;  //(BiTree *)malloc(sizeof(BiTree));
    BiTree *right = new BiTree; //(BiTree *)malloc(sizeof(BiTree));
    if (left && right)
    {
        left->left = NULL;
        left->right = NULL;
        if (LEN_OF_LEFT <= 0)
            left = NULL;
        else
            left->elem = a[index_root + 1];
        right->left = NULL;
        right->right = NULL;
        if (LEN == 1 + LEN_OF_LEFT)
            right = NULL;
        else
            right->elem = a[index_root + 1 + LEN_OF_LEFT];
        if (left)
        {
            ROOT->left = left;
            left->parent = ROOT;
        }
        if (right)
        {
            ROOT->right = right;
            right->parent = ROOT;
        }
        if (left)
        {
            //if (index_root_in_b(left->elem, b, num) > ROOT_IN_B)
                create(left, index_root + 1, a, b, num, index_root_in_b(left->elem, b, num) - ROOT_IN_B - 1, LEN_OF_LEFT, ROOT_IN_B);
            //else
                //create(left, index_root + 1, a, b, num, index_root_in_b(left->elem, b, num), LEN_OF_LEFT, ROOT_IN_B);
        }
        if (right)
        {    
            ROOT_IN_B = index_root_in_b(ROOT->elem, b, num);
            create(right, index_root + 1 + LEN_OF_LEFT, a, b, num, index_root_in_b(right->elem, b, num) - 1 - ROOT_IN_B, LEN - LEN_OF_LEFT - 1, ROOT_IN_B);
        }
    }
}

void POST_ORDER_traversal(BiTree *ROOT)
{
    //cout << ROOT->elem;
    if (ROOT->left)
        POST_ORDER_traversal(ROOT->left);
    //cout << ROOT->elem;
    if (ROOT->right)
        POST_ORDER_traversal(ROOT->right);
    cout << ROOT->elem;
}

void LEVEL_output(BiTree *ROOT , int level)
{
    if (level == 1)cout << ROOT->elem;
    else if (level > 1)
    {
        if (ROOT->left)LEVEL_output(ROOT->left , level - 1);
        if (ROOT->right)LEVEL_output(ROOT->right , level - 1);
    }
}

void FIND_THE_ELEM(BiTree *ROOT, char elem,BiTree ** T)
{
    if (ROOT->elem == elem)*T = ROOT;
    else 
    {
        if (ROOT->left)FIND_THE_ELEM(ROOT->left , elem , T);
        if (ROOT->right)FIND_THE_ELEM(ROOT->right , elem , T);
    }
}

void PATH_TO_ELEM(BiTree *T)
{
    if (T->parent)
    {
        PATH_TO_ELEM(T->parent);
    }
    cout << T->elem;
}

int LEVEL_OF_TREE(BiTree *ROOT)
{
    if (ROOT == NULL) return 0;
    int height_of_left = LEVEL_OF_TREE(ROOT->left);
    int height_of_right = LEVEL_OF_TREE(ROOT->right);
    return height_of_left >= height_of_right ? height_of_left + 1 : height_of_right + 1; 
}

void LEVEL_traversal(BiTree * ROOT)
{
    int level = LEVEL_OF_TREE(ROOT);
    for (int i = 1;i <= level;i++)
    {
        LEVEL_output(ROOT , i);
        cout << endl;
    }
}
//ABDHIEJKCFLMGNO
//HDIBJEKALFMCNGO