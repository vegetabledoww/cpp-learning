#include <iostream>
#include <unordered_map>
using namespace std;

// 双向链表节点
struct DListNode {
    int key;
    int value;
    DListNode* prev;
    DListNode* next;
    
    DListNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    DListNode(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

// LRU缓存类
class LRUCache {
private:
    unordered_map<int, DListNode*> cache;  // 哈希表：key -> 节点指针
    DListNode* head;  // 伪头部节点
    DListNode* tail;  // 伪尾部节点
    int capacity;     // 容量
    int size;         // 当前大小

public:
    // 构造函数：初始化容量，创建伪头尾节点
    LRUCache(int cap) : capacity(cap), size(0) {
        head = new DListNode();
        tail = new DListNode();
        head->next = tail;
        tail->prev = head;
    }

    // 获取key对应的value
    int get(int key) {
        // 检查key是否存在
        if (cache.find(key) == cache.end()) {
            return -1;  // 不存在返回-1
        }
        
        // 存在则获取节点，移到头部，返回value
        DListNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }

    // 插入或更新key-value
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            // key已存在：更新value并移到头部
            DListNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        } else {
            // key不存在：创建新节点
            DListNode* newNode = new DListNode(key, value);
            
            // 插入到头部
            addToHead(newNode);
            cache[key] = newNode;
            size++;
            
            // 如果超出容量，删除尾部节点
            if (size > capacity) {
                DListNode* removed = removeTail();
                cache.erase(removed->key);
                delete removed;
                size--;
            }
        }
    }

private:
    // 添加节点到头部
    void addToHead(DListNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    // 删除节点
    void removeNode(DListNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // 移动到头部
    void moveToHead(DListNode* node) {
        removeNode(node);
        addToHead(node);
    }

    // 删除尾部节点
    DListNode* removeTail() {
        DListNode* node = tail->prev;
        removeNode(node);
        return node;
    }
};

// 测试代码
int main() {
    // 测试用例1：LeetCode示例
    cout << "========== 测试用例1 ==========" << endl;
    LRUCache* lRUCache = new LRUCache(2);
    
    lRUCache->put(1, 1);  // 缓存是 {1=1}
    lRUCache->put(2, 2);  // 缓存是 {2=2, 1=1}
    
    cout << "get(1): " << lRUCache->get(1) << endl;  // 返回 1
    
    lRUCache->put(3, 3);  // 该操作会使得关键字 2 作废，缓存是 {3=3, 1=1}
    
    cout << "get(2): " << lRUCache->get(2) << endl;  // 返回 -1 (未找到)
    
    lRUCache->put(4, 4);  // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    
    cout << "get(1): " << lRUCache->get(1) << endl;  // 返回 -1 (未找到)
    cout << "get(3): " << lRUCache->get(3) << endl;  // 返回 3
    cout << "get(4): " << lRUCache->get(4) << endl;  // 返回 4
    
    cout << endl;

    // 测试用例2：容量为1
    cout << "========== 测试用例2 (capacity=1) ==========" << endl;
    LRUCache* cache2 = new LRUCache(1);
    
    cache2->put(2, 1);
    cout << "get(2): " << cache2->get(2) << endl;  // 返回 1
    
    cache2->put(3, 2);
    cout << "get(2): " << cache2->get(2) << endl;  // 返回 -1
    cout << "get(3): " << cache2->get(3) << endl;  // 返回 2
    
    cout << endl;

    // 测试用例3：容量为3
    cout << "========== 测试用例3 (capacity=3) ==========" << endl;
    LRUCache* cache3 = new LRUCache(3);
    
    cache3->put(1, 1);
    cache3->put(2, 2);
    cache3->put(3, 3);
    
    cout << "get(1): " << cache3->get(1) << endl;  // 返回 1
    cout << "get(2): " << cache3->get(2) << endl;  // 返回 2
    
    cache3->put(4, 4);  // key=3会被删除
    
    cout << "get(3): " << cache3->get(3) << endl;  // 返回 -1
    cout << "get(4): " << cache3->get(4) << endl;  // 返回 4
    
    cout << "\n测试完成！" << endl;
    
    return 0;
}

