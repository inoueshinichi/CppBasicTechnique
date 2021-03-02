#include "iterator.hpp"

#include <iostream>
#include <array>
#include <sstream>
#include <algorithm> //std::for_each
#include <initializer_list>

int main(int argc, char** argv) 
{
    /////////////////////////
    // C++におけるイテレータとは
    /////////////////////////

    /////////////////////////
    // コンテナに対するイテレータ
    std::array<int, 5> arr1{{1,3,9,4}};
    for (auto iter = std::begin(arr1); iter != std::end(arr1); ++iter)
    {
        std::cout << *iter << std::endl;
    }

    ///////////////////////////
    // C形式の配列に対するイテレータ
    int arr2[] = {1,3,9,4};
    for (int* iter = std::begin(arr2); iter != std::end(arr2); ++iter)
    {
        std::cout << *iter << std::endl;
    }

    ////////////////////////
    // streamに対するイテレータ

    // 文字列の入力ストリームにデータを入れる
    std::stringstream ss;
    ss << 1 << std::endl
       << 2 << std::endl
       << 3;

    // 文字列の入力ストリームからデータを読み込むイテレータを作る
    std::istream_iterator<int> iter(ss);
    std::istream_iterator<int> last;

    // イテレータを進めることにより、入力ストリームからデータを順に読み取る
    std::for_each(iter, last, [](int x) {
        std::cout << x << std::endl;
    });


    ////////////////////////////
    // Range-based forとイテレータ
    ////////////////////////////
    // Range Conceptを満たしたクラス...メンバ関数begin()/end()を持つ

    // Range-based for不使用
    for (auto iter = arr1.begin(); iter != arr1.end(); ++iter)
    {
        std::cout << *iter << ",";
    }
    std::cout << std::endl;

    // Range-based for使用
    for (auto&& e : arr1) {
        std::cout << *iter << ",";
    }
    std::cout << std::endl;

    // 文字列リテラルはC形式の配列型
    for (auto&& c : "arikitari")
    {
        std::cout << c << std::endl;
    }

    // initializer_listはRangeConceptを満たす
    for (auto&& n : {13,32})
    {
        std::cout << n << std::endl;
    }

    ///////////////////////////////////
    // イテレータをラップするイテレータを作る
    ///////////////////////////////////

    // 管理
    std::vector<Circle> circles;
    circles.emplace_back(Vec2f{1.0, 2.0}, 5);

    // posを取得
    for (auto& c : circles) {
        auto& p = c.pos;
        std::cout << p.x << p.y << std::endl;
    }
    // 上記のやり方は非常にだるくなる
    // -> std::vector<Circle>::iteratorをラップするイテレータを作る
    // iterator.hppでIteratorクラス、Rangeクラス、Rangeクラス用の実引数型推論用のテンプレート関数を定義
    std::vector<Circle> v(10);
    Circle arr[10] = {};
    for (auto&& p : make_circle_pos_iterator_range(v))
    {
        std::cout << p.x << p.y << std::endl;
    }
    for (auto&& p : make_circle_pos_iterator_range(arr))
    {
        st::cout << p.x << p.y << std::endl;
    }

    ///////////////////////////////////////////////
    // pythonのジェネレータをC++のイテレータで実装する方法
    ///////////////////////////////////////////////
    static auto engine = create_engine(); // 1スレッドに1つだけ

    // Concept
    static_assert(is_random_generator_iterator_v<random_generator_iterator<int>>, "err");

    std::cout << "generate: random_generator_iterator" << std::endl;
    for (auto ri = random_generator_iterator<int>(0, 10, engine);
         ri != random_generator_iterator<int>(); ++ir) {
        
        const auto n = *ri;
        std::cout << n << std::endl;
        if (n == 0)
            ri.stop();
    }

    std::cout << "generate: random_generater_range" << std::endl;
    for (auto&& n : random_generator_range<int>(0, 10, engine))
    {
        std::cout << n << std::endl;
        if (n == 0)
            break;
    }

    // static_assert(is_random_generator_iterator_v<random_generator_iterator_with_count<int>>, "err");
    // std::cout << "generate: random_generator_iterator_with_count" << std::endl;
    // for (auto ri = random_generator_iterator_with_count<int>(0, 10, engine);
    //     ri != random_generator_iterator_with_count<int>(10); ++ri)
    // {
    //     std::cout << *ri << std::endl;
    // }

    // std::cout << "generate: random_generator_range_with_count" << std::endl;
    // for (auto&& n : random_generator_range_with_count<int>(10, 0, 10, engine)) {
    //     std::cout << n << std::endl;
    // }

}