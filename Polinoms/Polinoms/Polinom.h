#pragma once
#include<iostream>
#include<string>

template <class T>
struct TLink {
	T val;
	TLink<T>* pNext;
};

struct TMonom
{
	double coeff;
	int x, y, z;
	TMonom(int x_ = 0, int y_ = 0, int z_ = 0, double coeff_ = 1.0);
	bool operator < (const TMonom& m)const;
	bool operator == (const TMonom& m)const;
	bool operator >(const TMonom& m)const;
	TMonom& operator =(const TMonom& m);
	TMonom operator *(const TMonom& m);
	TMonom operator *(const double alpha);

	friend std::istream& operator>>(std::istream& in, TMonom& m)
	{
		std::string res;
		in >> res;
		bool flag = false;
		for (unsigned int i = 0; i < res.size(); i++)
		{
			if (res[i] == 'x' || res[i] == 'y' || res[i] == 'z')
			{
				flag = true;
			}
			if (flag)
			{
				if (i + 1 < res.size())
				{
					if (res[i + 1] == '^')
					{
						m.input(res[i], res[i + 2] - '0');
						i += 2;
					}
					else
						m.input(res[i], 1);
				}
				else
					m.input(res[i], 1);

			}
			else
				if (i == 0)
				{
					std::string tmp;
					unsigned int j;
					for (j = 0; j < res.size(); j++)
					{
						if (res[j] == 'x' || res[j] == 'y' || res[j] == 'z')
							break;
						tmp += res[j];
					}
					i = j - 1;
					if (tmp == "-")
						m.coeff = -1;
					else
						m.coeff = std::stod(tmp);
				}
		}
		return in;
	}

	friend std::ostream& operator << (std::ostream& out, const TMonom& m)
	{
		if (m.x + m.y + m.z)
		{
			if (m.coeff != 1.0)
			{
				if (m.coeff != -1.0)
					out << m.coeff;
				else
					out << '-';
			}
			if (m.coeff != 1.0 && m.coeff != -1.0 && m.x)
				out << '*';
			out << m.print('x', m.x);
			if (m.x && m.y)
				out << '*';
			out << m.print('y', m.y);
			if (m.x && m.y && m.z)
				out << '*';
			out << m.print('z', m.z);
		}
		else
			out << m.coeff;
		return out;
	}
	std::string print(char p, int pow) const;
	void input(char p, int val);
};

TMonom::TMonom(int x_, int y_, int z_, double coeff_)
{
	x = x_;
	y = y_;
	z = z_;
	coeff = coeff_;
}

void TMonom::input(char p, int val)
{
	switch (p)
	{
	case 'x':x = val;
		break;
	case'y':y = val;
		break;
	case'z':z = val;
		break;
	}
}

std::string TMonom::print(char p, int pow) const
{
	std::string res = "";
	if (pow != 0)
	{
		if (pow > 1)
		{
			res += p;
			res += '^';
			res += std::to_string(pow);
		}
		else
		{
			res += p;
		}
	}
	return res;
}

bool TMonom::operator <(const TMonom& m) const
{
	int sum = x + y + z;
	int sum_m = m.x + m.y + m.z;
	return sum < sum_m;
}

bool TMonom::operator >(const TMonom& m) const
{
	int sum = x + y + z;
	int sum_m = m.x + m.y + m.z;
	return sum > sum_m;
}

bool TMonom::operator == (const TMonom& m) const
{
	return x == m.x && y == m.y && z == m.z;
}

TMonom& TMonom::operator =(const TMonom& m)
{
	coeff = m.coeff;
	x = m.x;
	y = m.y;
	z = m.z;
	return *this;
}

TMonom TMonom:: operator *(const TMonom& m)
{
	TMonom res;
	res.x = x + m.x;
	res.y = y + m.y;
	res.z = z + m.z;;
	res.coeff = coeff * m.coeff;
	return res;
}

TMonom TMonom:: operator *(const double a)
{
	TMonom res(this->x, this->y, this->z, this->coeff);
	res.coeff *= a;
	return res;
}


template <class T>
class TList {
protected:
	TLink<T>* pFirst, * pLast, * pCurr, * pPrev, * pStop;
	int size, pos;

public:
	TList();
	TList(const TList& list);
	~TList();
	void InsFirst(T elem);
	void InsLast(T elem);
	void DelFirst();
	void Reset() { pCurr = pFirst; }
	bool IsEnd() const { return pCurr == pStop; }
	void GoNext() { pPrev = pCurr; pCurr = pCurr->pNext; }
	void DelCurr();
	void InsCurr(T elem);
	int Get_Size()const { return size; }

	friend std::istream& operator >> (std::istream& in, TList<T>& list)
	{
		std::cout << "size=";
		int t;
		in >> t;
		if (t < 0)
			throw 0;
		for (int i = 0; i < t; i++)
		{
			T tmp;
			in >> tmp;
			list.InsLast(tmp);
		}
		return in;
	}
	friend std::ostream& operator<<(std::ostream& out, const TList<T> list)
	{
		TLink<T>* t = list.pFirst;
		while (t != list.pStop)
		{
			out << t->val << ' ';
			t = t->pNext;
		}
		return out;
	}
};

template<class T>
TList<T>::TList()
{
	pStop = NULL;
	pFirst = pLast = pCurr = pPrev = pStop;
	size = 0;
	pos = 0;
}

template<class T>
TList<T>::TList(const TList<T>& list)
{
	if (list.size == 0)
	{
		pStop = list.pStop;
		pFirst = pLast = pCurr = pPrev = pStop;
		size = 0;
		pos = 0;
	}
	else
	{
		pStop = list.pStop;
		pCurr = pPrev = pStop;
		pos = 0;
		TLink<T>* prev = new TLink<T>;
		prev->val = list.pFirst->val;
		prev->pNext = pStop;
		pFirst = prev;
		TLink<T>* curr = list.pFirst;
		while (curr->pNext != pStop)
		{
			curr = curr->pNext;
			TLink<T>* link = new TLink<T>;
			link->val = curr->val;
			link->pNext = pStop;
			prev->pNext = link;
			prev = link;
		}
		size = list.size;
		pLast = prev;
	}
}

template<class T>
TList<T>::~TList()
{
	pCurr = pPrev = pStop;
	pos = 0;
	while (pFirst != pStop)
	{
		TLink<T>* curr = pFirst->pNext;
		delete pFirst;
		pFirst = curr;
		--size;
	}
	pFirst = pLast = pStop;
}

template<class T>
void TList<T>::InsFirst(T elem)
{
	TLink<T>* tmp = new TLink<T>;
	tmp->val = elem;
	if (size == 0)
	{
		tmp->pNext = pStop;
		pFirst = pLast = tmp;
	}
	else
	{
		tmp->pNext = pFirst;
		pFirst = tmp;
	}
	size++;
}

template<class T>
void TList<T>::InsLast(T elem)
{
	TLink<T>* tmp = new TLink<T>;
	tmp->val = elem;
	tmp->pNext = pStop;
	if (size == 0)
	{
		pFirst = pLast = tmp;
	}
	else
	{
		pLast->pNext = tmp;
		pLast = tmp;
	}
	size++;
}

template<class T>
void TList<T>::DelFirst()
{
	if (size == 0)
		throw 0;
	else
	{
		TLink<T>* t = pFirst->pNext;
		delete pFirst;
		pFirst = t;
		size--;
	}
}

template <class T>
void TList<T>::DelCurr()
{
	if (size == 0 || pCurr == pStop)
		throw 0;
	if (pCurr == pFirst)
	{
		DelFirst();
		pCurr = pFirst;
	}
	else
	{
		pPrev->pNext = pCurr->pNext;
		delete pCurr;
		pCurr = pPrev->pNext;
		size--;
	}
}

template<class T>
void TList<T>::InsCurr(T elem)
{
	if (size == 0)
	{
		InsLast(elem);
		pPrev = pLast;
		pCurr = pPrev->pNext;
	}
	else
	{
		if (pCurr == pFirst)
		{
			InsFirst(elem);
			pPrev = pFirst;
			pCurr = pPrev->pNext;
		}
		else
		{
			TLink<T>* t = new TLink<T>;
			pPrev->pNext = t;
			t->val = elem;
			t->pNext = pCurr;
			pPrev = t;
			size++;
		}
	}
}


template<class T>
class THeadList : public TList<T> {
protected:
	TLink<T>* pHead;
public:
	THeadList();
	THeadList(const THeadList& h);
	~THeadList();
	void InsFirst(T elem);
	void DelFirst();
	void InsLast(T elem);
	void InsCurr(T elem);
	void DelCurr();
};

template<class T>
THeadList<T>::THeadList() :TList<T>()
{
	pHead = new TLink<T>;
	TList<T>::pStop = pHead;
	pHead->pNext = TList<T>::pStop;
	TList<T>::pFirst = TList<T>::pLast = TList<T>::pCurr = TList<T>::pPrev = TList<T>::pStop;
}

template<class T>
THeadList<T>::THeadList(const THeadList<T>& h)
{
	pHead = new TLink<T>;
	TList<T>::pStop = TList<T>::pFirst = TList<T>::pLast = TList<T>::pPrev = TList<T>::pCurr = pHead;
	pHead->pNext = TList<T>::pStop;
	if (h.size)
	{
		TLink<T>* prev = new TLink<T>;
		pHead->pNext = prev;
		TList<T>::pFirst = prev;
		TList<T>::pFirst->val = h.pFirst->val;
		TList<T>::pFirst->pNext = TList<T>::pStop;
		TLink<T>* curr = h.pFirst->pNext;
		while (curr != h.pStop)
		{
			TLink<T>* t = new TLink<T>;
			t->val = curr->val;
			t->pNext = TList<T>::pStop;
			prev->pNext = t;
			prev = t;
			curr = curr->pNext;
		}
		TList<T>::pLast = prev;
	}
	TList<T>::size = h.size;
	TList<T>::pos = 0;
}

template<class T>
THeadList<T>::~THeadList()
{
	TList<T>::~TList();
	delete pHead;
}

template<class T>
void THeadList<T>::InsFirst(T elem)
{
	TList<T>::InsFirst(elem);
	pHead->pNext = TList<T>::pFirst;
}

template <class T>
void THeadList<T>::DelFirst()
{
	TList<T>::DelFirst();
	pHead->pNext = TList<T>::pFirst;
}

template<class T>
void THeadList<T>::InsLast(T elem)
{
	TList<T>::InsLast(elem);
	pHead->pNext = TList<T>::pFirst;
}

template<class T>
void THeadList<T>::InsCurr(T elem)
{
	TList<T>::InsCurr(elem);
	pHead->pNext = TList<T>::pFirst;
}

template <class T>
void THeadList<T>::DelCurr()
{
	TList<T>::DelCurr();
	pHead->pNext = TList<T>::pFirst;
}

class TPolinom :public THeadList<TMonom> {
public:
	TPolinom();
	TPolinom(const TPolinom& p);
	void InsMonom(const TMonom& m);
	TPolinom& operator=(const TPolinom& p);
	TPolinom& operator += (const TPolinom& p);
	TPolinom operator + (const TPolinom& p);
	TPolinom operator * (const double val);
	TPolinom operator * (const TMonom& m);

	friend std::istream& operator >> (std::istream& in, TPolinom& p)
	{
		std::cout << "размер=";
		int t;
		in >> t;
		if (t < 0)
			throw 0;
		for (int i = 0; i < t; i++)
		{
			TMonom m;
			in >> m;
			p.InsMonom(m);
		}
		return in;
	}
	friend std::ostream& operator << (std::ostream& out, TPolinom& p)
	{
		for (p.Reset(); !p.IsEnd(); p.GoNext())
		{
			out << p.pCurr->val << ' ';
		}
		if (!p.size)
			out << "Полином пуст";
		return out;
	}
};

TPolinom::TPolinom() :THeadList<TMonom>()
{
	TMonom tmp;
	tmp.z = -1;
	tmp.coeff = 0.0;
	pHead->val = tmp;
}

TPolinom::TPolinom(const TPolinom& p) : THeadList<TMonom>(p)
{
	pHead->val = p.pHead->val;
}

void TPolinom::InsMonom(const TMonom& m)
{
	Reset();
	while (true)
	{
		if (pCurr->val < m)
		{
			InsCurr(m);
			break;
		}
		if (pCurr->val == m)
		{
			if (pCurr->val.coeff + m.coeff != 0)
				pCurr->val.coeff += m.coeff;
			else
				DelCurr();
			break;
		}
		GoNext();
	}
}

TPolinom& TPolinom::operator+=(const TPolinom& p)
{
	Reset();
	TLink<TMonom>* curr = p.pFirst;
	while (curr != p.pStop)
	{
		if (pCurr->val < curr->val)
		{
			InsCurr(curr->val);
			curr = curr->pNext;
		}
		else
		{
			if (pCurr->val == curr->val)
			{
				double tmp = pCurr->val.coeff + curr->val.coeff;
				pCurr->val.coeff = tmp;
				if (tmp)
					GoNext();
				else
					DelCurr();
				curr = curr->pNext;
			}
			else
				GoNext();
		}
	}
	return *this;
}

TPolinom TPolinom::operator + (const TPolinom& p)
{
	TPolinom res(*this);
	res.Reset();
	TLink<TMonom>* curr = p.pFirst;
	while (curr != p.pStop)
	{
		if (res.pCurr->val < curr->val)
		{
			res.InsCurr(curr->val);
			curr = curr->pNext;
		}
		else
		{
			if (res.pCurr->val == curr->val)
			{
				double tmp = res.pCurr->val.coeff + curr->val.coeff;
				if (tmp)
				{
					res.pCurr->val.coeff = tmp;
					res.GoNext();
				}
				else
					res.DelCurr();
				curr = curr->pNext;
			}
			else
			{
				res.GoNext();
			}
		}
	}
	return res;
}

TPolinom TPolinom:: operator*(const double val)
{
	if (val == 0.0)
	{
		TPolinom res;
		return res;
	}
	else
	{
		TPolinom res(*this);
		for (res.Reset(); !res.IsEnd(); res.GoNext())
			res.pCurr->val.coeff *= val;
		return res;
	}
}

TPolinom TPolinom::operator*(const TMonom& m)
{
	if (m.coeff == 0.0)
	{
		TPolinom res;
		return res;
	}
	else
	{
		TPolinom res(*this);
		for (res.Reset(); !res.IsEnd(); res.GoNext())
			res.pCurr->val = res.pCurr->val * m;
		return res;
	}
}

TPolinom& TPolinom:: operator=(const TPolinom& p)
{
	if (this != &p)
	{
		if (!p.size)
		{
			TList<TMonom>::~TList();
		}
		else
		{
			if (size < p.size)
			{
				int tmp = p.size - size;
				TLink<TMonom>* curr = pLast;
				for (int i = 0; i < tmp; i++)
				{
					TLink<TMonom>* new_elem = new TLink<TMonom>;
					curr->pNext = new_elem;
					curr = new_elem;
					curr->pNext = pStop;
				}
				pFirst = pHead->pNext;
				pLast = curr;
				curr = p.pFirst;
				for (Reset(); !IsEnd(); GoNext())
				{
					pCurr->val = curr->val;
					curr = curr->pNext;
				}
			}
			else
			{
				TLink<TMonom>* curr = p.pFirst;
				Reset();
				while (true)
				{
					pCurr->val = curr->val;
					curr = curr->pNext;
					if (curr == p.pStop)
						break;
					GoNext();
				}
				pLast = pCurr;
				GoNext();
				while (!IsEnd())
				{
					TLink<TMonom>* t = pCurr;
					GoNext();
					delete t;
				}
				pLast->pNext = pStop;
				pPrev = pLast;
			}
		}
	}
	size = p.size;
	pos = 0;
	return *this;
}