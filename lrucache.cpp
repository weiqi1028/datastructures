/***********************************************************************************
get(key) - Get the value (will always be positive) of the key if the key exists in
the cache, otherwise return -1.

set(key, value) - Set or insert the value if the key is not already present. When
the cache reached its capacity, it invalidates the least recently used item
before inserting a new item.
************************************************************************************/

class LRUCache{
    struct DoublyLinkedListNode {
        int key;
        int val;
        DoublyLinkedListNode *prev;
        DoublyLinkedListNode *next;
        DoublyLinkedListNode(int k, int v): key(k), val(v), prev(NULL), next(NULL) {}
    };
    
public:
    DoublyLinkedListNode *head;
    std::map<int, DoublyLinkedListNode *> cache;
    int capacity;
    int num;
    LRUCache(int capacity) {
        this->capacity = capacity;
        head = NULL;
        this->num = 0;
    }
    
    int get(int key) {
        if (cache.find(key) == cache.end())
            return -1;
        DoublyLinkedListNode *node = cache[key];
        remove(node);
        addHead(node);
        return node->val;
    }
    
    void set(int key, int value) {
        if (cache.find(key) != cache.end()) {
            DoublyLinkedListNode *node = cache[key];
            remove(node);
            addHead(node);
            node->val = value;
        }
        else {
            DoublyLinkedListNode *newNode = new DoublyLinkedListNode(key, value);
            if (num < capacity) {
                cache[key] = newNode;
                addHead(newNode);
                num++;
            }
            else {
                cache.erase(head->prev->key);
                remove(head->prev);
                addHead(newNode);
                cache[key] = newNode;
            }
        }
    }
    
    void addHead(DoublyLinkedListNode *node) {
        if (head == NULL) {
            head = node;
            head->next = head;
            head->prev = head;
        }
        else {
            DoublyLinkedListNode *tail = head->prev;
            tail->next = node;
            node->next = head;
            node->prev = tail;
            head->prev = node;
            head = node;
        }
    }
    
    void remove(DoublyLinkedListNode *node) {
        if (node == head)
            head = head->next;
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
};