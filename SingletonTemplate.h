#ifndef SINGLETONTEMPLATE
#define SINGLETONTEMPLATE

template <class T>
class SingletonTemplate {

private:
	static T* m_obj;

protected:
	SingletonTemplate() {
		m_obj = NULL;
	}
public:

	~SingletonTemplate() {
		delete m_obj;
	}

	static T* instance() {
		if (m_obj == NULL) {
			m_obj = new T();
		}
		return m_obj;
	}
};

template <class T>
T* SingletonTemplate<T>::m_obj = NULL;

#endif // SINGLETONTEMPLATE

