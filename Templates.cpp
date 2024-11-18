#include <iostream>
#include <vector>
#include <string>

// Typedefs for vector types
template <class T>
using ELEM = std::vector<T>;

template <class T>
using VEC = std::vector<ELEM<T>>;

template <class T>
using action_t = T(*)(T, T);

template <class T>
using pred_t = bool (*)(T);

template <class T>
using map_t = T(*)(T, T);

// Print single ELEM
template <class T>
void printElem(ELEM<T>& v) {
    if (v.size() > 1) std::cout << "[";
    for (auto i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i < v.size() - 1) std::cout << ", ";
    }
    if (v.size() > 1) std::cout << "]";
}

// Initialize a vector 
template <class T>
void initVec(VEC<T>& v, ELEM<T>&& cons) {
    v.push_back(cons);
}

// Print VEC (vector of ELEMS)
template <class T>
void printVec(VEC<T>& v) {
    if (v.size() > 1) std::cout << "[";
    for (auto i = 0; i < v.size(); ++i) {
        printElem(v[i]);
        if (i < v.size() - 1) std::cout << ", ";
    }
    if (v.size() > 1) std::cout << "]";
    std::cout << std::endl;
}

// Generate a VEC (vector of ELEMS) based on a function
template <class T>
VEC<T> generate(int N, action_t<T> f) {
    VEC<T> result;
    for (T i = 1; i < N; ++i) {
        result.push_back(ELEM<T>{f(i, i)});
    }
    return result;
}

// Zip two VECs
template <class T>
VEC<T> zip(VEC<T>& v, VEC<T>& w) {
    VEC<T> result;
    for (auto i = 0; i < v.size() && i < w.size(); ++i) {
        result.push_back({}); // Add an empty subvector to `result` for row i
        for (auto j = 0; j < v[i].size() && j < w[i].size(); ++j) {
            result[i].push_back(v[i][j]); // Add from the first vector
            result[i].push_back(w[i][j]); // Add from the second vector
        }
    }
    return result; // Return the final zipped vector
}


// Filter a VEC
template <class T>
VEC<T> filter(VEC<T>& v, pred_t<T> f) {
    VEC<T> result;
    for (auto& elem : v) {
        ELEM<T> temp;
        for (auto& val : elem) {
            if (f(val)) temp.push_back(val); //removes ELEMS that do not meet the predicate criterion
        }
        if (!temp.empty())
            result.push_back(temp);  //push back all the ELEMS that meet the predicate criterion
    }
    return result;
}

// Map a VEC
template <class T>
VEC<T> map(VEC<T>& v, action_t<T> f) {
    VEC<T> result;
    for (auto& elem : v) {
        ELEM<T> temp;
        for (auto& val : elem) {
            temp.push_back(f(val, val));//goes through all the elements in the vector and applies the functions and pushes it to temp vector.
        }
        result.push_back(temp); // pushes the temp vector to result(vector of elem)
    }
    return result;
}

// Reduce a VEC
template <class T>
ELEM<T> reduce(VEC<T>& v, map_t<T> f, ELEM<T> ident) {
    ELEM<T> result = ident;      //null value of the specified type
    for (auto& elem : v) {
        for (auto& val : elem) {
            result[0] = f(result[0], val);
        }
    }
    return result;
}

template<class T>
T k(T i, T j) {
    return i + j;
}

//Test functions
bool g(int x) {
    return x > 0;  //checks for positive numbers
}

int h(int x, int) {
    return x > 0 ? 1 : 0; // checks which number is greater
}

int f(int a, int) {
    return a * a;  // squares function
}

// Main program
int main() {
    VEC<int> v;
    initVec(v, ELEM<int>{1, 2, 3, 4});

    VEC<int> w;
    initVec(w, ELEM<int>{-1, 3, -3, 4});

    printVec(v);
    std::cout << std::string(10, '*') << std::endl;
    printVec(w);
    std::cout << std::string(10, '*') << std::endl;

    VEC<int> z = zip(v, w);
    printVec(z);
    std::cout << std::string(10, '*') << std::endl;

    VEC<int> x = zip(z, z);
    printVec(x);
    std::cout << std::string(10, '*') << std::endl;

    VEC<int> a = generate(10, f);
    printVec(a);

    VEC<int> y = filter(w, g);
    printVec(y);

    VEC<int> u = map(w, h);
    printVec(u);

    ELEM<int> e = reduce(u, k, ELEM<int>{0});
    printElem(e);

    std::cout << std::endl << std::string(10, '$') << std::endl;

    VEC<std::string> ws;
    initVec(ws, ELEM<std::string>{"hello", "there", "franco", "carlacci"});
    printVec(ws);

    ELEM<std::string> es = reduce(ws, k, ELEM<std::string>{""});
    printElem(es);

    VEC<char> wc;
    initVec(wc, ELEM<char>{'a', 'b', 'c', 'd'});
    std::cout << std::endl << std::string(10, '$') << std::endl;
    printVec(wc);

    ELEM<char> ec = reduce(wc, k, ELEM<char>{' '});
    std::cout << std::endl << std::string(10, '$') << std::endl;
    printElem(ec);

    return 0;
}
