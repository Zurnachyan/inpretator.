#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

struct TypeInt {
    std::string name;
    int value = 0;
};

struct TypeDouble {
    std::string name;
    double value = 0;
};

struct TypeString {
    std::string name;
    std::string value = "";
};

struct TypeBool {
    std::string name;
    bool value = 0;
};

std::vector <std::string> keywords = { "int", "double", "line", "logic", "if", "cycle", "print" };
std::vector <std::string> popoxakan;
std::vector <TypeInt> vecI;
std::vector <TypeDouble> vecD;
std::vector <TypeString> vecS;
std::vector <TypeBool> vecB;

void Int(std::string st, int num);
void Double(std::string st, double num);
void Line(std::string st, std::string num);
void Logic(std::string st, bool num);
bool is_number(std::string st);
void sum(std::string st, std::string str, std::string stri);
void sum(std::string st, double str, std::string stri);
void sum(std::string st, std::string str, double stri);
void sum(std::string st, double str, double stri);
void sub(std::string st, std::string str, std::string stri);
void sub(std::string st, double str, std::string stri);
void sub(std::string st, std::string str, double stri);
void sub(std::string st, double str, double stri);
void mul(std::string st, std::string str, std::string stri);
void mul(std::string st, double str, std::string stri);
void mul(std::string st, std::string str, double stri);
void mul(std::string st, double str, double stri);
void div(std::string st, std::string str, std::string stri);
void div(std::string st, double str, std::string stri);
void div(std::string st, std::string str, double stri);
void div(std::string st, double str, double stri);
void entitle(std::string st, std::string str);
void mathSign(std::string vera, std::string popox1, std::string sign, std::string popox2);
void mathSign(std::string vera, double popox1, std::string sign, std::string popox2);
void mathSign(std::string vera, std::string popox1, std::string sign, double popox2);
void mathSign(std::string vera, double popox1, std::string sign, double popox2);
bool to_bool(double& st, std::string sign, double& str);
bool condition(std::stringstream& sline);
void print(std::string st);
void translate(std::fstream& fin);

int main(){   
    std::fstream file;
    std::string file_name;
    std::cout << "Enter the file name" << std::endl;
    std::cin >> file_name;
    file.open(file_name, std::fstream::in);
    if (!file.is_open()) {
        std::cout << "Error while opening the file" << std::endl;
    }
    else {
        translate(file);
    }

    file.close();

    return 0; 
}

void translate(std::fstream& fin) {
    std::string str, st, tox, tox2, tox1 = "";
    int num = 0;
    double d_num = 0;
    std::string arj = "";
    unsigned p = 0;
    bool flag_if = false, flag_while = false, flag_err = true;

    while (!fin.eof()) {
        flag_err = true;
        st = "";
        std::getline(fin, str);

        if (str != "end_if" && flag_if) {
            continue;
        }
        else {
            flag_if = false;
        }

        if (str != "end_cycle" && flag_while) {
            continue;
        }
        else {
            if (str == "end_cycle" && !flag_while) {
                fin.seekg(p);
                continue;
            }
            flag_while = false;
        }

        std::stringstream sline(str);
        sline >> st;
        if (st == keywords[0]) {    //int
            sline >> st;
            bool flag = false;
            for (int i = 0; i < popoxakan.size(); i++) {
                if (popoxakan[i] == st) {
                    std::cout << "The variables have the same name" << std::endl;
                    flag = true;
                    break;
                }
            }
            if (flag) {
                continue;
            }
            popoxakan.push_back(st);
            sline >> tox;
            if (tox == "=") {
                sline >> num;
                Int(st, num);
                tox = "";
            }
            else {
                Int(st, 0);
            }
            flag_err = false;
            continue;
        }
        else if (st == keywords[1]) {   //double
            sline >> st;
            bool flag = false;
            for (int i = 0; i < popoxakan.size(); i++) {
                if (popoxakan[i] == st) {
                    std::cout << "The variables have the same name" << std::endl;
                    flag = true;
                    break;
                }
            }
            if (flag) {
                continue;
            }
            popoxakan.push_back(st);
            sline >> tox;
            if (tox == "=") {
                sline >> d_num;
                Double(st, d_num);
                tox = "";
            }
            else {
                Double(st, 0);
            }
            flag_err = false;
            continue;
        }
        else if (st == keywords[2]) {   //string
            sline >> st;
            bool flag = false;
            for (int i = 0; i < popoxakan.size(); i++) {
                if (popoxakan[i] == st) {
                    std::cout << "The variables have the same name" << std::endl;
                    flag = true;
                    break;
                }
            }
            if (flag) {
                continue;
            }
            popoxakan.push_back(st);
            sline >> tox;
            if (tox == "=") {
                sline >> arj;
                arj.erase(arj.find('\"'), 1);
                arj.erase(arj.find('\"'), 1);
                Line(st, arj);
                tox = "";
            }
            else {
                Line(st, "");
            }
            flag_err = false;
            continue;
        }
        else if (st == keywords[3]) {   //bool
            sline >> st;
            bool flag = false;
            for (int i = 0; i < popoxakan.size(); i++) {
                if (popoxakan[i] == st) {
                    std::cout << "The variables have the same name" << std::endl;
                    flag = true;
                    break;
                }
            }
            if (flag) {
                continue;
            }
            popoxakan.push_back(st);
            sline >> tox;
            if (tox == "=") {
                sline >> tox;
                if (tox == "false" || tox == "0") {
                    Logic(st, false);
                }
                else {
                    Logic(st, true);
                }
            }
            else {
                Logic(st, true);
            }
            flag_err = false;
            continue;
        }
        else if (st == keywords[4]) {       //if
            flag_err = false;
            if (!condition(sline)) {
                flag_if = true;
                continue;
            }
        }
        else if (st == keywords[5]) {        //while (cycle)
            flag_err = false;
            p = fin.tellg();
            p = p - str.size() - st.size();
            if (!condition(sline)) {
                flag_while = true;
                continue;
            }
        }
        else if (st == keywords[6]) {       //print
            getline(sline, tox);
            tox.erase(0, 1);
            print(tox);
            flag_err = false;
            continue;
        }
        else {
            for (int i = 0; i < popoxakan.size(); i++) {    //=, +, -, *, /
                if (popoxakan[i] == st) {
                    sline >> tox;
                    flag_err = false;
                    if (tox == "=") {
                        sline >> tox;
                        sline >> tox1;
                        sline >> tox2;
                        if (tox1 != "") {
                            if (is_number(tox) && is_number(tox2)) {
                                mathSign(st, std::stod(tox), tox1, std::stod(tox2));
                            }
                            else {
                                if (is_number(tox)) {
                                    mathSign(st, std::stod(tox), tox1, tox2);
                                }
                                else {
                                    if (is_number(tox2)) {
                                        mathSign(st, tox, tox1, std::stod(tox2));
                                    }
                                    else {
                                        mathSign(st, tox, tox1, tox2);
                                    }
                                }
                            }
                        }
                        else {
                            entitle(st, tox);
                        }
                    }
                    tox = ""; tox1 = ""; tox2 = "";
                    flag_err = false;
                    break;
                }
            }
        }
        if (!flag_err) {
            std::cout << "Error" << std::endl;
        }
    }
}


void Int(std::string st, int num) {
    TypeInt tmp;
    tmp.name = st;
    tmp.value = num;
    vecI.push_back(tmp);
}

void Double(std::string st, double num) {
    TypeDouble tmp;
    tmp.name = st;
    tmp.value = num;
    vecD.push_back(tmp);
}

void Line(std::string st, std::string num) {
    TypeString tmp;
    tmp.name = st;
    tmp.value = num;
    vecS.push_back(tmp);
}

void Logic(std::string st, bool num) {
    TypeBool tmp;
    tmp.name = st;
    tmp.value = num;
    vecB.push_back(tmp);
}


bool is_number(std::string st) {
    bool flag = true;
    for (int i = 0; i < st.length(); i++) {
        if (st[i] == '.' && flag) {
            flag = false;
            continue;
        }
        if (!(st[i] >= '0' && st[i] <= '9')) {
            return false;
        }
    }
    return true;
}


void sum(std::string st, std::string str, std::string stri) {
    double x = 0, y = 0;
    bool flag1 = true, flag2 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (flag1 == false && flag2 == false) {
            break;
        }
        if (vecI[i].name == str && flag1) {
            x = vecI[i].value;
            flag1 = false;
        }
        if (vecI[i].name == stri && flag2) {
            y = vecI[i].value;
            flag2 = false;
        }
    }

    if (flag1 || flag2) {
        for (int i = 0; i < vecD.size(); i++) {
            if (flag1 == false && flag2 == false) {
                break;
            }
            if (vecD[i].name == str && flag1) {
                x = vecD[i].value;
                flag1 = false;
            }
            if (vecD[i].name == stri && flag2) {
                y = vecD[i].value;
                flag2 = false;
            }
        }
    }

    bool flag3 = true;
    for (int i = 0; i < vecD.size(); i++) {
        if (vecD[i].name == st) {
            vecD[i].value = x + y;
            flag3 = false;
            break;
        }
    }

    if (flag3) {
        for (int i = 0; i < vecI.size(); i++) {
            if (vecI[i].name == st) {
                vecI[i].value = x + y;
                flag3 = false;
                break;
            }
        }
    }

    if (flag1 || flag2 || flag3) {
        std::cout << "Unknown veriable";
    }
}

void sum(std::string st, double str, std::string stri) {
    double x = 0;
    bool flag1 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == stri) {
            x = vecI[i].value;
            flag1 = false;
            break;
        }
    }

    if (flag1) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == stri) {
                x = vecD[i].value;
                flag1 = false;
                break;
            }
        }
    }

    bool flag2 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == st) {
            vecI[i].value = x + str;
            flag2 = false;
            break;
        }
    }

    if (flag2) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == st) {
                vecD[i].value = x + str;
                flag2 = false;
                break;
            }
        }
    }

    if (flag1 || flag2) {
        std::cout << "Unknown veriable";
    }
}

void sum(std::string st, std::string str, double stri) {
    double x = 0;
    bool flag1 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == str) {
            x = vecI[i].value;
            flag1 = false;
            break;
        }
    }

    if (flag1) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == str) {
                x = vecD[i].value;
                flag1 = false;
                break;
            }
        }
    }

    bool flag2 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == st) {
            vecI[i].value = stri + x;
            flag2 = false;
            break;
        }
    }

    if (flag2) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == st) {
                vecD[i].value = stri + x;
                flag2 = false;
                break;
            }
        }
    }

    if (flag1 || flag2) {
        std::cout << "Unknown veriable";
    }
}

void sum(std::string st, double str, double stri) {
    bool flag = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == st) {
            vecI[i].value = str + stri;
            flag = false;
            break;
        }
    }

    if (flag) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == st) {
                vecD[i].value = str + stri;
                flag = false;
                break;
            }
        }
    }

    if (flag) {
        std::cout << "Unknown variable" << std::endl;
    }
}


void sub(std::string st, std::string str, std::string stri) {
    double x = 0, y = 0;
    bool flag1 = true, flag2 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (flag1 == false && flag2 == false) {
            break;
        }
        if (vecI[i].name == str && flag1) {
            x = vecI[i].value;
            flag1 = false;
        }
        if (vecI[i].name == stri && flag2) {
            y = vecI[i].value;
            flag2 = false;
        }
    }

    if (flag1 == true || flag2 == true) {
        for (int i = 0; i < vecD.size(); i++) {
            if (flag1 == false && flag2 == false) {
                break;
            }
            if (vecD[i].name == str && flag1) {
                x = vecD[i].value;
                flag1 = false;
            }
            if (vecD[i].name == stri && flag2) {
                y = vecD[i].value;
                flag2 = false;
            }
        }
    }

    bool flag3 = true;
    for (int i = 0; i < vecD.size(); i++) {
        if (vecD[i].name == st) {
            vecD[i].value = x - y;
            flag3 = false;
            break;
        }
    }

    if (flag3) {
        for (int i = 0; i < vecI.size(); i++) {
            if (vecI[i].name == st) {
                vecI[i].value = x - y;
                flag3 = false;
                break;
            }
        }
    }

    if (flag1 || flag2 || flag3) {
        std::cout << "Unknown veriable";
    }
}

void sub(std::string st, double str, std::string stri) {
    double x = 0;
    bool flag1 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == stri) {
            x = vecI[i].value;
            flag1 = false;
            break;
        }
    }

    if (flag1) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == stri) {
                x = vecD[i].value;
                flag1 = false;
                break;
            }
        }
    }

    bool flag2 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == st) {
            vecI[i].value = str - x;
            flag2 = false;
            break;
        }
    }

    if (flag2) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == st) {
                vecD[i].value = str - x;
                flag2 = false;
                break;
            }
        }
    }

    if (flag1 || flag2) {
        std::cout << "Unknown veriable";
    }
}

void sub(std::string st, std::string str, double stri) {
    double x = 0;
    bool flag1 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == str) {
            x = vecI[i].value;
            flag1 = false;
            break;
        }
    }

    if (flag1) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == str) {
                x = vecD[i].value;
                flag1 = false;
                break;
            }
        }
    }

    bool flag2 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == st) {
            vecI[i].value = x - stri;
            flag2 = false;
            break;
        }
    }

    if (flag2) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == st) {
                vecD[i].value = x - stri;
                flag2 = false;
                break;
            }
        }
    }

    if (flag1 || flag2) {
        std::cout << "Unknown veriable";
    }
}

void sub(std::string st, double str, double stri) {
    bool flag = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == st) {
            vecI[i].value = str - stri;
            flag = false;
            break;
        }
    }

    if (flag) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == st) {
                vecD[i].value = str - stri;
                flag = false;
                break;
            }
        }
    }

    if (flag) {
        std::cout << "Unknown variable" << std::endl;
    }
}


void mul(std::string st, std::string str, std::string stri) {
    double x = 0, y = 0;
    bool flag1 = true, flag2 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (flag1 == false && flag2 == false) {
            break;
        }
        if (vecI[i].name == str && flag1) {
            x = vecI[i].value;
            flag1 = false;
        }
        if (vecI[i].name == stri && flag2) {
            y = vecI[i].value;
            flag2 = false;
        }
    }

    if (flag1 == true || flag2 == true) {
        for (int i = 0; i < vecD.size(); i++) {
            if (flag1 == false && flag2 == false) {
                break;
            }
            if (vecD[i].name == str && flag1) {
                x = vecD[i].value;
                flag1 = false;
            }
            if (vecD[i].name == stri && flag2) {
                y = vecD[i].value;
                flag2 = false;
            }
        }
    }

    bool flag3 = true;
    for (int i = 0; i < vecD.size(); i++) {
        if (vecD[i].name == st) {
            vecD[i].value = x * y;
            flag3 = false;
            break;
        }
    }

    if (flag3) {
        for (int i = 0; i < vecI.size(); i++) {
            if (vecI[i].name == st) {
                vecI[i].value = x * y;
                flag3 = false;
                break;
            }
        }
    }

    if (flag1 || flag2 || flag3) {
        std::cout << "Unknown veriable";
    }
}

void mul(std::string st, double str, std::string stri) {
    double x = 0;
    bool flag1 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == stri) {
            x = vecI[i].value;
            flag1 = false;
            break;
        }
    }

    if (flag1) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == stri) {
                x = vecD[i].value;
                flag1 = false;
                break;
            }
        }
    }

    bool flag2 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == st) {
            vecI[i].value = str * x;
            flag2 = false;
            break;
        }
    }

    if (flag2) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == st) {
                vecD[i].value = str * x;
                flag2 = false;
                break;
            }
        }
    }

    if (flag1 || flag2) {
        std::cout << "Unknown veriable";
    }
}

void mul(std::string st, std::string str, double stri) {
    double x = 0;
    bool flag1 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == str) {
            x = vecI[i].value;
            flag1 = false;
            break;
        }
    }

    if (flag1) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == str) {
                x = vecD[i].value;
                flag1 = false;
                break;
            }
        }
    }

    bool flag2 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == st) {
            vecI[i].value = x * stri;
            flag2 = false;
            break;
        }
    }

    if (flag2) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == st) {
                vecD[i].value = x * stri;
                flag2 = false;
                break;
            }
        }
    }

    if (flag1 || flag2) {
        std::cout << "Unknown veriable";
    }
}

void mul(std::string st, double str, double stri) {
    bool flag = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == st) {
            vecI[i].value = str * stri;
            flag = false;
            break;
        }
    }

    if (flag) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == st) {
                vecD[i].value = str * stri;
                flag = false;
                break;
            }
        }
    }

    if (flag) {
        std::cout << "Unknown variable" << std::endl;
    }
}


void div(std::string st, std::string str, std::string stri) {
    double x = 0, y = 0;
    bool flag1 = true, flag2 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (flag1 == false && flag2 == false) {
            break;
        }
        if (vecI[i].name == str && flag1) {
            x = vecI[i].value;
            flag1 = false;
        }
        if (vecI[i].name == stri && flag2) {
            y = vecI[i].value;
            flag2 = false;
        }
    }

    if (flag1 == true || flag2 == true) {
        for (int i = 0; i < vecD.size(); i++) {
            if (flag1 == false && flag2 == false) {
                break;
            }
            if (vecD[i].name == str && flag1) {
                x = vecD[i].value;
                flag1 = false;
            }
            if (vecD[i].name == stri && flag2) {
                y = vecD[i].value;
                flag2 = false;
            }
        }
    }

    bool flag3 = true;
    if (y == 0) {
        std::cout << "The denominator cannot be 0" << std::endl;
        flag3 = false;
    }
    else {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == st) {
                vecD[i].value = x / y;
                flag3 = false;
                break;
            }
        }
    }

    if (flag3) {
        for (int i = 0; i < vecI.size(); i++) {
            if (vecI[i].name == st) {
                vecI[i].value = x / y;
                flag3 = false;
                break;
            }
        }
    }

    if (flag1 || flag2 || flag3) {
        std::cout << "Unknown veriable";
    }
}

void div(std::string st, double str, std::string stri) {
    double x = 0;
    bool flag1 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == stri) {
            x = vecI[i].value;
            flag1 = false;
            break;
        }
    }

    if (flag1) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == stri) {
                x = vecD[i].value;
                flag1 = false;
                break;
            }
        }
    }

    bool flag2 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == st) {
            vecI[i].value = str / x;
            flag2 = false;
            break;
        }
    }

    if (flag2) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == st) {
                vecD[i].value = str / x;
                flag2 = false;
                break;
            }
        }
    }

    if (flag1 || flag2) {
        std::cout << "Unknown veriable";
    }
}

void div(std::string st, std::string str, double stri) {
    double x = 0;
    bool flag1 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == str) {
            x = vecI[i].value;
            flag1 = false;
            break;
        }
    }

    if (flag1) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == str) {
                x = vecD[i].value;
                flag1 = false;
                break;
            }
        }
    }

    bool flag2 = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == st) {
            vecI[i].value = x / stri;
            flag2 = false;
            break;
        }
    }

    if (flag2) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == st) {
                vecD[i].value = x / stri;
                flag2 = false;
                break;
            }
        }
    }

    if (flag1 || flag2) {
        std::cout << "Unknown veriable";
    }
}

void div(std::string st, double str, double stri) {
    bool flag = true;
    for (int i = 0; i < vecI.size(); i++) {
        if (vecI[i].name == st) {
            vecI[i].value = str / stri;
            flag = false;
            break;
        }
    }

    if (flag) {
        for (int i = 0; i < vecD.size(); i++) {
            if (vecD[i].name == st) {
                vecD[i].value = str / stri;
                flag = false;
                break;
            }
        }
    }

    if (flag) {
        std::cout << "Unknown variable" << std::endl;
    }
}


void entitle(std::string st, std::string str) {
    bool flag = true;
    double x = 0;
    std::string ch = "";

    if (!is_number(str)) {
        for (int i = 0; i < vecI.size(); i++) {
            if (str == vecI[i].name) {
                x = vecI[i].value;
                flag = false;
                break;
            }
        }

        if (flag) {
            for (int i = 0; i < vecD.size(); i++) {
                if (str == vecD[i].name) {
                    x = vecD[i].value;
                    flag = false;
                    break;
                }
            }
        }

        bool log = false;
        if (flag) {
            for (int i = 0; i < vecS.size(); i++) {
                if (str == vecS[i].name) {
                    ch = vecS[i].value;
                    flag = false;
                    log = false;
                    break;
                }
            }
        }

        if (ch == "" && str[0] == '\"' && str[str.length() - 1] == '\"' && log) {
            str.erase(str.find('\"'), 1);
            str.erase(str.find('\"'), 1);
            ch = str;
            flag = false;
        }
    }
    else {
        x = stod(str);
        flag = false;
    }


    bool flag1 = true;

    if (flag) {
        std::cout << "Unknown variable or value" << std::endl;
        flag1 = false;
    }
    else {
        for (int i = 0; i < vecI.size(); i++) {
            if (st == vecI[i].name) {
                vecI[i].value = x;
                flag1 = false;
                break;
            }
        }
        if (flag1) {
            for (int i = 0; i < vecD.size(); i++) {
                if (st == vecD[i].name && flag1) {
                    vecD[i].value = x;
                    flag1 = false;
                    break;
                }
            }
        }
        if (flag1) {
            for (int i = 0; i < vecS.size(); i++) {
                if (st == vecS[i].name && flag1) {
                    vecS[i].value = ch;
                    flag1 = false;
                    break;
                }
            }
        }
    }

    if (flag1) {
        std::cout << "Unknown variable" << std::endl;
    }
}


void mathSign(std::string vera, std::string popox1, std::string sign, std::string popox2) {
    if (sign == "+") {
        sum(vera, popox1, popox2);
    }
    else if (sign == "-") {
        sub(vera, popox1, popox2);
    }
    else if (sign == "*") {
        mul(vera, popox1, popox2);
    }
    else if (sign == "/") {
        div(vera, popox1, popox2);
    }
    else {
        std::cout << "Unknown sign";
    }
}

void mathSign(std::string vera, double popox1, std::string sign, std::string popox2) {
    if (sign == "+") {
        sum(vera, popox1, popox2);
    }
    else if (sign == "-") {
        sub(vera, popox1, popox2);
    }
    else if (sign == "*") {
        mul(vera, popox1, popox2);
    }
    else if (sign == "/") {
        div(vera, popox1, popox2);
    }
    else {
        std::cout << "Unknown sign";
    }
}

void mathSign(std::string vera, std::string popox1, std::string sign, double popox2) {
    if (sign == "+") {
        sum(vera, popox1, popox2);
    }
    else if (sign == "-") {
        sub(vera, popox1, popox2);
    }
    else if (sign == "*") {
        mul(vera, popox1, popox2);
    }
    else if (sign == "/") {
        div(vera, popox1, popox2);
    }
    else {
        std::cout << "Unknown sign";
    }
}

void mathSign(std::string vera, double popox1, std::string sign, double popox2) {
    if (sign == "+") {
        sum(vera, popox1, popox2);
    }
    else if (sign == "-") {
        sub(vera, popox1, popox2);
    }
    else if (sign == "*") {
        mul(vera, popox1, popox2);
    }
    else if (sign == "/") {
        div(vera, popox1, popox2);
    }
    else {
        std::cout << "Unknown sign";
    }
}


bool to_bool(double& st, std::string sign, double& str) {
    if (sign == "<") {
        return st < str;
    }
    else if (sign == ">") {
        return st > str;
    }
    else if (sign == "==") {
        return st == str;
    }
    else {
        std::cout << "Unknown sign";
        return -1;
    }
}

bool condition(std::stringstream& sline) {
    std::string st, sign;
    sline >> st;
    double x = 0, y = 0;
    bool flag = true, flag1 = true;

    if (is_number(st)) {
        x = stod(st);
    }
    else {
        for (int i = 0; i < vecI.size(); i++) {
            if (st == vecI[i].name) {
                x = vecI[i].value;
                flag = false;
                break;
            }
        }
        if (flag) {
            for (int i = 0; i < vecD.size(); i++) {
                if (st == vecD[i].name) {
                    x = vecD[i].value;
                    flag = false;
                    break;
                }
            }
        }
    }

    sline >> sign;
    sline >> st;

    if (is_number(st)) {
        y = stod(st);
    }
    else {
        for (int i = 0; i < vecI.size(); i++) {
            if (st == vecI[i].name) {
                y = vecI[i].value;
                flag1 = false;
                break;
            }
        }
        if (flag1) {
            for (int i = 0; i < vecD.size(); i++) {
                if (st == vecD[i].name) {
                    y = vecD[i].value;
                    flag1 = false;
                    break;
                }
            }
        }
    }

    return to_bool(x, sign, y);
}


void print(std::string st) {
    if (st[0] == '\"' && st[st.length() - 1] == '\"') {
        st.erase(st.find('\"'), 1);
        st.erase(st.find('\"'), 1);
        std::cout << st << std::endl;
    }
    else {
        bool flag = true;
        for (int i = 0; i < vecI.size(); i++) {
            if (vecI[i].name == st) {
                std::cout << vecI[i].value << std::endl;
                flag = false;
                break;
            }
        }

        if (flag) {
            for (int i = 0; i < vecD.size(); i++) {
                if (vecD[i].name == st) {
                    std::cout << vecD[i].value << std::endl;
                    flag = false;
                    break;
                }
            }
        }

        if (flag) {
            for (int i = 0; i < vecS.size(); i++) {
                if (vecS[i].name == st) {
                    std::cout << vecS[i].value << std::endl;
                    flag = false;
                    break;
                }
            }
        }

        if (flag) {
            for (int i = 0; i < vecB.size(); i++) {
                if (vecB[i].name == st) {
                    std::cout << vecB[i].value << std::endl;
                    flag = false;
                    break;
                }
            }
        }

        if (flag) {
            if (is_number(st)) {
                std::cout << stod(st) << std::endl;
            }
            else {
                std::cout << "Unknown veriable" << std::endl;
            }
        }
    }
}