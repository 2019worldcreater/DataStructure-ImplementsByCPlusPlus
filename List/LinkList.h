/*����һ���������̬����̬������������ģ�������������е�Ԫ��ΪNode��Node{data��index}; indexΪ��һ��Node�������е��±�
 * ����Ϊ��Щû��ָ�����Ե�����׼���ģ�
 * �ŵ㣺 ������������ɾ�ģ���̬����ֻ��Ҫ��indexֵ
 * ȱ�㣺�����ȱ����ơ�ʧȥ��˳�����������
 * ��Ҫ������������˼��
 *
 * ������һЩ ˫��ѭ������fore��next��������ѭ���б�tail->next=top�� �������⣺Լɪ�򻷣�ɶ�ģ��Լ��˽���У���һ����
 * ѭ���������������ͷָ�����βָ�룬��ô���Ժܷ������β��㣬Ҳ���Ժܷ���ϲ���������һ���˵�βָ����һ����ͷ��
 *
 * ��ͬ�����������ʺϵ�Ӧ������
 * */

#ifndef CLIONCPP_LINKLIST_H
#define CLIONCPP_LINKLIST_H

#include <cstdlib>
#include "../Tool/Status.h"
#include "../Tool/LinkNode.h"

using namespace StatusTool;

template<typename T>
class LinkList {
private:
    //�����еĽڵ㼴 Node<T>,����������data��ָ����next, data���ڱ���������Ϣ��nextָ����һ���ڵ�
    typedef Node<T> *nodePtr; //nodePtr === Node<T> *
    nodePtr head = nullptr; //ָ��ͷ����ͷָ�룬 ����ͷ�ڵ㣬��Щ�����߼�������
    int length = 0; //����ͷ����Ԫ�ظ���

    //�����±�index�Ľڵ��ָ��,ʧ�ܷ���null,�����Դ˻��ͷ���
    nodePtr getNodePtrByIndex(int index) {
        nodePtr node = nullptr;
        if (isValid(index)) {
            int i = -1;
            node = head;
            bool isFind = true;
            while (++i <= index) {
                if (node->next == nullptr) { //���ܳ���
                    isFind = false;
                    break;
                }
                node = node->next;
            }
            node = isFind ? node : nullptr; //ÿ�ζ��ɹ����Ż��� i == index
        }
        return node;
    }

    //�ڶ��д�������ڵ㣬����ֵ������, ������ָ�룬ע��ʧ�ܵĻ�����nullptr
    nodePtr createNode(T data) {
        nodePtr node = (nodePtr) malloc(sizeof(Node<T>)); //���ܷ���ָ��ջ�ڴ��ָ��
        if (node != nullptr) {
            node->data = data;
            node->next = nullptr;
        }
        return node;
    }

public:
    //�±�index�Ƿ���Ч(0~length-1),һ���Ǻ�����������ʱ���õģ�����head!=nullptr And top->next!=nullptrҲ��������
    bool isValid(int index) {
        //���ö�·&&���ص㣬���head!=nullptr,�����жϲ�����У�����head->next�������
        return isLinkListInitDone() && head->next != nullptr && index < length && index > -1;
    }

    //����ڵ�Node�д洢��T����������, �ܸ���
    LinkList(T *elements, int length) {
        head = createNode(elements[0]); //��ʼ��ͷ��㣬��Ϊһ��Ҫ���Σ�������㴫�˸�
        if (head != nullptr) {
            //β�巨����ڵ�
            nodePtr tail = head; //���һ���ڵ�
            int len = length;
            while (length--) { //length��
                tail->next = createNode(elements[len - length - 1]); //β���ڵ��nextָ���½ڵ�, ������ռ䲻����
                if (tail->next != nullptr) {
                    tail = tail->next; //����β���ڵ�
                    this->length++;
                }
            }
        }

    }

    LinkList() {
        T item;
        head = createNode(item); //Ϊͷ������ռ�
    }

    //����ͷ�������Ƿ�ɹ�
    bool isLinkListInitDone() {
        return head != nullptr;
    }

    ~LinkList() {
        releaseLinkList();
    }

    //�������������ͷ���
    void cleanLinkList() {
        if (isLinkListInitDone()) { //top->next���ܱ���
            if (head->next != nullptr) {
                int len = releaseLinkNodeFrom(&(head->next), this->length); //����ָ��ָ���ָ��,�������ڲ��ı�ָ���ֵ
                if (head->next == nullptr && len != -1) {
                    this->length = len;
                }
            }
        }
    }

    //�������
    void releaseLinkList() {
        if (isLinkListInitDone()) {
            int len = releaseLinkNodeFrom(&head, this->length);
            if (head == nullptr && len != -1) {
                this->length = len;
            }
        }
    }

    //����ֵ�ı�ɽڵ�ֵ����ֵ��ֵ��old
    bool modifyDataByIndex(int index, T data) {
        nodePtr node = getNodePtrByIndex(index);
        if (node != nullptr) {
            node->data = data;
            return true;
        }
        return false;
    }

//���ӽڵ㵽�������,trueΪ�ɹ�
    bool addNode(T data) {
        nodePtr tail;
        if (length == 0)
            tail = head;
        else
            tail = getNodePtrByIndex(length - 1); //���һ���ڵ�
        if (tail != nullptr) {
            nodePtr node = createNode(data);
            if (node != nullptr) {
                tail->next = node;
                this->length++;
                return true;
            }
        }
        return false;
    }

//ɾ���±�Ϊindex�Ľڵ㣬���߼��ϵ�index+1���������ڵ�ֵ��ֵ��data���ɹ�true
    bool deleteNodeByIndex(int index, T *data) {
        nodePtr preNode = nullptr;
        if (index == 0) //getNode���ܷ���ͷ���
            preNode = head;
        else
            preNode = getNodePtrByIndex(index - 1); //ɾ���ڵ��ǰһ��
        if (preNode != nullptr) {
            if (preNode->next != nullptr) {
                nodePtr node = preNode->next;
                nodePtr next = node->next;
                *data = node->data;
                preNode->next = next;
                free(node); //�ͷ�index�ڵ�
                this->length--;
                return true;
            }
        }
        return false;
    }

//����ڵ㵽�±�index����ԭλ�õĽڵ㿿��һλ���ɹ�����true
//��ʱ��index����Ϊ�����ȣ���addNode
    bool insertInto(int index, T data) {
        if (index == length)
            return addNode(data);
        else {
            nodePtr preNode = nullptr;
            if (index == 0)
                preNode = head;
            else
                preNode = getNodePtrByIndex(index - 1);
            if (preNode != nullptr) {
                nodePtr next = preNode->next; //ԭλ�ýڵ�
                if (next != nullptr) {
                    nodePtr node = createNode(data);
                    if (node != nullptr) {
                        node->next = next;
                        preNode->next = node;
                        this->length++;
                        return true;
                    }
                }
            }
        }
        return false;
    }

//����index(0~len-1)�ڵ�����ݣ��ɹ�����true
    bool getDataByIndex(int index, T *data) {
        nodePtr node = getNodePtrByIndex(index);
        if (node != nullptr) {
            *data = node->data;
            return true;
        }
        return false;
    }

//�����ȣ�-1���������ʼ��ʧ�ܣ�0 ���������
    int getLength() {
        return isLinkListInitDone() ? length : -1;
    }

//����δ��ʼ�����ʱ��Ϊtrue
    bool isEmpty() {
        return !isLinkListInitDone() || length < 1;
    }

//���ؽڵ��е�һ��������data��ȵĽڵ���±꣬������ͷ�������index+1��������ֵֻ���� 0~len-1
//�Ƽ����ص��±�ʹ�� isValid����
    int getIndexOfData(T data) {
        int index = 0;
        nodePtr node = getNodePtrByIndex(index);
        while (node != nullptr && node->data != data && node->next != nullptr) {
            node = node->next;
            index++;
        }
        if (node != nullptr && node->data == data)
            return index;

        return -1;
    }

//������������ֵ��˳��洢��all�У����� T r[getLength()], �����ܸ���
    int getAllData(T *all) {
        if (!isEmpty()) {
            int i = 0;
            nodePtr node = head;
            while (i < getLength()) {
                node = node->next;
                if (node == nullptr)
                    break;
                else
                    all[i] = node->data;
                i++;
            }
            return i;
        }
        return 0;
    }

};

#endif //CLIONCPP_LINKLIST_H
