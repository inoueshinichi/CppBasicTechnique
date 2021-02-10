//
//  Struct.hpp
//  OrientedObject
//
//  Created by Inoue Shinichi on 2018/05/18.
//  Copyright © 2018年 Inoue Shinichi. All rights reserved.
//

#ifndef Struct_hpp
#define Struct_hpp

#include <stdio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

#endif /* Struct_hpp */

struct Employee
{
    int number;
    char name[80];
    int salary;
};

struct Company
{
    struct Employee tanaka;
    struct Employee sato;
    struct Employee suzuki;
    char companyName[80];
};

#define GU 0
#define CHOKI 1
#define PA 2

#define WIN 0
#define LOSE 1
#define DRAW 2

class User
{
private:
    int hand;
public:
    void setHand();
    int getHand();
};

class Computer
{
private:
    int hand;
public:
    void setHand();
    int getHand();
};

class Judge
{
private:
    int judge;
public:
    void doJudge(User u, Computer c);
    void showJudge();
};

class MyMath
{
public:
    int twice(int a);
    long twice(long a);
    float twice(float a);
    double twice(double a);
};

class MyMessage
{
public:
    void showMessage();
    void showMessage(const char *s);
    void showMessage(const char *a, int n);
};

// 集約(has a)
class CellPhone
{
public:
    char number[20];
    bool smart;
    char *owner;
    CellPhone();
    CellPhone(const char *b, bool i);
    CellPhone(const CellPhone &cellphone); // コピーコンストラクタ
    ~CellPhone();
};


class EmployeeC
{
public:
    // staticメンバ変数はオブジェクトができていなくても、スコープがクラス内のグローバル変数として機能する.
    // ただし、グローバルで定義する必要がある。
    static int objNum;
    static const char *companyName;
    int number;
    char name[80];
    char *NAME; // コピーコンストラクタ用
    int salary;
    CellPhone phone; // 集約
    void showData();
    void showPhone();
    EmployeeC();
    ~EmployeeC();
    EmployeeC(int nu, const char *na, int sa);
    EmployeeC(int nu, char *na, int sa, char *cn, bool cs);
    EmployeeC(const EmployeeC &object); // コピーコンストラクタ
    EmployeeC &operator=(EmployeeC &obj); // 代入演算子のオーバーロード
};

class MySample
{
public:
    void useObject(EmployeeC *obj);
    EmployeeC* retObject();
};

class Book
{
private:
    int page;
    
public:
    int getPage();
    void setPage(int p);
};

class SimpleMath
{
private:
    double tempCalc(double a, double b, double c);
public:
    bool quadratic(double a, double b, double c, double *x1, double *x2);
};

class MyClass
{
public:
    int number;
    MyClass();
    MyClass(int m);
    ~MyClass();
    void func1(int a);
    virtual void func2(const char *s);
};

// 継承 from EmployeeC
class Salesman : public EmployeeC
{
public:
    int sales; // 売上
    
public:
    Salesman();
    Salesman(int nu, const char *na, int sa, int ss);
    void showData();  // オーバーロード
};

class Director : public EmployeeC
{
public:
    int stock; // 株式保有数
    void showData();
    Director();
    Director(int nu, const char *na, int sa, int st);
};

class Manager : public EmployeeC
{
public:
    int travelAllowance; // 出張費
    void showData();
    Manager();
    Manager(int nu, const char *na, int sa, int tr);
};

// 継承におけるコンストラクタとデストラクタの扱い
class NewClass : public MyClass
{
public:
    int new_data;
    NewClass();
    NewClass(int n, int m);
    ~NewClass();
    void func2(const char *s);
};

// オーバーライドによる多様性を活用した「お絵かきプログラム」
class Figure
{
public:
    static int figNum;
    Figure();
    virtual void draw() = 0; // 純粋仮想関数 
};

class Circle : public Figure
{
public:
    void draw(); // オーバーライド
};

class Triangle : public Figure
{
public:
    void draw(); // オーバーライド
};

class Regtangle : public Figure
{
public:
    void draw(); // オーバーライド
};

/*
// 集約(has a)
class CellPhone
{
public:
    char number[20];
    bool smart;
};
 */

class Point
{
public:
    int x;
    int y;
    Point operator+(Point obj);
    Point operator-(Point obj);
    bool operator==(Point obj);
    bool operator>(Point obj);
};
