#include <pch.h>



void Fiber::SetJobFunction(const FiberHandler& _Handler)
{
	m_JobFunction = _Handler;
	m_IsJob = true;
}



void Fiber::Run()
{
	if (m_IsJob)
	{
		if (m_JobFunction)
			m_JobFunction();
	}
	else
	{
		Start();

		while (true)
		{
			Update();

			Wait(0);
		}
	}
}