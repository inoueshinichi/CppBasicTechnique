//
//  Struct.cpp
//  OrientedObject
//
//  Created by Inoue Shinichi on 2018/05/18.
//  Copyright © 2018年 Inoue Shinichi. All rights reserved.
//

#include "struct.hpp"
#include <iostream>
#include <cmath>
using namespace std;

#define GU 0
#define CHOKI 1
#define PA 2

#define WIN 0
#define LOSE 1
#define DRAW 2

void User::setHand()
{
    cout << "0:グー, 1:チョキ, 2:パー" << endl;
    cout << "ユーザーの手を選んでください=";
    cin >> hand;
}

int User::getHand()
{
    return hand;
}

void Computer::setHand()
{
    hand = rand() % 3;
}

int Computer::getHand()
{
    cout << "コンピュータの手=" << hand << endl;
    return hand;
}

void Judge::doJudge(User u, Computer c)
{
    int user, computer;
    
    user = u.getHand();
    computer = c.getHand();
    if (user == computer)
    {
        judge = DRAW;
    }
    else if ((user == GU && computer == CHOKI) ||
             (user == PA && computer == GU) ||
             (user == CHOKI && computer == PA))
    {
        judge = WIN;
    }
    else {
        judge = LOSE;
    }
}

void Judge::showJudge()
{
    if (judge == WIN)
    {
        cout << "ユーザーの勝ちです!" << endl;
    }
    else if (judge == LOSE)
    {
        cout << "ユーザーの負けです!" << endl;
    }
    else {
        cout << "引き分けです!" << endl;
    }
}

// ポリモーフィズムの例
// 引数の型に対応
int MyMath::twice(int a)
{
    return a * 2;
}

long MyMath::twice(long a)
{
    return a * 2;
}

float MyMath::twice(float a)
{
    return a * 2;
}

double MyMath::twice(double a)
{
    return a * 2;
}

// 引数の数に対応
void MyMessage::showMessage()
{
    //cout << "こんにちは" << endl;
    showMessage("こんにちは");
}

void MyMessage::showMessage(const char *s)
{
    //cout << s << endl;
    showMessage(s, 1);
}

void MyMessage::showMessage(const char *a, int n)
{
    cout << "Message:"; // 変更した部分
    for (int i = 0; i < n; i++)
    {
        cout << a << endl;
    }
}


void EmployeeC::showData()
{
    cout << number << endl;
    cout << name << endl;
    cout << salary << endl;
}

void MySample::useObject(EmployeeC *obj)
{
    obj->showData();
}

EmployeeC* MySample::retObject()
{
    static EmployeeC obj;
    obj.number = 0;
    strcpy(obj.name, "誰だろう");
    obj.salary = 1000;
    return &obj;
}

// カプセル化の例
int Book::getPage()
{
    return page;
}

void Book::setPage(int p)
{
    if ((p >= 1) && (p <= 1000))
    {
        page = p;
    }
    else
    {
        cout << "1 ~ 1000を設定してください！" << endl;
    }
}

bool SimpleMath::quadratic(double a, double b, double c, double *x1, double *x2)
{
    double temp;
    temp = tempCalc(a, b, c);
    if (temp < 0)
    {
        return false;
    }
    else
    {
        *x1 = (-b + sqrt(temp))/(2*a);
        *x2 = (-b - sqrt(temp))/(2*a);
        return true; // 解あり
    }
}

double SimpleMath::tempCalc(double a, double b, double c)
{
    return b * b - 4 * a * c;
}

EmployeeC::EmployeeC()
{
    //number = 0;
    objNum++;
    number = objNum;
    strcpy(name, "未設定");
    salary = 150000;
    NAME = new char[80];
    strcpy(NAME, "未設定");
    
    printf("number: %d, name: %s, salary: %d\n", number, name, salary);
    cout << "EmployeeCクラスのコンストラクタが呼び出されました。" << endl;
}

EmployeeC::~EmployeeC()
{
    delete[] NAME;
    cout << "EmployeeCクラスのデストラクタが呼び出されました。" << endl;
}

EmployeeC::EmployeeC(int nu, const char *na, int sa)
{
    objNum++;
    number = objNum;
    number = nu;
    strcpy(name, na);
    salary = sa;
    NAME = new char[80];
    strcpy(NAME, na);
    
    printf("number: %d, name: %s, salary: %d\n", number, name, salary);
}

EmployeeC::EmployeeC(int nu, char *na, int sa, char *cn, bool cs)
: phone(cn, cs)
{
    number = nu;
    strcpy(name, na);
    salary = sa;
    NAME = new char[80];
    strcpy(NAME, na);
    
    printf("number: %d, name: %s, salary: %d NAME: %s\n", number, name, salary, NAME);
}

// コピーコンストラクタ
EmployeeC::EmployeeC(const EmployeeC & object)
: phone(object.phone) // CellPhoneクラスのコピーコンストラクタ
{
    NAME = new char[80];
    
    number = object.number;
    strcpy(name, object.name);
    salary = object.salary;
    strcpy(NAME, object.name);
    
    cout << "コピーコンストラクタが呼び出されました。" << endl;
}

// 代入演算子のオーバーロードの実装
EmployeeC &EmployeeC::operator=(EmployeeC &obj)
{
    // ポインタでないメンバ変数の値は、そのまま代入する
    this->number = obj.number;
    this->salary = obj.salary;
    
    // ポインタが指すメモリ領域をコピーする
    strcpy(this->NAME, obj.NAME);
    
    // 代入されたオブジェクト自体を返す
    return *this;
}

// コンストラクタとデストラクタ
MyClass::MyClass()
{
    cout << "コンストラクタが呼び出されました。" << endl;
}

MyClass::MyClass(int m)
{
    cout << "オーバーロードされた基本クラスのコンストラクタ " << m << endl;
}

MyClass::~MyClass()
{
    cout << "オブジェクト" << number;
    cout << "のデストラクタが呼び出されました。" << endl;
}

// 継承
Salesman::Salesman()
{
    sales = 1000;
}

/*
void Salesman::ShowData()
{
    cout << "Saleman" << endl;
    cout << number << endl;
    cout << name << endl;
    cout << salary << endl;
    cout << sales << endl;
}
*/

// 継承に於けるコンストラクタとデストラクタ
NewClass::NewClass()
{
    cout << "派生クラスのコンストラクタが呼び出されました" << endl;
}

NewClass::~NewClass()
{
    cout << "派生クラスのデストラクタが呼び出されました。" << endl;
}

// 基本クラスが複数コンストラクタを保つ場合、
NewClass::NewClass(int n, int m) : MyClass(m)
{
    // 派生クラスで追加されたメンバ変数を初期化する
    new_data = n;
    cout << "引数ありの派生クラスのコンストラクタだよ" << endl;
}

// オーバーライド
void MyClass::func1(int a)
{
    cout << a << endl;
}

void MyClass::func2(const char *s)
{
    cout << s << endl;
}

void NewClass::func2(const char *s)
{
    cout << "文字列データ:";
    MyClass::func2(s);
}

// オーバーライドと多様性
Salesman::Salesman(int nu, const char *na, int sa, int ss)
: EmployeeC(nu, na, sa)
{
    sales = ss;
}

void Salesman::showData()
{
    EmployeeC::showData();
    cout << "売上:" << sales << endl;
}

Director::Director()
{
    stock = 100;
}

Director::Director(int nu, const char *na, int sa, int st)
: EmployeeC(nu, na, sa)
{
    stock = st;
}

void Director::showData()
{
    EmployeeC::showData();
    cout << "株式保有数:" << stock << endl;
}

Manager::Manager()
{
    travelAllowance = 10000;
}

Manager::Manager(int nu, const char *na, int sa, int tr)
: EmployeeC(nu, na, sa)
{
    travelAllowance = tr;
}

void Manager::showData()
{
    EmployeeC::showData();
    cout << "出張費:" << travelAllowance << endl;
}

// オーバーライドによる多様性を活用した「お絵かきプログラム」
void Figure::draw()
{
    // 処理なし
}

void Circle::draw()
{
    cout << "○";
}

void Triangle::draw()
{
    cout << "△";
}

void Regtangle::draw()
{
    cout << "□";
}

Figure::Figure()
{
    figNum++;
    cout << "figNum:" << figNum << endl;
}

void EmployeeC::showPhone()
{
    cout << "携帯電話番号:" << phone.number << endl;
    cout << "スマホかどうか:" << phone.smart << endl;
}

CellPhone::CellPhone()
{
    cout << "CellPhoneクラスのコンストラクタが呼び出されました。" << endl;
    strcpy(number, "未設定");
    smart = false;
    owner = new char[20];
    strcpy(owner, "Owner");
    cout << "Cellphone owner: " << owner << endl;
}

CellPhone::~CellPhone()
{
    delete[] owner;
    cout << "CellPhoneクラスのデストラクタが呼び出されました。" << endl;
}

CellPhone::CellPhone(const char *b, bool i)
{
    cout << "CellPhoneクラスのコンストラクタが呼び出されました。" << endl;
    strcpy(number, b);
    smart = i;
    owner = new char[20];
    strcpy(owner, "Owner");
    cout << "電話番号：" << number << endl;
    cout << "スマホかどうか:" << smart << endl;
    cout << "Cellphone owner: " << owner << endl;
}


// コピーコンストラクタ
CellPhone::CellPhone(const CellPhone & cellphone)
{
    owner = new char[20];
    strcpy(owner, "spotify");
    cout << "コピコンストラクタ: owner :" << owner << endl;
    cout << "CellPhoneクラスのコピーコンストラクタが呼ばれました" << endl;
}

Point Point::operator+(Point obj)
{
    Point ans;
    
    // メンバ同士を加算する
    ans.x = this->x + obj.x;
    ans.y = this->y + obj.y;
    
    return ans;
}

Point Point::operator-(Point obj)
{
    Point ans;
    
    // メンバ同士を加算する
    ans.x = this->x - obj.x;
    ans.y = this->y - obj.y;
    
    return ans;
}

bool Point::operator==(Point obj)
{
    if ((this->x == obj.x) && (this->y == obj.y))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Point::operator>(Point obj)
{
    // ベクトルの長さ
    double v1, v2;
    v1 = sqrt(this->x * this->x + this->y * this->y);
    v2 = sqrt(obj.x * obj.x + obj.y * obj.y);
    
    if (v1 > v2)
    {
        return true;
    }
    else
    {
        return false;
    }
}
