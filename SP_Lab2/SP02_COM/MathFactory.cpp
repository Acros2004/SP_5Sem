#include "MathFactory.h"
#include "Math.h"

MathFactory::MathFactory() {
	m_lRef = 1;
}
MathFactory::~MathFactory() {};

HRESULT STDMETHODCALLTYPE MathFactory::QueryInterface(REFIID riid, void** ppv) {
	if (riid == IID_IUnknown)
		*ppv = (IUnknown*)this;
	else if (riid == IID_IClassFactory)
		*ppv = (IClassFactory*)this;
	else
		return E_NOINTERFACE;

	if (*ppv) {
		AddRef();
		return (S_OK);
	}
	else
		return (E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) MathFactory::AddRef() {
	InterlockedIncrement(&m_lRef);
	return m_lRef;
}

STDMETHODIMP_(ULONG) MathFactory::Release() {
	InterlockedDecrement(&m_lRef);
	if (m_lRef == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_lRef;
}

STDMETHODIMP MathFactory::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, void** ppvObj) {

	HRESULT hr = E_UNEXPECTED;

	Math* pMath = nullptr;

	if (pUnkOuter != NULL)//проверяем на аггрегацию 
		hr = CLASS_E_NOAGGREGATION;
	else if ((pMath = new Math()) == NULL)
		hr = E_OUTOFMEMORY;
	else {
		hr = pMath->QueryInterface(riid, ppvObj);
		pMath->Release();//мы его создаём и поэтому уменьшаем счётчик, так как там и так будет 1
	}

	if (FAILED(hr))
		delete pMath;

	return hr;
}

STDMETHODIMP  MathFactory::LockServer(BOOL fLock) {//активные блокировки
	if (fLock)
		InterlockedIncrement(&g_lLocks);
	else
		InterlockedDecrement(&g_lLocks);

	return S_OK;
}