// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"


// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);


TBitField::TBitField(int len)
{
    try {
        if (len < 1)
            throw 5;
        BitLen = len;
        MemLen = (len + SizeType) / SizeType;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = 0;
    }
    catch (int a) {
        ////
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    try {
        if (bf.MemLen < 1)
            throw 5;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    catch (int a) {
        ////
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    try {
        if (n < 0 || n >= BitLen)
            throw 6;
        return n / SizeType;
    }
    catch (int a) {
        ////
    }
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{

    try {
        if (n < 0 || n >= BitLen)
            throw 6;
        return ((TELEM)1) << (n % SizeType);
    }
    catch (int a) {
        ////
    }
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    pMem[GetMemIndex(n)] &= (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return pMem[GetMemIndex(n)]&(GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    try {
        if (bf.MemLen < 1)
            throw 5;
        if (MemLen != bf.MemLen) {
            delete[] pMem;
            MemLen = bf.MemLen;
            pMem = new TELEM[MemLen];
        }
        BitLen = bf.BitLen;
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
        return *this;
    }
    catch (int a) {
        ////
    }
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (bf.BitLen != BitLen)
        return 0;
    int fl = 1;
    for (int i = 0; i < MemLen-1; i++)
        if (bf.pMem[i] != pMem[i])
            fl = 0;
    for (int i = (MemLen - 1) * SizeType; i < BitLen; i++)
        if (GetBit(i) != bf.GetBit(i))
            fl = 0;
    return fl;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (bf.BitLen != BitLen)
        return 1;
    int fl = 1;
    for (int i = 0; i < MemLen-1; i++)
        if (bf.pMem[i] != pMem[i])
            fl = 0;
    for (int i = (MemLen - 1) * SizeType; i < BitLen; i++)
        if (GetBit(i) != bf.GetBit(i))
            fl = 0;
    return 1-fl;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    try {
        if (BitLen == 0 && bf.BitLen == 0)
            throw 10;
        TBitField t(max(BitLen,bf.BitLen));

        for (int i = 0; i < MemLen - 1; i++)
            t.pMem[i] |= pMem[i];

        for (int i = (MemLen - 1) * SizeType; i < BitLen; i++)
                if (GetBit(i))
                    t.SetBit(i);

        for (int i = 0; i < bf.MemLen - 1; i++)
            t.pMem[i] |= bf.pMem[i];

        for (int i = (bf.MemLen - 1) * SizeType; i < bf.BitLen; i++)
            if (bf.GetBit(i))
                t.SetBit(i);

        return t;
    }
    catch (int a) {
        ////
    }
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    try {
        if (BitLen == 0 && bf.BitLen == 0)
            throw 10;

        TBitField t(max(BitLen, bf.BitLen));

        for (int i = 0; i < min(MemLen,bf.MemLen) - 1; i++)
            t.pMem[i] |= (bf.pMem[i]&pMem[i]);

        for (int i = (min(bf.MemLen, MemLen) - 1) * SizeType; i < min(bf.BitLen, BitLen); i++)
            if ((GetBit(i) & bf.GetBit(i)))
                t.SetBit(i);

        return t;
    }
    catch (int a) {
        ////
    }
}

TBitField TBitField::operator~(void) // отрицание
{
    try {
        if (BitLen == 0)
            throw 10;
        TBitField t(BitLen);
        for (int i = 0; i < MemLen-1; i++)
            t.pMem[i] = (~pMem[i]);
        for (int i = (MemLen - 1) * SizeType; i < BitLen; i++)
            if (!GetBit(i))
                t.SetBit(i);
        return t;
    }
    catch (int a) {
        ////
    }
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    try {
        if (bf.MemLen < 1)
            throw 6;
        char o;
        for (int i = 0; i < bf.BitLen; i++) {
            cin >> o;
            if (o == '1')
                bf.SetBit(i);
        }
        return istr;
    }
    catch (int a) {
        ////
    }
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) {  
        ostr << (bf.GetBit(i)!=0);
    }
    return ostr;
}
