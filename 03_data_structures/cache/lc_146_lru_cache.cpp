/*
题目：LRU 缓存（LeetCode 146）

实现 LRUCache 类：get(key) 返回键对应的值，不存在则返回 -1；put(key,value)
插入或更新数据。容量不足时，删除最久没有使用的键。get 和 put 都应为 O(1)。

示例一：
输入：capacity=2，put(1,1)，put(2,2)，get(1)，put(3,3)，get(2)
输出：get(1)=1，get(2)=-1

示例二：
输入：capacity=1，put(2,1)，get(2)，put(3,2)，get(2)，get(3)
输出：1，-1，2
*/

#include <iostream>
#include <unordered_map>
using namespace std;
struct DLinkNode
{
    int key,val;
    DLinkNode* prev;
    DLinkNode* next;
    DLinkNode():key(0),val(0),prev(nullptr),next(nullptr){}
    DLinkNode(int _key,int _value):key(_key),val(_value),prev(nullptr),next(nullptr){}
};
class LRUCache
{
private:
    unordered_map<int, DLinkNode*> cache; // 哈希双向链表
    DLinkNode *head;
    DLinkNode *tail;
    int size;
    int capacity;

public:
    // 构造函数：初始化类成员变量列表,使用伪头部和尾部节点
    LRUCache(int capacity) : size(0), capacity(capacity)
    {
        head = new DLinkNode();
        tail = new DLinkNode();
        head->next = tail;
        tail->prev = head;
    }

    // 查
    int get(int key)
    {
        if (cache.count(key) != 0) // 查到啦
        {
            DLinkNode *node = cache[key];
            MoveToHead(node);
            return node->val;
        }
        else
        {
            return -1;
        }
    }

    // 改 或 增
void put(int key, int value) {
	if (!cache.count(key))
	{
		//如果key不存在，则创建一个新的节点
		DLinkNode* node = new DLinkNode(key, value);
		//添加进哈希表中
		cache[key] = node;
		//添加至双向链表的头部
		addToHead(node);
		++size;
		if (size > capacity)
		{
			//超出缓存的最大容量
			DLinkNode* removed = removeTail();//删除尾部节点
			//删除哈希表中对应的项
			cache.erase(removed->key);
			//防止内存泄露
			delete removed;
			--size;
		}
	}
	else
	{
		//如果key存在，先通过哈希表定位，再修改value，并移到头部
		DLinkNode* node = cache[key];
		node->val = value;
		MoveToHead(node);
	}
}

    // 将node结点添加到头部
    void addToHead(DLinkNode *node)
    {
       node->prev=head;
       node->next=head->next;
       head->next->prev=node;
       head->next=node;
    }

    // 删除结点
    void Delete(DLinkNode *node)
    {
        node->prev->next=node->next;
        node->next->prev=node->prev;
    }

    // 移动到队头
    void MoveToHead(DLinkNode *node)
    {
        Delete(node);
        addToHead(node);
    }

    // 删除尾部结点
    DLinkNode *removeTail()
    {
        DLinkNode* node=tail->prev;
        Delete(node);
        return node;
    }
};

int main()
{
    cout << "示例一 expected=1 -1 -1 3 4\n";
    LRUCache cache1(2);
    cache1.put(1, 1);
    cache1.put(2, 2);
    cout << "actual=" << cache1.get(1) << ' ';
    cache1.put(3, 3);
    cout << cache1.get(2) << ' ';
    cache1.put(4, 4);
    cout << cache1.get(1) << ' ' << cache1.get(3) << ' ' << cache1.get(4) << '\n';

    cout << "示例二 expected=1 -1 2\n";
    LRUCache cache2(1);
    cache2.put(2, 1);
    cout << "actual=" << cache2.get(2) << ' ';
    cache2.put(3, 2);
    cout << cache2.get(2) << ' ' << cache2.get(3) << '\n';
    return 0;
}


