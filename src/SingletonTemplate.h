#ifndef SINGLETONTEMPLATE
#define SINGLETONTEMPLATE

template <class T>
class SingletonTemplate
{

private:
	static T* m_obj;

protected:
	SingletonTemplate()
	{
		m_obj = 0;
	}

public:
	~SingletonTemplate()
	{
		delete m_obj;
	}

	static T* instance()
	{
		if (!m_obj) {
			m_obj = new T();
		}
		return m_obj;
	}
};

template <class T>
T* SingletonTemplate<T>::m_obj = 0;

#endif // SINGLETONTEMPLATE
