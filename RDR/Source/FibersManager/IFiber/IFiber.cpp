#include <pch.h>



IFiber::IFiber()
{
	m_Name = "UnnamedFiber";
	m_IsDirty = false;

	m_WakeAt = GetTickCount64();

	m_MainFiber = INVALID_HANDLE_VALUE;
	m_CurrFiber = CreateFiber(NULL, [](LPVOID _Param)
	{
		IFiber* self = (IFiber*)_Param;

		if (self)
		{
			__try
			{
				self->Run();
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				LOG_ERROR("Fatal error, exception execute handler !");
			}

			self->SetAsDirty();
		}

	}, this);
}



IFiber::~IFiber()
{
	DeleteFiber(m_CurrFiber);
}



void IFiber::Tick()
{
	m_MainFiber = IsThreadAFiber() ? GetCurrentFiber() : ConvertThreadToFiber(nullptr);

	if (GetTickCount64() < m_WakeAt)
	{
		return;
	}

	ThisFiber::s_Current = this;

	SwitchToFiber(m_CurrFiber);

	ThisFiber::s_Current = nullptr;
}



void IFiber::Wait(uint64_t _Duration)
{
	m_WakeAt = GetTickCount64() + _Duration;

	SwitchToFiber(m_MainFiber);
}



void IFiber::SetName(const std::string& _Name)
{
	m_Name = _Name;
}



const std::string IFiber::GetName() const
{
	return m_Name;
}



bool IFiber::IsDirty() const
{
	return m_IsDirty;
}



void IFiber::SetAsDirty()
{
	m_WakeAt = GetTickCount64() + LLONG_MAX;

	m_IsDirty = true;

	SwitchToFiber(m_MainFiber);
}



void ThisFiber::Wait(uint64_t _Duration)
{
	if (s_Current)
		s_Current->Wait(_Duration);
}