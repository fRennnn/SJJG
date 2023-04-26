#include<iostream>
using namespace std;

typedef int Rank;
#define DEFAULT_CAPACITY 3

template<typename T> class Vector{
protected:

    Rank _size;int _capacity;T* _elem;

    void copyFrom(T const * A,Rank lo,Rank hi);
    void expand();
    void shrink();
    bool bubble (Rank lo,Rank hi);
    void bubbleSort(Rank lo,Rank hi);
    Rank max(Rank lo,Rank hi);
    void selectionSort(Rank lo,Rank hi);
    void mergeSort(Rank lo,Rank hi);
    void quickSort(Rank lo,Rank hi);
    Rank partition(Rank lo,Rank hi);
    void heapSort(Rank lo,Rank hi);

public:
Vector(int c = DEFAULT_CAPACITY,int s = 0; T v = 0)
{
    _elem = new T[_capacity = c];
    for(_size = 0;_size <s;_elem[_size++] = v);
}
Vector(T const* A ,Rank n){copyFrom(A,0,n);}
Vector(T const* A,Rank lo,Rank hi){copyFrom(A,lo,hi);}
Vector(Vector<T> const& V){copyFrom(V._elem,0,V._size);}//向量整体复制
Vector(Vector<T> const& V,Rank lo,Rank hi){copyFrom(V._elem,lo,hi);}

~Vector(){delete [] _elem;}

//只读访问接口
Rank size() const {return _size;}
bool empty() const{return !_size;}
int disordered() const;
Rank find ( T const& e) const {return find(e,0,_size);}
Rank find ( T const& e,Rank lo,Rank hi) const;
Rank search(T const& e) const
{return (0>= _size)? -1 : search(e,0,_size);}
Rank search(T const& e,Rank lo,Rank hi) const;

//可写访问接口
T& operator[] (Rank r) const;//重载下标操作符，可以类似于数组形式的引用各元素
Vector<T> & operator= (Vector<T> const&);//重载赋值操作符，以便直接克隆向量
T remove(Rank r);
int remove(Rank lo,Rank hi);
Rank insert(T const& e){return insert(_size,e);}
void sort(Rank lo,Rank hi);
void sort(){sort(0,_size);}
void unsort(Rank lo,Rank hi);
void unsort(){unsort(0,_size);}
int deduplicate();
int uniquify();

//遍历
void traverse( void(*)(T&));
template<typename VST> void traverse(VST &);
};

template<typename T>
void Vector<T>::copyFrom(T const* A,Rank lo,Rank hi){
    _elem = newT[_capacity = 2*(hi-lo)];_size = 0;
    while(lo<hi){
        _elem[_size++] = A[lo++];
    }
}

template<typename T>Vector<T>& Vector<T>::operator= (Vector<T> const& V){
    if(_elem) delete [] _elem;
    copyFrom (V._elem,0,V.size());
    return *this;
}

template<typename T> void Vector<T>::expand(){
    if(_size < _capacity) return;
    if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T* oldElem = _elem; _elem = new T[_capacity <<= 1];
    for(int i=0;i<_size;i++)
      _elem[i] = oldElem[i];
    delete [] oldElem;
}

template<typename T> void Vector<T>::shrink(){
    if(_capacity < DEFAULT_CAPACITY<<1)return;
    if(_size << 2 > _capacity) return;
    T* oldElem = _elem; _elem = new T[_capacity >>=1 ];
    for(int i=0;i<_size;i++) _elem[i] = oldElem[i];
    delete [] oldElem;
}

template<typename T> T& Vector<T>::operator[](Rank r)const
{return _elem[r];}

/*template<typename T>const T & Vector<T>::operator[](Rank r)const
{return _elem[r];}*/

template<typename T> void permute(Vector<T> &V){
    for(int i=V.size();i>0;i--)
    swap(V[i-1],V[rand()%i]);
}

template<typename T> void Vector<T>::unsort(Rank lo,Rank hi){
    T* V = _elem + lo;
    for(Rank i = hi-lo;i>0;i--){
        swap(V[i-1],V[rank() % i]);
    }
}

template<typename T> static bool lt(T *a,T *b){return lt(*a,*b);}
template<typename T> static bool lt(T &a,T &b){return a<b;}
template<typename T> static bool eq(T *a,T *b){return eq(*a,*b);}
template<typename T> static bool eq(T &a,T &b){return a == b;}

template<typename T>//无序向量的顺序查找: 返回最后一个元素e的位置;失败时返回lo-1
Rank Vector<T>::find(T const& e,Rank lo,Rank hi)const{
    while( (lo<hi--) && (e != _elem[hi]) )//从后往前，顺序查找
    return hi;//若hi < lo，则意味失败;否则hi即命中元素的秩
}
 
template<typename T>
Rank Vector<T>::insert(Rank r,T const & e){
    expand();
    for(int i = _size;i>r;i--) _elem[i] = _elem[i-1];
    _elem[r] = e;_size++;
    return r;
} 

template<typename T> int Vector<T>::remove(Rank lo,Rank hi){
    if(lo==hi) return 0;
    while(hi<_size) _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return hi-lo;
}

template<typename T> T Vector<T>::remove(Rank r){
    T e = _elem[r];
    remove(r,r+1);
    return e;
}
//唯一化
template<typename T> int Vector<T>::deduplicate(){//删除无序向量中重复元素(高效版)
    int oldSize = _size;//记录原规模
    Rank i = 1;
    while(i<_size)
    (find(_elem[i],0,i)<0?
    i++:remove(i));
    return oldSize - _size;//向量规模变化量，即被删除元素总数
}

template<typename T> void Vector<T>::traverse(void (*visit)(T&))
{for(int i = 0;i<_size;i++)visit(_elem[i]);}//遍历向量

template<typename T> template<typename VST>
void Vector<T>::traverse(VST& visit)
{for(int i =0;i<_size;i++)visit(_elem[i]);}

template<typename T>  struct Increase
{ virtual void operator() (T &e) {e++;} };

template<typename T>  void increase(Vector<T> &V)
{ V.traverse(Increase<T>()); }

template<typename T> 
int Vector<T>::Disordered()
{
    int n = 0;
    for(int i = 1;i<_size;i++)
    if(_elem[i-1]>_elem[i])n++;
    return n;
}

template<typename T> int Vector<T>::uniquify(){
    Rank i = 0,j = 0;
    while(++j < _size)
      if(_elem[i] != _elem[j])
      _elem[++i] = _elem[j];
    _size = ++i;shrink();
    return j-i;
}
