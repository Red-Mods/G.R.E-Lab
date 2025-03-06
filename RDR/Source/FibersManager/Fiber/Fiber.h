#pragma once



using FiberHandler = std::function<void()>;



class Fiber : public IFiber
{
	public:
		Fiber() : IFiber(), m_IsJob(false) {}

		void SetJobFunction(const FiberHandler& _Handler);

		virtual void Run() override;

	private:
		FiberHandler m_JobFunction;
		bool m_IsJob;
};