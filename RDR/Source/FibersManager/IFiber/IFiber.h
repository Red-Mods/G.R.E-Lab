#pragma once



class IFiber
{
	public:
		IFiber();
		~IFiber();

		virtual void Run() = 0;

		void SetName(const std::string& _Name);
		const std::string GetName() const;

		bool IsDirty() const;

		void Tick();

		void Wait(uint64_t _Duration);

	protected:
		virtual void Start() {}
		virtual void Update() {}

	private:
		std::string m_Name;
		void* m_CurrFiber;
		void* m_MainFiber;
		ULONGLONG m_WakeAt;

		bool m_IsDirty;

		void SetAsDirty();
};



struct ThisFiber
{
	static void Wait(uint64_t _Duration);

	static inline IFiber* s_Current = nullptr;
};



using AtomicFiber = std::atomic<std::shared_ptr<IFiber>>;