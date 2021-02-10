#include <iostream>
#include <cstring>
#include <ctime>
#include "struct.hpp"
using namespace std;

void myFunc()
{
    MyClass obj1; // オブジェクトの生成
    obj1.number = 1;
    
    // ここでオブジェクトが破棄される
}

// staicメンバ変数
int EmployeeC::objNum = 0;
int Figure::figNum = -1;
const char *EmployeeC::companyName = "技術評論社";

// グローバルオブジェクト
EmployeeC yahoo;

// コピーコンストラクタ用
void show(EmployeeC obj);

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    struct Employee tanaka;
    
    tanaka.number = 1234;
    strcpy(tanaka.name, "田中一郎");
    tanaka.salary = 200000;
    
    cout << tanaka.number << endl;
    cout << tanaka.name << endl;
    cout << tanaka.salary << endl;
    
    struct Company gihyo;
    gihyo.tanaka.number = 1234;
    strcpy(gihyo.tanaka.name, "田中一郎");
    gihyo.tanaka.salary = 200000;
    gihyo.sato.salary = 250000;
    
    printf("User | Computer | Judge\n");
    
    User user;
    Computer computer;
    Judge judge;
    
    // 乱数の初期化
    srand(time(NULL));
    
    user.setHand();
    computer.setHand();
    judge.doJudge(user, computer);
    judge.showJudge();
    
    int a;
    double b;
    MyMath obj;
    a = obj.twice(123);
    b = obj.twice(3.14);
    printf("%d, %f\n", a, b);
    
    MyMessage msg;
    msg.showMessage();
    msg.showMessage("お元気ですか");
    msg.showMessage("技術評論社", 3);
    
    EmployeeC emp[3];
    emp[0].number = 1234;
    strcpy(emp[0].name, "田中一郎");
    emp[0].salary = 200000;
    emp[1].number = 1235;
    strcpy(emp[1].name, "佐藤次郎");
    emp[1].salary = 250000;
    emp[2].number = 1236;
    strcpy(emp[2].name, "鈴木一郎");
    emp[2].salary = 300000;
    for (int i = 0; i < 3; i++)
    {
        emp[i].showData();
    }
    
    EmployeeC inoue;
    EmployeeC *someone;
    someone = &inoue;
    someone->number = 1234;
    strcpy(someone->name, "井上真一");
    someone->salary = 100000;
    someone->showData();
    
    EmployeeC *ec;
    MySample ms;
    ec = ms.retObject();
    ms.useObject(ec);
    
    // Book class
    Book bk;
    bk.setPage(123);
    cout << bk.getPage() << endl;
    bk.setPage(30000);
    cout << bk.getPage() << endl;
    
    SimpleMath sm;
    double x1, x2;
    
    // 2次方程式の解を求める
    if (sm.quadratic(3, 10, 7, &x1, &x2) == true)
    {
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
    }
    else
    {
        cout << "解なし" << endl;
    }
    
    EmployeeC human;
    EmployeeC sophisticatedHuman(1, "洗練された人", 1000000);
    
    myFunc();
    MyClass obj2;
    obj2.number = 2;
    
    //Salesman man;
    //man.ShowData();
    
    NewClass ncOjb(2,3);
    cout << "***********" << endl;
    
    NewClass newObj;
    // 継承したメンバ関数
    newObj.func1(123);
    // オーバーライドしたメンバ関数
    newObj.func2("技術評論社");
    
    // 基本クラスのオブジェクト
    MyClass mc;
    //仮想関数を呼ば出す
    mc.func2("基本クラスの仮想関数");
    
    // オブジェクトを作成
    Director d(1111, "役員一郎", 500000, 1000);
    Manager m1(2222, "課長一郎", 3500000, 10000);
    Manager m2(3333, "課長次郎", 3000000, 5000);
    Salesman s1(4444, "営業一郎", 230000, 1235);
    Salesman s2(5555, "営業次郎", 250000, 4567);
    Salesman s3(6666, "営業三郎", 270000, 6789);
    
    d.showData();
    cout << "**************************" << endl;
    m1.showData();
    cout << "**************************" << endl;
    m2.showData();
    cout << "**************************" << endl;
    s1.showData();
    cout << "**************************" << endl;
    s2.showData();
    cout << "**************************" << endl;
    s3.showData();
    cout << "**************************" << endl;
    
    // オーバーライドによる多様性(たぶん、一番重要)
    // 基本クラスのポインタの配列を作成する
    EmployeeC *p[6];
    
    // 派生クラスのオブジェクトを作成し、基本クラスのポインタに代入する
    Director y(1111, "役員一郎", 500000, 1000);
    p[0] = &y;
    Manager b1(2222, "課長一郎", 3500000, 10000);
    p[1] = &b1;
    Manager b2(3333, "課長次郎", 3000000, 5000);
    p[2] = &b2;
    Salesman e1(4444, "営業一郎", 230000, 1235);
    p[3] = &e1;
    Salesman e2(5555, "営業次郎", 250000, 4567);
    p[4] = &e2;
    Salesman e3(6666, "営業三郎", 270000, 6789);
    p[5] = &e3;
    
    // メンバ関数を呼び出す
    for (int i = 0; i < 6; i++)
    {
        p[i]->showData();
        cout << "***オーバーライドによる多様性***" << endl;
    }
    
    // オーバーライドと多様性を活用した「お絵かきプログラム」
    Figure *pF[100];
    for (int i = 0; i < 100; ++i)
    {
        pF[i] = NULL;
    }
    
    Circle c1;
    pF[Figure::figNum] = &c1;
    Triangle t1, t2;
    pF[Figure::figNum] = &t1;
    pF[Figure::figNum] = &t2;
    Regtangle r1, r2, r3;
    pF[Figure::figNum] = &r1;
    pF[Figure::figNum] = &r2;
    pF[Figure::figNum] = &r3;
    
    // 図の描画
    for (int i = 0; (pF + i) != NULL; i++)
    // for (int i = 0; i <= Figure::figNum; i++)
    {
        //cout << i << endl;
        pF[i]->draw();
    }
    cout << endl;
    
    // 先頭から３番目の図形を削除する
    // 3番目<-4番目, 4番目<-5番目, 5番目<-6番目
    // i= 2~4
    for (int i=2; i<5; i++)
    // for (i=2; i<=Figure::figNum; i++)
    {
        pF[i] = pF[i+1];
    }
    // ポインタpF[2]はpF[3]の中身に書き換わった。
    // pF[4]をNULLにする
    pF[4] = NULL;
    
    // 図の再描画
    for (int i = 0; (pF + i) != NULL; i++)
    // for (i = 0; i <= Figure::figNum; i++)
    {
        pF[i]->draw();
    }
    cout << endl;
    
    // staicメンバ変数
    cout << "現在の社員数:" << EmployeeC::objNum << endl;
    
    // 集約　グローバルオブジェクト
    yahoo.number = 1234;
    strcpy(yahoo.name, "YAHOO");
    yahoo.salary = 2000000;
    strcpy(yahoo.phone.number, "111-1111-1111");
    yahoo.phone.smart = true;
    yahoo.showPhone();
    
    // 集約　ローカルオブジェクト
    EmployeeC rakuten;
    rakuten.number = 1235;
    strcpy(yahoo.name, "楽天");
    rakuten.salary = 1000000;
    strcpy(rakuten.phone.number, "222-2222-2222");
    rakuten.phone.smart = true;
    rakuten.showPhone();
    
    // 集約　動的オブジェクト
    EmployeeC *amazon = new EmployeeC;
    amazon->number = 1236;
    strcpy(amazon->name, "Amazon");
    amazon->salary = 30000000;
    strcpy(amazon->phone.number, "333-3333-3333");
    amazon->phone.smart = false;
    amazon->showPhone();
    delete amazon;
    
    // メンバオブジェクトの引数付きコンストラクタの処理
    EmployeeC google(1111, const_cast<char*>("google"), 10101010, const_cast<char*>("070-4453-9999"), true);
    
    google.showData();
    google.showPhone();
    
    // コピーコンストラクタ
    cout << "ここからコピーコンストラクタのテスト" << endl;
    EmployeeC testObj(1001, const_cast<char*>("TEST"), 10, const_cast<char*>("000-1111-2222"), true);
    
    cout << "show()を呼び出します。" << endl;
    show(testObj);
    cout << "show()を抜けました." << endl;
    
    cout << "氏名：" << testObj.NAME << endl;
    cout << "集約オブジェクトの動的Owner:" << testObj.phone.owner << endl;
    
    // 代入演算子のオーバーロード
    EmployeeC takuro, takuya;
    takuro.number = 1234;
    strcpy(takuro.NAME, "たくろう");
    takuro.salary = 22222;
    
    // オブジェクトを代入
    takuya = takuro;
    
    cout << "takuya:" << takuya.NAME << endl;
    strcpy(takuya.NAME, "技術たくや");
    cout << "takuya:" << takuya.NAME << endl;
    // takuroのNAMEは変わらない
    cout << "takuro:" << takuro.NAME << endl;
    
    // 算術演算子のオーバーロード
    Point A, B, C;
    A.x = 1;
    A.y = 2;
    B.x = 3;
    B.y = 4;
    
    C = A - B;
    
    cout << "x座標：" << C.x << endl;
    cout << "y座標：" << C.y << endl;
    
    // 比較演算子のオーバーロード
    Point X, Y;
    
    X.x = 1;
    X.y = 2;
    Y.x = 3;
    Y.y = 4;
    
    if (X == Y)
    {
        cout << "XとYは等しい" << endl;
    }
    else
    {
        cout << "XとYは等しくない" << endl;
    }
    
    if (X > Y)
    {
        cout << "XはYよりも大きい" << endl;
    }
    else
    {
        cout << "XはYよりも大きくない" << endl;
    }
    
    
    return 0;
}

// コピーコンストラクタ用
void show(EmployeeC obj)
{
    cout << "社員番号:" << obj.number << endl;
    cout << "氏名：" << obj.name << endl;
    cout << "給与:" << obj.salary << endl;
    cout << "動的:" << obj.NAME << endl;
    cout << "集約オブジェクトのTEL:" << obj.phone.number << endl;
    cout << "集約オブジェクトの動的owner:" << obj.phone.owner << endl;
}
