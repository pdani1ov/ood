#pragma once
#include <map>
#include <functional>
#include <set>

template <typename T>
class IObservable;

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, IObservable<T>& observable) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, unsigned priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
	virtual std::string GetName() = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, unsigned priority = 0) override
	{
		//сделать лучше, чем за линейное время
		for (auto it = m_observers.begin(); it != m_observers.end(); it++)
		{

			if (it->second == &observer)
			{
				return;
			}
		}

		m_observers.insert(std::make_pair(priority, &observer));
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		for (auto it = m_observers.rbegin(); it != m_observers.rend(); it++)
		{
			it->second->Update(data, *this);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		for (auto it = m_observers.begin(); it != m_observers.end(); it++)
		{
			if (it->second == &observer)
			{
				m_observers.erase(it);
				return;
			}
		}
	}

	virtual std::string GetName() = 0;
protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	std::multimap<unsigned, ObserverType*> m_observers;
};