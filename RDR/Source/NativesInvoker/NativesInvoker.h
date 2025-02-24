#pragma once



namespace rage
{
	class NativeCallContext
	{
		public:
			template<typename T>
			T GetArgument(int _Index)
			{
				uintptr_t* arguments = (uintptr_t*)m_Args;

				return *(T*)&arguments[_Index];
			}

			template<typename T>
			void SetArgument(int _Index, T _Value)
			{
				uintptr_t* arguments = (uintptr_t*)m_Args;

				if (arguments)
				{
					*(T*)&arguments[_Index] = _Value;
				}
			}

			template<typename T>
			void SetResult(int _Index, T _Value)
			{
				uintptr_t* returnValues = (uintptr_t*)m_Return;

				if (returnValues)
				{
					*(T*)&returnValues[_Index] = _Value;
				}
			}

			template<typename T>
			T GetResult(int _Index)
			{
				uintptr_t* returnValues = (uintptr_t*)m_Return;

				return *(T*)&returnValues[_Index];
			}

			void* GetArgumentBuffer()
			{
				return m_Args;
			}

			uint32_t GetArgumentCount() const
			{
				return m_ArgsCount;
			}

			uint32_t GetDataCount() const
			{
				return m_DataCount;
			}

			void CopyReferencedParametersOut() const
			{
				for (uint32_t i = 0; i < m_DataCount; i++)
				{
					Vector3* outputVector = m_OutputVectors[i];
					Vector3 inVector = m_InputVectors[i];

					outputVector->X = inVector.X;
					outputVector->Y = inVector.Y;
					outputVector->Z = inVector.Z;
				}
			}

		protected:
			void* m_Return;
			uint32_t m_ArgsCount;
			void* m_Args;
			uint32_t m_DataCount;
			Vector3* m_OutputVectors[4];
			Vector3 m_InputVectors[4];
	};



	class NativeContext : public NativeCallContext
	{
		public:
			NativeContext()
			{
				m_Args = &m_TempStack;
				m_Return = &m_TempStack;

				m_ArgsCount = 0;
				m_DataCount = 0;

				memset(m_TempStack, 0, sizeof(m_TempStack));
			}

			template<typename T>
			void Push(T _Value)
			{
				if (sizeof(T) > sizeof(uintptr_t))
				{
					throw "Invalid size";
				}

				*reinterpret_cast<T*>(m_TempStack + sizeof(uintptr_t) * m_ArgsCount) = _Value;

				m_ArgsCount++;
			}

			template<typename T>
			T GetResult()
			{
				return *reinterpret_cast<T*>(m_TempStack);
			}

		private:
			uint8_t m_TempStack[32 * sizeof(uintptr_t)];
	};



	using f_NativeHandler = void(*)(NativeCallContext* _NativeContext);



	class NativesInvoker
	{
		public:
			using f_RegisterNative = void(*)(void* _Unused, uint32_t _Hash, f_NativeHandler _Handler);

			static void Initialize();

			static f_NativeHandler GetNativeHandler(unsigned int _Hash);

			static void RegisterNative(uint32_t _Hash, f_NativeHandler _Handler);

		private:
			static inline uintptr_t* s_NativeRegistration;

			static inline f_RegisterNative s_RegisterNative;

			static bool IsInitialized();
	};



	template<unsigned int _Hash, typename Result, typename... Args>
	inline Result Invoke(Args... _Args)
	{
		NativeContext context;
		(context.Push(_Args), ...);

		static auto handler = NativesInvoker::GetNativeHandler(_Hash);

		if (handler)
		{
			handler(&context);
		}

		context.CopyReferencedParametersOut();

		if constexpr (!std::is_void_v<Result>)
		{
			return context.GetResult<Result>();
		}
	}
}