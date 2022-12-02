#pragma once 

#include <msclr/marshal_cppstd.h>
#include <stdlib.h>
#include <string>

namespace fgengine {
	namespace utils
	{
		template<typename T>
		public ref class ManagedClass
		{
		protected:
			T* m_Instance;
		public:
			ManagedClass()
			{
				m_Instance = new T();
			}

			ManagedClass(T* instance)
				: m_Instance(instance)
			{
			}

			virtual ~ManagedClass()
			{
				if (m_Instance != nullptr)
				{
					delete m_Instance;
					m_Instance = nullptr;
				}
			}

			!ManagedClass()
			{
				if (m_Instance != nullptr)
				{
					delete m_Instance;
					m_Instance = nullptr;
				}
			}

			T* GetHandle()
			{
				return m_Instance;
			}
		}
	}
}