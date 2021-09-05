#include<iostream>
#include<vector>
#include<optional>
/* сдвигаем вправо и влево и если переменная не изменилась ,
   значит в конце был 0 , значит четное*/
bool IsEven(int value) {
    int tmp = value;
    (value>>=1)<<=1;
    return tmp==value;
}

/*Тут все ясно*/
template<class T>
class RingBuffer {
    private:
        std::vector<std::optional<T>> buffer;
        int count;
        int it;
    public:
        RingBuffer(int count_,int it_, std::vector<std::optional<T>> buffer_):
            count(count_),
            it(it_),
            buffer(buffer_){}

        RingBuffer(int count_):
            count(count_),
            it(0), 
            buffer(std::vector<std::optional<T>>(count_, std::nullopt)){}

        void push(T element) {
            it = it%count;
            buffer[it] = element;
            it++;
        }

        void pop() {
            it = (it - 1)%count;
            buffer[it] = std::nullopt;
        }
        ~RingBuffer(){}
};

/* Просто лист только циклический */
template<class T>
class RingBufferSecond {
    private:
        struct Node{
            Node* next;
            std::optional<T> data;
            Node* prev;
        };
        Node* Iterator;
        Node* Base;
        int count;
    public:
        RingBufferSecond(int count_):count(count_){
            Base = new Node{nullptr, std::nullopt, nullptr};
            Iterator = Base;
            for (int i = 0; i < count; ++i) {
                if (i == 0) {
                    Iterator->next = new Node {nullptr, std::nullopt, nullptr};
                    Iterator->data = std::nullopt;
                    Node* prev = Iterator;
                    Iterator = Iterator->next;
                    Iterator->prev = prev;
                } else if (i == (count - 1)) {
                   Iterator->next = Base; 
                    Node* prev = Iterator;
                   Iterator = Iterator->next;
                   Iterator->prev = prev;
                } else {
                    Iterator->next = new Node{nullptr, std::nullopt,nullptr};
                    Node* prev = Iterator;
                    Iterator = Iterator->next;
                    Iterator->prev = prev;
                }
            }
        }

        void push(T element) {
            Iterator->data = element;
            Iterator = Iterator->next;
        }
        void pop() {
            Iterator->data = std::nullopt;
            Iterator = Iterator->prev;
        }
        
        ~RingBufferSecond(){
            for (int i = 0; i < count; i++) {
                Node* prev = Base;
                if (i != count-1)
                    Base = Base->next;
                delete prev;
            }
        }
};

/*
 Вообще не уверен , что это самый маленьkий алгоритм по тикам,
 но он работает за логарифмическое время (nlog(n))
 те любые алгоритмы которые работают за большее точно
 не выигрывают при больших n) все что нужно это маленькое количество 
 локальных переменных bнутри функции и параметров функции чтобы
 не класть много лишнего в стек и заранее приготовленный буффер,
 чтобы перекладывать значения, был план учитывать в каком из
 массивов отсортированные значения и не перекладывть их до
 самой поcледнeй ступени , но тогда все будет зависеть от
 глубины деревьев поэтому тиков больше чем в таком случае,
 при этом если окажется что , отсортированные массивы
 находятся в разных областях, то нужен будет 3ий буффер */
void merchsort(int* a, int* b, int left, int right) {
    if (right - left == 2) { 
        if (a[left] > a[right-1]) {
            int tmp;
            tmp = a[left];
            a[left] = a[right-1];
            a[right-1] = tmp;
        }
    } else if (right - left > 2) {
        int middle = (right + left)/2;
        merchsort(a, b, left, middle);
        merchsort(a, b, middle, right);
        int it1 = left;
        int it2 = middle;
        int i;
        for (i = left; it1 < middle && it2 < right; i++) {
           b[i] = (a[it1] < a[it2])?a[it1++]:a[it2++]; 
        }
        if (it1 == middle) {
            for (;i < right; i++) {
                b[i] = a[it2++];
            }
        } else {
            for (;i < right; i++) {
                b[i] = a[it1++];
            }
        }
        for (i = left; i < right; i++) {
            a[i] = b[i];
        }
    } else {}
}

void sort(int* a, int length) {
    int* b = new int[length];
    merchsort(a,b, 0, length);
    delete [] b;
}
int main() {
    /*int N;
    std::cin >> N;
    std::cout<< IsEven(N) << std::endl;
    */
    /*std::vector<std::optional<int>> a = {std::nullopt, std::nullopt, 1, 2, 3, 4, std::nullopt};
    RingBuffer<int> rb(7);
    rb.push(-1);
    rb.push(0);
    rb.push(2);
    rb.pop();*/
    int N;
    std::cin >> N;
    int * a = new int[N];
    for (int i = 0; i < N; i++) {
        std::cin >> a[i];
    }
    sort(a, N);
    for (int i = 0; i < N; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
