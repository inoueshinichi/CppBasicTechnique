#pragma once

#include <vector>
#include <type_traits>
#include <random>

///////////////////////////////////
// イテレータをラップするイテレータを作る
///////////////////////////////////

struct Vec2f {
    float x;
    float y;
};

struct Circle {
    Vec2f pos;
    float size;
};

// C++17以降ではstd::iterator<T>が非推奨になったので、
// イテレータを作るときは、ゼロからすべて実装することになる

///////////////////////////////////////////////////
// std::vector<Circle>::iteratorをラップするイテレータ
///////////////////////////////////////////////////
template <class Iterator, typename std::enable_if<std::is_same<Circle, 
    typename std::iterator_traits<Iterator>::value_type>::value>::type* = nullptr>
class circle_pos_iterator
#if __cplusplus < 201500 // C++17ではstd::iteratorは消える
    : std::iterator<typename std::iterator_traits<Iterator>::iterator_category, Vec2f>
#endif
{
private:
    using ref_iterator_type = Iterator;
    ref_iterator_type iter_;
#if __cplusplus < 201500
    using base_type = std::iterator<typename std::iterator_traits<
                                             Iterator>::iterator_category, Vec2f>;
#endif
public:
    circle_pos_iterator() = default;
    circle_pos_iterator(Iterator iter) noexcept : iter_(iter) {}
    circle_pos_iterator(const circle_pos_iterator&) = default;
    circle_pos_iterator(circle_pos_iterator&&) = default;
    circle_pos_iterator& operator=(const circle_pos_iterator&) = default;
    circle_pos_iterator& operator=(circle_pos_iterator&&) = default;
    ref_iterator_type get_raw_iterator() const { return iter_; };
#if __cplusplus < 201500
    using iterator_category = typename base_type::iterator_category;
    using value_type = typename base_type::value_type;
    using difference_type = typename base_type::difference_type;
    using pointer = typename base_type::pointer;
    using reference = typename base_type::reference;
#else
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
    using value_type = Vec2f;
    using difference_type = std::ptrdiff_t;
    using pointer = Vec2f*;
    using reference = Vec2f&;
#endif
    Vec2f& operator*() noexcept { return iter_->pos; }
    Vec2f operator*() const noexcept { return iter_-> pos; };
};


// ひたすらoperator overloadを書いていくが、もととなるイテレータの種類によって、
// 定義できないoperatorも存在するので, SFINAEで弾く
// template <class iterator_category, typename std::enable_if<std::is_base_of<std::bidirectional_iterator_tag,
//                             iterator_category>::value, std::nullptr_t>::type = nullptr>
// circle_pos_iterator& operator--() noexcept {
//     --this->iter_;
//     return *this;
// }


////////////////////////////////////////
// Range-based forにわたすためにRangeを作成
////////////////////////////////////////
template <class Iterator>
class circle_pos_iterator_range 
{
public:
    using iterator = circle_pos_iterator<Iterator>;
private:
    iterator begin_;
    iterator end_;
public:
    circle_pos_iterator_range() = delete;
    circle_pos_iterator_range(Iterator begin, Iterator end) : begin_(begin), end_(end) {}
    circle_pos_iterator_range(const circle_pos_iterator_range&) = default;
    circle_pos_iterator_range(circle_pos_iterator_range&&) = default;
    circle_pos_iterator_range& operator=(const circle_pos_iterator_range&) = default;
    circle_pos_iterator_range& operator=(circle_pos_iterator_range&&) = default;
    iterator& begin() noexcept { return this->begin_; }
    const iterator& begin() const noexcept { return this->begin_; }
    iterator& end() noexcept { return this->end_; }
    const iterator& end() const noexcept { return this->end_; }
};
// begin()/end()があるだけで、特に何もしない


//////////////
// Factory関数
//////////////
// Rangeクラスのmake_xxx系関数
// 作成理由：C++14まではクラスのテンプレート実引数推定ができないので、Range-based forの記述
// の際に、テンプレートパラメータ指定が必要になり冗長的記述になるため。
// int main(void) {
//     std::vector<Circle> v(10);
//     Circle arr[10] = {};
//     for (auto&& p : circle_pos_iterator_range<std::vector<Circle>::iterator>(v))
//     {
//         std::cout << p.x << p.y << std::endl;
//     }
//     for (auto&& p : circle_pos_iterator_range<Circle*>(arr))
//     {

//     }
// }

// 対処法 -> テンプレート関数の実引数型推論を使う
template <class Iterator, typename std::enable_if<std::is_same<Circle, 
    typename std::iterator_traits<Iterator>::value_type>::value>::type* = nullptr>
circle_pos_iterator_range<Iterator> make_circle_pos_iterator_range(Iterator begin, Iterator end)
{
    return {begin, end};
}

template <class Container>
circle_pos_iterator_range<typename Container::iterator> make_circle_pos_iterator_range(Container c)
{
    return make_circle_pos_iterator_range(c.begin(), c.end());
}

template <std::size_t N>
circle_pos_iterator_range<Circle*> make_circle_pos_iterator_range(Circle (&arr)[N])
{
    return make_circle_pos_iterator_range(std::begin(arr), std::end(arr));
}


///////////////////////////////////////////////
// pythonのジェネレータをC++のイテレータで実装する方法
///////////////////////////////////////////////

// /////////////////////
// // pythonのジェネレータ
// from random import randint
// def random_generator_range(n, min_, max_):
//     while True:
//         yield randint(min_, max_)

// def random_generator_range_with_count(n, min_, max_):
//     i = 0
//     while i < n:
//         yield randint(min_, max_)
//         i += 1

// print("generate: random_generator_range")
// for n in random_generator_range(10, 0, 10):
//     print(n)
//     if 0 == n:
//         break

// print("generate: random_generator_range_with_count")
// for n in random_generator_range_with_count(10, 0, 10):
//     print(n)


decltype(auto) create_engine()
{
    std::random_device seed_gen;
    static std::mt19937 engine(seed_gen());
    return engine;
}


template <class T>
class random_generator_iterator
    // : public random_generator_iterator_base
// #if __cplusplus < 201500
    /*,*/ : public std::iterator<std::input_iterator_tag, T> // C++17から非推奨だが面倒なので継承
// #endif
{
    // 中略
    using iterator = std::iterator<std::input_iterator_tag, T>;
    using distribution = typename std::uniform_real_distribution<typename iterator::value_type>;
private:
    struct impl {
        distribution dist;
        std::reference_wrapper<std::mt19937_64> engine;
        bool next_is_end;
        impl() = default;
        impl(const impl&) = delete;
        impl(impl&&) = default;
        impl& operator=(const impl&) = delete;
        impl& operator=(impl&&) = default;
        impl(typename iterator::value_type min, typename iterator::value_type max, std::mt19937_64& mt) 
            : dist(min, max)
            , engine(mt)
            , next_is_end(false)
        {}
        typename iterator::value_type generate() { return this->dist(this->engine.get()); }
    };

    std::unique_ptr<impl> pimpl_;
    bool is_end_iterator_;
public:
    constexpr random_generator_iterator() noexcept
        : pimpl_()
        , is_end_iterator_(true)
    {}

    random_generator_iterator(const random_generator_iterator&) = delete;
    random_generator_iterator(random_generator_iterator&&) = default;
    random_generator_iterator& operator=(const random_generator_iterator&) = delete;
    random_generator_iterator& operator=(random_generator_iterator&&) = default;

    random_generator_iterator(typename iterator::value_type min, typename iterator::value_type max, std::mt19937& mt)
        : pimpl_(std::make_unique<impl>(min, max, mt))
        , is_end_iterator_(false)
    {}

    void stop() noexcept { this-> pimpl_->next_is_end = true; }
    typename iterator::value_type operator*() { return this->pimpl_->generate(); }
    random_generator_iterator& operator++() noexcept
    {
        if (this->pimpl_->next_is_end)
            this->is_end_iterator_ = true;
        return *this;
    }

    random_generator_iterator operator++(int) noexcept
    {
        const auto re = *this;
        if (this->pimpl_->next_is_end)
            this->is_end_iterator_ = true;
        return re;
    }

    constexpr bool operator==(const random_generator_iterator& r) const noexcept
    {
        return this->is_end_iteratpr_ == r.is_end_iterator_;
    }

    constexpr bool operator!=(const random_generator_iterator& r) const noexcept
    {
        return !(*this == r);
    }
};

// 課題：乱数生成器をどうするか
// C++の乱数ライブラリは
// 1) 乱数生成器
// 2) Distribution
// を分離した設計になっている。
// ※ここで乱数生成器は基本的に各スレッドで1個持って使い回すことを想定している。
// つまり、乱数生成を行うイテレータは乱数生成器への参照を保持する必要がある。
// -> std:::reference_wrapperを用いる!

template <class T>
class random_generator_range 
{
public:
    using value_type = T;
    using iterator = random_generator_iterator<value_type>;

private:
    value_type min_;
    value_type max_;
    std::reference_wrapper<std::mt19937_64> mt_;
public:
    random_generator_range() = delete;
    random_generator_range(const random_generator_range&) = delete;
    random_generator_range(random_generator_range&&) = default;
    random_generator_range& operator=(const random_generator_range&) = delete;
    random_generator_range& operator=(random_generator_range&&) = default;
    random_generator_range(value_type min, value_type max, std::mt19937_64& mt)
        : min_(min)
        , max_(max)
        , mt_(mt)
    {}

    iterator begin() noexcept { return iterator{min_, max_, mt_.get()}; }
    iterator end() noexcept { return iterator{}; }
};
