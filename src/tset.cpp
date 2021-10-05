// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp): BitField(mp),MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf),MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem)!=0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return (BitField==s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return BitField!=s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet st(BitField | s.BitField);
    return st;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet t(*this);
    t.InsElem(Elem);
    return t;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet t(*this);
    t.DelElem(Elem);
    return t;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet t(BitField & s.BitField);
    return t;
}

TSet TSet::operator~(void) // дополнение
{
    TSet t(~BitField);
    return t;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int a;
    istr >> a;
    while (a >= 0) {
        s.InsElem(a);
        istr >> a;
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    int fl=0;
    ostr << "{";
    for (int i = 0; i < s.MaxPower; i++)
        if (s.IsMember(i))
            ostr <<(fl?",":"") << i,fl++;
    ostr << "}";
    return ostr;
}
