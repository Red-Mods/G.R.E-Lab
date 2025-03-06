#pragma once



enum RunFilter
{
	RunFilter_Main,

	RUN_FILTER_COUNT
};



class FibersPool : public Singleton<FibersPool>
{
	public:
		void DoRun(RunFilter _RunFilter);
		void DoGarbageCollection();

		void Add(RunFilter _RunFilter, const std::shared_ptr<IFiber>& _Fiber);

		template<typename T>
		void Add(RunFilter _RunFilter)
		{
			std::shared_ptr<T> fiber = std::make_shared<T>();

			std::string name = typeid(T).name();
			name = Utils::Replace(name, "class ", "");

			fiber->SetName(name);

			return Add(_RunFilter, fiber);
		}

		template<typename T>
		void AddJob(RunFilter _RunFilter, const FiberHandler& _Handler)
		{
			std::shared_ptr<T> fiber = std::make_shared<T>();

			fiber->SetName("TempJob" + std::to_string(m_LastUniqueId));
			fiber->SetJobFunction(_Handler);

			Add(_RunFilter, fiber);
		}

		void Remove(RunFilter _RunFilter, size_t _Index);
		void Clear();

		size_t Count() const;

	private:
		static const size_t POOL_SIZE = 64;

		AtomicFiber m_Fibers[RUN_FILTER_COUNT][POOL_SIZE];

		mutable size_t m_LastUniqueId = 0;
};