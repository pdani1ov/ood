#pragma once
#include <functional>
#include <unordered_set>
#include <set>
#include <map>

template <typename T, typename P>
class IObservable;

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T, typename P>
class IObserver
{
public:
	virtual void Update(T const& data, IObservable<T, P>& observable, std::set<P> params) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T, typename P>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T, P>& observer, std::set<P> const& params, unsigned priority) = 0;
	virtual void NotifyObservers(std::set<P> const& params) = 0;
	virtual void RemoveObserver(IObserver<T, P>& observer, std::set<P> const& params) = 0;
	virtual std::string GetName() = 0;
};

// Реализация интерфейса IObservable
template <class T, class P>
class CObservable : public IObservable<T, P>
{
public:
	typedef IObserver<T, P> ObserverType;

	//Передавать по константной ссылке
	void RegisterObserver(ObserverType& observer, std::set<P> const& params, unsigned priority = 0) override
	{
		//сделать лучше, чем за линейное время

		if (m_observers.find(&observer) == m_observers.end()) {
			auto newInfo = std::make_shared<ObserverInfo>(&observer, params, priority);
			m_observers.insert(std::make_pair(&observer, newInfo));
			m_sortedObservers.insert(*newInfo);
		}
		else
		{
			std::cout << "This observer already exist" << std::endl;
		}
	}

	void NotifyObservers(std::set<P> const& params) override
	{
		T data = GetChangedData();
		for (auto it = m_sortedObservers.begin(); it != m_sortedObservers.end(); it++)
		{
			auto info = *it;
			std::set<P> commonParams = GetUpdatedObserverParams(params, it->params);
			it->observer->Update(data, *this, commonParams);
		}
	}

	//Указать события, от которых я хочу отписать и сделать быстрее, чем за линейное время
	void RemoveObserver(ObserverType& observer, std::set<P> const& params) override
	{
		if (m_observers.contains(&observer))
		{	
			auto info = m_observers[&observer];
			std::set<P> newParams = GetNonRemovedParams(params, info->params);

			m_observers.erase(&observer);
			m_sortedObservers.erase(*info);
			
			if (newParams.size() != 0) {
				auto newInfo = std::make_shared<ObserverInfo>(&observer, newParams, info->priority);
				m_observers.insert(std::make_pair(&observer, newInfo));
				m_sortedObservers.insert(*newInfo);
			}
		}
	}

	virtual std::string GetName() = 0;
protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:

	struct ObserverInfo
	{
		ObserverInfo(ObserverType* newObserver, std::set<P> const& newParams, unsigned const newPriority)
			:observer(newObserver),
			params(newParams),
			priority(newPriority)
		{}

		ObserverType* observer;
		std::set<P> params;
		unsigned priority;
	};

	struct Compare {
		bool operator()(ObserverInfo const& info1, ObserverInfo const& info2) const {
			return info1.priority > info2.priority;
		}
	};

	std::set<P> GetUpdatedObserverParams(std::set<P> const& updatedParams, std::set<P> const& observerParams)
	{
		std::set<P> commonParams;

		for (auto& parameter : updatedParams)
		{
			if (observerParams.contains(parameter))
			{
				commonParams.insert(parameter);
			}
		}

		return commonParams;
	};

	std::set<P> GetNonRemovedParams(std::set<P> const& removedParams, std::set<P> const& observerParams)
	{
		std::set<P> uncommonParams;

		for (auto& parameter : observerParams)
		{
			if (!removedParams.contains(parameter))
			{
				uncommonParams.insert(parameter);
			}
		}

		return uncommonParams;
	};

	std::multiset<ObserverInfo, Compare> m_sortedObservers;
	std::map<ObserverType*, std::shared_ptr<ObserverInfo>> m_observers;
};