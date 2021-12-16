#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
template<typename T>
class vector {
    T **vector_storage;
    int vector_size;
    int now_size;
public:
    /**
     * TODO
     * a type for actions of the elements of a vector, and you should write
     *   a class named const_iterator with same interfaces.
     */
    /**
     * you can see RandomAccessIterator at CppReference for help.
     */
    void shrink_storage(){
            T **tmp_storage;
            //tmp_storage= new T[now_size];
            build_storage(tmp_storage,now_size);
            int tmp_size=now_size;
            for(int i=0;i<now_size;i++){
                tmp_storage[i]=new T(*vector_storage[i]);
            }
            //delete []vector_storage;
            delete_storage(vector_storage,now_size);
            //vector_storage= new T[2*now_size];
            vector_size=2*now_size;
            build_storage(vector_storage,vector_size);
            for(int i=0;i<now_size;i++){
                vector_storage[i]=new T(*tmp_storage[i]);
            }
            delete_storage(tmp_storage,tmp_size);
    }
 
    class const_iterator;
    class iterator {
    private:
        /**
         * TODO add data members
         *   just add whatever you want.
         */
        int index;
        T **vector_type;
        // template<T>
        friend iterator vector<T>::insert(iterator pos, const T &value);
        // template<T>
        friend iterator vector<T>::insert(const size_t &ind, const T &value);
        // template<T>
        friend iterator vector<T>::erase(iterator pos);
        // template<T>
        friend iterator vector<T>::erase(iterator pos);
    public:
        //my try
        iterator (int vector_num=0,T **other=NULL):index(vector_num){
            vector_type=other;
        }
        iterator(const iterator &other){
            index=other.index;
            vector_type=other.vector_type;
        }
        ~iterator(){
            vector_type=NULL;
            index=0;
        }
        /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
        iterator operator+(const int &n) const {
            //TODO
            iterator tmp_iterator ;
            tmp_iterator.index=index+n;
            tmp_iterator.vector_type=vector_type;
            return tmp_iterator;
        }
        iterator operator-(const int &n) const {
            //TODO
           iterator tmp_iterator ;
           tmp_iterator.index=index-n;
           tmp_iterator.vector_type=vector_type;
            return tmp_iterator;
        }
        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const iterator &rhs) const {
            //TODO
            if(this->vector_type!=rhs->vector_type)throw("invalid_iterator");
            return index-rhs.index;
        }
        iterator& operator+=(const int &n) {
            //TODO
            index+=n;
            return *this;
        }
        iterator& operator-=(const int &n) {
            //TODO
            index-=n;
            return *this;
        }
        /**
         * TODO iter++
         */
        iterator operator++(int) {
            iterator tmp_iterator;
            tmp_iterator->index=index;
            tmp_iterator->vector_type=vector_type;
            index++;
            return tmp_iterator;
        }
        /**
         * TODO ++iter
         */
        iterator& operator++() {
            index++;
            return *this;
        }
        /**
         * TODO iter--
         */
        iterator operator--(int) {
            iterator tmp_iterator;
            tmp_iterator.index=index;
            tmp_iterator.vector_type=vector_type;
            index--;
            return tmp_iterator;
        }
        /**
         * TODO --iter
         */
        iterator& operator--() {
            index--;
            return *this;
        }
        /**
         * TODO *it
         */
        T& operator*() const{
            return *vector_type[index];
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const {
            if(vector_type!=rhs.vector_type)throw("invalid_iterator");
            if(index==rhs.index)return 1;
            else return 0;
        }
        bool operator==(const const_iterator &rhs) const {
            if(vector_type!=rhs.vector_type)throw("invalid_iterator");
            if(index==rhs.index)return 1;
            else return 0;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            if(vector_type!=rhs.vector_type)throw("invalid_iterator");
            if(index==rhs.index)return 0;
            else return 1;
        }
        bool operator!=(const const_iterator &rhs) const {
            if(vector_type!=rhs.vector_type)throw("invalid_iterator");
            if(index==rhs.index)return 0;
            else return 1;
        }
    };
    /**
     * TODO
     * has same function as iterator, just for a const object.
     */
    class const_iterator {
        int index;
        T **vector_type;
            public:
        //my try
        const_iterator (int vector_num=0,T **other=NULL):index(vector_num){
            vector_type=other;
        }
        const_iterator(const const_iterator &other){
            index=other.index;
            vector_type=other.vector_type;
        }
        ~const_iterator(){
            index=0;
            vector_type=NULL;
        }
        /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
        const const_iterator operator+(const int &n) const {
            //TODO
            const_iterator tmp_iterator ;
            tmp_iterator.index=index+n;
            tmp_iterator.vector_type=vector_type;
            return tmp_iterator;
        }
        const const_iterator operator-(const int &n) const {
            //TODO
           const_iterator tmp_iterator ;
           tmp_iterator.index=index-n;
           tmp_iterator.vector_type=vector_type;
            return tmp_iterator;
        }
        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const const_iterator &rhs) const {
            //TODO
            if(this->vector_type!=rhs->vector_type)throw("invalid_iterator");
            return index-rhs.index;
        }
        const const_iterator& operator+=(const int &n) {
            //TODO
            index+=n;
            return *this;
        }
        const const_iterator& operator-=(const int &n) {
            //TODO
            index-=n;
            return *this;
        }
        /**
         * TODO iter++
         */
        const const_iterator operator++(int) {
            const_iterator tmp_iterator;
            tmp_iterator->index=index;
            tmp_iterator->vector_type=vector_type;
            index++;
            return tmp_iterator;
        }
        /**
         * TODO ++iter
         */
        const const_iterator& operator++() {
            index++;
            return *this;
        }
        /**
         * TODO iter--
         */
       const  const_iterator operator--(int) {
            const_iterator tmp_iterator;
            tmp_iterator.index=index;
            tmp_iterator.vector_type=vector_type;
            index--;
            return tmp_iterator;
        }
        /**
         * TODO --iter
         */
        const const_iterator& operator--() {
            index--;
            return *this;
        }
        /**
         * TODO *it
         */
        const T& operator*() const{
            return *vector_type[index];
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const {
            if(vector_type!=rhs.vector_type)throw("invalid_iterator");
            if(index==rhs.index)return 1;
            else return 0;
        }
        bool operator==(const const_iterator &rhs) const {
            if(vector_type!=rhs.vector_type)throw("invalid_iterator");
            if(index==rhs.index)return 1;
            else return 0;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            if(vector_type!=rhs.vector_type)throw("invalid_iterator");
            if(index==rhs.index)return 0;
            else return 1;
        }
        bool operator!=(const const_iterator &rhs) const {
            if(vector_type!=rhs.vector_type)throw("invalid_iterator");
            if(index==rhs.index)return 0;
            else return 1;
        }
    };
    /**
     * TODO Constructs
     * Atleast two: default constructor, copy constructor
     */
    void build_storage(T **&storage,int size){
        storage=new T* [size];
    }
    void delete_storage(T **&storage,int size){
        for(int i=size-1;i>=0;i--){
            delete storage[i];
        }
        delete []storage;
    }
    vector(int n=20):vector_size(n),now_size(0){
        build_storage(vector_storage,vector_size);
    }
    vector(const vector &other) {
        vector_size=other.vector_size;
        now_size=other.now_size;
        // vector_storage= new* T[vector_size];
        // for(int i=0;i<vector_size;i++)
        build_storage(vector_storage,vector_size);
        for(int i=0;i<now_size;i++){
            vector_storage[i]=new T (*other.vector_storage[i]);
        }
    }
    /**
     * TODO Destructor
     */
    ~vector() {
    //delete []vector_storage;
    delete_storage(vector_storage,now_size);
    vector_size=0;now_size=0;}
    /**
     * TODO Assignment operator
     */
    vector &operator=(const vector &other) {
        
        if(this==&other)return *this;
        //delete []vector_storage;
        delete_storage(vector_storage,now_size);
        vector_size=other.vector_size;
        now_size=other.now_size;
        //vector_storage =new T[vector_size];
        build_storage(vector_storage,vector_size);
        for(int i=0;i<now_size;i++){
            vector_storage[i]=new T(*other.vector_storage[i]);
        }
        return *this;
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     */
    T & at(const size_t &pos) {
        if(pos<0||pos>=now_size)throw("index_out_of_bound");
        return *vector_storage[pos];
    }
    const T & at(const size_t &pos) const {
        if(pos<0||pos>=now_size)throw("index_out_of_bound");
        return *vector_storage[pos];
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     * !!! Pay attentions
     *   In STL this operator does not check the boundary but I want you to do.
     */
    T & operator[](const size_t &pos) { 
        if(pos<0||pos>=now_size)throw("index_out_of_bound");
        return *vector_storage[pos];
    }
    const T & operator[](const size_t &pos) const {
        if(pos<0||pos>=now_size)throw("index_out_of_bound");
        return *vector_storage[pos];
    }
    /**
     * access the first element.
     * throw container_is_empty if size == 0
     */
    const T & front() const {
        if(now_size==0)throw("contianer_is_empty");
        return *vector_storage[0];
    }
    /**
     * access the last element.
     * throw container_is_empty if size == 0
     */
    const T & back() const {
        if(now_size==0)throw("container_is_empty");
        return *vector_storage[now_size-1];
    }
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() {
       return  iterator(0,vector_storage);
    }
    const_iterator cbegin() const {
        return const_iterator(0,vector_storage);
    }
    /**
     * returns an iterator to the end.
     */
    iterator end() {
        return iterator(now_size,vector_storage);
    }
    const_iterator cend() const {
        return const_iterator(now_size,vector_storage);
    }
    /**
     * checks whether the container is empty
     */
    bool empty() const {
        if(!now_size)return 1;
        else return 0;
    }
    /**
     * returns the number of elements
     */
    size_t size() const {
        return now_size;
    }
    /**
     * clears the contents
     */
    void clear() {
        //delete []vector_storage;
        delete_storage(vector_storage,now_size);
        vector_size=0;
        now_size=0;
    }
    /**
     * inserts value before pos
     * returns an iterator pointing to the inserted value.
     */
    iterator insert(iterator pos, const T &value) {
        int index=pos.index;
        int cnt=0;
        T **tmp_storage;
        //tmp_storage = new T[vector_size+1];
        build_storage(tmp_storage,now_size+1);
        int tmp_size=now_size+1;
        for(int i=0;i<now_size;i++,cnt++){
            if(i==index){
                tmp_storage[cnt]=new T(value);
                cnt++;
            }
            tmp_storage[cnt]=new T(*vector_storage[i]);
        }
        //delete []vector_storage;
       delete_storage(vector_storage,now_size);
        now_size++;
        vector_size++; 
        //vector_storage= new T[vector_size];
        build_storage(vector_storage,vector_size);
        for(int i=0;i<now_size;i++){
            vector_storage[i]=new T(*tmp_storage[i]);
        }
        delete_storage(tmp_storage,tmp_size);
        return iterator(index,vector_storage);
    }
    /**
     * inserts value at index ind.
     * after inserting, this->at(ind) == value
     * returns an iterator pointing to the inserted value.
     * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
     */
    iterator insert(const size_t &ind, const T &value) {
        if(ind>vector_size+1)throw("index_out_of_bound");
        int cnt=0;
        T **tmp_storage;
        //tmp_storage = new T[vector_size+1];
        build_storage(tmp_storage,now_size+1);
        int tmp_size=now_size+1;
        for(int i=0;i<now_size;i++,cnt++){
            if(i==ind){
                tmp_storage[cnt]=new T(value);
                cnt++;
            }
            tmp_storage[cnt]=new T(*vector_storage[i]);
        }
        //delete []vector_storage;
        delete_storage(vector_storage,now_size);//出锅了！？！？！？
        now_size++;
        vector_size++; 
        //vector_storage= new T[vector_size];
        build_storage(vector_storage,vector_size);
        for(int i=0;i<now_size;i++){
            vector_storage[i]=new T(*tmp_storage[i]);
        }
        delete_storage(tmp_storage,tmp_size);
        return iterator(ind,vector_storage);
    }
    /**
     * removes the element at pos.
     * return an iterator pointing to the following element.
     * If the iterator pos refers the last element, the end() iterator is returned.
     */
    iterator erase(iterator pos) {
        int index=pos.index;
        for(int i=index;i<now_size-1;i++){
            *vector_storage[i]=*vector_storage[i+1];
        }
        delete vector_storage[now_size-1];
        now_size--;
        if(now_size*4<vector_size)shrink_storage();
        return iterator(index,vector_storage);
    }
    /**
     * removes the element with index ind.
     * return an iterator pointing to the following element.
     * throw index_out_of_bound if ind >= size
     */
    iterator erase(const size_t &ind) {
        if(ind>=vector_size)throw("index_out_of_bound");
        for(int i=ind;i<now_size-1;i++){
            *vector_storage[i]=*vector_storage[i+1];
        }
        delete vector_storage[now_size-1];
        now_size--;
        if(4*now_size<vector_size)shrink_storage();
        return iterator(ind,vector_storage);
    }
    /**
     * adds an element to the end.
     */
    void push_back(const T &value) {
        if(now_size==vector_size){//expand
            T **tmp_storage;
            //tmp_storage= new T[vector_size];
            build_storage(tmp_storage,vector_size);
            int tmp_size=vector_size;
            for(int i=0;i<now_size;i++){
                tmp_storage[i]=new T(*vector_storage[i]);
            }
            //delete []vector_storage;
            delete_storage(vector_storage,now_size);
            vector_size=2*vector_size;
           // vector_storage= new T[vector_size];
           build_storage(vector_storage,vector_size);
            for(int i=0;i<now_size;i++){
                vector_storage[i]=new T(*tmp_storage[i]);
            } 
            delete_storage(tmp_storage,tmp_size);
        }
        vector_storage[now_size]=new T(value);
        now_size++;
    }
    /**
     * remove the last element from the end.
     * throw container_is_empty if size() == 0
     */
    void pop_back() {
        if(!now_size)throw("container_is_empty");
        delete vector_storage[now_size-1];
        now_size--;
        if(4*now_size<vector_size){
        shrink_storage();
        }
        
    }
};

}

#endif