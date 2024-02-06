#pragma once

#include<objbase.h>//интерфейсы, глобальные ключи
#include<iostream>
#include "Interface.h"

extern long g_lObjs;
extern long g_lLocks;

class Math :public IAdder, public IMultiplier
{
private:
	volatile ULONG m_lRef;
public:
	Math();
	~Math();

	STDMETHOD(QueryInterface(REFIID riid, void** ppv));
	STDMETHOD_(ULONG, AddRef(void));
	STDMETHOD_(ULONG, Release(void));

	STDMETHOD(Add(const double x, const double y, double& z));
	STDMETHOD(Sub(const double x, const double y, double& z));
	STDMETHOD(Mul(const double x, const double y, double& z));
	STDMETHOD(Div(const double x, const double y, double& z));

};